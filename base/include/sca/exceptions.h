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

#ifndef SCA_EXCEPTIONS_H
#define SCA_EXCEPTIONS_H

#include <stdexcept>

namespace sca {

    // Exception type for unimplemented user functions
    class not_implemented_error : public std::logic_error {
    public:
        not_implemented_error (const std::string& msg) :
            std::logic_error(msg)
        {
        }
    };

}

#endif // SCA_EXCEPTIONS_H
