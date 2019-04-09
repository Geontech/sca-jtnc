
from sca.codegen.jinja.python.ports.portfactory import PythonPortFactory
from sca.codegen.jinja.ports import PortFactoryList
from sca.codegen.jinja.python.ports.frontend import FrontendPortFactory

class FEIPortFactory(PortFactoryList):
    def __init__(self):
        factories = (FrontendPortFactory(), PythonPortFactory())
        super(FEIPortFactory,self).__init__(*factories)
