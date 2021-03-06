/*
 * This file is protected by Copyright. Please refer to the COPYRIGHT file 
 * distributed with this source distribution.
 * 
 * This file is part of SCA-JTNC core.
 * 
 * SCA-JTNC core is free software: you can redistribute it and/or modify it 
 * under the terms of the GNU Lesser General Public License as published by the 
 * Free Software Foundation, either version 3 of the License, or (at your 
 * option) any later version.
 * 
 * SCA-JTNC core is distributed in the hope that it will be useful, but WITHOUT 
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
#include <dlfcn.h>

#include "sca/DeviceComponent.h"

DeviceComponent::DeviceComponent (char* componentRegistry_ior, char* _id, char* _label, char* compositeDev_ior) : ResourceComponent(_id, _label), component_running_mutex(),
    component_running(&component_running_mutex) {
    if (compositeDev_ior) {
        compDev_ior = compositeDev_ior;
    }
    initializeCommonAttributes(_id);
}

DeviceComponent::DeviceComponent (char* componentRegistry_ior, char* _id, char* _label, char* sftwrPrfl, char* compositeDev_ior) : ResourceComponent(_id, _label), component_running_mutex(),
    component_running(&component_running_mutex) {
    if (compositeDev_ior) {
        compDev_ior = compositeDev_ior;
    }
    initializeCommonAttributes(_id);
}

DeviceComponent::DeviceComponent (char* componentRegistry_ior, char* _id, char* _label, char* sftwrPrfl, CF::Properties capacities, char* compositeDev_ior) : ResourceComponent(_id, _label), component_running_mutex(),
    component_running(&component_running_mutex) {
    if (compositeDev_ior) {
        compDev_ior = compositeDev_ior;
    }
    initializeCommonAttributes(_id);
}

DeviceComponent::DeviceComponent (char* componentRegistry_ior, char* _id, char* _label, char* sftwrPrfl, CF::Properties capacities) : ResourceComponent(_id, _label), component_running_mutex(),
    component_running(&component_running_mutex) {
    initializeCommonAttributes(_id);
}

void DeviceComponent::initializeCommonAttributes(const std::string _id) {
    _identifier = _id;
    _started = false;
    _aggregateDevice = CF::AggregateDevice::_nil();
    _usageState = CF::CapacityManagement::IDLE;
    _adminState = CF::AdministratableInterface::UNLOCKED;
    if (not compDev_ior.empty()) {
        CORBA::Object_var _aggDev_obj = sca::corba::Orb()->string_to_object(compDev_ior.c_str());
        if (CORBA::is_nil(_aggDev_obj)) {
            std::cout<<"Invalid composite device IOR: " << compDev_ior<<std::endl;
        } else {
            _aggregateDevice = CF::AggregateDevice::_narrow(_aggDev_obj);
            _aggregateDevice->addDevice(this->_this(), _identifier.c_str());
        }
    }
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
    ResourceComponent::releaseObject();
    /*PortableServer::POA_ptr root_poa = sca::corba::RootPOA();
    PortableServer::ObjectId_var oid = root_poa->servant_to_id(this);
    root_poa->deactivate_object(oid);
    component_running.signal();

    _resourceReleased(this);*/
    
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
    return _usageState;
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
    return _adminState;
}

void DeviceComponent::adminState (CF::AdministratableInterface::AdminType _adminType) {
    _adminState = _adminType;
}

bool DeviceComponent::isLocked ()
{
    if (_adminState == CF::AdministratableInterface::LOCKED) {
        return true;
    } else {
        return false;
    }
}


bool DeviceComponent::isDisabled ()
{
    return false;
}


bool DeviceComponent::isBusy ()
{
    if (_usageState == CF::CapacityManagement::BUSY) {
        return true;
    } else {
        return false;
    }
}


bool DeviceComponent::isIdle ()
{
    if (_usageState == CF::CapacityManagement::IDLE) {
        return true;
    } else {
        return false;
    }
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
  _deviceManagerFullRegistry = CF::FullComponentRegistry::_nil();
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
  _deviceManagerFullRegistry = CF::FullComponentRegistry::_narrow(obj);
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

CF::AggregateDevice_ptr DeviceComponent::compositeDevice()
{
    return CF::AggregateDevice::_duplicate(_aggregateDevice);
};

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

void DeviceComponent::setUsageState (CF::CapacityManagement::UsageType newUsageState)
{
    _usageState = newUsageState;
}

void DeviceComponent::setAdminState (CF::AdministratableInterface::AdminType new_adminState)
{
    _adminState = new_adminState;
}

void DeviceComponent::deactivatePort (PortBase* servant)
{
    PortableServer::POA_var poa = servant->_default_POA();
    PortableServer::ObjectId_var oid = poa->servant_to_id(servant);
    poa->deactivate_object(oid);
}

void DeviceComponent::start_device(DeviceComponent::ctor_type ctor, struct sigaction sa, int argc, char* argv[])
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

    DeviceComponent* device = ctor(devMgr_ior, id, blank_string, composite_device);

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

const std::string& DeviceComponent::getIdentifier() const
{
    return _identifier;
}

void DeviceComponent::start_lib_device(DeviceComponent::ctor_type ctor, struct sigaction sa, int argc, char* argv[])
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

    DeviceComponent* device = ctor(devMgr_ior, id, blank_string, composite_device);

    // setting all the execparams passed as argument, this method resides in the Resource_impl class
    device->setExecparamProperties(execparams);

    //perform post construction operations for the device
    std::string tmp_devMgr_ior = devMgr_ior;
    try {
      device->postConstruction( tmp_devMgr_ior);
      device->_remove_ref();
    }
    catch( CF::InvalidObjectReference &ex ) {
      if ( device ) device->_remove_ref();
      exit(EXIT_FAILURE);
    } catch ( CORBA::SystemException &ex ) {
        if ( device ) device->_remove_ref();
        exit(EXIT_FAILURE);
    } catch ( ... ) {
        if ( device ) device->_remove_ref();
        exit(EXIT_FAILURE);
    }
}

