
from sca.codegen.jinja.loader import CodegenLoader
from sca.codegen.jinja.python import PythonTemplate

from sca.codegen.jinja.python.component.pull import PullComponentGenerator
from mapping import PersonaComponentMapper

if not '__package__' in locals():
    # Python 2.4 compatibility
    __package__ = __name__.rsplit('.', 1)[0]

loader = CodegenLoader(__package__,
                       {'common': 'sca.codegen.jinja.common',
                        'base':   'sca.codegen.jinja.python.component.base',
                        'pull':   'sca.codegen.jinja.python.component.pull'})

class PersonaComponentGenerator(PullComponentGenerator):
    def loader(self, component):
        return loader

    def componentMapper(self):
        return PersonaComponentMapper()

    def templates(self, component):
        templates = PullComponentGenerator.templates(self, component)
        templates.append(PythonTemplate('persona_base.py', component['personaclass']['file']))
        return templates
