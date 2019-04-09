
from sca.codegen import utils
from sca.codegen.jinja.loader import CodegenLoader
from sca.codegen.jinja.python import PythonCodeGenerator, PythonTemplate

from sca.codegen.jinja.python.component.pull import PullComponentGenerator
from mapping import ProgrammableComponentMapper

if not '__package__' in locals():
    # Python 2.4 compatibility
    __package__ = __name__.rsplit('.', 1)[0]

loader = CodegenLoader(__package__,
                       {'common': 'sca.codegen.jinja.common',
                        'base':   'sca.codegen.jinja.python.component.base',
                        'pull':   'sca.codegen.jinja.python.component.pull'})

class ProgrammableComponentGenerator(PullComponentGenerator):
    def loader(self, component):
        return loader

    def componentMapper(self):
        return ProgrammableComponentMapper()

    def templates(self, component):
        templates = PullComponentGenerator.templates(self, component)
        templates.append(PythonTemplate('programmable_base.py', component['progclass']['file']))
        return templates

    def map(self, softPkg):
        dict = PullComponentGenerator.map(self, softPkg)
        dict['hasHwLoadRequestProp'] = False
        dict['hasHwLoadStatusProp'] = False
        for prop in dict['properties']:
            if prop.has_key('structdef'):
                if str(prop['structdef']['pyclass']) == "HwLoadRequest":
                    dict['hasHwLoadRequestProp'] = True
                if str(prop['structdef']['pyclass']) == "HwLoadStatus":
                    dict['hasHwLoadStatusProp'] = True
        return dict
 
