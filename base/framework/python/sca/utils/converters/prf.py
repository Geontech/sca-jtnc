# This file is protected by Copyright. Please refer to the COPYRIGHT file
# distributed with this source distribution.
#
# This file is part of SCA-JTNC core.
#
# SCA-JTNC core is free software: you can redistribute it and/or modify it under
# the terms of the GNU Lesser General Public License as published by the Free
# Software Foundation, either version 3 of the License, or (at your option) any
# later version.
#
# SCA-JTNC core is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
# details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see http://www.gnu.org/licenses/.
#
import logging
from sca.parsers import prf

logging.basicConfig(level=logging.INFO)
log = logging.getLogger(__name__)

class BadKindConversion(Exception):
    pass

class UnsupportedComplexConversion(Exception):
    pass

class UnsupportedStructConversion(Exception):
    pass

def convert(ossie_prf):
    '''
    Imports 'ossie_prf' (a REDHAWK ossie.parsers.prf.parse() object) into an
    SCA-compliant PRF format and returns it (the output of sca.parsers.prf.parse()).
    '''
    def do_try(fn, xml, p):
        try:
            fn(xml, p)
        except Exception as e:
            log.warning('Dropping property because: %s' % e.message)

    xml = prf.parseString('<properties/>')
    [do_try(_add_rh_simple, xml, p)         for p in ossie_prf.get_simple()]
    [do_try(_add_rh_simplesequence, xml, p) for p in ossie_prf.get_simplesequence()]
    [do_try(_add_rh_struct, xml, p)         for p in ossie_prf.get_struct()]
    [do_try(_add_rh_structsequence, xml, p) for p in ossie_prf.get_structsequence()]
    return xml

# Internal functions below.

def _resolve_kindtype(kindtype='configure', commandline='false'):
    '''
    Kind Conversions
        allocation         -> allocation
        configure          -> configure
        property - cmdline ---^
        property + cmdline ---v
        execparam          -> execparam
    
    (un)Kind Conversions, which result in an exception
        message            -> DROP

    Conversions that don't exist at all.
        N/A                -> factory
        N/A                -> test
    '''
    ALLOCATION_KIND = 'allocation'
    CONFIGURE_KIND = 'configure'
    EXECPARAM_KIND = 'execparam'
    PROPERTY_KIND = 'property'
    MAP_FALSE = {
        ALLOCATION_KIND : ALLOCATION_KIND,
        CONFIGURE_KIND  : CONFIGURE_KIND,
        EXECPARAM_KIND  : EXECPARAM_KIND,
    }
    MAP_TRUE = MAP_FALSE.copy()

    MAP_TRUE[PROPERTY_KIND]  = EXECPARAM_KIND
    MAP_FALSE[PROPERTY_KIND] = CONFIGURE_KIND
    try:
        if 'true' == commandline:
            return MAP_TRUE[kindtype]
        elif 'false' == commandline:
            return MAP_FALSE[kindtype]
        else:
            raise BadKindConversion(
                'Valid values of "commandline" are "true" and "false", strings.'
            )
    except:
        raise BadKindConversion(
            'Non-translatable kindtype: %s' % kindtype
            )

def _map_kinds(rh_kinds, commandline='false'):
    '''
    Returns a list of SCA Kinds that map from REDHAWK kinds
    rh_kinds - list of REDHAWK kinds (usually prfobj.get_kind())
    commandline  - if the parent property has this member, pass the value
    '''
    out_kinds = []
    for k in rh_kinds:
        out_kinds.append(
            prf.kind(_resolve_kindtype(k.kindtype, commandline))
            )
    return None if not len(out_kinds) else out_kinds

def _map_configurationkind(rh_configurationkinds):
    '''
    Returns a single configurationkind instance for the first
    configuration kind in rh_configurationkinds (get_configurationkind
    returns a list).  This function will warn if multiple kinds are listed
    '''
    if not rh_configurationkinds:
        return None
    
    if len(rh_configurationkinds) > 1:
        log.warning('Using first configurationkind; multiple are listed for property')
    
    return prf.configurationkind(_resolve_kindtype(rh_configurationkinds[0].kindtype))

def _to_sca_enumerations(rh_enumerations):
    '''
    Returns an SCA 4 enumerations object using the REDHAWK enumerations data
    May return None if no enumerations were provided.
    '''
    sca_enums = None
    if rh_enumerations:
        sca_enums = prf.enumerations()
        for e in rh_enumerations.get_enumeration():
            sca_enums.add_enumeration(prf.enumeration(
                label = e.get_label(),
                value = e.get_value()
            ))
    return sca_enums

def _to_sca_action(rh_action):
    '''
    Returns an SCA 4 action object using the REDHAWK action data
    '''
    return prf.action(type_=rh_action.get_type())

