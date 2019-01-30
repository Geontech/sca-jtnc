#
# This file is protected by Copyright. Please refer to the COPYRIGHT file
# distributed with this source distribution.
#
# This file is part of SCA-JTNC bulkioInterfaces.
#
# SCA-JTNC bulkioInterfaces is free software: you can redistribute it and/or modify it under
# the terms of the GNU Lesser General Public License as published by the Free
# Software Foundation, either version 3 of the License, or (at your option) any
# later version.
#
# SCA-JTNC bulkioInterfaces is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
# details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see http://www.gnu.org/licenses/.
#
###############################################################################
# C++ (via automake and libtool)
pkgconfigdir = $(libdir)/pkgconfig
# pkgconfig_DATA = bulkio.pc

## Place generated object files (.o) into the same directory as their source
## files, in order to avoid collisions when non-recursive make is used.
AUTOMAKE_OPTIONS = subdir-objects

## Additional flags to pass to aclocal when it is invoked automatically at
## make time. The ${ACLOCAL_FLAGS} variable is picked up from the environment
## to provide a way for the user to supply additional arguments.
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

lib_LTLIBRARIES = libbulkio-@BULKIO_API_VERSION@.la
libbulkio_@BULKIO_API_VERSION@_la_LDFLAGS = -version-info $(BULKIO_SO_VERSION)

libbulkio_@BULKIO_API_VERSION@_la_SOURCES = \
    cpp/bulkio.cpp \
    cpp/bulkio_in_port.cpp \
    cpp/bulkio_in_stream.cpp \
    cpp/bulkio_out_port.cpp \
    cpp/bulkio_out_stream.cpp \
    cpp/bulkio_attachable_port.cpp \
    cpp/bulkio_sri_helpers.cpp \
    cpp/bulkio_stream.cpp \
    cpp/bulkio_time_helpers.cpp \
    cpp/bulkio_time_operators.cpp \
    cpp/bulkio_datablock.cpp \
    cpp/bulkio_p.h \
    cpp/BulkioTransport.cpp \
    cpp/CorbaTransport.h \
    cpp/CorbaTransport.cpp \
    cpp/LocalTransport.h \
    cpp/LocalTransport.cpp \
    cpp/shm/FifoIPC.h \
    cpp/shm/FifoIPC.cpp \
    cpp/shm/MessageBuffer.h \
    cpp/shm/ShmInputTransport.h \
    cpp/shm/ShmInputTransport.cpp \
    cpp/shm/ShmOutputTransport.h \
    cpp/shm/ShmOutputTransport.cpp \
    cpp/shm/ShmTransportFactory.cpp

## Define the list of public header files and their install location.
library_includedir = $(includedir)/bulkio
library_include_HEADERS = cpp/include/bulkio/bulkio.h \
	cpp/include/bulkio/BULKIO_Interfaces.h \
	cpp/include/bulkio/BulkioTransport.h \
	cpp/include/bulkio/bulkio_base.h \
	cpp/include/bulkio/bulkio_callbacks.h \
	cpp/include/bulkio/bulkio_traits.h \
	cpp/include/bulkio/bulkio_in_port.h \
	cpp/include/bulkio/bulkio_in_stream.h \
	cpp/include/bulkio/bulkio_out_port.h \
	cpp/include/bulkio/bulkio_out_stream.h \
	cpp/include/bulkio/bulkio_attachable_base.h \
	cpp/include/bulkio/bulkio_stream.h \
	cpp/include/bulkio/bulkio_time_operators.h \
	cpp/include/bulkio/bulkio_datablock.h \
	cpp/include/bulkio/bulkio_datatransfer.h \
	cpp/include/bulkio/bulkio_typetraits.h \
	cpp/include/bulkio/bulkio_compat.h

## The generated configuration header is installed in its own subdirectory of
## $(libdir).  The reason for this is that the configuration information put
## into this header file describes the target platform the installed library
## has been built for.  Thus the file must not be installed into a location
## intended for architecture-independent files, as defined by the Filesystem
## Hierarchy Standard (FHS).
## The nodist_ prefix instructs Automake to not generate rules for including
## the listed files in the distribution on 'make dist'.  Files that are listed
## in _HEADERS variables are normally included in the distribution, but the
## configuration header file is generated at configure time and should not be
## shipped with the source tarball.
#bulkio_libincludedir = $(libdir)/bulkio-$(BULKIO_API_VERSION)/include

libbulkio_@BULKIO_API_VERSION@_la_CXXFLAGS = -Wall -I -I../base/include -I../base/include/sca/CF -I$(top_builddir)/base/include -I$(top_builddir)/base/include/sca/CF -I$(srcdir)/cpp -I $(srcdir)/cpp/include/bulkio -DLOGGING $(BULKIOINTERFACES_CFLAGS) $(BOOST_CPPFLAGS) $(OMNIORB_CFLAGS) $(OSSIE_CFLAGS)

libbulkio_@BULKIO_API_VERSION@_la_LIBADD = $(top_builddir)/base/framework/idl/BULKIO/libscabulkioidl.la

###############################################################################
# General
#

.PHONY: install-python clean-python reallyclean

install-exec-hook: install-python

clean-local: clean-python

reallyclean: distclean
	rm -f Makefile.in
