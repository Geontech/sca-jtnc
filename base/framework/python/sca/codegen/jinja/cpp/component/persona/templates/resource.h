
/*{% block license %}*/
/*# Allow child templates to include license #*/
/*{% endblock %}*/
//% set className = component.userclass.name 
//% set baseClass = component.reprogclass.name if component is device else component.baseclass.name
//% set includeGuard = className.upper() + '_IMPL_H'
#ifndef ${includeGuard}
#define ${includeGuard}

/*{% if component is device %}*/
#include "${component.reprogclass.header}"
/*{% else %}*/
#include "${component.baseclass.header}"
#include "DeviceComponent.h"
/*{% endif %}*/

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

        ~${className}();
        int serviceFunction();
//% if component is device
        CORBA::Boolean allocateCapacity(const CF::Properties& capacities) 
            throw (CF::Device::InvalidState, CF::Device::InvalidCapacity, CF::Device::InsufficientCapacity, CORBA::SystemException);
        void deallocateCapacity(const CF::Properties& capacities) 
            throw (CF::Device::InvalidState, CF::Device::InvalidCapacity, CORBA::SystemException);

    protected:
        void hwLoadRequest(CF::Properties& request);

//% else 
        virtual void setParentDevice(DeviceComponent* parentDevice) { _parentDevice = parentDevice; };
        virtual DeviceComponent* getParentDevice() { return _parentDevice; };
    
    private:
        DeviceComponent* _parentDevice;
//% endif

//% if component is executabledevice
    private:
        Resource_impl* generateResource(int argc, char* argv[], ConstructorPtr fnptr, const char* libName);
//% endif
};

#endif // ${includeGuard}
