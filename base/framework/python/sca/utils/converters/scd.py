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
import re
from sca.parsers import scd

logging.basicConfig(level=logging.INFO)
log = logging.getLogger(__name__)

class UnknownComponentType(Exception):
    pass

class UnsupportedInterface(Exception):
    pass

def convert(ossie_scd):
    '''
    Converts the 'ossie_scd' (ossie.parsers.scd.parse() output) to an
    SCA 4.x compliant SCD (sca.parsers.scd.parse()).
    '''
    # The way this routine will work is to infer from the componenttype what
    # interfaces to add, and therefore what componentfeatures to describe.
    # Then the remaining interfaces are read and added, if missing.
    # Interfaces like Resource are deprecated, and dropped.
    xml = scd.parseString('<softwarecomponent />')

    # Determine what is being built and setup base interfaces
    componenttype = ossie_scd.get_componenttype()
    interface_map = None
    if componenttype   == 'resource':         # REDHAWK Component
        _set_component_repid_type(xml, _SCA_REPID_RESOURCE_COMPONENT, componenttype)
        interface_map = _make_repid_interface_map(ossie_scd, _SCA_RESOURCE_COMPONENT)

    elif componenttype == 'device':           # REDHAWK Device
        _set_component_repid_type(xml, _SCA_REPID_DEVICE_COMPONENT, componenttype)
        interface_map = _make_repid_interface_map(ossie_scd, _SCA_DEVICE_COMPONENT)

    elif componenttype == 'executabledevice': # REDHAWK Executable Device
        _set_component_repid_type(xml, _SCA_REPID_EXECUTABLE_DEVICE_COMPONENT, componenttype)
        interface_map = _make_repid_interface_map(ossie_scd, _SCA_EXECUTABLE_DEVICE_COMPONENT)

    else:
        raise UnknownComponentType('REDHAWK Component type is unknown in SCA 4: %s' % componenttype)

    # Populate interfaces and componentfeatures lists, skipping those that are ports
    # which will be added later.
    interfaces = scd.interfaces()
    features = scd.componentfeatures()
    for repid, interface in interface_map.iteritems():
        interfaces.add_interface(interface)

        if not _filter_port_repid(repid):
            features.add_supportsinterface(
                _sca_supportsinterface(repid)
                )

    # componentfeatures.ports
    ports = scd.ports()
    features.set_ports(ports)
    ossie_ports = ossie_scd.get_componentfeatures().get_ports()
    for p in ossie_ports.get_provides():
        if not _filter_repid(p.get_repid()):
            ports.add_provides(scd.provides(
                repid        = p.get_repid(),
                providesname = p.get_providesname(),
                ))
        else:
            log.warning('Dropping unsupported provides port: %s' % p.get_providesname())
    for p in ossie_ports.get_uses():
        if not _filter_repid(p.get_repid()):
            ports.add_uses(scd.uses(
                repid      = p.get_repid(),
                usesname   = p.get_usesname(),
                ))
        else:
            log.warning('Dropping unsupported uses port: %s' % p.get_usesname())

    # Set the interfaces and componentfeatures, return xml.
    xml.set_interfaces(interfaces)
    xml.set_componentfeatures(features)
    return xml

# Internal functions

def _sca_interface(repid, inherited_repids=[]):
    '''
    Returns an scd.interface object configured with the repid and inherited repids
    '''
    interface = scd.interface(repid=repid, name=_name_from(repid))
    for irid in inherited_repids:
        interface.add_inheritsinterface(scd.inheritsinterface(repid=irid))
    return interface

def _from_ossie_interface(ossie_interface):
    '''
    Converts an ossie.parsers.scd.interface to sca.parsers.scd.interface.
    If an incompatible interface is found, it raises an exception.
    '''
    repid = ossie_interface.get_repid()
    if _filter_repid(repid):
        raise UnsupportedInterface('Unsupported OSSIE interface: %s' % repid)

    # Iterate over inherited to verify they're valid.
    inherited_repids = []
    for inherited in ossie_interface.get_inheritsinterface():
        repid = inherited.get_repid()
        if not _filter_repid(repid):
            inherited_repids.append(repid)
        else:
            raise UnsupportedInterface('Unsupported inherited OSSIE interface: %s' % repid)

    sca_interface = _sca_interface(
        repid            = repid,
        inherited_repids = inherited_repids
        )

    return sca_interface

