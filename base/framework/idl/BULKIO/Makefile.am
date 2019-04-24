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
%SK.cpp %.h %DynSK.cpp : $(top_srcdir)/idl/sca/BULKIO/%.idl
	$(AM_V_GEN)$(IDL) -I $(IDLDIR) -I $(IDLDIR)/COS -I $(top_srcdir)/idl -bcxx -Wba -Wbd=DynSK.cpp -Wbh=.h -Wbs=SK.cpp -Wbkeep_inc_path $<
# omniORB uses the a ".hh" suffix for its COS header files, but omniidl doesn't
# know the difference, so we must modify generated headers to account for that.
	$(AM_V_at)$(SED) 's|<COS/\(.*\)\.h>|<COS/\1.hh>|' $*.h > $*.h.tmp
	$(AM_V_at)mv $*.h.tmp $*.h
	$(AM_V_at)mkdir -p ../../../include/sca/BULKIO
	$(AM_V_at)cp $*.h ../../../include/sca/BULKIO

clean-local:
	rm -f ../../include/sca/BULKIO/*.h

install-data-hook :
	touch $(DESTDIR)$(pkgincludedir)/BULKIO/*.h

BUILT_SOURCES =	bio_dataBitSK.cpp \
		bio_dataDoubleSK.cpp \
		bio_dataFloatSK.cpp \
		bio_dataLongLongSK.cpp \
		bio_dataSDDSSK.cpp \
		bio_dataUlongSK.cpp \
		bio_dataUshortSK.cpp \
		bio_dataXMLSK.cpp \
		bio_updateSRISK.cpp \
		bio_dataCharSK.cpp \
		bio_dataFileSK.cpp \
		bio_dataLongSK.cpp \
		bio_dataOctetSK.cpp \
		bio_dataShortSK.cpp \
		bio_dataUlongLongSK.cpp \
		bio_dataVITA49SK.cpp \
		bio_runtimeStatsSK.cpp \
		bulkioDataTypesSK.cpp \
		bio_dataExtSK.cpp \
		bio_dataExtDynSK.cpp \
		bio_dataBitDynSK.cpp \
		bio_dataDoubleDynSK.cpp \
		bio_dataFloatDynSK.cpp \
		bio_dataLongLongDynSK.cpp \
		bio_dataSDDSDynSK.cpp \
		bio_dataUlongDynSK.cpp \
		bio_dataUshortDynSK.cpp \
		bio_dataXMLDynSK.cpp \
		bio_updateSRIDynSK.cpp \
		bio_dataCharDynSK.cpp \
		bio_dataFileDynSK.cpp \
		bio_dataLongDynSK.cpp \
		bio_dataOctetDynSK.cpp \
		bio_dataShortDynSK.cpp \
		bio_dataUlongLongDynSK.cpp \
		bio_dataVITA49DynSK.cpp \
		bio_runtimeStatsDynSK.cpp \
		bulkioDataTypesDynSK.cpp

CLEANFILES = $(BUILT_SOURCES)

pkgconfigdir = $(libdir)/pkgconfig
dist_pkgconfig_DATA = bulkioInterfaces.pc

bulkioheaderdir = $(pkgincludedir)/BULKIO
dist_bulkioheader_HEADERS = bio_dataBit.h bio_dataExt.h bio_dataDouble.h bio_dataFloat.h bio_dataLongLong.h bio_dataSDDS.h bio_dataUlong.h bio_dataUshort.h bio_dataXML.h bio_updateSRI.h bio_dataChar.h bio_dataFile.h bio_dataLong.h bio_dataOctet.h bio_dataShort.h bio_dataUlongLong.h bio_dataVITA49.h bio_runtimeStats.h bulkioDataTypes.h

lib_LTLIBRARIES = libscabulkioidl.la
nodist_libscabulkioidl_la_SOURCES = $(BUILT_SOURCES)
libscabulkioidl_la_CXXFLAGS = -Wall -Wno-switch $(OMNIORB_CFLAGS) $(OMNICOS_CFLAGS) $(OMNITHREAD_CFLAGS) $(OMNIDYNAMIC_CFLAGS) -I../../../include -I../../../include/sca -I../../../include/sca/CF
libscabulkioidl_la_LIBADD = $(OMNIORB_LIBS) $(OMNITHREAD_LIBS) $(OMNIDYNAMIC_LIBS)
libscabulkioidl_la_LDFLAGS = -Wall -version-info $(LIBSCACF_VERSION_INFO)
