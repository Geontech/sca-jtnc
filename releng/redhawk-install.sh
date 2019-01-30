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

core=redhawk
codegen=redhawk-codegen
bulkio=bulkioInterfaces
burstio=burstioInterfaces
frontend=frontendInterfaces
gpp=GPP

set -e
if [ "$SCAHOME" == "" ]; then
    echo "ERROR:  SCAHOME has not been defined."
    exit 2
fi

if [ "$SCAROOT" == "" ]; then
    echo "ERROR:  SCAROOT has not been defined."
    exit 2
fi

echo "Install location (SCAHOME) is currently set to $SCAHOME"
echo "SDR location (SCAROOT) is currently set to $SCAROOT"
echo -n "Continue [Y]/N ? "
read CONFIRM
if [[ "$CONFIRM" = [nN] ]]; then
    exit 0
fi

nproc=`/usr/bin/getconf _NPROCESSORS_ONLN`

pushd $core/src
./reconf
./configure
make clean
make -j$nproc
make install
popd

# Create a environment setup script
cat > $SCAHOME/environment-setup << EOF
export SCAHOME=${SCAHOME}
export SCAROOT=${SCAROOT}
export PATH=\${SCAHOME}/bin:\${PATH}
export LD_LIBRARY_PATH=\${SCAHOME}/lib64:\${SCAHOME}/lib:\${LD_LIBRARY_PATH}
export PYTHONPATH=\${SCAHOME}/lib64/python:\${SCAHOME}/lib/python:\${PYTHONPATH}
EOF

cat > $SCAHOME/environment-setup.csh << EOF
setenv SCAHOME ${SCAHOME}
setenv SCAROOT ${SCAROOT}
setenv PATH \${SCAHOME}/bin:\${PATH}
if (! \$?LD_LIBRARY_PATH) then
    setenv LD_LIBRARY_PATH
endif
setenv LD_LIBRARY_PATH \${SCAHOME}/lib64:\${SCAHOME}/lib:\${LD_LIBRARY_PATH}
if (! \$?PYTHONPATH) then
    setenv PYTHONPATH
endif
setenv PYTHONPATH \${SCAHOME}/lib64/python:\${SCAHOME}/lib/python:\${PYTHONPATH}
EOF

# Setup the environment for compilation steps below that need it
. $SCAHOME/environment-setup

pushd $codegen
python setup.py build
python setup.py install --home=${SCAHOME} --old-and-unmanageable
popd

pushd $bulkio
./reconf
./configure
make clean
make -j$nproc
make install
popd

pushd $burstio
./reconf
./configure
make clean
make -j$nproc
make install
popd

pushd $frontend
./reconf
./configure
make clean
make
make install
popd

pushd $gpp/cpp
./reconf
./configure
make clean
make -j$nproc
make install
popd

echo
echo "REDHAWK is now installed."
echo "Prior to running REDHAWK, you must setup your environment"
echo "  In bash: . \$SCAHOME/environment-setup"
echo "  In tcsh: source \$SCAHOME/environment-setup"
echo
echo "Would you like to setup a domain?"
echo -n "Continue [Y]/N ? "
read CONFIRM
if [[ "$CONFIRM" = [nN] ]]; then
    exit 0
fi

cd $SCAROOT/dom/domain
cp DomainManager.dmd.xml.template DomainManager.dmd.xml
sed -i s/@UUID@/`uuidgen`/g DomainManager.dmd.xml
sed -i s/@NAME@/REDHAWK_${USER}/g DomainManager.dmd.xml
sed -i "s/@DESCRIPTION@/A REDHAWK Domain for ${USER}/g" DomainManager.dmd.xml

. $SCAHOME/environment-setup
$SCAROOT/dev/devices/GPP/cpp/gpp_setup -v  \
    --nodecfg \
    --sdrroot=$SCAROOT \
    --gpppath=/devices/GPP \
    --domainname=REDHAWK_${USER} \
    --inplace \
    --clean
