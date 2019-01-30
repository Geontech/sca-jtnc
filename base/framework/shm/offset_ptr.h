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

#ifndef OFFSET_PTR_HH
#define OFFSET_PTR_HH

#include <cstddef>

template <typename T>
inline T* offset_ptr(void* base, ptrdiff_t offset)
{
    char* ptr = reinterpret_cast<char*>(base);
    ptr += offset;
    return reinterpret_cast<T*>(ptr);
}

template <typename T>
inline const T* offset_ptr(const void* base, ptrdiff_t offset)
{
    const char* ptr = reinterpret_cast<const char*>(base);
    ptr += offset;
    return reinterpret_cast<const T*>(ptr);
}

#endif // OFFSET_PTR_HH
