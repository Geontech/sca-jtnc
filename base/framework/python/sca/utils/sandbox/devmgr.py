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

import logging
import threading
import atexit

from omniORB import CORBA
from sca.cf import CF__POA, CF
from sca.utils import log4py

# Prepare the ORB
orb = CORBA.ORB_init()
poa = orb.resolve_initial_references("RootPOA")

log = logging.getLogger(__name__)

def _deviceManagerShutdown():
    devMgr = DeviceManagerStub.instance(False)
    if devMgr:
        devMgr.shutdown()

atexit.register(_deviceManagerShutdown)

class DeviceManagerStub(CF__POA.FullComponentRegistry):
    """
    Proxy used to provide launched Devices a point with which to register
    """
    def __init__(self):
        self.__devices = {}
        self.__services = {}
        self.__lock = threading.RLock()

    _instance = None
    _instanceLock = threading.RLock()

    @classmethod
    def instance(cls, create=True):
        cls._instanceLock.acquire()
        try:
            if not cls._instance and create:
                log.debug('Launching virtual DeviceManager')
                cls._instance = DeviceManagerStub()
                cls._instance._object_id = poa.activate_object(cls._instance)
            return cls._instance
        finally:
            cls._instanceLock.release()

    def shutdown(self):
        log.debug('Shutting down virtual DeviceManager')
        poa.deactivate_object(self._object_id)

    def _registerDevice(self, identifier, device):
        if identifier in self.__devices:
            log.warning("Device '%s' already registered with virtual DeviceManager", identifier)
        log.debug("Registering device '%s' with virtual DeviceManager", identifier)
        devptr = device.componentObject
        self.__devices[identifier] = devptr

    def _getDeviceIdentifier(self, device):
        try:
            return device._get_identifer()
        except:
            pass
        for identifier, knownDevice in self.__devices.iteritems():
            if knownDevice._is_equivalent(device):
                return identifier
        return None

    def _unregisterDevice(self, identifier):
        if not identifier:
            log.warning('Virtual DeviceManager ignoring unregistration of unidentified device')
        elif identifier not in self.__devices:
            log.warning("Device '%s' not registered with virtual DeviceManager", identifier)
        else:
            log.debug("Unregistering device '%s' from virtual DeviceManager", identifier)
            del self.__devices[identifier]

    def registerComponent(self, registeringDevice):
        try:
            identifier = registeringDevice.identifier
        except:
            return
        self.__lock.acquire()
        try:
            self._registerDevice(identifier, registeringDevice)
        finally:
            self.__lock.release()
    
    def _get_domMgr(self):
        return CF.DomainManager._nil
    
    def _get_identifier(self):
        return ""

    def unregisterComponent(self, unregisteringDevice_id):
        self.__lock.acquire()
        try:
            self._unregisterDevice(unregisteringDevice_id)
        finally:
            self.__lock.release()

    def getDevice(self, identifier):
        self.__lock.acquire()
        try:
            retval = self.__devices.get(identifier, None)
            return retval
        finally:
            self.__lock.release()

    def getService(self, name):
        self.__lock.acquire()
        try:
            return self.__services.get(name, None)
        finally:
            self.__lock.release()
