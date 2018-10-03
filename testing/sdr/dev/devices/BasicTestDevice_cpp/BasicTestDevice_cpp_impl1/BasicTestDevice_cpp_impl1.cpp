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

  

#include "BasicTestDevice_cpp_impl1.h"

BasicTestDevice_cpp_impl1_i::BasicTestDevice_cpp_impl1_i(char *devMgr_ior, char *id, char *label, char *sftwrPrfl) :
          DeviceComponent (devMgr_ior, id, label, sftwrPrfl) {
    initResource(devMgr_ior, id, sftwrPrfl);
};


BasicTestDevice_cpp_impl1_i::BasicTestDevice_cpp_impl1_i(char *devMgr_ior, char *id, char *label, char *sftwrPrfl, char *compDev) :
          DeviceComponent (devMgr_ior, id, label, sftwrPrfl, compDev) {
    initResource(devMgr_ior, id, sftwrPrfl);
};

void BasicTestDevice_cpp_impl1_i::initResource(char *devMgr_ior, char *id, char *sftwrPrfl) 
{
    loadProperties();
    this->profile = "/devices/BasicTestDevice_cpp_impl/BasicTestDevice_cpp_impl.spd.xml";
    //thread_started = false;
};
      
BasicTestDevice_cpp_impl1_i::~BasicTestDevice_cpp_impl1_i() {
};

CORBA::Boolean BasicTestDevice_cpp_impl1_i::allocateCapacity (const CF::Properties & capacities)
    throw (CORBA::SystemException, CF::CapacityManagement::InvalidCapacity, CF::InvalidState) 
{
    
    /*bool response = true;
    std::string tmp;
    PropertyInterface *pCptr;

    for (unsigned int i = 0; i < capacities.length(); i++) {
        tmp = capacities[i].id;
        pCptr = getPropertyFromId(tmp);
        if (!pCptr) {
            response = false;
            break;
        } else if (pCptr->compare(capacities[i].value) > 0) {
            response = false;
            break;
        }
    }
    if (!response) {
        return false;
    }
        
    for (unsigned int i = 0; i < capacities.length(); i++) {
        tmp = capacities[i].id;
        pCptr = getPropertyFromId(tmp);
        pCptr->decrement(capacities[i].value);
    }*/
    return true;
}

void BasicTestDevice_cpp_impl1_i::deallocateCapacity (const CF::Properties & capacities)
    throw (CORBA::SystemException, CF::CapacityManagement::InvalidCapacity, CF::InvalidState) 
{

    /*std::string tmp;
    PropertyInterface *pCptr;

    for (unsigned int i=0; i<capacities.length(); i++) {
        tmp = capacities[i].id;
        pCptr = getPropertyFromId(tmp);
        if (!pCptr) {
            continue;
        }
        pCptr->increment(capacities[i].value);
    }*/
}
