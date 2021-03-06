/*
 * This file is protected by Copyright. Please refer to the COPYRIGHT file 
 * distributed with this source distribution.
 * 
 * This file is part of REDHAWK core.
 * 
 * REDHAWK core is free software: you can redistribute it and/or modify it 
 * under the terms of the GNU Lesser General Public License as published by the 
 * Free Software Foundation, either version 3 of the License, or (at your 
 * option) any later version.
 * 
 * REDHAWK core is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License 
 * for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License 
 * along with this program.  If not, see http://www.gnu.org/licenses/.
 */

#include <iostream>
#include <string.h>
#include <signal.h>
#include <sys/signalfd.h>

#include "sca/AggregateDeviceComponent.h"

AggregateExecutableDeviceComponent::AggregateExecutableDeviceComponent (char* componentRegistry_ior, char* _id, char* _label, char* sftwrPrfl) : DeviceComponent(componentRegistry_ior, _id, _label, sftwrPrfl) {
    //initializeCommonAttributes(_id);

    _devices = new CF::ObjectSequence();
}

AggregateExecutableDeviceComponent::AggregateExecutableDeviceComponent (char* componentRegistry_ior, char* _id, char* _label, char* sftwrPrfl, char* compositeDev_ior) : DeviceComponent(componentRegistry_ior, _id, _label, sftwrPrfl, compositeDev_ior) {
    //initializeCommonAttributes(_id);
    _devices = new CF::ObjectSequence();
}
AggregateExecutableDeviceComponent::AggregateExecutableDeviceComponent (char* componentRegistry_ior, char* _id, char* _label, char* sftwrPrfl, CF::Properties capacities) : DeviceComponent(componentRegistry_ior, _id, _label, sftwrPrfl) {
    //initializeCommonAttributes(_id);
    _devices = new CF::ObjectSequence();
}
AggregateExecutableDeviceComponent::AggregateExecutableDeviceComponent (char* componentRegistry_ior, char* _id, char* _label, char* sftwrPrfl, CF::Properties capacities, char *compDev) : DeviceComponent(componentRegistry_ior, _id, _label, sftwrPrfl, compDev) {
    //initializeCommonAttributes(_id);
    _devices = new CF::ObjectSequence();
}

/*void DeviceComponent::initializeCommonAttributes(const std::string _id) {
    _identifier = _id;
    _started = false;
}*/

AggregateExecutableDeviceComponent::~AggregateExecutableDeviceComponent () {
}

void AggregateExecutableDeviceComponent::unload (const char* fileName) throw (CORBA::SystemException, CF::InvalidState, CF::InvalidFileName)
{
}
void AggregateExecutableDeviceComponent::load (CF::FileSystem_ptr fs, const char* fileName, CF::LoadableInterface::LoadType loadKind)
        throw (CF::LoadableInterface::LoadFail, CF::InvalidFileName, CF::LoadableInterface::InvalidLoadKind,
                CF::InvalidState, CORBA::SystemException)
{
}

void AggregateExecutableDeviceComponent::addDevice(CORBA::Object_ptr associatedDevice, const char* identifier)  throw (CF::InvalidObjectReference)
{
    unsigned int devSeqLength = _devices->length();

    CF::DeviceComponent_var tmp_assocdev = CF::DeviceComponent::_narrow(associatedDevice);
    for (unsigned int i = 0; i < devSeqLength; i++) {
        //CF::DeviceComponent_var tmpdev = (*_devices)[i]._narrow();
        CF::DeviceComponent_var tmpdev = CF::DeviceComponent::_narrow(_devices[i]);
        if (tmpdev) {
            if (!strcmp(tmp_assocdev->identifier(), tmpdev->identifier())) {
                return;
            }
        }
    }
    _devices->length(devSeqLength + 1);
    _devices[devSeqLength] = CORBA::Object::_duplicate(associatedDevice);
}

