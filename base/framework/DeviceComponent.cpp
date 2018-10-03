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

#include "sca/DeviceComponent.h"

DeviceComponent::DeviceComponent (char* componentRegistry_ior, char* _id, char* _label, char* sftwrPrfl) : component_running_mutex(),
    component_running(&component_running_mutex) {
    initializeCommonAttributes(_id);
}

DeviceComponent::DeviceComponent (char* componentRegistry_ior, char* _id, char* _label, char* sftwrPrfl, char* compositeDev_ior) : component_running_mutex(),
    component_running(&component_running_mutex) {
    initializeCommonAttributes(_id);
}

void DeviceComponent::initializeCommonAttributes(const std::string _id) {
    _identifier = _id;
    _started = false;
}

DeviceComponent::~DeviceComponent () {
}

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
}

void DeviceComponent::disconnectPorts(const CF::PortAccessor::Disconnections& portDisconnections) throw (CF::PortAccessor::InvalidPort, CORBA::SystemException) {
}

void DeviceComponent::getProvidesPorts(CF::PortAccessor::Connections& portConnections ) throw (CF::PortAccessor::InvalidPort, CORBA::SystemException) {
}

/*void DeviceComponent::configure (const CF::Properties& configProperties) throw (CF::PropertySet::PartialConfiguration, CF::PropertySet::InvalidConfiguration, CORBA::SystemException) {
}

void DeviceComponent::query (CF::Properties& configProperties) throw (CF::UnknownProperties, CORBA::SystemException) {
}*/

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
    /*std::map<std::string, char*>::iterator iter;
    for (iter = execparams.begin(); iter != execparams.end(); iter++) {
        const std::string id = iter->first;
        PropertyInterface* property = getPropertyFromId(id);
        // the property can belong to a resource, device, or Device/Domain
        // Manager.  If the property is not found, then it might be a resource
        // property passed through the nodeBooter to the DeviceManager
        if (property) {
            CORBA::Any val = ossie::string_to_any(iter->second, property->type);
            property->setValue(val);
        } else {
        }
    }*/
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
   /*struct ComponentType {
      string identifier;
      string profile;
      CF::ComponentEnumType type;
      Object componentObject;
      CF::Ports providesPorts;
      CF::Properties specializedInfo;
   };*/

  // register ourself with my DeviceManager
  _deviceManagerRegistry->registerComponent(this_dev);

  // setup original capacity values cache
  /*PropertySet_impl::PropertyMap::iterator pi = propTable.begin();
  for( ; pi != propTable.end(); pi++ ) {
      PropertyInterface *p = pi->second;
      if ( p and p->isAllocatable() ) {
          CF::DataType res;
          res.id = p->id.c_str();
          p->getValue(res.value);
          bool found = false;
          for ( unsigned int j=0; j < originalCap.length(); j++) {
              if ( strcmp(p->id.c_str(), originalCap[j].id) == 0 ) {
                  originalCap[j].value = res.value;
                  found = true;
              }
          }
          if ( !found ) {
              ossie::corba::push_back( originalCap, res );
          }
      }
  }*/
}

void DeviceComponent::start_device(DeviceComponent::ctor_type ctor, struct sigaction sa, int argc, char* argv[])
{
    char* devMgr_ior = 0;
    char* id = 0;
    char* blank_string = 0;
    char* composite_device = 0;
    //const char* logging_config_uri = 0;
    //int debug_level = -1; // use log level from configuration file 
    std::string logcfg_uri("");
    std::string log_id("");
        
    for (int index = 1; index < argc; ++index) {
        if (std::string(argv[index]) == std::string("-i")) {
            std::cout<<"Interactive mode (-i) no longer supported. Please use the sandbox to run Components/Devices/Services outside the scope of a Domain"<<std::endl;
            exit(-1);
        }
    }
    
    std::cout<<"(1)"<<std::endl;
    std::map<std::string, char*> execparams;
                
    for (int i = 0; i < argc; i++) {
            
        if (strcmp("COMPONENT_REGISTRY_IOR", argv[i]) == 0) {
            devMgr_ior = argv[++i];
        } else if (strcmp("DEVICE_ID", argv[i]) == 0) {
            id = argv[++i];
            log_id = id;
        } else if (strcmp("COMPOSITE_DEVICE_IOR", argv[i]) == 0) {
            composite_device = argv[++i];
        } else if (i > 0) {  // any other argument besides the first one is part of the execparams
            std::string paramName = argv[i];
            execparams[paramName] = argv[++i];
        }
    }

    std::cout<<"(2)"<<std::endl;

    // The ORB must be initialized before configuring logging, which may use
    // CORBA to get its configuration file. Devices do not need persistent IORs.
    sca::corba::CorbaInit(argc, argv);
    std::cout<<"(4)"<<std::endl;

    //if ((devMgr_ior == 0) || (id == 0) || (profile == 0) || (label == 0)) {
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
    std::cout<<"(5)"<<std::endl;

    DeviceComponent* device = ctor(devMgr_ior, id, blank_string, composite_device);
    std::cout<<"(6)"<<std::endl;

    // setting all the execparams passed as argument, this method resides in the Resource_impl class
    device->setExecparamProperties(execparams);
    std::cout<<"(7)"<<std::endl;

    //perform post construction operations for the device
    std::string tmp_devMgr_ior = devMgr_ior;
    try {
    std::cout<<"(8)"<<std::endl;
      device->postConstruction( tmp_devMgr_ior);
    std::cout<<"(9)"<<std::endl;
    }
    catch( CF::InvalidObjectReference &ex ) {
      if ( device ) device->_remove_ref();
      //ossie::logging::Terminate();
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
        //ossie::logging::Terminate();
        sca::corba::OrbShutdown(true);
        exit(EXIT_FAILURE);
    } catch ( ... ) {
        if ( device ) device->_remove_ref();
        //ossie::logging::Terminate();
        sca::corba::OrbShutdown(true);
        exit(EXIT_FAILURE);
    }

    device->run();
    device->_remove_ref();
    //ossie::logging::Terminate();
    sca::corba::OrbShutdown(true);
}


