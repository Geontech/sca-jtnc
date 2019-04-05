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
#include <signal.h>

#include "sca/ResourceComponent.h"
//#include "sca/Events.h"
//#include "ossie/Component.h"

ResourceComponent::ResourceComponent (const char* _uuid) :
    _identifier(_uuid),
    _started(false),
    component_running_mutex(),
    component_running(&component_running_mutex),
    _initialized(false)
{
    std::cout<<"............. resourcecomponent constructor 1"<<std::endl;
}


ResourceComponent::ResourceComponent (const char* _uuid, const char *label) :
    _identifier(_uuid),
    naming_service_name(label),
    _started(false),
    component_running_mutex(),
    component_running(&component_running_mutex),
    _initialized(false)
{
    std::cout<<"............. resourcecomponent constructor 2"<<std::endl;
}

ResourceComponent::~ResourceComponent ()
{
    std::cout<<"............. destroying resourcecomponent"<<std::endl;
}


void ResourceComponent::setAdditionalParameters(std::string& softwareProfile, std::string &application_registrar_ior, std::string &nic)
{
    _softwareProfile = softwareProfile;
    /*CORBA::ORB_ptr orb = sca::corba::Orb();
    CORBA::Object_var applicationRegistrarObject = CORBA::Object::_nil();
    try {
      applicationRegistrarObject = orb->string_to_object(application_registrar_ior.c_str());
    } catch ( ... ) {
      setDomainManager(CF::DomainManager::_nil());
      return;
    }
    CF::ApplicationRegistrar_var applicationRegistrar = sca::corba::_narrowSafe<CF::ApplicationRegistrar>(applicationRegistrarObject);
    if (!CORBA::is_nil(applicationRegistrar)) {
      try {
          CF::DomainManager_var dm=applicationRegistrar->domMgr();
          setDomainManager(dm);
          return;
      }
      catch(...){
      }
    }

    CF::DeviceManager_var devMgr = sca::corba::_narrowSafe<CF::DeviceManager>(applicationRegistrarObject);
    if (!CORBA::is_nil(devMgr)) {
        try {
            CF::DomainManager_var dm=devMgr->domMgr();
            setDomainManager(dm);
            return;
        }
        catch(...){
        }
    }*/
}

void ResourceComponent::constructor ()
{
}


void ResourceComponent::start () throw (CORBA::SystemException, CF::ControllableInterface::StartError)
{
    //startPorts();
    _started = true;
}


void ResourceComponent::stop () throw (CORBA::SystemException, CF::ControllableInterface::StopError)
{
    //stopPorts();
    _started = false;
}

char* ResourceComponent::identifier () throw (CORBA::SystemException)
{
    return CORBA::string_dup(_identifier.c_str());
}

/*char* ResourceComponent::softwareProfile ()
throw (CORBA::SystemException)
{
    return CORBA::string_dup(_softwareProfile.c_str());
}*/

CORBA::Boolean ResourceComponent::started () throw (CORBA::SystemException)
{
    return _started;
}

void ResourceComponent::initialize () throw (CF::LifeCycle::InitializeError, CORBA::SystemException)
{
    std::cout<<".............. initialize"<<std::endl;
  //startPropertyChangeMonitor(_identifier);
  if (!_initialized) {
      _initialized = true;
      try {
          constructor();
      } catch (const std::exception& exc) {
          CF::StringSequence messages;
          sca::corba::push_back(messages, exc.what());
          throw CF::LifeCycle::InitializeError(messages);
      }
  }
}

void ResourceComponent::releaseObject() throw (CORBA::SystemException, CF::LifeCycle::ReleaseError)
{
    //releasePorts();
    //stopPropertyChangeMonitor();
    PortableServer::POA_ptr root_poa = sca::corba::RootPOA();
    PortableServer::ObjectId_var oid = root_poa->servant_to_id(this);
    root_poa->deactivate_object(oid);

    component_running.signal();

    _resourceReleased(this);
}

void ResourceComponent::run() {
    // Start handling CORBA requests
    component_running.wait();
}

void ResourceComponent::halt() {
    component_running.signal();
}

const std::string& ResourceComponent::getIdentifier() const
{
    return _identifier;
}

void ResourceComponent::setCurrentWorkingDirectory(std::string& cwd) {
    this->currentWorkingDirectory = cwd;
}

std::string& ResourceComponent::getCurrentWorkingDirectory() {
    return this->currentWorkingDirectory;
}

const std::string& ResourceComponent::getDeploymentRoot() const
{
    return _deploymentRoot;
}

void ResourceComponent::setCommandLineProperty(const std::string& id, const sca::Value& value)
{
    if (id == "PROFILE_NAME") {
        _softwareProfile = value.toString();
    } else if (id == "RH::DEPLOYMENT_ROOT") {
        _deploymentRoot = value.toString();
    } else {
        PropertySet_impl::setCommandLineProperty(id, value);
    }
}