def _to_sca_description(rh_description):
    '''
    Returns an SCA 4 description object using the REDHAWK description data
    '''
    if rh_description:
        return prf.description(valueOf_=rh_description)
    else:
        return None

def _to_sca_value(rh_value):
    '''
    Returns an SCA 4 value object using the REDHAWK value data
    '''
    return prf.value(valueOf_=rh_value)

def _to_sca_complex_value(str_value='0 + j0'):
    '''
    Returns a tuple of (real, imag) prf.value objects
    '''
    value_cplx = complex(str_value.strip().replace('j','') + 'j')
    return (
        prf.value(value_cplx.real),
        prf.value(value_cplx.imag)
        )

def _to_sca_struct(rh_struct):
    '''
    Creates an SCA 4.x representation of a REDHAWK struct.
    NOTE: SCA 4.x structs cannot have simplesequence members.
    NOTE: SCA 4.x structs cannot have simple complex members, since these
            are represented as structs, and structs cannot contain other
            structs in either framework at this time (SCA 4.x or REDHAWK 2.2)
    '''
    if rh_struct.get_simplesequence():
        raise UnsupportedStructConversion(
            'SCA structs cannot contain simplesequences. (ID: %s)' % rh_struct.get_id()
        )
    
    configurationkind = _map_configurationkind(rh_struct.get_configurationkind())
    sca_struct = prf.struct(
        _id               = rh_struct.get_id(),
        mode              = rh_struct.get_mode(),
        name              = rh_struct.get_name(),
        description       = _to_sca_description(rh_struct.get_description()),
        configurationkind = configurationkind)

    for simple in rh_struct.get_simple():
        if simple.get_complex() == 'true':
            raise UnsupportedStructConversion(
                'SCA structs cannot contain complex simples (becoming structs with struct members, ID: %s)' % rh_struct.get_id()
                )
        sca_struct.add_simple(prf.simple(
            _id          = simple.get_id(),
            type_        = simple.get_type(),
            name         = simple.get_name(),
            description  = _to_sca_description(simple.get_description()),
            value        = prf.value(simple.get_value()),
            units        = simple.get_units(),
            _range       = simple.get_range(),
            enumerations = _to_sca_enumerations(simple.get_enumerations())
            ))
    return sca_struct

def _sca_complex_struct(_id, name=None, type_=None, str_value=None):
    '''
    Creates an SCA 4.x struct with two simples:
        _id::real w/ 'real' portion of str_value
        _id::imag w/ 'imaginary' portion of str_value
    
    str_value should be a string, like '3 + j4'
    '''
    sca_struct = prf.struct(
        _id     = _id,
        name    = name or _id,
        type_   = type_
    )
    rvalue = ivalue = None
    if str_value:
        (rvalue, ivalue) = _to_sca_complex_value(str_value)

    real_id = _id + '::real'
    sca_struct.add_simple(prf.simple(
        _id   = real_id,
        name  = real_id,
        type_ = type_,
        value = rvalue
        ))
    imag_id = _id + '::imag'
    sca_struct.add_simple(prf.simple(
        _id   = imag_id,
        name  = imag_id,
        type_ = type_,
        value = ivalue
        ))
    return sca_struct

def _add_rh_simple(xml, rh_simple):
    '''
    Adds an SCA 4.x simple from a REDHAWK simple
    '''
    if rh_simple.get_optional() == 'true':
        log.warning(
            'Ignoring "optional"; it has no translation to SCA 4.x (ID: %s)' % rh_simple.get_id()
            )

    kinds = _map_kinds(rh_simple.get_kind(), rh_simple.get_commandline())
    if rh_simple.get_complex() == 'false':
        sca_simple = prf.simple(
            _id          = rh_simple.get_id(),
            type_        = rh_simple.get_type(),
            name         = rh_simple.get_name(),
            mode         = rh_simple.get_mode(),
            description  = _to_sca_description(rh_simple.get_description()),
            value        = _to_sca_value(rh_simple.get_value()),
            units        = rh_simple.get_units(),
            _range       = rh_simple.get_range(),
            enumerations = _to_sca_enumerations(rh_simple.get_enumerations()),
            kind         = kinds,
            action       = _to_sca_action(rh_simple.get_action())
        )
        xml.add_simple(sca_simple)
    else:
        if rh_simple.get_commandline() == 'true':
            raise UnsupportedComplexConversion(
                'Conversion from complex simple becomes a struct, which cannot be an execparam (ID: %s)' % rh_simple.get_id()
            )
        log.warning('Converting a REDHAWK Complex Simple into a struct (ID: %s)' % rh_simple.get_id())
        sca_struct = _sca_complex_struct(
            _id       = rh_simple.get_id(),
            type_     = rh_simple.get_type(),
            str_value = rh_simple.get_value()
            )
        sca_struct.set_mode(rh_simple.get_mode())
        sca_struct.set_description(_to_sca_description(rh_simple.get_description()))
        xml.add_struct(sca_struct)

