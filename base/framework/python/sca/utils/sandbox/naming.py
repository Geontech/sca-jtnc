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

import threading

from omniORB import CORBA, URI

from sca.cf import CF, CF__POA
from sca.utils.log4py import logging

class ApplicationRegistrarStub(CF__POA.FullComponentRegistry):
    """
    Class to extend virtual NamingContext to support ApplicationRegistrar
    operations.
    """
    def __init__(self, orb):
        self._context = {}
        self._lock = threading.RLock()
        self._orb = orb

    def getObject(self, _id):
        print '........... getObject 1', self._context
        print '================= getObject:', self._context.get(_id, None)._get_started()
        with self._lock:
            return self._context.get(_id, None)

    def registerComponent(self, registeringComponent):
        print '===== begin registerComponent (component)'
        with self._lock:
            _id = registeringComponent.identifier
            if _id in self._context:
                raise CF.RegisterError()
            self._context[_id] = registeringComponent.componentObject._narrow(CF.ResourceComponent)
            resource = registeringComponent.componentObject._narrow(CF.ResourceComponent)
            print '================= registering (id:'+_id+'):', registeringComponent.componentObject
            print '================= registering:', registeringComponent.componentObject._get_started()
            print self._orb.object_to_string(registeringComponent.componentObject)
            print '================= done registering'
        obj = self.getObject(_id)
