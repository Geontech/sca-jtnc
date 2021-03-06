#include "alloc_shm_base.h"

/*******************************************************************************************

    AUTO-GENERATED CODE. DO NOT MODIFY

    The following class functions are for the base class for the component class. To
    customize any of these functions, do not modify them here. Instead, overload them
    on the child class

******************************************************************************************/

alloc_shm_base::alloc_shm_base(const char *uuid, const char *label) :
    ResourceComponent(uuid, label),
    ThreadedComponent()
{
    setThreadName(label);

    loadProperties();
}

alloc_shm_base::~alloc_shm_base()
{
}

/*******************************************************************************************
    Framework-level functions
    These functions are generally called by the framework to perform housekeeping.
*******************************************************************************************/
void alloc_shm_base::start() throw (CORBA::SystemException, CF::ControllableInterface::StartError)
{
    ResourceComponent::start();
    ThreadedComponent::startThread();
}

void alloc_shm_base::stop() throw (CORBA::SystemException, CF::ControllableInterface::StopError)
{
    ResourceComponent::stop();
    if (!ThreadedComponent::stopThread()) {
        throw CF::ControllableInterface::StopError(CF::CF_NOTSET, "Processing thread did not die");
    }
}

void alloc_shm_base::releaseObject() throw (CORBA::SystemException, CF::LifeCycle::ReleaseError)
{
    // This function clears the component running condition so main shuts down everything
    try {
        stop();
    } catch (CF::ControllableInterface::StopError& ex) {
        // TODO - this should probably be logged instead of ignored
    }

    ResourceComponent::releaseObject();
}

void alloc_shm_base::loadProperties()
{
}


