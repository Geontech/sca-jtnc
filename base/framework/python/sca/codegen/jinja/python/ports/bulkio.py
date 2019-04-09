
from sca.codegen.lang.idl import IDLInterface
from sca.codegen.lang import python
from sca.codegen.jinja.ports import PortFactory

from generator import PythonPortGenerator

class BulkioPortFactory(PortFactory):
    NAMESPACE = 'BULKIO'

    def match(self, port):
        interface = IDLInterface(port.repid())
        if interface.namespace() != self.NAMESPACE:
            return False
        return interface.interface().startswith('data')

    def generator(self, port):
        return BulkioPortGenerator(port)

class BulkioPortGenerator(PythonPortGenerator):
    def imports(self):
        return ('import bulkio',)

    def className(self):
        if self.direction == 'uses':
            direction = 'Out'
        else:
            direction = 'In'
        # Trim 'data' from front of interface to get data type
        datatype = self.interface.lstrip('data')
        # If interface is unsigned need to make sure next character is upper
        # case to conform with bulkio base classes
        if datatype.startswith('U'):
            datatype = datatype[0] + datatype[1].upper() + datatype[2:]
        return 'bulkio.' + direction + datatype + 'Port'

    def supportsMultiOut(self):
        return (self.direction == 'uses')

    def _ctorArgs(self, port):
        args = [python.stringLiteral(port.name())]
        if self.direction == 'provides' and 'SDDS' not in self.interface and 'VITA' not in self.interface:
            args.append('maxsize=self.DEFAULT_QUEUE_SIZE')
        return args