ExecutableDeviceComponent::ExecutableDeviceComponent(char* componentRegistry_ior, char* _id, char* _label, char* compositeDev_ior) :
    DeviceComponent(componentRegistry_ior, _id, _label, compositeDev_ior)
{
    _processIdIncrement = 0;
    executorService.start();
};

ExecutableDeviceComponent::ExecutableDeviceComponent(char* componentRegistry_ior, char* _id, char* _label, char* sftwrPrfl, char* compositeDev_ior) :
    DeviceComponent(componentRegistry_ior, _id, _label, sftwrPrfl, compositeDev_ior)
{
    _processIdIncrement = 0;
    executorService.start();
};

ExecutableDeviceComponent::ExecutableDeviceComponent(char* componentRegistry_ior, char* _id, char* _label, char* sftwrPrfl, CF::Properties capacities) :
    DeviceComponent(componentRegistry_ior, _id, _label, sftwrPrfl, capacities)
{
    _processIdIncrement = 0;
    executorService.start();
};

ExecutableDeviceComponent::ExecutableDeviceComponent(char* componentRegistry_ior, char* _id, char* _label, char* sftwrPrfl, CF::Properties capacities, char* compositeDev_ior) :
    DeviceComponent(componentRegistry_ior, _id, _label, sftwrPrfl, capacities, compositeDev_ior)
{
    _processIdIncrement = 0;
    executorService.start();
};

ExecutableDeviceComponent::~ExecutableDeviceComponent()
{
    executorService.stop();
};

void ExecutableDeviceComponent::unload (const char* fileName) throw (CF::InvalidFileName, CF::InvalidState, CORBA::SystemException)
{
};

void ExecutableDeviceComponent::load (CF::FileSystem_ptr fs, const char* fileName, CF::LoadableInterface::LoadType loadKind)
    throw (CF::LoadableInterface::LoadFail, CF::InvalidFileName, CF::LoadableInterface::InvalidLoadKind, CF::InvalidState, CORBA::SystemException)
{
};

void ExecutableDeviceComponent::terminate (const CF::ExecutableInterface::ExecutionID_Type &executionId)
    throw (CF::InvalidState, CF::ExecutableInterface::InvalidProcess, CORBA::SystemException)
{
    
};

/*ResourceComponent* ExecutableDeviceComponent::instantiateComponent (const char* libraryName, const CF::Properties& options, const CF::Properties& parameters) 
{
    // Open up the cached .so file
    std::string absPath = get_current_dir_name();
    absPath.append(libraryName);
    void* pHandle = dlopen(absPath.c_str(), RTLD_NOW);
    if (!pHandle) {
        char* errorMsg = dlerror();
        std::cout<<"Unable to open library '" << absPath.c_str() << "': " << errorMsg<<std::endl;
        return NULL;
    }  

    // Add SKIP_FLAG to properties
    CF::Properties combinedProps = parameters;
    unsigned int skipRunInd;
    skipRunInd = combinedProps.length();
    combinedProps.length(skipRunInd + 1);
    combinedProps[skipRunInd].id = CORBA::string_dup("SKIP_RUN");
    combinedProps[skipRunInd].value <<= true;
    combinedProps.length(combinedProps.length() + 1);
    combinedProps[combinedProps.length() - 1].id = CORBA::string_dup("COMPOSITE_DEVICE_IOR");
    combinedProps[combinedProps.length() - 1].value <<= sca::corba::objectToString(this->_this());

    for (size_t ii = 0; ii < combinedProps.length(); ii++) {
        std::string id(combinedProps[ii].id);
        std::string val = sca::any_to_string(combinedProps[ii].value);
    }

    // Convert combined properties into ARGV/ARGC format
    std::string propId;
    std::string propValue;
    unsigned int argCounter = 0;
    int argc = combinedProps.length() * 2;
    char* argv[argc];
    for (unsigned int i = 0; i < combinedProps.length(); i++) {
        propId = combinedProps[i].id;
        propValue = sca::any_to_string(combinedProps[i].value);

        argv[argCounter] = (char*) malloc(propId.size() + 1);
        strcpy(argv[argCounter++], propId.c_str());

        argv[argCounter] = (char*) malloc(propValue.size() + 1);
        strcpy(argv[argCounter++], propValue.c_str());
    }
    // Look for the 'construct' C-method
    const char* symbol = "construct";
    void* fnPtr = dlsym(pHandle, symbol);
    if (!fnPtr) {
        char* errorMsg = dlerror();
        std::cout<<"Unable to find symbol '" << symbol << "': " << errorMsg<<std::endl;
        return NULL;
    }
    typedef ResourceComponent* (*ConstructorPtr)(int, char*[]);
    // Cast the symbol as a ConstructorPtr
    ConstructorPtr constructPtr = reinterpret_cast<ConstructorPtr>(fnPtr);

    // Attempt to instantiate the persona device via the constructor pointer
    DeviceComponent* personaPtr = NULL;
    try {
        constructPtr(argc, argv, this);
        //personaPtr = generatePersona(argc, argv, constructPtr, libraryName);
    } catch (...) {
        std::cout<<"Unable to construct component: '" << argv[0] << "'"<<std::endl;
    }

    for (unsigned int i = 0; i < argCounter; i++) {
        free(argv[i]);
    }

    return personaPtr;
}*/
std::string ExecutableDeviceComponent::getRealPath(const std::string& path)
{
    // Assume that all paths are relative to the deployment root, which is
    // given by the launching device (or the Sandbox)
    boost::filesystem::path realpath = boost::filesystem::path(std::getenv("SCAROOT")) / "dom" / path;
    if (!boost::filesystem::exists(realpath)) {
        std::string message = "File " + path + " does not exist";
        throw CF::InvalidFileName(CF::CF_EEXIST, message.c_str());
    }
    return realpath.string();
}

