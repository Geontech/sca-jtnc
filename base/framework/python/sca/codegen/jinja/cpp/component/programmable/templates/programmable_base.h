
/*{% block license %}*/
/*# Allow child templates to include license #*/
/*{% endblock %}*/
//% set className = component.reprogclass.name
//% set baseClass = component.baseclass.name
//% set includeGuard = className.upper() + '_IMPL_REPROG_H'
//% set executesHWComponents = component.executesHWComponents 
//% set executesPersonaDevices = not executesHWComponents
//% set executeType = "resource" if executesHWComponents else "persona"
//% set executeClass = "ResourceComponent" if executesHWComponents else "DeviceComponent"
#ifndef ${includeGuard}
#define ${includeGuard}

#include "${component.baseclass.header}"
/*{% if component is device %}*/
#include "sca/prop_helpers.h"
#include "entry_point.h"
#include <dlfcn.h>
/*{% endif %}*/


namespace HW_LOAD {
  
  struct default_hw_load_request_struct {
    default_hw_load_request_struct ()
    {
    };

    static std::string getId() {
        return std::string("hw_load_request");
    };

    std::string request_id;
    std::string requester_id;
    std::string hardware_id;
    std::string load_filepath;
  };

  struct default_hw_load_status_struct {
    default_hw_load_status_struct ()
    {
    };

    static std::string getId() {
        return std::string("hw_load_status");
    };

    std::string request_id;
    std::string requester_id;
    std::string hardware_id;
    std::string load_filepath;
    unsigned short state;
  };

  enum load_status_states {
    INACTIVE=0U,
    ACTIVE,
    PENDING,
    ERRORED
  };
}

inline bool operator>>= (const CORBA::Any& a, HW_LOAD::default_hw_load_request_struct& s) {
    CF::Properties* temp;
    if (!(a >>= temp)) return false;
    CF::Properties& props = *temp;
    for (unsigned int idx = 0; idx < props.length(); idx++) {
        if (!strcmp("hw_load_request::request_id", props[idx].id)) {
            if (!(props[idx].value >>= s.request_id)) return false;
        }
        if (!strcmp("hw_load_request::requester_id", props[idx].id)) {
            if (!(props[idx].value >>= s.requester_id)) return false;
        }
        if (!strcmp("hw_load_request::hardware_id", props[idx].id)) {
            if (!(props[idx].value >>= s.hardware_id)) return false;
        }
        if (!strcmp("hw_load_request:load_filepath", props[idx].id)) {
            if (!(props[idx].value >>= s.load_filepath)) return false;
        }
    }
    return true;
};

inline void operator<<= (CORBA::Any& a, const HW_LOAD::default_hw_load_request_struct& s) {
    CF::Properties props;
    props.length(4);
    props[0].id = CORBA::string_dup("hw_load_request::request_id");
    props[0].value <<= s.request_id;
    props[1].id = CORBA::string_dup("hw_load_request::requester_id");
    props[1].value <<= s.requester_id;
    props[2].id = CORBA::string_dup("hw_load_request::hardware_id");
    props[2].value <<= s.hardware_id;
    props[3].id = CORBA::string_dup("hw_load_request::load_filepath");
    props[3].value <<= s.load_filepath;
    a <<= props;
};



inline bool operator>>= (const CORBA::Any& a, HW_LOAD::default_hw_load_status_struct& s) {
    CF::Properties* temp;
    if (!(a >>= temp)) return false;
    CF::Properties& props = *temp;
    for (unsigned int idx = 0; idx < props.length(); idx++) {
        if (!strcmp("hw_load_status::request_id", props[idx].id)) {
            if (!(props[idx].value >>= s.request_id)) return false;
        }
        if (!strcmp("hw_load_status::requester_id", props[idx].id)) {
            if (!(props[idx].value >>= s.requester_id)) return false;
        }
        if (!strcmp("hw_load_status::hardware_id", props[idx].id)) {
            if (!(props[idx].value >>= s.hardware_id)) return false;
        }
        if (!strcmp("hw_load_status:load_filepath", props[idx].id)) {
            if (!(props[idx].value >>= s.load_filepath)) return false;
        }
        if (!strcmp("hw_load_status:state", props[idx].id)) {
            if (!(props[idx].value >>= s.state)) return false;
        }
    }
    return true;
};

