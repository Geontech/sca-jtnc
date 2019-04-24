
/*{% block license %}*/
/*# Allow child templates to include license #*/
/*{% endblock %}*/
/*{% block includes %}*/
#include <iostream>
#include "sca/scaSupport.h"

#include "${component.userclass.header}"
/*{% endblock %}*/
/*{% block main %}*/
/*{% if component is device %}*/
/*{% if not component.impl.module %}*/

${component.userclass.name} *devicePtr;

void signal_catcher(int sig)
{
    // IMPORTANT Don't call exit(...) in this function
    // issue all CORBA calls that you need for cleanup here before calling ORB shutdown
    if (devicePtr) {
        devicePtr->halt();
    }
}
/*{% endif %}*/
/*{% endif %}*/
/*{% if not component is device and component.impl.module %}*/
extern "C" {
    ResourceComponent* make_component(const std::string& uuid, const std::string& identifier)
    {
        return new ${component.userclass.name}(uuid.c_str(), identifier.c_str());
    }
}
/*{% else %}*/
/*{% if not component.impl.module %}*/
int main(int argc, char* argv[])
{
/*{% if component is device %}*/
    struct sigaction sa;
    sa.sa_handler = signal_catcher;
    sa.sa_flags = 0;
    devicePtr = 0;

    DeviceComponent::start_device(&devicePtr, sa, argc, argv);
/*{% else %}*/
/*{%   set servant = component.basename + '_servant' %}*/
    ${component.userclass.name}* ${servant};
    Component::start_component(${servant}, argc, argv);
/*{% endif %}*/
    return 0;
}
/*{% endif %}*/
/*{% endif %}*/
/*{% endblock %}*/
