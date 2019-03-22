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
#ifndef PERSONAEXECUTABLEDEVICE_IMPL_REPROG_H
#define PERSONAEXECUTABLEDEVICE_IMPL_REPROG_H

#include "PersonaExecutableDevice_base.h"
#include "sca/DeviceComponent.h"
class PersonaExecutableDevice_persona_base;

class PersonaExecutableDevice_persona_base : public PersonaExecutableDevice_base
{
    ENABLE_LOGGING
    public:
        PersonaExecutableDevice_persona_base(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl);
        PersonaExecutableDevice_persona_base(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl, char *compDev);
        PersonaExecutableDevice_persona_base(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl, CF::Properties capacities);
        PersonaExecutableDevice_persona_base(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl, CF::Properties capacities, char *compDev);
        virtual void construct();
        virtual void setParentDevice(DeviceComponent* parentDevice) {
            _parentDevice = parentDevice;
        };
        virtual DeviceComponent* getParentDevice() { return _parentDevice; };
        virtual void adminState(CF::AdministratableInterface::AdminType adminState) 
            throw (CORBA::SystemException);
        virtual void releaseObject() 
            throw (CF::LifeCycle::ReleaseError, CORBA::SystemException);

    protected:

        virtual void hwLoadRequest(CF::Properties& loadRequest)=0;
        virtual CORBA::Boolean attemptToProgramParent();
        virtual CORBA::Boolean attemptToUnprogramParent();

        // Lifecycle methods around the programming of parent/hardware
        //    These methods may be overriden to provide custom functionality
        //    at different stages in the lifecycle
        virtual void beforeHardwareProgrammed() {};
        virtual void afterHardwareProgramSuccess() {};
        virtual void afterHardwareProgramFailure() {};
        virtual void beforeHardwareUnprogrammed() {};
        virtual void afterHardwareUnprogrammed() {};
    private:
        DeviceComponent*            _parentDevice;
        bool                    _parentAllocated;
        CF::Properties          _previousRequestProps;
        virtual void formatRequestProps(const CF::Properties& requestProps, CF::Properties& formattedProps);
};

#endif