inline void operator<<= (CORBA::Any& a, const HW_LOAD::default_hw_load_status_struct& s) {
    CF::Properties props;
    props.length(4);
    props[0].id = CORBA::string_dup("hw_load_status::request_id");
    props[0].value <<= s.request_id;
    props[1].id = CORBA::string_dup("hw_load_status::requester_id");
    props[1].value <<= s.requester_id;
    props[2].id = CORBA::string_dup("hw_load_status::hardware_id");
    props[2].value <<= s.hardware_id;
    props[3].id = CORBA::string_dup("hw_load_status::load_filepath");
    props[3].value <<= s.load_filepath;
    props[3].id = CORBA::string_dup("hw_load_status::state");
    props[3].value <<= s.state;
    a <<= props;
};


/*{% if component is device %}*/
typedef std::string ${executeType.capitalize()}Id;
typedef std::map<${executeType.capitalize()}Id, ${executeClass}*> ${executeType.capitalize()}Map;
typedef std::map<unsigned int, ${executeType.capitalize()}Id> ProcessMap;
typedef ${executeType.capitalize()}Map::iterator ${executeType.capitalize()}MapIter;
typedef ProcessMap::iterator ProcessMapIter;
typedef std::vector<std::string> StrVec;
/*{% endif %}*/


template <typename HW_LOAD_REQUEST=HW_LOAD::default_hw_load_request_struct, 
          typename HW_LOAD_STATUS=HW_LOAD::default_hw_load_status_struct>
class ${className};

template <typename HW_LOAD_REQUEST, typename HW_LOAD_STATUS>
class ${className} : public ${baseClass}
{
    ENABLE_LOGGING;

    public:

        typedef HW_LOAD_REQUEST HwLoadRequestStruct;
        typedef HW_LOAD_STATUS  HwLoadStatusStruct;
        typedef std::vector<HwLoadRequestStruct> HwLoadRequestVec;
        typedef std::vector<HwLoadStatusStruct> HwLoadStatusVec;
        typedef ${className}<HW_LOAD_REQUEST BOOST_PP_COMMA()
                             HW_LOAD_STATUS> ${className}_type;

/*{% if component is not device %}*/
        ${className}(const char *uuid, const char *label) :
            ${baseClass}(uuid, label) 
        {
            construct(); 
        }
//% else
        ${className} (
                                    char            *devMgr_ior,
                                    char            *id,
                                    char            *lbl,
                                    char            *sftwrPrfl )
        : 
            ${baseClass}(devMgr_ior, id, lbl, sftwrPrfl)
        {
            construct();
        }

        ${className} (
                                    char            *devMgr_ior,
                                    char            *id,
                                    char            *lbl,
                                    char            *sftwrPrfl,
                                    char            *compDev )
        :
            ${baseClass}(devMgr_ior, id, lbl, sftwrPrfl, compDev)
        {
            construct();
        }

        ${className} (
                                    char            *devMgr_ior, 
                                    char            *id, 
                                    char            *lbl, 
                                    char            *sftwrPrfl, 
                                    CF::Properties  capacities ) 
        :
            ${baseClass}(devMgr_ior, id, lbl, sftwrPrfl, capacities)
        {
            construct();
        }

