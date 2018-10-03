/*
 * This file is protected by Copyright. Please refer to the COPYRIGHT file 
 * distributed with this source distribution.
 * 
 * This file is part of REDHAWK core.
 * 
 * REDHAWK core is free software: you can redistribute it and/or modify it 
 * under the terms of the GNU Lesser General Public License as published by the 
 * Free Software Foundation, either version 3 of the License, or (at your 
 * option) any later version.
 * 
 * REDHAWK core is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License 
 * for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License 
 * along with this program.  If not, see http://www.gnu.org/licenses/.
 */


#ifndef BASICTESTDEVICE_CPP_IMPL1_IMPL_H
#define BASICTESTDEVICE_CPP_IMPL1_IMPL_H

#include <stdlib.h>
#include <string>
#include <map>
#include <list>

#include "sca/CF/CF.h"
#include "sca/CF/DeviceComponent.h"

#include "sca/DeviceComponent.h"

using namespace std;
#include <sys/time.h>
#include <queue>
#include <fstream>

class BasicTestDevice_cpp_impl1_i;
class BasicTestDevice_cpp_impl1_i :
    public virtual POA_CF::DeviceComponent, public DeviceComponent
{
    public:
        //BasicTestDevice_cpp_impl1_i(char *devMgr_ior, char *id, char *sftwrPrfl);
        BasicTestDevice_cpp_impl1_i(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl);
        //BasicTestDevice_cpp_impl1_i(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl, CF::Properties capacities);
        //BasicTestDevice_cpp_impl1_i(char *devMgr_ior, char *id, char *sftwrPrfl, char *compositeDev);
        BasicTestDevice_cpp_impl1_i(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl, char *compositeDev);
        //BasicTestDevice_cpp_impl1_i(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl, CF::Properties capacities, char *compositeDev);

        void initResource(char *devMgr_ior, char *id, char *sftwrPrfl);

        ~BasicTestDevice_cpp_impl1_i(void);

        CORBA::Boolean allocateCapacity (const CF::Properties & capacities)
                throw (CORBA::SystemException, CF::CapacityManagement::InvalidCapacity, CF::InvalidState);
        void deallocateCapacity (const CF::Properties & capacities)
                throw (CORBA::SystemException, CF::CapacityManagement::InvalidCapacity, CF::InvalidState);

        void releaseObject() throw (CF::LifeCycle::ReleaseError, CORBA::SystemException);

        // main omni_thread function
        void loadProperties();

    protected:
        CORBA::Long memCapacity;
        CORBA::Long BogoMipsCapacity;
        CORBA::Long propOne;
        CORBA::Long propTwo;

    //private:
        // For component shutdown
        /*string comp_uuid;

        string naming_service_name;

        // Threading stuff
        omni_mutex data_in_signal_lock;
        omni_mutex process_data_lock;
        omni_mutex attribute_access;    // used when modifying variables
        CF::DeviceSequence *devSeq;
        // Functional members
        // Housekeeping and data management variables

        bool thread_started;*/


};
#endif
