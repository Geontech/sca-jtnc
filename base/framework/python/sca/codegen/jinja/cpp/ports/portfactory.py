
from sca.codegen.jinja.ports import PortFactoryList

from generic import GenericPortFactory
from bulkio import BulkioPortFactory
from frontend import FrontendPortFactory
from frontend import FrontendOutputPortFactory
from event import PropertyEventPortGenerator
from message import MessagePortFactory
from burstio import BurstioPortFactory

class CppPortFactory(PortFactoryList):
    def __init__(self):
        factories = (FrontendOutputPortFactory(), BulkioPortFactory(), BurstioPortFactory(), PropertyEventPortGenerator,
                     MessagePortFactory(), GenericPortFactory())
        super(CppPortFactory,self).__init__(*factories)

class FEIPortFactory(PortFactoryList):
    def __init__(self):
        factories = (FrontendPortFactory(),CppPortFactory())
        super(FEIPortFactory,self).__init__(*factories)