        ${className} (
                                    char            *devMgr_ior,
                                    char            *id,
                                    char            *lbl,
                                    char            *sftwrPrfl,
                                    CF::Properties  capacities,
                                    char            *compDev )
        :
            ${baseClass}(devMgr_ior, id, lbl, sftwrPrfl, capacities, compDev)
        {
            construct();
        }
        
/*{% endif %}*/
        virtual ~${className}() {
            // Clean up all children that were executed
            ${executeType.capitalize()}MapIter ${executeType}Iter;
            for (${executeType}Iter = _${executeType}Map.begin(); ${executeType}Iter != _${executeType}Map.end(); ${executeType}Iter++) {
                delete ${executeType}Iter->second;
            }
        }

/*{% if component is device %}*/
        void construct() {
//% if executesPersonaDevices
            setUsageState(CF::CapacityManagement::BUSY);

//% endif
            _${executeType}Map.clear();
            _processMap.clear();
            _processIdIncrement = 0;
            counter = 0;

            _defaultHwLoadStatuses.clear();
            _defaultHwLoadStatuses.resize(1);

            // Set property pointers to use default properties
            _hwLoadRequestsPtr = &_defaultHwLoadRequests;
            _hwLoadStatusesPtr = &_defaultHwLoadStatuses;
        }

        void load ( CF::FileSystem_ptr           fs, 
                    const char*                  fileName, 
                    CF::LoadableInterface::LoadType loadKind )
            throw ( 
                CF::LoadableInterface::LoadFail, 
                CF::InvalidFileName, 
                CF::LoadableInterface::InvalidLoadKind,
                CF::InvalidState, 
                CORBA::SystemException ) 
        {
            /*bool isSharedLibrary = (loadKind == CF::LoadableInterface::SHARED_LIBRARY);
            bool existsOnDevFS   = _deviceManager->fileSys()->exists(fileName);
            
            // For ${executeType} shared librariess that already reside on the dev file 
            // system, use the dev filesystem to copy into cache
            if (isSharedLibrary && existsOnDevFS) { 
                fs = _deviceManager->fileSys();
            }*/

            ${baseClass}::load(fs, fileName, loadKind);
        }
        
        void cleanupComponent(ComponentEntry* component)
        {
            // Only if this is the last reference to the servant can we safely unload
            // its shared libraries, because we need to know that it has been deleted
            if (component->servant->_refcount_value() == 1) {
                component->servant->_remove_ref();
                std::cout<<"Unloading bundle " << component->bundle->name()<<std::endl;
                component->bundle->unload();
                delete component;
                return;
            }

            // Try again after a small delay
            boost::system_time when = boost::get_system_time() + boost::posix_time::microseconds(125);
            executorService.schedule(when, &ProgrammableDevice_prog_base::cleanupComponent, this, component);
        };

        void componentReleased(ResourceComponent* component)
        {
            std::cout<<"Component released: " << component->getIdentifier()<<std::endl;
            typename ComponentTable::iterator entry;
            for (entry = activeComponents.begin(); entry != activeComponents.end(); ++entry) {
                if (entry->second->servant == component) {
                    break;
                }
            }

            if (entry == activeComponents.end()) {
                std::cout<<"Received release notification from unmanaged component "<< component->getIdentifier()<<std::endl;
                return;
            }

            executorService.execute(&ProgrammableDevice_prog_base::cleanupComponent, this, entry->second);
            activeComponents.erase(entry);
        };

