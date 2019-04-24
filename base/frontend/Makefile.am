#
# This file is protected by Copyright. Please refer to the COPYRIGHT file
# distributed with this source distribution.
#
# This file is part of SCA-JTNC frontendInterfaces.
#
# SCA-JTNC frontendInterfaces is free software: you can redistribute it and/or modify it under
# the terms of the GNU Lesser General Public License as published by the Free
# Software Foundation, either version 3 of the License, or (at your option) any
# later version.
#
# SCA-JTNC frontendInterfaces is distributed in the hope that it will be useful, but WITHOUT
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
pkgconfig_DATA = frontend.pc

## Place generated object files (.o) into the same directory as their source
## files, in order to avoid collisions when non-recursive make is used.
AUTOMAKE_OPTIONS = subdir-objects

## Additional flags to pass to aclocal when it is invoked automatically at
## make time. The ${ACLOCAL_FLAGS} variable is picked up from the environment
## to provide a way for the user to supply additional arguments.
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

lib_LTLIBRARIES = libfrontend-@FRONTEND_API_VERSION@.la
libfrontend_@FRONTEND_API_VERSION@_la_LDFLAGS = -version-info $(FRONTEND_SO_VERSION)

libfrontend_@FRONTEND_API_VERSION@_la_SOURCES = \
    cpp/fe_port_impl.cpp \
    cpp/fe_rfsource_port_impl.cpp \
    cpp/fe_tuner_device.cpp

## Define the list of public header files and their install location.
library_includedir = $(includedir)/frontend
library_include_HEADERS = \
	cpp/fe_gps_port_impl.h \
	cpp/fe_navdata_port_impl.h \
	cpp/fe_port_impl.h \
	cpp/fe_rfinfo_port_impl.h \
	cpp/fe_rfsource_port_impl.h \
	cpp/fe_tuner_device.h \
        cpp/fe_tuner_device.cpp \
	cpp/fe_tuner_port_impl.h \
	cpp/fe_tuner_struct_props.h \
	cpp/frontend.h \
	cpp/fe_types.h

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
#frontend_libincludedir = $(libdir)/frontend-$(FRONTEND_API_VERSION)/include

libfrontend_@FRONTEND_API_VERSION@_la_CXXFLAGS = -Wall -I../base/include -I../base/include/sca/CF -I$(top_builddir)/base/include -I$(top_builddir)/base/include/sca/CF  -I$(top_builddir)/base/bulkio/cpp/include -I $(srcdir)/cpp -DLOGGING $(FRONTEND_INF_INCLUDES) $(BOOST_CPPFLAGS) $(OMNIORB_CFLAGS) $(OSSIE_CFLAGS)

libfrontend_@FRONTEND_API_VERSION@_la_LIBADD =  $(top_builddir)/base/framework/idl/FRONTEND/libscafrontendidl.la

###############################################################################
# General
#

.PHONY: install-python clean-python reallyclean

install-exec-hook: install-python

clean-local: clean-python

reallyclean: distclean
	rm -f Makefile.in

