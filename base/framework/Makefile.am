#
# This file is protected by Copyright. Please refer to the COPYRIGHT file 
# distributed with this source distribution.
# 
# This file is part of SCA-JTNC core.
# 
# SCA-JTNC core is free software: you can redistribute it and/or modify it under 
# the terms of the GNU Lesser General Public License as published by the Free 
# Software Foundation, either version 3 of the License, or (at your option) any 
# later version.
# 
# SCA-JTNC core is distributed in the hope that it will be useful, but WITHOUT 
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS 
# FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
# details.
# 
# You should have received a copy of the GNU Lesser General Public License 
# along with this program.  If not, see http://www.gnu.org/licenses/.
#

AM_CPPFLAGS = -I../include -I../include/sca/CF

lib_LTLIBRARIES = libscacf.la
libscacf_la_SOURCES = ModuleLoader.cpp ResourceComponent.cpp DeviceComponent.cpp bitbuffer.cpp bitops.cpp BufferManager.cpp AggregateDeviceComponent.cpp helperFunctions.cpp UsesPort.cpp Port_impl.cpp Transport.cpp ProvidesPort.cpp CorbaUtils.cpp ThreadedComponent.cpp PropertyInterface.cpp PropertySet_impl.cpp prop_helpers.cpp PropertyMap.cpp Value.cpp AnyUtils.cpp PropertyType.cpp type_traits.cpp shm/Allocator.cpp  shm/HeapClient.cpp  shm/Heap.cpp  shm/MappedFile.cpp  shm/Superblock.cpp  shm/SuperblockFile.cpp  shm/System.cpp

libscacf_la_CXXFLAGS = -Wall $(BOOST_CPPFLAGS) $(OMNICOS_CFLAGS) $(OMNIORB_CFLAGS) $(LOG4CXX_FLAGS)
# Include the omniORB internal directory, otherwise CorbaUtils will not build
libscacf_la_CXXFLAGS +=-I$(OMNIORB_INCLUDEDIR)/omniORB4/internal
libscacf_la_LIBADD = $(BOOST_LDFLAGS) $(BOOST_FILESYSTEM_LIB) $(BOOST_SERIALIZATION_LIB) $(BOOST_THREAD_LIB) $(BOOST_SYSTEM_LIB) $(OMNICOS_LIBS) $(OMNIORB_LIBS) $(LOG4CXX_LIBS) -ldl -lrt
libscacf_la_LDFLAGS = -Wall -version-info $(LIBSCACF_VERSION_INFO)