        CF::ExecutableInterface::ExecutionID_Type* execute (
                        const char*             name, 
                        const CF::Properties&   options, 
                        const CF::Properties&   parameters )
            throw (
                CF::ExecutableInterface::ExecuteFail, 
                CF::InvalidFileName, 
                CF::ExecutableInterface::InvalidOptions, 
                CF::ExecutableInterface::InvalidParameters,
                CF::ExecutableInterface::InvalidFunction, 
                CF::InvalidState, 
                CORBA::SystemException )
        {
            // Initialize local variables
            DeviceComponent* persona = NULL; 
            std::string personaId;

            // Attempt to instantiate the object contained in the shared library
            std::string string_name(name);
            //string_name = std::getenv("SCAROOT")+std::string("/dev")+string_name;
            string_name = std::string("/dev")+string_name;
            persona = instantiatePersona(string_name.c_str(), options, parameters);
            if (persona == NULL) {
                throw (CF::ExecutableInterface::ExecuteFail());
            }

            // Grab the name from the instantiated object 
            personaId = sca::corba::returnString(persona->identifier());
            
            // Save off the name-pid and name-object mappings
            _personaMap[personaId] = persona;
            _processMap[++_processIdIncrement] = personaId;

            persona->addReleaseListener(this, &ProgrammableDevice_prog_base::componentReleased);

            CF::ExecutableInterface::ExecutionID_Type_var retval = new CF::ExecutableInterface::ExecutionID_Type();
            retval->threadId = (CORBA::ULongLong) 0;
            retval->processId = (CORBA::ULongLong) _processIdIncrement;
            retval->processCollocation = CORBA::string_dup("none");
            /*CF::ULongSeq_var cores = new CF::ULongSeq;
            cores->length(0);
            retval->cores = cores;*/
            retval->cores.length(0);

            return retval._retn();
        };

        /*struct DeviceEntry {
            //boost::scoped_ptr<ModuleBundle> bundle;
            DeviceComponent* servant;
        };
        typedef std::map<int,DeviceEntry*> ComponentTable;
        ComponentTable activeComponents;*/
        int counter;
        sca::ExecutorService executorService;

        void terminate (CF::ExecutableInterface::ExecutionID_Type exec_arg)
            throw (
                CF::InvalidState, 
                CF::ExecutableInterface::InvalidProcess, 
                CORBA::SystemException ) 
        {
            // Initialize local variables
            ProcessMapIter processIter;
            ${executeType.capitalize()}MapIter ${executeType}Iter;
            ${executeType.capitalize()}Id ${executeType}Id;

            // Search for the ${executeType}Id that related to the incoming terminate request
            processIter = _processMap.find(exec_arg.processId);
            if (processIter != _processMap.end()) {

                // Search for the ${executeType} that related to the found ${executeType}Id
                ${executeType}Iter = _${executeType}Map.find(processIter->second);
                if (${executeType}Iter != _${executeType}Map.end()) {
                    try {
                        _deviceManagerFullRegistry->unregisterComponent(${executeType}Iter->second->identifier());
                    } catch ( ... ) {
                    }
/*{% if executesPersonaDevices %}*/
                    ${executeType}Iter->second->setAdminState(CF::AdministratableInterface::UNLOCKED);
/*{% endif %}*/
                    ${executeType}Iter->second->releaseObject();
                    _processMap.erase(processIter); // Erase process mapping here to minimize collisions with non-persona processIds
                    _${executeType}Map.erase(${executeType}Iter);
                    return;
                }
            }
        }
        
