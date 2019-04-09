
from sca.codegen.lang import cpp
from sca.codegen.jinja.mapping import PortMapper

class CppPortMapper(PortMapper):
    def _mapPort(self, port, generator):
        cppport = {}
        cppport['cppname'] = cpp.identifier(port.name())
        cppport['cpptype'] = generator.className()
        cppport['constructor'] = generator.constructor(port.name())
        cppport['multiout'] = generator.supportsMultiOut()
        return cppport
