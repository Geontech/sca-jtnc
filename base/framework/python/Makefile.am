#
# This file is protected by Copyright. Please refer to the COPYRIGHT file 
# distributed with this source distribution.
# 
# This file is part of REDHAWK core.
# 
# REDHAWK core is free software: you can redistribute it and/or modify it under 
# the terms of the GNU Lesser General Public License as published by the Free 
# Software Foundation, either version 3 of the License, or (at your option) any 
# later version.
# 
# REDHAWK core is distributed in the hope that it will be useful, but WITHOUT 
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS 
# FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
# details.
# 
# You should have received a copy of the GNU Lesser General Public License 
# along with this program.  If not, see http://www.gnu.org/licenses/.
#

# vim: noet: softtabstop=0

# Because omniidl is definitely not capable
.NOTPARALLEL:

# Mimic automake silent rules
SCA_V_pysetup = $(sca__v_pysetup_$(V))
sca__v_pysetup_ = $(sca__v_pysetup__$(AM_DEFAULT_VERBOSITY))
sca__v_pysetup_0 = --quiet
sca__v_pysetup__0 = $(sca__v_pysetup_0)

all-local:
	python setup.py $(SCA_V_pysetup) build

clean-local:
	python setup.py clean
	rm -rf build

sca/cf/%_idl.py : $(top_srcdir)/idl/sca/*/%.idl
	$(AM_V_GEN)$(IDL) -bpython -Wbpackage=sca.cf -Wbextern=CosNaming -Wbextern=CosEventComm -Wbextern=CosEventChannelAdmin -I $(IDLDIR) -I $(OMNICOS_IDLDIR) -I $(top_srcdir)/idl $<

sca/bulkio/%_idl.py : $(top_srcdir)/idl/sca/BULKIO/%.idl
	$(AM_V_GEN)$(IDL) -bpython -Wbpackage=sca.bulkio -Wbextern=CFBooleanSeq:sca.cf -Wbextern=CFDoubleSeq:sca.cf -Wbextern=CFLongLongSeq:sca.cf -Wbextern=CFOctetSeq:sca.cf -Wbextern=CFStringSeq:sca.cf -Wbextern=CFULongSeq:sca.cf -Wbextern=CFCharSeq:sca.cf -Wbextern=CFFloatSeq:sca.cf -Wbextern=CFLongSeq:sca.cf -Wbextern=CFShortSeq:sca.cf -Wbextern=CFULongLongSeq:sca.cf -Wbextern=CFUShortSeq:sca.cf -Wbextern=CFProperties:sca.cf -Wbextern=CFCommonTypes:sca.cf -Wbextern=CFPortAccessor:sca.cf -Wbextern=AdditionalTypes:sca.cf -Wbextern=CFPrimitiveTypes:sca.cf -Wbextern=CosNaming -Wbextern=CosEventComm -Wbextern=CosEventChannelAdmin -I $(IDLDIR) -I $(OMNICOS_IDLDIR) -I $(top_srcdir)/idl $<

EXTRA_DIST = setup.py

BUILT_SOURCES = \
 sca/cf/CFAdministratableInterface_idl.py \
 sca/cf/CFCharSeq_idl.py \
 sca/cf/CFDeviceAttributes_idl.py \
 sca/cf/CFFileManager_idl.py \
 sca/cf/CFLongLongSeq_idl.py \
 sca/cf/CFProperties_idl.py \
 sca/cf/CFULongLongSeq_idl.py \
 sca/cf/CFAggregateDeviceAttributes_idl.py \
 sca/cf/CFCommonTypes_idl.py \
 sca/cf/CFDomainInstallation_idl.py \
 sca/cf/CFFileSystem_idl.py \
 sca/cf/CFLongSeq_idl.py \
 sca/cf/CFPropertySet_idl.py \
 sca/cf/CFULongSeq_idl.py \
 sca/cf/CFAggregateDevice_idl.py \
 sca/cf/CFComponentFactory_idl.py \
 sca/cf/CFDomainManager_idl.py \
 sca/cf/CFFloatSeq_idl.py \
 sca/cf/CFOctetSeq_idl.py \
 sca/cf/CFReleasableManager_idl.py \
 sca/cf/CFUShortSeq_idl.py \
 sca/cf/CFApplicationFactory_idl.py \
 sca/cf/CFComponentIdentifier_idl.py \
 sca/cf/CFDoubleSeq_idl.py \
 sca/cf/CFFullComponentRegistry_idl.py \
 sca/cf/CFPlatformTypes_idl.py \
 sca/cf/CFShortSeq_idl.py \
 sca/cf/SE_DomainEvent_idl.py \
 sca/cf/CFApplicationManager_idl.py \
 sca/cf/CFComponentRegistry_idl.py \
 sca/cf/CFEventChannelRegistry_idl.py \
 sca/cf/CF_idl.py \
 sca/cf/CFPortAccessor_idl.py \
 sca/cf/CFSpecializedInfo_idl.py \
 sca/cf/SE_StateEvent_idl.py \
 sca/cf/CFBooleanSeq_idl.py \
 sca/cf/CFControllableInterface_idl.py \
 sca/cf/CFExecutableInterface_idl.py \
 sca/cf/CFLifeCycle_idl.py \
 sca/cf/CFPrimitiveSeqTypes_idl.py \
 sca/cf/CFStringSeq_idl.py \
 sca/cf/StandardEvent_idl.py \
 sca/cf/CFCapacityManagement_idl.py \
 sca/cf/CFDeploymentAttributes_idl.py \
 sca/cf/CFFile_idl.py \
 sca/cf/CFLoadableInterface_idl.py \
 sca/cf/CFPrimitiveTypes_idl.py \
 sca/cf/CFTestableInterface_idl.py \
 sca/cf/UTCTime_idl.py \
 sca/cf/DeviceComponent_idl.py \
 sca/cf/AdditionalTypes_idl.py \
 sca/bulkio/bio_dataFloat_idl.py \
 sca/bulkio/bio_dataBit_idl.py \
 sca/bulkio/bio_dataDouble_idl.py \
 sca/bulkio/bio_dataLongLong_idl.py \
 sca/bulkio/bio_dataSDDS_idl.py \
 sca/bulkio/bio_dataUlong_idl.py \
 sca/bulkio/bio_dataUshort_idl.py \
 sca/bulkio/bio_dataXML_idl.py \
 sca/bulkio/bio_updateSRI_idl.py \
 sca/bulkio/bio_dataChar_idl.py \
 sca/bulkio/bio_dataFile_idl.py \
 sca/bulkio/bio_dataLong_idl.py \
 sca/bulkio/bio_dataOctet_idl.py \
 sca/bulkio/bio_dataShort_idl.py \
 sca/bulkio/bio_dataUlongLong_idl.py \
 sca/bulkio/bio_dataVITA49_idl.py \
 sca/bulkio/bio_runtimeStats_idl.py \
 sca/bulkio/bulkioDataTypes_idl.py

CLEANFILES = $(BUILT_SOURCES)

install-exec-hook:
	$(PYTHON) setup.py install -f --$(PYTHON_INSTALL_SCHEME)=$(DESTDIR)$(prefix) --old-and-unmanageable