        CORBA::Boolean allocateCapacity(const CF::Properties& capacities) 
            throw (
                CF::InvalidState, 
                CF::CapacityManagement::InvalidCapacity, 
                CORBA::SystemException ) 
        {
            boost::mutex::scoped_lock lock(_allocationMutex);

            // Initialize local variables
            bool allocationSuccess = false;
            std::string id;
            std::string incoming${executeType.capitalize()};
            CF::Properties loadProps;
            ${executeType.capitalize()}MapIter iter;
            HwLoadStatusVec hwLoadStatusStruct;
            HwLoadStatusVec* statusVecPtr;
            HwLoadRequestVec* loadRequestsPtr;

            // Iterate through all incoming capacities
            for (unsigned int ii = 0; ii < capacities.length(); ii++) {
                id = capacities[ii].id;

                if (id == HW_LOAD_REQUEST_PROP()) {

                    CORBA::AnySeq* anySeqPtr;
                    CF::Properties* cfPropsPtr;
                    
                    // Grab the current hw_load_request struct
                    loadRequestsPtr = getHwLoadRequests();
                    if (loadRequestsPtr == NULL) {
                        std::cout<<"Unable to get HwLoadRequest vector! Pointer is NULL"<<std::endl;
                        continue;
                    }

                    // Attempt to Convert Any unwrappable type
                    if (capacities[ii].value >>= anySeqPtr) {
                        // Convert AnySeq to HwLoadRequestVector
                        loadRequestsPtr->resize(anySeqPtr->length());
                        for (size_t iv = 0; iv < anySeqPtr->length(); iv++) {
                            (*anySeqPtr)[iv] >>= (*loadRequestsPtr)[iv];
                        }
                    } else if (capacities[ii].value >>= cfPropsPtr) {
                        // Convert CF Properties to HwLoadRequestVector
                        loadRequestsPtr->resize(cfPropsPtr->length());
                        for (size_t iv = 0; iv < cfPropsPtr->length(); iv++) {
                            (*cfPropsPtr)[iv].value >>= (*loadRequestsPtr)[iv];
                        }
                    } else {
                        std::cout<<"Unable to convert HW_LOAD_REQUEST prop!"<<std::endl;
                        continue;
                    }

                    // Validate that hw_load_requests are valid
                    if (hwLoadRequestsAreValid(*loadRequestsPtr)) {
                        
                        // Grab the current hw_load_status struct
                        statusVecPtr = getHwLoadStatuses();
                        if (statusVecPtr == NULL) {
                            std::cout<<"Unable to get HwLoadStatus vector! Pointer is NULL"<<std::endl;
                            continue;
                        }
                        
                        // Apply the load request onto the status vector
                        allocationSuccess = applyHwLoadRequests(*loadRequestsPtr,
                                                                *statusVecPtr);
                        if (allocationSuccess) {
                            executePropertyCallback(HW_LOAD_REQUEST_PROP());
                        }
                    }
                }
            }

            updateAdminStates();
            return allocationSuccess;
        }
        
        void deallocateCapacity(const CF::Properties& capacities) 
            throw (
                CF::InvalidState, 
                CORBA::SystemException ) 
        {
            // Initialize local variables
            bool deallocationSuccess = false;
            std::string id;
            std::string valueStr;
            HwLoadStatusVec* statusVecPtr;
            CORBA::AnySeq* anySeqPtr;
            CF::Properties* cfPropsPtr;
            HwLoadRequestVec loadRequestsToRemove;

            for (unsigned int ii = 0; ii < capacities.length(); ii++) {
                id = capacities[ii].id;

                if (id == HW_LOAD_REQUEST_PROP()) {
                    // Attempt to Convert Any to unwrappable type
                    if (capacities[ii].value >>= anySeqPtr) {
                        // Convert AnySeq to HwLoadRequestVector
                        loadRequestsToRemove.resize(anySeqPtr->length());
                        for (size_t iv = 0; iv < anySeqPtr->length(); iv++) {
                            (*anySeqPtr)[iv] >>= loadRequestsToRemove[iv];
                        }
                    } else if (capacities[ii].value >>= cfPropsPtr) {
                        // Convert CF Properties to HwLoadRequestVector
                        loadRequestsToRemove.resize(cfPropsPtr->length());
                        for (size_t iv = 0; iv < cfPropsPtr->length(); iv++) {
                            (*cfPropsPtr)[iv].value >>= loadRequestsToRemove[iv];
                        }
                    } else {
                        std::cout<<"Unable to convert HW_LOAD_REQUEST property"<<std::endl;
                        continue;
                    }
                    
                    // Grab the current hw_load_status struct
                    statusVecPtr = getHwLoadStatuses();
                    if (statusVecPtr == NULL) {
                        std::cout<<"Unable to get HwLoadStatus vector! Pointer is NULL"<<std::endl;
                        continue;
                    }
                    
                    // Convert AnySeq to HwLoadRequestVector
                    deallocationSuccess = true;
                    for (size_t iv = 0; iv < loadRequestsToRemove.size(); iv++) {
                        deallocationSuccess |= removeHwLoadRequestFromStatus(loadRequestsToRemove[iv], (*statusVecPtr));
                    }
                }
            }

            updateAdminStates();
            if (deallocationSuccess == false) {
                throw CF::CapacityManagement::InvalidCapacity("Unable to deallocation capacities", capacities);
            }
        }
        
