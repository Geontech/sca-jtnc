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

#include "ShmVisitor.h"

#include <sys/types.h>
#include <dirent.h>

#include <ossie/shm/System.h>

using redhawk::shm::SuperblockFile;

void ShmVisitor::visit()
{
    std::string shmdir = redhawk::shm::getSystemPath();
    DIR* dir = opendir(shmdir.c_str());
    if (!dir) {
        throw std::runtime_error("could not open shm filesystem " + shmdir);
    }

    while (struct dirent* entry = readdir(dir)) {
        const std::string filename = entry->d_name;
        if ((filename == ".") || (filename == "..")) {
            continue;
        }

        if (SuperblockFile::IsSuperblockFile(filename)) {
            SuperblockFile file(filename);
            try {
                file.open(false);
            } catch (const std::exception& exc) {
                heapException(filename, exc);
                continue;
            }
            visitHeap(file);
        } else {
            visitFile(filename);
        }
    }

    closedir(dir);
}
