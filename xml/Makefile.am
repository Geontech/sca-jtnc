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

dtddir = $(datadir)/xml/sca/4.1.0/dtd
xsddir = $(datadir)/xml/sca/4.1.0/xsd
dist_dtd_DATA = \
		dtd/applicationdeployment.4.1.dtd \
		dtd/deviceconfiguration.4.1.dtd \
		dtd/devicepkg.4.1.dtd \
		dtd/domainmanagerconfiguration.4.1.dtd \
		dtd/platformdeployment.4.1.dtd \
		dtd/properties.4.1.dtd \
		dtd/softpkg.4.1.dtd \
		dtd/softwareassembly.4.1.dtd \
		dtd/softwarecomponent.4.1.dtd \
		dtd/catalog.xml

dist_xsd_DATA = \
		xsd/applicationdeployment.4.1.xsd \
		xsd/deviceconfiguration.4.1.xsd \
		xsd/devicepkg.4.1.xsd \
		xsd/domainmanagerconfiguration.4.1.xsd \
		xsd/platformdeployment.4.1.xsd \
		xsd/properties.4.1.xsd \
		xsd/softpkg.4.1.xsd \
		xsd/softwareassembly.4.1.xsd \
		xsd/softwarecomponent.4.1.xsd

if HAVE_XMLCATALOG
install-exec-hook:
	-xmlcatalog --noout --add delegatePublic "-//JTNC//DTD SCA V4.1.0" "$(datadir)/xml/sca/4.1.0/dtd/catalog.xml" /etc/xml/catalog

endif