        void releaseObject() 
            throw ( CF::LifeCycle::ReleaseError, 
                    CORBA::SystemException)
        {
            // Initialize local variables
            ProcessMapIter processIter;
            ${executeType.capitalize()}MapIter ${executeType}Iter;

            // Terminate all children that were executed
            for (processIter = _processMap.begin(); processIter != _processMap.end(); processIter++) {
                _deviceManagerFullRegistry->unregisterComponent(_${executeType}Map[processIter->second]->identifier());
                _${executeType}Map[processIter->second]->releaseObject();
            }

            // Clean up all children that were executed
            for (${executeType}Iter = _${executeType}Map.begin(); ${executeType}Iter != _${executeType}Map.end(); ${executeType}Iter++) {
                ${executeType}Iter->second->releaseObject();
                //delete ${executeType}Iter->second;
                //${executeType}Iter->second = NULL;
            }

            ${baseClass}::releaseObject();
            setAdminState(CF::AdministratableInterface::SHUTTING_DOWN);
        }
        
        HwLoadRequestVec* getHwLoadRequests() { 
            return getPropertyPtr(_hwLoadRequestsPtr, 
                                  &_defaultHwLoadRequests);
        };
        
        HwLoadStatusVec* getHwLoadStatuses() { 
            return getPropertyPtr(_hwLoadStatusesPtr, 
                                  &_defaultHwLoadStatuses);
        };

        void setHwLoadRequestsPtr(HwLoadRequestVec* propPtr) {
            if (propPtr == NULL) {
               std::cout<<"CANNOT SET HW_LOAD_REQUESTS_PTR: PROPERTY IS NULL"<<std::endl;
               return;
            }
            _hwLoadRequestsPtr = propPtr;
        }
        
        void setHwLoadStatusesPtr(HwLoadStatusVec* propPtr) {
            if (propPtr == NULL) {
               std::cout<<"CANNOT SET HW_LOAD_STATUSES_PTR: PROPERTY IS NULL"<<std::endl;
               return;
            }
            _hwLoadStatusesPtr = propPtr;
        }

    protected:
        ${executeType.capitalize()}Map      _${executeType}Map;        // Mapping of name to object ptr
        ProcessMap      _processMap;         // Mapping of name to processId
        unsigned int    _processIdIncrement; // Used to generate unique ProcessIds
        boost::mutex    _allocationMutex;    // Used to ensure one allocation occurs at a time
        
        // Define the name of the properties
        virtual std::string HW_LOAD_REQUEST_PROP() { return "hw_load_requests"; };
        virtual std::string HW_LOAD_STATUS_PROP()  { return "hw_load_statuses"; };


        virtual ${executeClass}* generate${executeType.capitalize()} (
                                    int                         argc, 
                                    char*                       argv[], 
                                    ConstructorPtr              fnptr, 
                                    const char*                 libraryName)=0;

        virtual ${executeClass}* instantiate${executeType.capitalize()} (
                                    const char*                 libraryName, 
                                    const CF::Properties&       options, 
                                    const CF::Properties&       parameters) 
        {
            // Open up the cached .so file
            std::string absPath = std::getenv("SCAROOT");
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

            // Cast the symbol as a ConstructorPtr
            ConstructorPtr constructPtr = reinterpret_cast<ConstructorPtr>(fnPtr);

            // Attempt to instantiate the ${executeType} device via the constructor pointer
            ${executeClass}* ${executeType}Ptr = NULL;
            try {
                ${executeType}Ptr = generate${executeType.capitalize()}(argc, argv, constructPtr, libraryName);
            } catch (...) {
                std::cout<<"Unable to construct ${executeType} device: '" << argv[0] << "'"<<std::endl;
            }

            for (unsigned int i = 0; i < argCounter; i++) {
                free(argv[i]);
            }

            return ${executeType}Ptr;
        }