def _sca_supportsinterface(repid, supportsname=None):
    '''
    Returns an scd.supportsinterface configured with the repid and (optional)
    alternative supportsname.  See _supportsname_from for if that is necessary
    in your case.
    '''
    return scd.supportsinterface(
        repid        = repid,
        supportsname = supportsname or _supportsname_from(repid)
        )

def _name_from(repid):
    '''
    Pulls the 'name' from a given repid:
       IDL:CF/ResourceComponent:1.0                      -> ResourceComponent
       IDL:omg.org/CosEventChannelAdmin/EventChannel:1.0 -> EventChannel
    '''
    NAME = r'(IDL:)(.+?/)+(.+?)(:.+$)'
    match = re.match(NAME, repid)
    return match.group(3)

def _supportsname_from(repid):
    '''
    Pulls the expected 'sourcename' from a given repid
    '''
    return _name_from(repid)

def _componenttype_from(componenttype=None, repid=None):
    '''
    Pulls the expected 'componenttype' from a given repid
    '''
    val = None
    if componenttype:
        val = componenttype
    elif repid:
        val = _name_from(repid).lower()
    return scd.componenttype(valueOf_=val)

def _filter_repid(repid):
    '''
    Returns 'true' if the repid should be dropped.  'false' otherwise.
    '''
    FILTERED = [
        'IDL:CF/Logging:1.0',
        'IDL:CF/LogEventConsumer:1.0',
        'IDL:CF/LogConfiguration:1.0',
        'IDL:ExtendedEvent/MessageEvent:1.0',
        'IDL:omg.org/CosEventChannelAdmin/EventChannel:1.0',
        'IDL:CF/PropertyEmitter:1.0',
    ]
    return repid in FILTERED

def _filter_port_repid(repid):
    '''
    Returns 'true' if the repid should be ignored as a ports list,
    'false' otherwise.  Also includes types listed in _filter_repid.
    '''
    result = _filter_repid(repid)
    result = result or repid.startswith('IDL:BULKIO/')
    result = result or repid.startswith('IDL:FRONTEND/')
    return result

def _set_component_repid_type(xml, repid, type_=None):
    '''
    Configures the componentrepid repid and componenttype valueOf_ to repid
    '''
    xml.set_componenttype(_componenttype_from(componenttype=type_, repid=repid))
    xml.set_componentrepid(scd.componentrepid(repid))

def _make_repid_interface_map(ossie_scd, sca_list):
    '''
    Creates a map of repid to sca.interface instance beginning with
    the sca_list and adding any from ossie_scd that were missed.
    '''
    combined = { i.get_repid(): i for i in sca_list }
    interfaces = ossie_scd.get_interfaces()
    if interfaces:
        for i in interfaces.get_interface():
            if not i.get_repid() in combined:
                try:
                    combined[i.get_repid()] = _from_ossie_interface(i)
                except Exception as e:
                    log.warning('Dropping interface because: %s' % e.message)
    return combined


# constants IDL Interface REPIDs and interface objects

_SCA_REPID_TESTABLE_INTERFACE = 'IDL:CF/TestableInterface:1.0'
_SCA_TESTABLE_INTERFACE = _sca_interface(_SCA_REPID_TESTABLE_INTERFACE)

_SCA_REPID_PROPERTY_SET = 'IDL:CF/PropertySet:1.0'
_SCA_PROPERTY_SET = _sca_interface(_SCA_REPID_PROPERTY_SET)

_SCA_REPID_PORT_ACCESSOR = 'IDL:CF/PortAccessor:1.0'
_SCA_PORT_ACCESSOR = _sca_interface(_SCA_REPID_PORT_ACCESSOR)

_SCA_REPID_LIFE_CYCLE = 'IDL:CF/LifeCycle:1.0'
_SCA_LIFE_CYCLE = _sca_interface(_SCA_REPID_LIFE_CYCLE)

_SCA_REPID_CONTROLLABLE_INTERFACE = 'IDL:CF/ControllableInterface:1.0'
_SCA_CONTROLLABLE_INTERFACE = _sca_interface(_SCA_REPID_CONTROLLABLE_INTERFACE)

_SCA_REPID_DEVICE_ATTRIBUTES = 'IDL:CF/DeviceAttributes:1.0'
_SCA_DEVICE_ATTRIBUTES = _sca_interface(_SCA_REPID_DEVICE_ATTRIBUTES)

