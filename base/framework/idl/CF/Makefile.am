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
%SK.cpp %.h %DynSK.cpp : $(top_srcdir)/idl/sca/CF/%.idl
	$(AM_V_GEN)$(IDL) -I $(IDLDIR) -I $(IDLDIR)/COS -I $(top_srcdir)/idl -bcxx -Wba -Wbd=DynSK.cpp -Wbh=.h -Wbs=SK.cpp -Wbkeep_inc_path $<
# omniORB uses the a ".hh" suffix for its COS header files, but omniidl doesn't
# know the difference, so we must modify generated headers to account for that.
	$(AM_V_at)$(SED) 's|<COS/\(.*\)\.h>|<COS/\1.hh>|' $*.h > $*.h.tmp
	$(AM_V_at)mv $*.h.tmp $*.h
	$(AM_V_at)mkdir -p ../../../include/sca/CF
	$(AM_V_at)cp $*.h ../../../include/sca/CF

clean-local:
	rm -f ../../include/sca/CF/*.h

install-data-hook :
	touch $(DESTDIR)$(pkgincludedir)/CF/*.h

BUILT_SOURCES =	CFAdministratableInterfaceSK.cpp \
		CFCharSeqSK.cpp \
		CFDeviceAttributesSK.cpp \
		CFFileManagerSK.cpp \
		CFLongLongSeqSK.cpp \
		CFPropertiesSK.cpp \
		CFULongLongSeqSK.cpp \
		CFAggregateDeviceAttributesSK.cpp \
		CFCommonTypesSK.cpp \
		CFDomainInstallationSK.cpp \
		CFFileSystemSK.cpp \
		CFLongSeqSK.cpp \
		CFPropertySetSK.cpp \
		CFULongSeqSK.cpp \
		CFAggregateDeviceSK.cpp \
		CFComponentFactorySK.cpp \
		CFDomainManagerSK.cpp \
		CFFloatSeqSK.cpp \
		CFOctetSeqSK.cpp \
		CFReleasableManagerSK.cpp \
		CFUShortSeqSK.cpp \
		CFApplicationFactorySK.cpp \
		CFComponentIdentifierSK.cpp \
		CFDoubleSeqSK.cpp \
		CFFullComponentRegistrySK.cpp \
		CFPlatformTypesSK.cpp \
		CFShortSeqSK.cpp \
		SE_DomainEventSK.cpp \
		CFApplicationManagerSK.cpp \
		CFComponentRegistrySK.cpp \
		CFEventChannelRegistrySK.cpp \
		CFSK.cpp \
		CFPortAccessorSK.cpp \
		CFSpecializedInfoSK.cpp \
		SE_StateEventSK.cpp \
		CFBooleanSeqSK.cpp \
		CFControllableInterfaceSK.cpp \
		CFExecutableInterfaceSK.cpp \
		CFLifeCycleSK.cpp \
		CFPrimitiveSeqTypesSK.cpp \
		CFStringSeqSK.cpp \
		StandardEventSK.cpp \
		CFCapacityManagementSK.cpp \
		CFDeploymentAttributesSK.cpp \
		CFFileSK.cpp \
		CFLoadableInterfaceSK.cpp \
		CFPrimitiveTypesSK.cpp \
		UTCTimeSK.cpp \
		CFTestableInterfaceSK.cpp \
		DeviceComponentSK.cpp \
		AdditionalTypesSK.cpp \
		PortSK.cpp \
		QueryablePortSK.cpp \
		NegotiablePortSK.cpp \
		NegotiablePortDynSK.cpp \
		QueryablePortDynSK.cpp \
		PortDynSK.cpp \
		CFAdministratableInterfaceDynSK.cpp \
		CFCharSeqDynSK.cpp \
		CFDeviceAttributesDynSK.cpp \
		CFFileManagerDynSK.cpp \
		CFLongLongSeqDynSK.cpp \
		CFPropertiesDynSK.cpp \
		CFULongLongSeqDynSK.cpp \
		CFAggregateDeviceAttributesDynSK.cpp \
		CFCommonTypesDynSK.cpp \
		CFDomainInstallationDynSK.cpp \
		CFFileSystemDynSK.cpp \
		CFLongSeqDynSK.cpp \
		CFPropertySetDynSK.cpp \
		CFULongSeqDynSK.cpp \
		CFAggregateDeviceDynSK.cpp \
		CFComponentFactoryDynSK.cpp \
		CFDomainManagerDynSK.cpp \
		CFFloatSeqDynSK.cpp \
		CFOctetSeqDynSK.cpp \
		CFReleasableManagerDynSK.cpp \
		CFUShortSeqDynSK.cpp \
		CFApplicationFactoryDynSK.cpp \
		CFComponentIdentifierDynSK.cpp \
		CFDoubleSeqDynSK.cpp \
		CFFullComponentRegistryDynSK.cpp \
		CFPlatformTypesDynSK.cpp \
		CFShortSeqDynSK.cpp \
		SE_DomainEventDynSK.cpp \
		CFApplicationManagerDynSK.cpp \
		CFComponentRegistryDynSK.cpp \
		CFEventChannelRegistryDynSK.cpp \
		CFDynSK.cpp \
		CFPortAccessorDynSK.cpp \
		CFSpecializedInfoDynSK.cpp \
		SE_StateEventDynSK.cpp \
		CFBooleanSeqDynSK.cpp \
		CFControllableInterfaceDynSK.cpp \
		CFExecutableInterfaceDynSK.cpp \
		CFLifeCycleDynSK.cpp \
		CFPrimitiveSeqTypesDynSK.cpp \
		CFStringSeqDynSK.cpp \
		StandardEventDynSK.cpp \
		CFCapacityManagementDynSK.cpp \
		CFDeploymentAttributesDynSK.cpp \
		CFFileDynSK.cpp \
		CFLoadableInterfaceDynSK.cpp \
		CFPrimitiveTypesDynSK.cpp \
		UTCTimeDynSK.cpp \
		CFTestableInterfaceDynSK.cpp \
		DeviceComponentDynSK.cpp \
		AdditionalTypesDynSK.cpp

CLEANFILES = $(BUILT_SOURCES)


cfheaderdir = $(pkgincludedir)/CF
dist_cfheader_HEADERS = AdditionalTypes.h UTCTime.h Port.h QueryablePort.h NegotiablePort.h CFAdministratableInterface.h DeviceComponent.h CFCharSeq.h CFDeviceAttributes.h CFFileManager.h CFLongLongSeq.h CFProperties.h CFULongLongSeq.h CFAggregateDeviceAttributes.h CFCommonTypes.h CFDomainInstallation.h CFFileSystem.h CFLongSeq.h CFPropertySet.h CFULongSeq.h CFAggregateDevice.h CFComponentFactory.h CFDomainManager.h CFFloatSeq.h CFOctetSeq.h CFReleasableManager.h CFUShortSeq.h CFApplicationFactory.h CFComponentIdentifier.h CFDoubleSeq.h CFFullComponentRegistry.h CFPlatformTypes.h CFShortSeq.h SE_DomainEvent.h CFApplicationManager.h CFComponentRegistry.h CFEventChannelRegistry.h CF.h CFPortAccessor.h CFSpecializedInfo.h SE_StateEvent.h CFBooleanSeq.h CFControllableInterface.h CFExecutableInterface.h CFLifeCycle.h CFPrimitiveSeqTypes.h CFStringSeq.h StandardEvent.h CFCapacityManagement.h CFDeploymentAttributes.h CFFile.h CFLoadableInterface.h CFPrimitiveTypes.h CFTestableInterface.h

lib_LTLIBRARIES = libscaidl.la
nodist_libscaidl_la_SOURCES = $(BUILT_SOURCES)
libscaidl_la_CXXFLAGS = -Wall -Wno-switch $(OMNIORB_CFLAGS) $(OMNICOS_CFLAGS) $(OMNITHREAD_CFLAGS) $(OMNIDYNAMIC_CFLAGS) -I../../../include
libscaidl_la_LIBADD = $(OMNIORB_LIBS) $(OMNITHREAD_LIBS) $(OMNIDYNAMIC_LIBS)
libscaidl_la_LDFLAGS = -Wall -version-info $(LIBSCACF_VERSION_INFO)