        virtual bool hwLoadRequestsAreValid(const HwLoadRequestVec& hwLoadRequestVec) 
        {
            bool isValid = true;
            for (size_t ii = 0; ii < hwLoadRequestVec.size(); ii++) {
                isValid &= hwLoadRequestIsValid(hwLoadRequestVec[ii]);
            }
            return isValid;
        }


        virtual bool hwLoadRequestIsValid(const HwLoadRequestStruct& hwLoadRequestStruct) 
        {
            // Defaults to true... Override this method for more control
            return true;
        }


        virtual bool applyHwLoadRequests (
                                    HwLoadRequestVec&           loadRequestVec, 
                                    HwLoadStatusVec&            loadStatusVec)
        {
            // Setup local variables
            bool success = true;
            int availableStatusIndex;

            // Maintain which statuses were used incase of failures
            std::vector<int> usedStatusIndices; 
            usedStatusIndices.resize(loadRequestVec.size());
            for (size_t ii = 0; ii < usedStatusIndices.size(); ii++) {
                usedStatusIndices[ii] = -1;
            } 

            // Iterate through all requests and find available statuses
            for (size_t ii = 0; ii < loadRequestVec.size(); ii++) {
                
                // Find an available hw load status struct
                availableStatusIndex = findAvailableHwLoadStatusIndex(loadStatusVec);
                if (availableStatusIndex > -1) {
                    success |= applyHwLoadRequest(loadRequestVec[ii], loadStatusVec[availableStatusIndex]);
                    usedStatusIndices[ii] = availableStatusIndex;;
                } else {
                    std::cout<<"Device cannot be allocated against. No load capacity"<<std::endl;
                    success = false;
                }

                // Kick out if there was any issue
                if (success == false) {
                    // Remove any successful requests that made it through initially
                    for (size_t ii = 0; ii < usedStatusIndices.size(); ii++) {
                        resetHwLoadStatus(loadStatusVec[usedStatusIndices[ii]]);
                    }
                    break;
                }
            }
          
            // Clear out the loadRequest property since we're complete
            loadRequestVec.clear();

            return success;
        }
       
 
        virtual bool applyHwLoadRequest (
                                    const HwLoadRequestStruct&  incomingRequest, 
                                    HwLoadStatusStruct&         newStatus)
        {
            newStatus.request_id = incomingRequest.request_id;
            newStatus.requester_id = incomingRequest.requester_id;
            newStatus.hardware_id = incomingRequest.hardware_id;
            newStatus.load_filepath = incomingRequest.load_filepath;
            newStatus.state = HW_LOAD::PENDING;

            // Call user-defined 'loadHardware' and update state based on result
            if (loadHardware(newStatus)) {
                newStatus.state = HW_LOAD::ACTIVE;
                return true;
            }

            // User-defined 'loadhardware' method returned false
            newStatus.state = HW_LOAD::ERRORED;
            return false;
        }

        virtual void resetHwLoadStatus(HwLoadStatusStruct& loadStatusStruct) {
            unloadHardware(loadStatusStruct);
            loadStatusStruct.request_id = "";
            loadStatusStruct.requester_id = "";
            loadStatusStruct.hardware_id = "";
            loadStatusStruct.load_filepath = "";
            loadStatusStruct.state = HW_LOAD::INACTIVE;
        }
        
        // Override this method to physically load the hardware
        virtual bool loadHardware(HwLoadStatusStruct& newStatus) { 
            return true; 
        }

        // Override this method to physically unload the hardware
        virtual void unloadHardware(const HwLoadStatusStruct& loadStatusStruct) {
        }

