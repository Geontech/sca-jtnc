
from sca.codegen import utils
from sca.codegen.jinja.loader import CodegenLoader
from sca.codegen.jinja.common import ShellTemplate, AutomakeTemplate, AutoconfTemplate
from sca.codegen.jinja.python import PythonTemplate
from sca.codegen.jinja.python.properties import PythonPropertyMapper
from sca.codegen.jinja.python.ports import PythonPortMapper
from sca.codegen.jinja.python.component.frontend.portfactory import FEIPortFactory
from sca.codegen.jinja.python.component.pull import PullComponentGenerator

from mapping import BinaryComponentMapper

if not '__package__' in locals():
    # Python 2.4 compatibility
    __package__ = __name__.rsplit('.', 1)[0]

loader = CodegenLoader(__package__,
                       {'common': 'sca.codegen.jinja.common',
                        'pull':   'sca.codegen.jinja.python.component.pull',
                        'base':   'sca.codegen.jinja.python.component.base'})

class BinaryComponentGenerator(PullComponentGenerator):
    # Need to keep auto_start and queued_ports to handle legacy options
    def parseopts (self, auto_start=True, queued_ports=False, legacy_structs=True):
        self.legacy_structs = utils.parseBoolean(legacy_structs)

    def loader(self, component):
        return loader

    def componentMapper(self):
        return BinaryComponentMapper()

    def propertyMapper(self):
        return PythonPropertyMapper(legacy_structs=self.legacy_structs)

    def portMapper(self):
        return PythonPortMapper()

    def portFactory(self):
        return FEIPortFactory()

    def templates(self, component):
        templates = [
            PythonTemplate('resource_base.py', component['baseclass']['file']),
            PythonTemplate('resource.py', component['userclass']['file'], executable=True, userfile=True),
            AutoconfTemplate('pull/configure.ac'),
            AutomakeTemplate('base/Makefile.am'),
            AutomakeTemplate('Makefile.am.ide', userfile=True),
            ShellTemplate('common/reconf')
        ]
        return templates
