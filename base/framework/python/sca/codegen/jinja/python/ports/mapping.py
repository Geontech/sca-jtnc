
from sca.codegen.lang import python

from sca.codegen.jinja.mapping import PortMapper

class PythonPortMapper(PortMapper):
    def _mapPort(self, port, generator):
        pyport = {}
        pyport['pyname'] = python.identifier('port_'+port.name())
        pyport['portname'] = python.identifier(port.name())
        pyport['constructor'] = generator.constructor(port)
        pyport['multiout'] = generator.supportsMultiOut()
        return pyport
