
/*{% from "mFunction/gpl.cpp" import gplHeader%}*/
${gplHeader(component)}

//% set className = component.userclass.name
//% set baseClass = component.baseclass.name
//% set includeGuard = component.userclass.name.upper() + '_IMPL_H'
#ifndef ${includeGuard}
#define ${includeGuard}

#include "${component.baseclass.header}"

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
    protected:
        int preProcess();
        int postProcess();
};


#endif // ${includeGuard}
