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

# vim: noet: softtabstop=0
%SK.cpp %.h %DynSK.cpp : $(top_srcdir)/idl/sca/FRONTEND/%.idl
	$(AM_V_GEN)$(IDL) -I $(IDLDIR) -I $(IDLDIR)/COS -I $(top_srcdir)/idl -bcxx -Wba -Wbd=DynSK.cpp -Wbh=.h -Wbs=SK.cpp -Wbkeep_inc_path $<
# omniORB uses the a ".hh" suffix for its COS header files, but omniidl doesn't
# know the difference, so we must modify generated headers to account for that.
	$(AM_V_at)$(SED) 's|<COS/\(.*\)\.h>|<COS/\1.hh>|' $*.h > $*.h.tmp
	$(AM_V_at)mv $*.h.tmp $*.h
	$(AM_V_at)mkdir -p ../../../include/sca/FRONTEND
	$(AM_V_at)cp $*.h ../../../include/sca/FRONTEND

clean-local:
	rm -f ../../include/sca/FRONTEND/*.h

install-data-hook :
	touch $(DESTDIR)$(pkgincludedir)/FRONTEND/*.h

BUILT_SOURCES =	FrontendSK.cpp \
    FrontendDynSK.cpp \
    Frontend.h \
    GPSSK.cpp \
    GPSDynSK.cpp \
    GPS.h \
    NavigationDataSK.cpp \
    NavigationDataDynSK.cpp \
    NavigationData.h \
    RFInfoSK.cpp \
    RFInfoDynSK.cpp \
    RFInfo.h \
    TunerControlSK.cpp \
    TunerControlDynSK.cpp \
    TunerControl.h

CLEANFILES = $(BUILT_SOURCES)

pkgconfigdir = $(libdir)/pkgconfig
dist_pkgconfig_DATA = frontendInterfaces.pc

frontendheaderdir = $(pkgincludedir)/FRONTEND
dist_frontendheader_HEADERS = Frontend.h GPS.h NavigationData.h RFInfo.h TunerControl.h

lib_LTLIBRARIES = libscafrontendidl.la
nodist_libscafrontendidl_la_SOURCES = $(BUILT_SOURCES)
libscafrontendidl_la_CXXFLAGS = -Wall -Wno-switch $(OMNIORB_CFLAGS) $(OMNICOS_CFLAGS) $(OMNITHREAD_CFLAGS) $(OMNIDYNAMIC_CFLAGS) -I../../../include -I../../../include/sca -I../../../include/sca/CF -I../../../include/sca/BULKIO
libscafrontendidl_la_LIBADD = $(BULKIO_LIBS) $(SCA_LIBS)
libscafrontendidl_la_LDFLAGS = -Wall -version-info $(LIBSCACF_VERSION_INFO)
