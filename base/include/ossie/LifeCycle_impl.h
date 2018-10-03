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


#ifndef LIFECYCLE_IMPL_H
#define LIFECYCLE_IMPL_H

#include "CF/cf.h"
#include "ossie/Autocomplete.h"


/*
The LifeCycle interface defines generic operations for component
initialization and and releasing instantiated objects.

 */

class LifeCycle_impl
#ifdef BEGIN_AUTOCOMPLETE_IGNORE
    : public virtual POA_CF::LifeCycle
#endif
{
public:
    LifeCycle_impl () {
    };

    // Override this method with component specific initialization.
    void initialize ()
    throw (CF::LifeCycle::InitializeError, CORBA::SystemException);

    // Override this method with the code require to release the object.
    void releaseObject ()
    throw (CF::LifeCycle::ReleaseError, CORBA::SystemException);

};
#endif                                            /*  */