ResourceComponent* ResourceComponent::create_component(ResourceComponent::ctor_type ctor, const CF::Properties& properties)
{
    const sca::PropertyMap& parameters = sca::PropertyMap::cast(properties);

    std::string identifier;
    std::string name_binding;
    std::string application_registrar_ior;
    std::string profile_name;
    std::string logging_config_uri;
    std::string dpath;
    //int debug_level = -1;
    sca::PropertyMap cmdlineProps;
    for (sca::PropertyMap::const_iterator prop = parameters.begin(); prop != parameters.end(); ++prop) {
        const std::string id = prop->getId();
        std::cout<<"============ got id: "<<id<<std::endl;
        if (id == "COMPONENT_IDENTIFIER") {
            identifier = prop->getValue().toString();
        } else if (id == "PROFILE_NAME") {
            profile_name = prop->getValue().toString();
        } else if (id == "NAME_BINDING") {
            name_binding = prop->getValue().toString();
        } else if (id == "COMPONENT_REGISTRY_IOR") {
            application_registrar_ior = prop->getValue().toString();
        } else if (id == "DEBUG_LEVEL") {
            //debug_level = atoi(prop->getValue().toString().c_str());
        } else if (id == "LOGGING_CONFIG_URI") {
            logging_config_uri = prop->getValue().toString();
        } else if (id == "DOM_PATH") {
            dpath = prop->getValue().toString();
        } else {
            cmdlineProps.push_back(*prop);
        }
    }
    ResourceComponent* resource = ctor(identifier, name_binding);

    // Initialize command line properties, which can include special properties
    // like PROFILE_NAME.
    for (sca::PropertyMap::const_iterator prop = cmdlineProps.begin(); prop != cmdlineProps.end(); ++prop) {
        resource->setCommandLineProperty(prop->getId(), prop->getValue());
    }

    // Activate the component servant.
    PortableServer::ObjectId_var oid = sca::corba::RootPOA()->activate_object(resource);
    CF::ResourceComponent_var resource_obj = resource->_this();

    CF::ComponentRegistry_ptr _applicationRegistry = CF::ComponentRegistry::_nil();
    //CF::FullComponentRegistry_ptr _applicationFullRegistry = CF::FullComponentRegistry::_nil();
    CORBA::Object_var obj = sca::corba::Orb()->string_to_object(application_registrar_ior.c_str());
    if (CORBA::is_nil(obj)) {
        std::cout<<"Invalid registrar IOR"<<std::endl;
        exit(-1);
    }
    _applicationRegistry = CF::ComponentRegistry::_narrow(obj);
    if (CORBA::is_nil(_applicationRegistry)) {
        std::cout<<"Could not narrow registrar IOR"<<std::endl;
        exit(-1);
    }
    //_applicationFullRegistry = CF::FullComponentRegistry::_narrow(obj);

    CF::ComponentType this_comp;
    this_comp.identifier = identifier.c_str();
    this_comp.profile = profile_name.c_str();
    this_comp.type = CF::DEVICE_COMPONENT;
    this_comp.componentObject = resource->_this();
    this_comp.providesPorts.length(0);
    this_comp.specializedInfo.length(0);
    _applicationRegistry->registerComponent(this_comp);

    // Get the application naming context and bind the component into it.
    /*if (!application_registrar_ior.empty()) {
        CORBA::Object_var applicationRegistrarObject = sca::corba::stringToObject(application_registrar_ior);
        CF::ApplicationRegistrar_var applicationRegistrar = sca::corba::_narrowSafe<CF::ApplicationRegistrar>(applicationRegistrarObject);

        if (!CORBA::is_nil(applicationRegistrar)) {
            try {
                // Set up the DomainManager container
                CF::DomainManager_var domainManager = applicationRegistrar->domMgr();
                resource->setDomainManager(domainManager);

                // If it inherits from the Component class, set up the Application
                // container as well
                Component* component = dynamic_cast<Component*>(resource);
                if (component) {
                    CF::Application_var application = applicationRegistrar->app();
                    component->setApplication(application);
                }

                // Register with the application
                applicationRegistrar->registerComponent(name_binding.c_str(), resource_obj);
            }
            catch( CF::InvalidObjectReference &e ) {
            }
            catch( CF::DuplicateName &e ){
            }
            catch(CORBA::SystemException &ex){
                throw;
            }

        } else {
            // the registrar is not available (because the invoking infrastructure only uses the name service)
            CosNaming::NamingContext_var applicationContext = sca::corba::_narrowSafe<CosNaming::NamingContext>(applicationRegistrarObject);
            sca::corba::bindObjectToContext(resource_obj, applicationContext, name_binding);
        }
    }*/

    return resource;
}

static ResourceComponent* main_component = 0;
static void sigint_handler(int signum)
{
    main_component->halt();
}

