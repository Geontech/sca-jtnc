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
#ifndef PERSONAEXECUTABLEDEVICE_IMPL_H
#define PERSONAEXECUTABLEDEVICE_IMPL_H

#include "PersonaExecutableDevice_persona_base.h"

class PersonaExecutableDevice_i;

class PersonaExecutableDevice_i : public PersonaExecutableDevice_persona_base
{
    ENABLE_LOGGING
    public:
        PersonaExecutableDevice_i(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl);
        PersonaExecutableDevice_i(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl, char *compDev);
        PersonaExecutableDevice_i(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl, CF::Properties capacities);
        PersonaExecutableDevice_i(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl, CF::Properties capacities, char *compDev);
        ~PersonaExecutableDevice_i();
        int serviceFunction();
        CORBA::Boolean allocateCapacity(const CF::Properties& capacities) 
            throw (CF::InvalidState, CF::CapacityManagement::InvalidCapacity, CORBA::SystemException);
        void deallocateCapacity(const CF::Properties& capacities) 
            throw (CF::InvalidState, CF::CapacityManagement::InvalidCapacity, CORBA::SystemException);

    protected:
        void hwLoadRequest(CF::Properties& request);
};

#endif