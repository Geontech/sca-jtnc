
from sca.codegen.lang.idl import IDLInterface
from sca.codegen.lang import cpp
from sca.codegen.jinja.ports import PortFactory

from generator import CppPortGenerator

class BulkioPortFactory(PortFactory):
    NAMESPACE = 'BULKIO'

    def match(self, port):
        interface = IDLInterface(port.repid())
        if interface.namespace() != self.NAMESPACE:
            return False
        return interface.interface().startswith('data')

    def generator(self, port):
        return BulkioPortGenerator(port)

class BulkioPortGenerator(CppPortGenerator):
    def header(self):
        return '<bulkio/bulkio.h>'

    def className(self):
        # Trim 'data' from front of interface to get data type
        datatype = self.interface.lstrip('data')
        # If interface is unsigned need to make sure next character is upper
        # case to conform with bulkio base classes
        if datatype.startswith('U'):
            datatype = datatype[0] + datatype[1].upper() + datatype[2:]
        if self.direction == 'provides':
            direction = 'In'
        else:
            direction = 'Out'
        return 'bulkio::' + direction + datatype + 'Port'

    def supportsMultiOut(self):
        return (self.direction == 'uses')

    def _ctorArgs(self, name):
        return (cpp.stringLiteral(name),)
