
import jinja2

from sca.codegen.lang.idl import IDLInterface
from sca.codegen.lang import cpp
from sca.codegen.jinja.ports import PortFactory
from sca.codegen.jinja.cpp import CppTemplate

from generator import CppPortGenerator

if not '__package__' in locals():
    # Python 2.4 compatibility
    __package__ = __name__.rsplit('.', 1)[0]

_headerMap = {
    'AnalogTuner':     '<frontend/fe_tuner_port_impl.h>',
    'DigitalTuner':    '<frontend/fe_tuner_port_impl.h>',
    'FrontendTuner':   '<frontend/fe_tuner_port_impl.h>',
    'GPS':             '<frontend/fe_gps_port_impl.h>',
    'NavData':         '<frontend/fe_navdata_port_impl.h>',
    'RFInfo':          '<frontend/fe_rfinfo_port_impl.h>',
    'RFSource':        '<frontend/fe_rfsource_port_impl.h>'
}

class FrontendPortFactory(PortFactory):
    NAMESPACE = 'FRONTEND'

    def match(self, port):
        return IDLInterface(port.repid()).namespace() == self.NAMESPACE

    def generator(self, port):
        interface = IDLInterface(port.repid()).interface()
        return FrontendPortGenerator(port)

class FrontendPortGenerator(CppPortGenerator):
    def header(self):
        return '<frontend/frontend.h>'

    def headers(self):
        return [_headerMap[self.interface]]

    def className(self):
        return "frontend::" + self.templateClass()

    def templateClass(self):
        if self.direction == 'uses':
            porttype = 'Out'
        else:
            porttype = 'In'
        porttype += self.interface + 'Port'
        return porttype

    def _ctorArgs(self, name):
        if self.direction == 'uses':
            return (cpp.stringLiteral(name),)
        else:
            return [cpp.stringLiteral(name),"this"]

    def loader(self):
        return jinja2.PackageLoader(__package__)

class FrontendOutputPortFactory(PortFactory):
    NAMESPACE = 'FRONTEND'

    def match(self, port):
        return IDLInterface(port.repid()).namespace() == self.NAMESPACE and (not port.isProvides())

    def generator(self, port):
        interface = IDLInterface(port.repid()).interface()
        return FrontendPortGenerator(port)

class FrontendOutputPortGenerator(CppPortGenerator):
    def header(self):
        return '<frontend/frontend.h>'

    def headers(self):
        return [_headerMap[self.interface]]

    def className(self):
        return "frontend::" + self.templateClass()

    def templateClass(self):
        if self.direction == 'uses':
            porttype = 'Out'
        else:
            porttype = 'In'
        porttype += self.interface + 'Port'
        return porttype

    def _ctorArgs(self, name):
        if self.direction == 'uses':
            return (cpp.stringLiteral(name),)
        else:
            return [cpp.stringLiteral(name),"this"]

    def loader(self):
        return jinja2.PackageLoader(__package__)

