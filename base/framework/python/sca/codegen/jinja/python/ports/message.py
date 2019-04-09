
from sca.codegen.jinja.ports import PortFactory

from generator import BuiltinPythonPort

class MessagePortFactory(PortFactory):
    REPID = 'IDL:ExtendedEvent/MessageEvent:1.0'

    def match(self, port):
        return (port.repid() == self.REPID)

    def generator(self, port):
        if port.isProvides():
            return MessageConsumerPortGenerator(port)
        else:
            return MessageSupplierPortGenerator(port)

class MessageConsumerPortGenerator(BuiltinPythonPort):
    def __init__(self, port):
        BuiltinPythonPort.__init__(self, 'sca.events.MessageConsumerPort', port)

    def _ctorArgs(self, name):
        return ('thread_sleep=0.1','parent = self')

class MessageSupplierPortGenerator(BuiltinPythonPort):
    def __init__(self, port):
        BuiltinPythonPort.__init__(self, 'sca.events.MessageSupplierPort', port)
