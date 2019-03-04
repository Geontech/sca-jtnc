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

#include "PersonaDevice.h"

PersonaDevice_i *devicePtr;

/*void signal_catcher(int sig)
{
    // IMPORTANT Don't call exit(...) in this function
    // issue all CORBA calls that you need for cleanup here before calling ORB shutdown
    if (devicePtr) {
        devicePtr->halt();
    }
}
int main(int argc, char* argv[])
{
    std::cout<<"================ main begin"<<std::endl;
    struct sigaction sa;
    sa.sa_handler = signal_catcher;
    sa.sa_flags = 0;
    devicePtr = 0;

    DeviceComponent::start_device(&devicePtr, sa, argc, argv);
    std::cout<<"================ main end"<<std::endl;
    return 0;
}
*/
extern "C" {
    DeviceComponent* construct(int argc, char* argv[], DeviceComponent* parentDevice) {

std::cout<<"------------- persona construct (1)"<<std::endl;
        struct sigaction sa;
        /*sa.sa_handler = signal_catcher;
        sa.sa_flags = 0;*/
        devicePtr = 0;
std::cout<<"------------- persona construct (2)"<<std::endl;

        //DeviceComponent::start_device(&devicePtr, sa, argc, argv);
        DeviceComponent::start_lib_device(&devicePtr, sa, argc, argv);
std::cout<<"------------- persona construct (3)"<<std::endl;

        // Any addition parameters passed into construct can now be
        // set directly onto devicePtr since it is the instantiated
        // Redhawk device
        //      Example:
        //         devicePtr->setSharedAPI(sharedAPI);
        devicePtr->setParentDevice(parentDevice);
std::cout<<"------------- persona construct (4)"<<std::endl;

        return devicePtr;
    }
}