_SCA_REPID_ADMINISTRATABLE_INTERFACE = 'IDL:CF/AdministratableInterface:1.0'
_SCA_ADMINISTRATABLE_INTERFACE = _sca_interface(_SCA_REPID_ADMINISTRATABLE_INTERFACE)

_SCA_REPID_CAPACITY_MANAGEMENT = 'IDL:CF/CapacityManagement:1.0'
_SCA_CAPACITY_MANAGEMENT = _sca_interface(_SCA_REPID_CAPACITY_MANAGEMENT)

_SCA_REPID_AGGREGATE_DEVICE_ATTRIBUTES = 'IDL:CF/AggregateDeviceAttributes:1.0'
_SCA_AGGREGATE_DEVICE_ATTRIBUTES = _sca_interface(_SCA_REPID_AGGREGATE_DEVICE_ATTRIBUTES)

_SCA_REPID_EXECUTABLE_INTERFACE = 'IDL:CF/ExecutableInterface:1.0'
_SCA_EXECUTABLE_INTERFACE = _sca_interface(_SCA_REPID_EXECUTABLE_INTERFACE)

_SCA_REPID_LOADABLE_INTERFACE = 'IDL:CF/LoadableInterface:1.0'
_SCA_LOADABLE_INTERFACE = _sca_interface(_SCA_REPID_LOADABLE_INTERFACE)


# Top-level interface lists for ResourceComponent, DeviceComponent, and ExecutableDeviceComponent

_SCA_REPID_RESOURCE_COMPONENT = 'IDL:CF/ResourceComponent:1.0'
_SCA_RESOURCE_COMPONENT = [
    _sca_interface(
        repid            = _SCA_REPID_RESOURCE_COMPONENT,
        inherited_repids = [
            _SCA_REPID_TESTABLE_INTERFACE,
            _SCA_REPID_PROPERTY_SET,
            _SCA_REPID_PORT_ACCESSOR,
            _SCA_REPID_LIFE_CYCLE,
            _SCA_REPID_CONTROLLABLE_INTERFACE
        ]),
    _SCA_TESTABLE_INTERFACE,
    _SCA_PROPERTY_SET,
    _SCA_PORT_ACCESSOR,
    _SCA_LIFE_CYCLE,
    _SCA_CONTROLLABLE_INTERFACE
]

_SCA_REPID_DEVICE_COMPONENT = 'IDL:CF/DeviceComponent:1.0'
_SCA_DEVICE_COMPONENT = [
    _sca_interface(
        repid            = _SCA_REPID_DEVICE_COMPONENT,
        inherited_repids = [
            _SCA_REPID_DEVICE_ATTRIBUTES,
            _SCA_REPID_ADMINISTRATABLE_INTERFACE,
            _SCA_REPID_CAPACITY_MANAGEMENT,
            _SCA_REPID_AGGREGATE_DEVICE_ATTRIBUTES,
            _SCA_REPID_TESTABLE_INTERFACE,
            _SCA_REPID_PROPERTY_SET,
            _SCA_REPID_PORT_ACCESSOR,
            _SCA_REPID_LIFE_CYCLE,
            _SCA_REPID_CONTROLLABLE_INTERFACE,
        ]),
    _SCA_DEVICE_ATTRIBUTES,
    _SCA_ADMINISTRATABLE_INTERFACE,
    _SCA_CAPACITY_MANAGEMENT,
    _SCA_AGGREGATE_DEVICE_ATTRIBUTES,
    _SCA_TESTABLE_INTERFACE,
    _SCA_PROPERTY_SET,
    _SCA_PORT_ACCESSOR,
    _SCA_LIFE_CYCLE,
    _SCA_CONTROLLABLE_INTERFACE
]

_SCA_REPID_EXECUTABLE_DEVICE_COMPONENT = 'IDL:CF/ExecutableDeviceComponent:1.0'
_SCA_EXECUTABLE_DEVICE_COMPONENT = [
    _sca_interface(
        repid            = _SCA_REPID_EXECUTABLE_DEVICE_COMPONENT,
        inherited_repids = [
            _SCA_REPID_EXECUTABLE_INTERFACE,
            _SCA_REPID_LOADABLE_INTERFACE,
            _SCA_REPID_DEVICE_COMPONENT,
        ]),
    _SCA_EXECUTABLE_INTERFACE,
    _SCA_LOADABLE_INTERFACE,
    _SCA_DEVICE_COMPONENT
]
