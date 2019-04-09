
from sca.codegen.lang import cpp
from sca.codegen.lang.idl import IDLInterface
from sca.codegen.jinja.ports import PortGenerator

class CppPortGenerator(PortGenerator):
    def __init__(self, port):
        PortGenerator.__init__(self, port)
        self._header = None

    def __eq__(self, other):
        return self.className() == other.className()

    def className(self):
        porttype = self.interfaceClass().replace('::', '_')
        if self.direction == 'uses':
            porttype += '_Out_i'
        else:
            porttype += '_In_i'
        return porttype

    def interfaceClass(self):
        return cpp.idlClass(self.idl)

    def header(self):
        return self._header

    def setHeader(self, header):
        if not self.hasDeclaration():
            raise AssertionError('Cannot change header for non-generated ports')
        self._header = header

    def dependencies(self):
        return tuple()

    def _ctorArgs(self, name):
        return tuple()

    def constructor(self, name):
        return '%s(%s)' % (self.className(), ', '.join(self._ctorArgs(name)))

    def _declaration(self):
        return None

    def hasDeclaration(self):
        return self._declaration() is not None

    def declaration(self):
        template = self._declaration()
        return self.get_template(template)

    def supportsMultiOut(self):
        return False
