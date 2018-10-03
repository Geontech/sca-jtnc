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

import os

def sdrRoot():
    if 'SDRROOT' in os.environ and os.path.exists(os.environ['SDRROOT']):
        sdrroot = os.path.normpath(os.environ['SDRROOT'])
    elif os.path.exists('/sdr/sca'):
        sdrroot = '/sdr/sca'
    elif os.path.exists('/sdr'):
        sdrroot = '/sdr'
    else:
        print "Cannot find SDR root directory"
        return False
        
    return sdrroot

def scaRoot():
    if 'OSSIEHOME' in os.environ and os.path.exists(os.environ['OSSIEHOME']):
        scaroot = os.path.normpath(os.environ['OSSIEHOME'])
    elif os.path.exists('/usr/local/include/sca') and os.path.exists('/usr/local/share/sca'):
        scaroot = '/usr/local'
    elif os.path.exists('/usr/include/sca') and os.path.exists('/usr/share/sca'):
        scaroot = '/usr'
    else:
        print "Cannot find OSSIE installation location."
        return False

    return scaroot

def idlRoot():
    scaroot = scaRoot()
    if not scaRoot: return False

    if os.path.exists(os.path.join(scaroot,'share/sca/idl')):
        idlroot = os.path.join(scaroot,'share/sca/idl')
    else:
        print "Cannot find OSSIE IDL location."
        return False

    return idlroot

def scaInclude():
    scaroot = scaRoot()
    if not scaRoot: return False

    if os.path.exists(os.path.join(scaroot,'include/sca')):
        scainclude = os.path.join(scaroot,'include/sca')
    else:
        print "Cannot find OSSIE IDL location."
        return False
        
    return scainclude

def scaShare():
    scaroot = scaRoot()
    if not scaRoot: return False

    if os.path.exists(os.path.join(scaroot,'share/sca')):
        scashare = os.path.join(scaroot,'share/sca')
    else:
        print "Cannot find OSSIE share location."
        return False
        
    return scashare
