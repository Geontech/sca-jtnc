#include <iostream>
#include "sca/scaSupport.h"

#include "alloc_shm.h"
extern "C" {
    ResourceComponent* make_component(const std::string& uuid, const std::string& identifier)
    {
        return new alloc_shm_i(uuid.c_str(), identifier.c_str());
    }
}

