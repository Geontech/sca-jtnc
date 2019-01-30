#!/usr/bin/env bash
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


if test "x$GENERATE_DS" == "x"; then 
  # Assume it's on the path
  GENERATE_DS="generateDS.py"
fi

GENERATE_DS_FLAGS="-f --silence -m"
echo "Generating DCD parser"
${GENERATE_DS} ${GENERATE_DS_FLAGS} -o sca/parsers/dcd.py     ../../../xml/xsd/deviceconfiguration.4.1.xsd
echo "Generating DMD parser"
${GENERATE_DS} ${GENERATE_DS_FLAGS} -o sca/parsers/dmd.py     ../../../xml/xsd/domainmanagerconfiguration.4.1.xsd
echo "Generating DPD parser"
${GENERATE_DS} ${GENERATE_DS_FLAGS} -o sca/parsers/dpd.py     ../../../xml/xsd/devicepkg.4.1.xsd
echo "Generating PRF parser"
${GENERATE_DS} ${GENERATE_DS_FLAGS} -o sca/parsers/prf.py     ../../../xml/xsd/properties.4.1.xsd
echo "Generating AppDep parser"
${GENERATE_DS} ${GENERATE_DS_FLAGS} -o sca/parsers/adep.py ../../../xml/xsd/applicationdeployment.4.1.xsd
echo "Generating PlatDep parser"
${GENERATE_DS} ${GENERATE_DS_FLAGS} -o sca/parsers/pdep.py ../../../xml/xsd/platformdeployment.4.1.xsd
echo "Generating SAD parser"
${GENERATE_DS} ${GENERATE_DS_FLAGS} -o sca/parsers/sad.py     ../../../xml/xsd/softwareassembly.4.1.xsd
echo "Generating SCD parser"
${GENERATE_DS} ${GENERATE_DS_FLAGS} -o sca/parsers/scd.py     ../../../xml/xsd/softwarecomponent.4.1.xsd
echo "Generating SPD parser"
${GENERATE_DS} ${GENERATE_DS_FLAGS} -o sca/parsers/spd.py     ../../../xml/xsd/softpkg.4.1.xsd
