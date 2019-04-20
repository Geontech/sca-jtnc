
/*{% extends "base/main.cpp" %}*/

/*{% block main %}*/
${super()}
/*{% if component is device %}*/
extern "C" {
    DeviceComponent* construct(int argc, char* argv[], DeviceComponent* parentDevice) {

        struct sigaction sa;
        sa.sa_handler = signal_catcher;
        sa.sa_flags = 0;
        devicePtr = 0;

        DeviceComponent::start_device(&devicePtr, sa, argc, argv);

        // Any addition parameters passed into construct can now be
        // set directly onto devicePtr since it is the instantiated
        // Redhawk device
        //      Example:
        //         devicePtr->setSharedAPI(sharedAPI);
        devicePtr->setParentDevice(parentDevice);

        return devicePtr;
    }
}
/*{% else %}*/
/*{% set servant = component.basename + '_servant' %}*/
extern "C" {
    Resource_impl* construct(int argc, char* argv[], DeviceComponent* parentDevice) {

        ${component.userclass.name}* ${servant};
        Resource_impl::start_component(${servant}, argc, argv);

        // Any addition parameters passed into construct can now be
        // set directly onto component_servant since it is the instantiated
        // Redhawk component
        //      Example:
        //         component_servant->setSharedAPI(sharedAPI);
        ${servant}->setParentDevice(parentDevice);

        return ${servant};
    }
}
/*{% endif %}*/
/*{% endblock %}*/