void ResourceComponent::connectUsesPorts(const CF::PortAccessor::Connections& portConnections) throw (CF::PortAccessor::InvalidPort, CORBA::SystemException) {
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

void ResourceComponent::disconnectPorts(const CF::PortAccessor::Disconnections& portDisconnections) throw (CF::PortAccessor::InvalidPort, CORBA::SystemException) {
}

void ResourceComponent::getProvidesPorts(CF::PortAccessor::Connections& portConnections ) throw (CF::PortAccessor::InvalidPort, CORBA::SystemException) {
}

void ResourceComponent::runTest (CORBA::ULong TestID, CF::Properties& testValues) throw (CF::UnknownProperties, CF::TestableInterface::UnknownTest, CORBA::SystemException) {
}

void ResourceComponent::start_component(ResourceComponent::ctor_type ctor, int argc, char* argv[])
{
    for (int index = 1; index < argc; ++index) {
        if (std::string(argv[index]) == std::string("-i")) {
            std::cout<<"Interactive mode (-i) no longer supported. Please use the sandbox to run Components/Devices/Services outside the scope of a Domain"<<std::endl;
            exit(-1);
        }
    }
    // Scan the arguments for NAME_BINDING, setting the thread/process name
    // based on the name. If this isn't done prior to initializing CORBA, the
    // ORB creates some threads that will get the original process name, and
    // any threads they create, and so on.
    for (int index = 1; index < argc; ++index) {
        if (strcmp("NAME_BINDING", argv[index]) == 0) {
            if (++index < argc) {
                std::string value = argv[index];
                value = value.substr(0, 15);
                pthread_setname_np(pthread_self(), value.c_str());
            }
            break;
        }
    }

    // The ORB must be initialized before anything that might depend on CORBA,
    // such as PropertyMap and logging configuration
    sca::corba::CorbaInit(argc, argv);

    // Parse command line arguments.
    //int debug_level = -1; // use log config uri as log level context
    std::string logcfg_uri;
    std::string dpath("");
    bool skip_run = false;
    sca::PropertyMap cmdlineProps;
    for (int i = 1; i < argc; i++) {
        if (strcmp("SKIP_RUN", argv[i]) == 0) {
            skip_run = true;
        } else {
            const std::string name = argv[i++];
            std::string value;
            if (i < argc) {
                value = argv[i];
            } else {
                std::cerr << "No value given for " << name << std::endl;
            }
            if (name ==  "LOGGING_CONFIG_URI") {
                logcfg_uri = value;
                cmdlineProps[name] = value;
            } else if (name == "DEBUG_LEVEL") {
                //debug_level = atoi(value.c_str());
                cmdlineProps[name] = value;
            } else if (name == "DOM_PATH") {
                dpath = value;
            } else {  // any other argument is part of the cmdlineProps
                cmdlineProps[name] = value;
            }
        }
    }

    if (!cmdlineProps.contains("COMPONENT_REGISTRY_IOR")) {
        std::cout<<std::endl<<"usage: "<<argv[0]<<" [execparams]"<<std::endl<<std::endl;
        std::cout<<"The set of execparams is defined in the .prf for the component"<<std::endl;
        std::cout<<"They are provided as arguments pairs ID VALUE, for example:"<<std::endl;
        std::cout<<"     "<<argv[0]<<" INT_PARAM 5 STR_PARAM ABCDED"<<std::endl<<std::endl;
        exit(-1);
    }

    // setup logging context for a component resource
    std::string component_identifier = cmdlineProps.get("COMPONENT_IDENTIFIER", "").toString();
    std::string name_binding = cmdlineProps.get("NAME_BINDING", "").toString();

    try {
        // Create the servant.
        ResourceComponent* resource = create_component(ctor, cmdlineProps);

        std::string pathAndFile = argv[0];
        unsigned lastSlash      = pathAndFile.find_last_of("/");
        std::string cwd         = pathAndFile.substr(0, lastSlash);
        resource->setCurrentWorkingDirectory(cwd);

        if (skip_run){
            return;
        }

        // Store away a reference to the main component and establish a handler for
        // SIGINT that will break out of run()
        main_component = resource;
        struct sigaction sa;
        sa.sa_handler = &sigint_handler;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;
        sigaction(SIGINT, &sa, NULL);

        resource->run();

        //sca::events::Manager::Terminate();

        // Ignore SIGINT from here on out to ensure that the ORB gets shut down
        // properly
        sa.sa_handler = SIG_IGN;
        sigemptyset(&sa.sa_mask);
        sigaction(SIGINT, &sa, NULL);
        main_component = 0;

        resource->_remove_ref();

        sca::corba::OrbShutdown(true);
    }
    catch( CORBA::SystemException &e ){
        std::cerr << "ResourceComponent: Unhandled CORBA exception, exiting comp: " << component_identifier << "/"  <<  name_binding << std::endl;
        try {
            sca::corba::OrbShutdown(true);

        }
        catch(...){
        }
    }
    catch (...) {
        std::cerr << "ResourceComponent: Unknown exception, exiting comp: " << component_identifier << "/"  <<  name_binding << std::endl;
        try {
            sca::corba::OrbShutdown(true);
        }
        catch(...){
        }

    }


}