void AggregateExecutableDeviceComponent::removeDevice(const char* identifier)  throw (CF::InvalidObjectReference)
{
    unsigned int devSeqLength = _devices->length();
    std::string tmp_assoc_identifier = sca::corba::returnString(identifier);

    for (unsigned int i = 0; i < devSeqLength; i++) {
        CF::DeviceComponent_var tmpdev = CF::DeviceComponent::_narrow(_devices[i]);
        std::string tmp_dev_identifier = sca::corba::returnString(tmpdev->identifier());
        if (tmp_assoc_identifier == tmp_dev_identifier) {
            for (unsigned int j = i + 1; j < devSeqLength; j++) {
                _devices[j-1] = _devices[j];
            }
            _devices->length(devSeqLength - 1);
            break;
        }
    }

    return;
}

/*
void DeviceComponent::run() {
    component_running.wait();
}

void DeviceComponent::halt() {
    //component_running.signal();
}

char* DeviceComponent::identifier () throw (CORBA::SystemException)
{
    return CORBA::string_dup(this->_identifier.c_str());
}

CORBA::Boolean DeviceComponent::started() throw (CORBA::SystemException) {
    return _started;
}

void DeviceComponent::start () throw (CF::ControllableInterface::StartError, CORBA::SystemException) {
    _started = true;
}

void DeviceComponent::stop () throw (CF::ControllableInterface::StopError, CORBA::SystemException) {
    _started = false;
}

void DeviceComponent::initialize () throw (CF::LifeCycle::InitializeError, CORBA::SystemException) {
}

void DeviceComponent::releaseObject() throw (CF::LifeCycle::ReleaseError, CORBA::SystemException) {
    PortableServer::POA_ptr root_poa = sca::corba::RootPOA();
    PortableServer::ObjectId_var oid = root_poa->servant_to_id(this);
    root_poa->deactivate_object(oid);
    component_running.signal();
}

void DeviceComponent::connectUsesPorts(const CF::PortAccessor::Connections& portConnections) throw (CF::PortAccessor::InvalidPort, CORBA::SystemException) {
    for (unsigned int i=0; i<portConnections.length(); i++) {
        std::string port_name = sca::corba::returnString(portConnections[i].portConnectionId.portName);
        std::string connection_id = sca::corba::returnString(portConnections[i].portConnectionId.connectionId);

        PortServantMap::iterator existing = _portServants.find(port_name);
        if (existing == _portServants.end()) {
            CF::PortAccessor::ConnectionErrorType error;
            error.portConnectionId = portConnections[i].portConnectionId;
            error.errorCode = 1;
            throw CF::PortAccessor::InvalidPort(error);
        }
        if (connection_id.empty()) {
            connection_id = sca::generateUUID();
        }
        sca::UsesPort* usesport = dynamic_cast<sca::UsesPort*>(_portServants[port_name]);
        if (usesport) {
            usesport->connectPort(portConnections[i].portReference, connection_id.c_str());
        } else {
            CF::PortAccessor::ConnectionErrorType error;
            error.portConnectionId = portConnections[i].portConnectionId;
            error.errorCode = 1;
            throw CF::PortAccessor::InvalidPort(error);
        }
    }

}

void DeviceComponent::disconnectPorts(const CF::PortAccessor::Disconnections& portDisconnections) throw (CF::PortAccessor::InvalidPort, CORBA::SystemException) {
}

void DeviceComponent::getProvidesPorts(CF::PortAccessor::Connections& portConnections ) throw (CF::PortAccessor::InvalidPort, CORBA::SystemException) {
}

void DeviceComponent::runTest (CORBA::ULong TestID, CF::Properties& testValues) throw (CF::UnknownProperties, CF::TestableInterface::UnknownTest, CORBA::SystemException) {
}

CF::CapacityManagement::UsageType DeviceComponent::usageState ()throw (CORBA::SystemException) {
    return CF::CapacityManagement::IDLE;
}

CORBA::Boolean DeviceComponent::allocateCapacity (const CF::Properties& capacities) throw (CF::InvalidState, CF::CapacityManagement::InvalidCapacity, CORBA::SystemException) {
    return true;
}

void DeviceComponent::deallocateCapacity (const CF::Properties& capacities) throw (CF::InvalidState, CF::CapacityManagement::InvalidCapacity, CORBA::SystemException) {
}

CF::DeviceAttributes::OperationalType DeviceComponent::operationalState () throw (CORBA::SystemException) {
    return CF::DeviceAttributes::ENABLED;
}

CF::AdministratableInterface::AdminType DeviceComponent::adminState () throw (CORBA::SystemException) {
    return CF::AdministratableInterface::LOCKED;
}

void DeviceComponent::adminState (CF::AdministratableInterface::AdminType _adminType) {
}

void DeviceComponent::setExecparamProperties(std::map<std::string, char*>& execparams)
{
    std::map<std::string, char*>::iterator iter;
    for (iter = execparams.begin(); iter != execparams.end(); iter++) {
        const std::string id = iter->first;
        PropertyInterface* property = getPropertyFromId(id);
        // the property can belong to a resource, device, or Device/Domain
        // Manager.  If the property is not found, then it might be a resource
        // property passed through the nodeBooter to the DeviceManager
        if (property) {
            CORBA::Any val = sca::string_to_any(iter->second, property->type);
            property->setValue(val);
        } else {
        }
    }
}

void  DeviceComponent::setAdditionalParameters ( std::string &registrar_ior)
{
  _deviceManagerRegistry = CF::ComponentRegistry::_nil();
  CORBA::Object_var obj = sca::corba::Orb()->string_to_object(registrar_ior.c_str());
  if (CORBA::is_nil(obj)) {
    std::cout<<"Invalid device manager IOR"<<std::endl;
    exit(-1);
  }
  _deviceManagerRegistry = CF::ComponentRegistry::_narrow(obj);
  if (CORBA::is_nil(_deviceManagerRegistry)) {
    std::cout<<"Could not narrow device manager IOR"<<std::endl;
    exit(-1);
  }
}

void  DeviceComponent::postConstruction (std::string &registrar_ior)
{
    // resolves Domain and Device Manger relationships
    setAdditionalParameters(registrar_ior);

    // establish IDM Channel connectivity
    CF::ComponentType this_dev;
    this_dev.identifier = this->_identifier.c_str();
    this_dev.profile = this->profile.c_str();
    this_dev.type = CF::DEVICE_COMPONENT;
    this_dev.componentObject = this->_this();
    this_dev.providesPorts.length(0);
    this_dev.specializedInfo.length(0);

    // register ourself with my DeviceManager
    _deviceManagerRegistry->registerComponent(this_dev);
}

void DeviceComponent::addPort (const std::string& name, PortBase* servant)
{
    insertPort(name, servant);

    // Activate the port in its default POA (usually, the root)
    PortableServer::POA_var poa = servant->_default_POA();
    PortableServer::ObjectId_var oid = poa->activate_object(servant);

    // Allow additional post-activation initialization
    servant->initializePort();
}

void DeviceComponent::addPort (const std::string& name, const std::string& description, PortBase* servant)
{
    addPort(name, servant);
    servant->setDescription(description);
}

void DeviceComponent::insertPort (const std::string& name, PortBase* servant)
{
    PortServantMap::iterator existing = _portServants.find(name);
    if (existing != _portServants.end()) {
        deactivatePort(existing->second);
    }
    _portServants[name] = servant;
}

void DeviceComponent::deactivatePort (PortBase* servant)
{
    PortableServer::POA_var poa = servant->_default_POA();
    PortableServer::ObjectId_var oid = poa->servant_to_id(servant);
    poa->deactivate_object(oid);
}
*/
void AggregateExecutableDeviceComponent::start_device(AggregateExecutableDeviceComponent::ctor_type ctor, struct sigaction sa, int argc, char* argv[])
{
    char* devMgr_ior = 0;
    char* id = 0;
    char* blank_string = 0;
    char* composite_device = 0;

    for (int index = 1; index < argc; ++index) {
        if (std::string(argv[index]) == std::string("-i")) {
            std::cout<<"Interactive mode (-i) no longer supported. Please use the sandbox to run Components/Devices/Services outside the scope of a Domain"<<std::endl;
            exit(-1);
        }
    }
    
    std::map<std::string, char*> execparams;
                
    for (int i = 0; i < argc; i++) {
            
        if (strcmp("COMPONENT_REGISTRY_IOR", argv[i]) == 0) {
            devMgr_ior = argv[++i];
        } else if (strcmp("DEVICE_ID", argv[i]) == 0) {
            id = argv[++i];
        } else if (strcmp("COMPOSITE_DEVICE_IOR", argv[i]) == 0) {
            composite_device = argv[++i];
        } else if (i > 0) {  // any other argument besides the first one is part of the execparams
            std::string paramName = argv[i];
            execparams[paramName] = argv[++i];
        }
    }

    // The ORB must be initialized before configuring logging, which may use
    // CORBA to get its configuration file. Devices do not need persistent IORs.
    sca::corba::CorbaInit(argc, argv);

    if ((devMgr_ior == 0) || (id == 0)) {
        exit(-1);
    }

    // Associate SIGINT to signal_catcher interrupt handler
    if( sigaction( SIGINT, &sa, NULL ) == -1 ) {
        exit(EXIT_FAILURE);
    }

    // Associate SIGQUIT to signal_catcher interrupt handler
    if( sigaction( SIGQUIT, &sa, NULL ) == -1 ) {
        exit(EXIT_FAILURE);
    }

    // Associate SIGTERM to signal_catcher interrupt handler
    if( sigaction( SIGTERM, &sa, NULL ) == -1 ) {
        exit(EXIT_FAILURE);
    }

    /* Ignore SIGInterrupt because when you CTRL-C the node
        booter we don't want the device to die, and it's the shells responsibility
        to send CTRL-C to all foreground processes (even children) */
    signal(SIGINT, SIG_IGN);

    AggregateExecutableDeviceComponent* device = ctor(devMgr_ior, id, blank_string, composite_device);

    // setting all the execparams passed as argument, this method resides in the Resource_impl class
    device->setExecparamProperties(execparams);

    //perform post construction operations for the device
    std::string tmp_devMgr_ior = devMgr_ior;
    try {
      device->postConstruction( tmp_devMgr_ior);
    }
    catch( CF::InvalidObjectReference &ex ) {
      if ( device ) device->_remove_ref();
      sca::corba::OrbShutdown(true);
      exit(EXIT_FAILURE);
    } catch ( CORBA::SystemException &ex ) {
        std::ostringstream eout;
        eout<<"CORBA::"<<ex._name()<<"(";
        const char* minor = ex.NP_minorString();
        if (minor)
            eout<<minor;
        else {
            eout << "0x" << std::hex << ex.minor();
        }
        eout << ", CORBA::";
        switch (ex.completed()) {
            case CORBA::COMPLETED_YES:
                eout << "COMPLETED_YES";
                break;
            case CORBA::COMPLETED_NO:
                eout << "COMPLETED_NO";
                break;
            default:
                eout << "COMPLETED_MAYBE";
        }
        eout << ")";
        if ( device ) device->_remove_ref();
        sca::corba::OrbShutdown(true);
        exit(EXIT_FAILURE);
    } catch ( ... ) {
        if ( device ) device->_remove_ref();
        sca::corba::OrbShutdown(true);
        exit(EXIT_FAILURE);
    }

    device->run();
    device->_remove_ref();
    sca::corba::OrbShutdown(true);
}


