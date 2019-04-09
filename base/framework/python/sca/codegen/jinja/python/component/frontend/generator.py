
from sca.codegen import utils
from sca.codegen.jinja.loader import CodegenLoader
from sca.codegen.jinja.common import ShellTemplate, AutomakeTemplate, AutoconfTemplate
from sca.codegen.jinja.python import PythonTemplate
from sca.codegen.jinja.python.component.frontend.portfactory import FEIPortFactory
from sca.codegen.jinja.python.component.pull import PullComponentGenerator

from mapping import FrontendComponentMapper, FrontendPropertyMapper

if not '__package__' in locals():
    # Python 2.4 compatibility
    __package__ = __name__.rsplit('.', 1)[0]

loader = CodegenLoader(__package__,
                       {'common': 'sca.codegen.jinja.common',
                        'pull':   'sca.codegen.jinja.python.component.pull',
                        'base':   'sca.codegen.jinja.python.component.base'})

class FrontendComponentGenerator(PullComponentGenerator):
    def map(self, softpkg):
        component = super(FrontendComponentGenerator,self).map(softpkg)
        if 'FrontendTuner' in component['implements']:
            # For FEI tuner devices, disable member variable generation for
            # properties that are inherited from frontend::FrontendTunerDevice
            # base class
            for prop in component['properties']:
                if prop['pyname'] in ('device_kind', 'device_model',
                                       'frontend_tuner_allocation',
                                       'frontend_listener_allocation',
                                       'frontend_scanner_allocation',
                                       'frontend_tuner_status'):
                    prop['inherited'] = True
        return component

    def loader(self, component):
        return loader

    def componentMapper(self):
        return FrontendComponentMapper()

    def propertyMapper(self):
        return FrontendPropertyMapper(legacy_structs=False)

    def portFactory(self):
        return FEIPortFactory()

    def templates(self, component):
        templates = [
            PythonTemplate('resource_base.py', component['baseclass']['file']),
            PythonTemplate('resource.py', component['userclass']['file'], executable=True, userfile=True),
            AutoconfTemplate('pull/configure.ac'),
            AutomakeTemplate('base/Makefile.am'),
            AutomakeTemplate('base/Makefile.am.ide', userfile=True),
            ShellTemplate('common/reconf')
        ]
        return templates
