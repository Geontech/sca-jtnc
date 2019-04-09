
from sca.codegen.lang.idl import IDLInterface
from sca.codegen.jinja.ports import PortGenerator
from sca.codegen.jinja.ports import PortFactory
from generator import PythonPortGenerator
from sca.codegen.lang import python 

class FrontendPortFactory(PortFactory):
    NAMESPACE = 'FRONTEND'

    def match(self, port):
        return IDLInterface(port.repid()).namespace() == self.NAMESPACE

    def generator(self, port):
        interface = IDLInterface(port.repid()).interface()
        return FrontendPortGenerator(port)

class FrontendPortGenerator(PythonPortGenerator):
    def className(self):
        return "frontend." + self.templateClass()

    def templateClass(self):
        if self.direction == 'uses':
            porttype = 'Out'
        else:
            porttype = 'In'
        porttype += self.interface + 'Port'
        return porttype

    def _ctorArgs(self, port):
        return [python.stringLiteral(port.name())]

    def constructor(self, name):
        fei_ports = ['InDigitalTunerPort','InDigitalScanningTunerPort','InFrontendTunerPort','InAnalogTunerPort','InGPSPort','InRFInfoPort','InRFSourcePort','InNavDataPort']
        for _port in fei_ports:
            if _port in self.className():
                return '%s(%s, self)' % (self.className(), ', '.join(self._ctorArgs(name)))
        return '%s(%s)' % (self.className(), ', '.join(self._ctorArgs(name)))

    def loader(self):
        return jinja2.PackageLoader(__package__)
