
from sca.codegen.lang import python
from sca.codegen.lang.idl import IDLInterface
from sca.codegen.jinja.ports import PortFactory

from generator import PythonPortGenerator

class BurstioPortFactory(PortFactory):
    NAMESPACE = 'BURSTIO'

    def match(self, port):
        return IDLInterface(port.repid()).namespace() == self.NAMESPACE
    
    def generator(self, port):
        return BurstioPortGenerator(port)

class BurstioPortGenerator(PythonPortGenerator):
    def _ctorArgs(self, port):
        return (python.stringLiteral(port.name()),)

    def imports(self):
        return ('from sca import burstio',)

    def className(self):
        # The port class is the interface name (first character capitalized),
        # plus the direction, e.g., "BurstByteIn" for "burstByte" provides port
        classname = 'burstio.' + self.interface[0].upper() + self.interface[1:]
        if self.direction == 'uses':
            classname += 'Out'
        else:
            classname += 'In'
        return classname

    def supportsMultiOut(self):
        return (self.direction == 'uses')
