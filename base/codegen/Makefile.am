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
	rm -rf build

EXTRA_DIST = setup.py

install-exec-hook:
	$(PYTHON) setup.py install -f --$(PYTHON_INSTALL_SCHEME)=$(DESTDIR)$(prefix) --old-and-unmanageable
