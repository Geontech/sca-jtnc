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

#ifndef ANYUTILS_H
#define ANYUTILS_H

#include <omniORB4/CORBA.h>
#include "sca/prop_helpers.h"

namespace sca {

    namespace any {

        // Returns true if an Any has no value (i.e., type is null).
        inline bool isNull (const CORBA::Any& any) {
            CORBA::TypeCode_var type = any.type();
            return (type->kind() == CORBA::tk_null);
        }

        // Numeric conversion of Any types, using standard C++ rules
        bool toBoolean (const CORBA::Any&);
        CORBA::Octet toOctet (const CORBA::Any&);
        CORBA::Short toShort (const CORBA::Any&);
        CORBA::UShort toUShort (const CORBA::Any&);
        CORBA::Long toLong (const CORBA::Any&);
        CORBA::ULong toULong (const CORBA::Any&);
        CORBA::LongLong toLongLong (const CORBA::Any&);
        CORBA::ULongLong toULongLong (const CORBA::Any&);
        CORBA::Float toFloat (const CORBA::Any&);
        CORBA::Double toDouble (const CORBA::Any&);

        bool toNumber (const CORBA::Any&, bool&);
        bool toNumber (const CORBA::Any&, CORBA::Octet&);
        bool toNumber (const CORBA::Any&, CORBA::Short&);
        bool toNumber (const CORBA::Any&, CORBA::UShort&);
        bool toNumber (const CORBA::Any&, CORBA::Long&);
        bool toNumber (const CORBA::Any&, CORBA::ULong&);
        bool toNumber (const CORBA::Any&, CORBA::LongLong&);
        bool toNumber (const CORBA::Any&, CORBA::ULongLong&);
        bool toNumber (const CORBA::Any&, CORBA::Float&);
        bool toNumber (const CORBA::Any&, CORBA::Double&);

    }; // namespace any

}; // namespace sca

#endif // ANYUTILS_H