CF::ExecutableInterface::ExecutionID_Type* ExecutableDeviceComponent::execute (
                const char*             name, 
                const CF::Properties&   options, 
                const CF::Properties&   parameters )
    throw (CF::ExecutableInterface::ExecuteFail, CF::InvalidFileName, CF::ExecutableInterface::InvalidOptions, CF::ExecutableInterface::InvalidParameters,
        CF::ExecutableInterface::InvalidFunction, CF::InvalidState, CORBA::SystemException )
{
    const std::string path = getRealPath(name);

    boost::scoped_ptr<sca::ModuleBundle> bundle(new sca::ModuleBundle(path));

    sca::Module* module;
    try {
        // Resolve all required symbols now so that we can catch the error and
        // turn it into an exception, rather than having the process exit at
        // point-of-use
        module = bundle->load(path, sca::ModuleLoader::NOW, sca::ModuleLoader::LOCAL);
    } catch (const std::exception& exc) {
        throw CF::ExecutableInterface::ExecuteFail(CF::CF_EINVAL, exc.what());
    }

    typedef ResourceComponent* (*ConstructorPtr)(const std::string&, const std::string&);
    ConstructorPtr make_component;
    try {
        make_component = reinterpret_cast<ConstructorPtr>(module->symbol("make_component"));
    } catch (const std::exception& exc) {
        throw CF::ExecutableInterface::InvalidFunction();
    }

    ResourceComponent* servant = ResourceComponent::create_component(make_component, parameters);
    
    if (servant == NULL) {
        std::cout<<"unable to instantiate component"<<std::endl;
    }

    ComponentEntry* component = new ComponentEntry;
    component->servant = servant;
    component->bundle.swap(bundle);

    int thread_id = ++_processIdIncrement;
    activeComponents[thread_id] = component;

    servant->addReleaseListener(this, &ExecutableDeviceComponent::componentReleased);

    CF::ExecutableInterface::ExecutionID_Type_var retval = new CF::ExecutableInterface::ExecutionID_Type();
    retval->threadId = (CORBA::ULongLong) 0;
    retval->processId = (CORBA::ULongLong) _processIdIncrement;
    retval->processCollocation = CORBA::string_dup("none");
    retval->cores.length(0);

    return retval._retn();
}

void ExecutableDeviceComponent::componentReleased(ResourceComponent* component)
{
    ComponentTable::iterator entry;
    for (entry = activeComponents.begin(); entry != activeComponents.end(); ++entry) {
        if (entry->second->servant == component) {
            break;
        }
    }

    if (entry == activeComponents.end()) {
        std::cout<<"Received release notification from unmanaged component "<< component->getIdentifier()<<std::endl;
        return;
    }

    executorService.execute(&ExecutableDeviceComponent::cleanupComponent, this, entry->second);
    activeComponents.erase(entry);
}

void ExecutableDeviceComponent::cleanupComponent(ComponentEntry* component)
{
    // Only if this is the last reference to the servant can we safely unload
    // its shared libraries, because we need to know that it has been deleted
    if (component->servant->_refcount_value() == 1) {
        component->servant->_remove_ref();
        component->bundle->unload();
        delete component;
        return;
    }

    // Try again after a small delay
    boost::system_time when = boost::get_system_time() + boost::posix_time::microseconds(125);
    executorService.schedule(when, &ExecutableDeviceComponent::cleanupComponent, this, component);
}

