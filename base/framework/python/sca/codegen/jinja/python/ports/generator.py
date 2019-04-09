
from sca.codegen.lang import python
from sca.codegen.lang.idl import IDLInterface
from sca.codegen.jinja.ports import PortGenerator

class PythonPortGenerator(PortGenerator):
    def __eq__(self, other):
        return self.className() == other.className()

    def className(self):
        return self.templateClass() + '_i'

    def templateClass(self):
        interface = self.interface[0].upper() + self.interface[1:]
        porttype = 'Port' + self.pyNamespace() + interface
        if self.direction == 'uses':
            porttype += 'Out'
        else:
            porttype += 'In'
        return porttype

    def attributeClass(self):
        return self.direction+'port'

    def imports(self):
        return []

    def pyNamespace(self):
        return self.namespace.replace('omg.org/', '')

    def corbaClass(self):
        return self.pyNamespace() + '.' + self.interface

    def poaClass(self):
        if self.direction == 'uses':
            return 'CF__POA.Port'
        else:
            return self.pyNamespace() + '__POA.' + self.interface

    def _ctorArgs(self, port):
        return []

    def constructor(self, port):
        return '%s(%s)' % (self.className(), ', '.join(self._ctorArgs(port)))

    def supportsMultiOut(self):
        return False

class BuiltinPythonPort(PythonPortGenerator):
    def __init__(self, pyclass, port):
        PythonPortGenerator.__init__(self, port)
        self.__imports = (python.importModule(pyclass),)
        self.__name = pyclass.split('.')[-1]

    def imports(self):
        return self.__imports

    def className(self):
        return self.__name
