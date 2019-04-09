
import sca.parsers.scd

from sca.codegen.utils import strenum

ComponentTypes = strenum('resource', 'device', 'loadabledevice', 'executabledevice', 'service', 'sharedpackage')
PortTypes = strenum('data', 'control', 'responses', 'test', 'virtual')


class SoftwareComponent(object):
    def __init__(self, scdFile):
        self.__scd = sca.parsers.scd.parse(scdFile)

        if not self.__scd.componentfeatures.ports:
            self.__ports = []
            return

        # Start with the provides ports.
        self.__ports = [ProvidesPort(p) for p in self.__scd.componentfeatures.ports.provides]

        # For each uses port, check if it is really intended to be a "bidirectional" port.
        # If it is, merge with the existing provides port, otherwise make a new port.
        for uses in self.__scd.componentfeatures.ports.uses:
            port = self._findPort(uses.usesname)
            if port is not None:
                if port.repid() != uses.repid:
                    raise ValueError, 'Duplicate port name for different interfaces'
                port._setUses(True)
            else:
                self.__ports.append(UsesPort(uses))

    def _findPort(self, name):
        for port in self.__ports:
            if port.name() == name:
                return port
        return None

    def type(self):
        return str(self.__scd.componenttype)

    def repid(self):
        return self.__scd.componentrepid

    def supports(self, interface):
        for support in self.__scd.componentfeatures.supportsinterface:
            if support.repid == interface:
                return True
        return False

    def interfaces(self):
        return self.__scd.interfaces.interface

    def ports(self):
        return self.__ports

    def uses(self):
        return [p for p in self.__ports if p.isUses()]

    def provides(self):
        return [p for p in self.__ports if p.isProvides()]

class Port(object):
    def __init__(self, name, xml, uses=False, provides=False):
        self.__name = name
        self.__xml = xml
        self.__uses = uses
        self.__provides = provides

    def _setUses(self, uses):
        self.__uses = uses

    def isUses(self):
        return self.__uses

    def isProvides(self):
        return self.__provides

    def isBidirectional(self):
        return self.isUses() and self.isProvides()

    def name(self):
        return self.__name

    def repid(self):
        return self.__xml.repid

    def types(self):
        if self.__xml.porttype:
            return [pt.type_ for pt in self.__xml.porttype]
        else:
            return [PortTypes.CONTROL]

    def hasDescription(self):
        return self.__xml.description is not None

    def description(self):
        return self.__xml.description

def UsesPort(port):
    return Port(port.usesname, port, uses=True)

def ProvidesPort(port):
    return Port(port.providesname, port, provides=True)
