
from sca.codegen.lang.idl import IDLInterface
from sca.codegen.lang import cpp
from sca.codegen.jinja.ports import PortFactory

from generator import CppPortGenerator

class BurstioPortFactory(PortFactory):
    NAMESPACE = 'BURSTIO'

    def match(self, port):
        return IDLInterface(port.repid()).namespace() == self.NAMESPACE

    def generator(self, port):
        return BurstioPortGenerator(port)

class BurstioPortGenerator(CppPortGenerator):
    def header(self):
        return '<burstio/burstio.h>'

    def className(self):
        # The port class is the interface name (first character capitalized),
        # plus the direction, e.g., "BurstByteIn" for "burstByte" provides port
        porttype = self.interface[0].upper() + self.interface[1:]
        if self.direction == 'uses':
            porttype += 'Out'
        else:
            porttype += 'In'
        return 'burstio::' + porttype

    def supportsMultiOut(self):
        return (self.direction == 'uses')

    def _ctorArgs(self, name):
        return (cpp.stringLiteral(name),)