def _add_rh_simplesequence(xml, rh_simpleseq):
    '''
    Adds SCA 4.x representation of a REDHAWK Simple Sequence
    NOTE: Complex simple sequences become struct sequences
    NOTE: "optional" is not recognized for SCA 4.x simple sequences
    '''
    if rh_simpleseq.get_optional() == 'true':
        log.warning('Ignoring "optional"; it has no translation to SCA 4.x (ID: %s)' % rh_simpleseq.get_id())

    if rh_simpleseq.get_complex() == 'false':
        kinds = _map_kinds(rh_simpleseq.get_kind())
        values = prf.values()
        for v in rh_simpleseq.get_values().get_value():
            values.add_value(_to_sca_value(v))

        sca_simpleseq = prf.simplesequence(
            _id          = rh_simpleseq.get_id(),
            type_        = rh_simpleseq.get_type(),
            name         = rh_simpleseq.get_name(),
            mode         = rh_simpleseq.get_mode(),
            description  = _to_sca_description(rh_simpleseq.get_description()),
            values       = values,
            units        = rh_simpleseq.get_units(),
            _range       = rh_simpleseq.get_range(),
            kind         = kinds,
            action       = _to_sca_action(rh_simpleseq.get_action())
            )
        xml.add_simplesequence(sca_simpleseq)
    else:
        # Create a struct and struct sequence filled with struct values.
        log.warning('Converting a REDHAWK complex simple sequence into a struct sequence (ID: %s)' % rh_simpleseq.get_id())
        configurationkind = _map_configurationkind(rh_simpleseq.get_kind())
        structseq_value_id = rh_simpleseq.get_id() + '::value'
        real_value_id = structseq_value_id + '::real'
        imag_value_id = structseq_value_id + '::imag'
        xml.add_struct(
            _sca_complex_struct(
                _id   = structseq_value_id,
                type_ = rh_simpleseq.get_type(),
            ))
        sca_structseq = prf.structsequence(
            _id               = rh_simpleseq.get_id(),
            structrefid       = structseq_value_id,
            name              = rh_simpleseq.get_name(),
            mode              = rh_simpleseq.get_mode(),
            description       = _to_sca_description(rh_simpleseq.get_description()),
            configurationkind = configurationkind
        )
        for v in rh_simpleseq.get_values().get_value():
            # Returns "value" objects and simpleref needs the stored value.
            (r, i) = _to_sca_complex_value(v)
            r_ref = prf.simpleref(real_value_id, r.get_valueOf_())
            i_ref = prf.simpleref(imag_value_id, i.get_valueOf_())
            sca_structseq.add_structvalue(
                prf.structvalue([r_ref, i_ref])
            )
        xml.add_structsequence(sca_structseq)

def _add_rh_struct(xml, rh_struct):
    '''
    Adds an SCA 4.x representation of a REDHAWK struct.
    NOTE: See framework limitations of _to_sca_struct.
    '''
    xml.add_struct(_to_sca_struct(rh_struct))

def _add_rh_structsequence(xml, rh_structseq):
    '''
    Adds SCA 4.x representation of a REDHAWK struct sequence.
    NOTE: SCA 4.x struct sequences can only contain compliant struct
            definitions.  See the limitations of _add_rh_struct.
    '''
    configurationkind = _map_configurationkind(rh_structseq.get_configurationkind())
    structseq_ref = _to_sca_struct(rh_structseq.get_struct())
    sca_structseq = prf.structsequence(
            _id               = rh_structseq.get_id(),
            structrefid       = structseq_ref.get_id(),
            name              = rh_structseq.get_name(),
            mode              = rh_structseq.get_mode(),
            description       = _to_sca_description(rh_structseq.get_description()),
            configurationkind = configurationkind
    )
    for sv in rh_structseq.get_structvalue():
        if sv.get_simplesequenceref():
            raise UnsupportedStructConversion(
                'Struct sequence cannot contain structs that have complex simples (ID: %s)' % rh_structseq.get_id()
                )
        sca_sv = prf.structvalue()
        for ref in sv.get_simpleref():
            sca_sv.add_simpleref(
                prf.simpleref(
                    refid=ref.get_refid(),
                    value=ref.get_value()
                    )
                )
        sca_structseq.add_structvalue(sca_sv)
    xml.add_struct(structseq_ref)
    xml.add_structsequence(sca_structseq)
