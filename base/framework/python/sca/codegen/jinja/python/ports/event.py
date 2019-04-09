
from sca.codegen.lang import python

from generator import BuiltinPythonPort

class PropertyEventPortGenerator(BuiltinPythonPort):
    REPID = 'IDL:omg.org/CosEventChannelAdmin/EventChannel:1.0'
    NAME = 'propEvent'

    def __init__(self, port):
        BuiltinPythonPort.__init__(self, 'sca.events.PropertyEventSupplier', port)

    @classmethod
    def match(cls, port):
        return (port.repid() == cls.REPID) and (port.name() == cls.NAME)

    def _ctorArgs(self, name):
        return ('self',)
