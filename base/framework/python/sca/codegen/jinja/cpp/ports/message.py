
from sca.codegen.lang import cpp
from sca.codegen.jinja.ports import PortFactory

from generator import CppPortGenerator

class MessagePortFactory(PortFactory):
    REPID = 'IDL:ExtendedEvent/MessageEvent:1.0'

    def match(self, port):
        return (port.repid() == self.REPID)

    def generator(self, port):
        if port.isProvides():
            return MessageConsumerPortGenerator(port)
        else:
            return MessageSupplierPortGenerator(port)

class MessagePortGenerator(CppPortGenerator):
    def _ctorArgs(self, name):
        return [cpp.stringLiteral(name)]

    def header(self):
        return '<sca/MessageInterface.h>'

class MessageConsumerPortGenerator(MessagePortGenerator):
    def className(self):
        return 'MessageConsumerPort'

class MessageSupplierPortGenerator(MessagePortGenerator):
    def className(self):
        return 'MessageSupplierPort'
