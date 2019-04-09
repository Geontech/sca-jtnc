
from sca.codegen.jinja.ports import PortFactoryList

from generic import GenericPortFactory
from bulkio import BulkioPortFactory
from burstio import BurstioPortFactory
from event import PropertyEventPortGenerator
from message import MessagePortFactory

class PythonPortFactory(PortFactoryList):
    def __init__(self):
        factories = (BulkioPortFactory(), BurstioPortFactory(), PropertyEventPortGenerator,
                     MessagePortFactory(), GenericPortFactory())
        super(PythonPortFactory,self).__init__(*factories)
