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
from sca.parsers import spd

logging.basicConfig(level=logging.INFO)
log = logging.getLogger(__name__)

def convert(ossie_spd):
    xml = spd.parseString('<softpkg />')

    # SoftPkg Attributes id, name, type, version (optional)
    xml.set_id(ossie_spd.get_id())
    xml.set_name(ossie_spd.get_name())
    xml.set_type(ossie_spd.get_type())
    if ossie_spd.get_version():
        xml.set_version(ossie_spd.get_version())

    # [0, 1] Title, description, propertyfile, descriptor
    if ossie_spd.get_title():
        xml.set_title(spd.title(ossie_spd.get_title()))
    if ossie_spd.get_description():
        xml.set_description( _sca_description(ossie_spd.get_description()) )
    if ossie_spd.get_propertyfile():
        xml.set_propertyfile( _sca_propertyfile(ossie_spd.get_propertyfile()) )
    if ossie_spd.get_descriptor():
        ossie_desc = ossie_spd.get_descriptor()
        xml.set_descriptor(spd.descriptor(
            name      = ossie_desc.get_name(),
            localfile = _sca_localfile(ossie_desc.get_localfile())
        ))

    # [0, inf] Author(s)
    for author in ossie_spd.get_author():
        xml.add_author(_sca_author(author))

    # Implementation(s)
    for impl in ossie_spd.get_implementation():
        xml.add_implementation(_sca_implementation(impl))

    # Usesdevice(s)
    if ossie_spd.get_usesdevice():
        xml.add_usesdevice(_sca_usesdevice(ossie_spd.get_usesdevice()))

    return xml

# Internal functions
def _sca_propertyfile(ossie_pf):
    return spd.propertyfile(
        type_     = ossie_pf.get_type(),
        localfile = spd.localfile(
            name  = ossie_pf.get_localfile().get_name()
        ))

def _sca_description(ossie_description):
    if ossie_description:
        return spd.description(ossie_description)
    else:
        return None

def _sca_implementation(ossie_implementation):
    sca_impl = spd.implementation(
        _id           = ossie_implementation.get_id(),
        aepcompliance = ossie_implementation.get_aepcompliance(),
    )
    if ossie_implementation.get_description():
        sca_impl.set_description(
            _sca_description(ossie_implementation.get_description())
        )
    if ossie_implementation.get_propertyfile():
        sca_impl.set_propertyfile(
            _sca_propertyfile(ossie_implementation.get_propertyfile())
        )
    if ossie_implementation.get_compiler():
        sca_impl.set_compiler(
            _sca_compiler(ossie_implementation.get_compiler())
        )
    if ossie_implementation.get_programminglanguage():
        sca_impl.set_programminglanguage(
            _sca_programminglanguage(ossie_implementation.get_programminglanguage())
        )
    sca_impl.set_code(_sca_code(ossie_implementation.get_code()))
    return sca_impl

def _sca_author(ossie_author):
    sca_author = spd.author()
    for name in ossie_author.get_name():
        sca_author.add_name(spd.name(name))
    if ossie_author.get_company():
        sca_author.set_company(spd.company(ossie_author.get_company()))
    if ossie_author.get_webpage():
        sca_author.set_webpage(spd.webpage(ossie_author.get_webpage()))
    return sca_author

def _sca_localfile(ossie_localfile):
    return spd.localfile(name = ossie_localfile.get_name())

def _sca_propertyref(ossie_propertyref):
    return spd.propertyref(
        refid = ossie_propertyref.get_refid(),
        value = ossie_propertyref.get_value())

def _sca_usesdevice(ossie_usesdevice):
    sca_usesdevice = spd.usesdevice(
        _id = ossie_usesdevice.get_id(),
        type_ = ossie_usesdevice.get_type())
    # [0, N] propertyref
    for ref in ossie_usesdevice.get_propertyref():
        sca_usesdevice.add_propertyref( _sca_propertyref(ref) )
    return sca_usesdevice

def _sca_implref(ossie_implref):
    return spd.implref(repid = ossie_implref.get_repid())

def _sca_softpkgref(ossie_softpkgref):
    localfile = _sca_localfile(ossie_softpkgref.get_localfile())

    # [0, ?]
    implref = []
    for impl in ossie_softpkgref.get_implref():
        implref.append( _sca_implref(impl) )

    return spd.softpkgref(localfile = localfile, implref = implref)

def _sca_compiler(ossie_compiler):
    c = spd.compiler(name = ossie_compiler.get_name())
    if ossie_compiler.get_version():
        c.set_version(ossie_compiler.get_version())
    return c

def _sca_programminglanguage(ossie_programminglanguage):
    p = spd.programminglanguage(name = ossie_programminglanguage.get_name())
    if ossie_programminglanguage.get_version():
        p.set_version(ossie_programminglanguage.get_version())
    return p

def _sca_humanlanguage(ossie_humanlanguage):
    h = spd.humanlanguage(name = ossie_humanlanguage.get_name())
    if ossie_humanlanguage.get_version():
        h.set_version(ossie_humanlanguage.get_version())
    return h

def _sca_code(ossie_code):
    sca_code = spd.code(type_ = ossie_code.get_type())
    sca_code.set_localfile(_sca_localfile(ossie_code.get_localfile()))

    # Optional elements
    ep = ossie_code.get_entrypoint()
    s  = ossie_code.get_stacksize()
    p  = ossie_code.get_priority()
    if ep:
        sca_code.set_entrypoint(spd.entrypoint(ep))
    if s:
        sca_code.set_stacksize(s)
    if p:
        sca_code.set_priority(p)
    return sca_code