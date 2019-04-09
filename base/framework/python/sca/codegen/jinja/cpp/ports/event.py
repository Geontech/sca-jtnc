
from sca.codegen.lang import cpp

from generator import CppPortGenerator

class PropertyEventPortGenerator(CppPortGenerator):
    REPID = 'IDL:omg.org/CosEventChannelAdmin/EventChannel:1.0'
    NAME = 'propEvent'

    @classmethod
    def match(cls, port):
        return (port.repid() == cls.REPID) and (port.name() == cls.NAME)

    def _ctorArgs(self, name):
        return [cpp.stringLiteral(name)]

    def className(self):
        return 'PropertyEventSupplier'

    def header(self):
        return '<sca/PropertyInterface.h>'