        virtual bool removeHwLoadRequestFromStatus (
                                    const HwLoadRequestStruct&  hwLoadRequest,
                                    HwLoadStatusVec&            hwStatusVec)
        {
            // Iterate through status vector and reset struct that matches request_id
            for (size_t ii = 0; ii < hwStatusVec.size(); ii++) {
                if (hwLoadRequest.request_id == hwStatusVec[ii].request_id) {
                    resetHwLoadStatus(hwStatusVec[ii]);
                    return true;
                }
            }
            return false;
        }

        virtual bool hasAnInactiveHwLoadStatus() 
        {
            HwLoadStatusVec* statusVecPtr = getHwLoadStatuses();
            if (statusVecPtr == NULL) {
                std::cout<<"Unable to get HwLoadStatus vector! Pointer is NULL"<<std::endl;
                return false;
            }
            return (findAvailableHwLoadStatusIndex((*statusVecPtr)) >= 0);
        }

        virtual void updateAdminStates()
        {
            if (hasAnInactiveHwLoadStatus()) {
//% if executesPersonaDevices
                // Unlock all devices if there is capacity for more loads
                ${executeType.capitalize()}MapIter iter;
                for (iter = _${executeType}Map.begin(); iter != _${executeType}Map.end(); iter++) {
                    iter->second->adminState(CF::AdministratableInterface::UNLOCKED);
                }
//% endif
                setAdminState(CF::AdministratableInterface::UNLOCKED);
            } else {
/*{% if executesPersonaDevices %}*/
                // Lock all personas that are not loaded onto the device
                
                // Grab the current hw_load_status struct
                HwLoadStatusVec* statusVecPtr = getHwLoadStatuses();
                if (statusVecPtr == NULL) {
                    std::cout<<"Unable to get HwLoadStatus vector! Pointer is NULL"<<std::endl;
                    return;
                }

                // Grab all of the Requester Ids to compare against
                std::vector<std::string> allRequesterIds;
                allRequesterIds.resize(statusVecPtr->size());
                for (size_t ii = 0; ii < statusVecPtr->size(); ii++) {
                    allRequesterIds.push_back(statusVecPtr->at(ii).requester_id);
                }

                // Any persona that has a load running should not be locked
                ${executeType.capitalize()}MapIter iter;
                for (iter = _${executeType}Map.begin(); iter != _${executeType}Map.end(); iter++) {
                    if (strVecContainsStr(allRequesterIds, iter->first)) {
                        continue; // Skip the running ${executeType}s
                    }
                    iter->second->adminState(CF::AdministratableInterface::LOCKED);
                }
/*{% endif %}*/
                setAdminState(CF::AdministratableInterface::LOCKED);
            }
        }

    private:
        // Property pointers
        HwLoadRequestVec* _hwLoadRequestsPtr;
        HwLoadStatusVec*  _hwLoadStatusesPtr;

        // Default properties (incase child does not set own properties)
        HwLoadRequestVec  _defaultHwLoadRequests;
        HwLoadStatusVec   _defaultHwLoadStatuses;

        int findAvailableHwLoadStatusIndex(const HwLoadStatusVec& loadStatusVec)
        {
            // Initialize local variables
            int returnVal = -1;

            // Iterate through all statuses and look for an INACTIVE one
            for (size_t ii = 0; ii < loadStatusVec.size(); ii++) {
                if (loadStatusVec[ii].state == HW_LOAD::INACTIVE) {
                    returnVal = ii;
                    break;
                }
            }

            return returnVal;
        }

        static bool strVecContainsStr(StrVec& strVec, const std::string& value) {
            return std::find(strVec.begin(), strVec.end(), value) != strVec.end();
        }
        
        template <typename TYPE>
        TYPE* getPropertyPtr(TYPE* propertyPtr, TYPE* defaultProperty) {
            if (propertyPtr != NULL) return propertyPtr;
            return defaultProperty;
        }

//% endif
};

#endif // ${includeGuard}
