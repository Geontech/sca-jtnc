
/*{% block license %}*/
/*# Allow child templates to include license #*/
/*{% endblock %}*/
//% set className = component.reprogclass.name
//% set baseClass = component.baseclass.name
//% set includeGuard = baseClass.upper() + '_IMPL_REPROG_H'
#ifndef ${includeGuard}
#define ${includeGuard}

#include "${component.baseclass.header}"
//% if component is device
#include "sca/Device_impl.h"
//% if component is executabledevice
#include "sca/ExecutableDevice_impl.h"
#include "sca/prop_helpers.h"
#include "entry_point.h"
#include <dlfcn.h>

typedef std::string ResourceId;
typedef std::map<ResourceId, Resource_impl*> ResourceMap;
typedef ResourceMap::iterator ResourceMapIter;
typedef std::map<unsigned int, ResourceId> ProcessMap;
typedef ProcessMap::iterator ProcessMapIter;
//% endif
//% endif

class ${className};

class ${className} : public ${baseClass}
{
    ENABLE_LOGGING
    public:
//% if component is not device
        ${className}(const char *uuid, const char *label);
//% else
        ${className}(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl);
        ${className}(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl, char *compDev);
        ${className}(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl, CF::Properties capacities);
        ${className}(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl, CF::Properties capacities, char *compDev);
//% endif
        virtual void construct();
        virtual void setParentDevice(Device_impl* parentDevice) { _parentDevice = parentDevice; };
        virtual Device_impl* getParentDevice() { return _parentDevice; };

//% if component is device
        virtual void adminState(CF::Device::AdminType adminState) 
            throw (CORBA::SystemException);
//% if component is executabledevice
        virtual CF::ExecutableDevice::ProcessID_Type execute (const char* name, const CF::Properties& options, const CF::Properties& parameters)
            throw ( CF::ExecutableDevice::ExecuteFail, CF::InvalidFileName, CF::ExecutableDevice::InvalidOptions, 
                    CF::ExecutableDevice::InvalidParameters, CF::ExecutableDevice::InvalidFunction, CF::Device::InvalidState, 
                    CORBA::SystemException);
        virtual void terminate (CF::ExecutableDevice::ProcessID_Type processId) 
            throw ( CF::Device::InvalidState, CF::ExecutableDevice::InvalidProcess, CORBA::SystemException);
//% endif
        virtual void releaseObject() 
            throw (CF::LifeCycle::ReleaseError, CORBA::SystemException);

    protected:

        virtual void hwLoadRequest(CF::Properties& loadRequest)=0;
        virtual CORBA::Boolean attemptToProgramParent();
        virtual CORBA::Boolean attemptToUnprogramParent();

        // Lifecycle methods around the programming of parent/hardware
        //    These methods may be overriden to provide custom functionality
        //    at different stages in the lifecycle
        virtual void beforeHardwareProgrammed() {};
        virtual void afterHardwareProgramSuccess() {};
        virtual void afterHardwareProgramFailure() {};
        virtual void beforeHardwareUnprogrammed() {};
        virtual void afterHardwareUnprogrammed() {};

//% if component is executabledevice
        virtual bool hasRunningResources();
        virtual Resource_impl* generateResource(int argc, char* argv[], ConstructorPtr fnptr, const char* libraryName)=0;
//% endif

    private:
        Device_impl*            _parentDevice;
        bool                    _parentAllocated;
        CF::Properties          _previousRequestProps;
//% if component is executabledevice
        ResourceMap             _resourceMap;
        ProcessMap              _processMap;
        unsigned int            _processIdIncrement;

        Resource_impl* instantiateResource(const char* libraryName, const CF::Properties& options, const CF::Properties& parameters);
//% endif
//% endif
        virtual void formatRequestProps(const CF::Properties& requestProps, CF::Properties& formattedProps);
};

#endif // ${includeGuard}
