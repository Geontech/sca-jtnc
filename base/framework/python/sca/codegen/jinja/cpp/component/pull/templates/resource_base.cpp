
//% set baseClass = component.superclasses[0].name
//% set artifactType = component.artifacttype
//% set className = component.baseclass.name
/*{% block license %}*/
/*# Allow child templates to include license #*/
/*{% endblock %}*/
/*{% block includes %}*/
#include "${component.baseclass.header}"
/*{% endblock %}*/
/*{% block includeExtentions %}*/
/*# Allow for child template extensions #*/
/*{% endblock %}*/

/*{% block headerComment %}*/
/*******************************************************************************************

    AUTO-GENERATED CODE. DO NOT MODIFY

    The following class functions are for the base class for the ${artifactType} class. To
    customize any of these functions, do not modify them here. Instead, overload them
    on the child class

******************************************************************************************/
/*{% endblock %}*/

/*{% if component is device %}*/
${className}::${className}(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl) :
    ${baseClass}(devMgr_ior, id, lbl, sftwrPrfl),
/*{% if component is aggregatedevice %}*/
    AggregateDevice_impl(),
/*{% endif %}*/
    ThreadedComponent()
{
    construct();
}

${className}::${className}(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl, char *compDev) :
    ${baseClass}(devMgr_ior, id, lbl, sftwrPrfl, compDev),
/*{% if component is aggregatedevice %}*/
    AggregateDevice_impl(),
/*{% endif %}*/
    ThreadedComponent()
{
    construct();
}

${className}::${className}(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl, CF::Properties capacities) :
    ${baseClass}(devMgr_ior, id, lbl, sftwrPrfl, capacities),
/*{% if component is aggregatedevice %}*/
    AggregateDevice_impl(),
/*{% endif %}*/
    ThreadedComponent()
{
    construct();
}

${className}::${className}(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl, CF::Properties capacities, char *compDev) :
    ${baseClass}(devMgr_ior, id, lbl, sftwrPrfl, capacities, compDev),
/*{% if component is aggregatedevice %}*/
    AggregateDevice_impl(),
/*{% endif %}*/
    ThreadedComponent()
{
    construct();
}
/*{% else %}*/
/*{% block componentConstructor %}*/
${className}::${className}(const char *uuid, const char *label) :
    ${baseClass}(uuid, label),
    ThreadedComponent()
{
    setThreadName(label);

/*{% block constructorBody %}*/
    loadProperties();
/*{% for port in component.ports %}*/
/*{%   if loop.first %}*/

/*{%   endif %}*/
    ${port.cppname} = new ${port.constructor};
/*{%   if port.hasDescription %}*/
    addPort("${port.name}", "${port.description}", ${port.cppname});
/*{%   else %}*/
    addPort("${port.name}", ${port.cppname});
/*{%   endif %}*/
/*{%   if port.name == 'propEvent' %}*/
/*{%     for property in component.events %}*/
    ${port.cppname}->registerProperty(this->_identifier, this->naming_service_name, this->getPropertyFromId("${property.identifier}"));
/*{%     endfor %}*/
    this->registerPropertyChangePort(${port.cppname});
/*{%   endif %}*/
/*{% endfor %}*/
/*{% if component.hasmultioutport %}*/

    this->addPropertyListener(connectionTable, this, &${className}::connectionTableChanged);
/*{% endif %}*/
/*{% endblock %}*/
}
/*{% endblock %}*/
/*{% endif %}*/

${className}::~${className}()
{
/*{% block destructorBody %}*/
/*{% for port in component.ports %}*/
    ${port.cppname}->_remove_ref();
    ${port.cppname} = 0;
/*{% endfor %}*/
/*{% endblock %}*/
}

/*{% if component is device %}*/
void ${className}::construct()
{
/*# Devices have multiple constructors; rather than duplicate the code, the
 *# constructor body is placed in the construct() method. #*/
${self.constructorBody()}
}

/*{% endif %}*/
/*******************************************************************************************
    Framework-level functions
    These functions are generally called by the framework to perform housekeeping.
*******************************************************************************************/
/*{% block start %}*/
void ${className}::start() throw (CORBA::SystemException, CF::ControllableInterface::StartError)
{
    ${baseClass}::start();
    ThreadedComponent::startThread();
}
/*{% endblock %}*/

/*{% block stop %}*/
void ${className}::stop() throw (CORBA::SystemException, CF::ControllableInterface::StopError)
{
    ${baseClass}::stop();
    if (!ThreadedComponent::stopThread()) {
        throw CF::Resource::StopError(CF::CF_NOTSET, "Processing thread did not die");
    }
}
/*{% endblock %}*/

/*{% block releaseObject %}*/
void ${className}::releaseObject() throw (CORBA::SystemException, CF::LifeCycle::ReleaseError)
{
    // This function clears the ${artifactType} running condition so main shuts down everything
    try {
        stop();
    } catch (CF::Resource::StopError& ex) {
        // TODO - this should probably be logged instead of ignored
    }

    ${baseClass}::releaseObject();
}
/*{% endblock %}*/

/*{% if component.hasmultioutport %}*/
void ${className}::connectionTableChanged(const std::vector<connection_descriptor_struct>* oldValue, const std::vector<connection_descriptor_struct>* newValue)
{
/*{%   for port in component.ports if port.multiout %}*/
    ${port.cppname}->updateConnectionFilter(*newValue);
/*{%   endfor %}*/
}

/*{% endif %}*/
/*{% block loadProperties %}*/
/*{% from "properties/properties.cpp" import addproperty, initsequence, initializestructseq %}*/
void ${className}::loadProperties()
{
/*{% for prop in component.properties %}*/
//%    if prop.cppvalues and prop is not structsequence
    ${initsequence(prop)|indent(4)}
//%    endif
/*{%   if not prop.inherited %}*/
    ${addproperty(prop)|indent(4)}

/*{%   elif prop.cppvalue %}*/
    ${prop.cppname} = ${prop.cppvalue};
/*{%   endif %}*/
//%    if prop.cppvalues and prop is structsequence
${initializestructseq(prop)}
/*{%   endif %}*/
/*{% endfor %}*/
}
/*{% endblock %}*/

/*{% block extensions %}*/
/*# Allow for child class extensions #*/
/*{% endblock %}*/
