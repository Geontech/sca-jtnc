
import jinja2

from sca.codegen.jinja.generator import TopLevelGenerator
from sca.codegen.jinja.common import ShellTemplate, SpecfileTemplate

from mapping import ComponentProjectMapper

if not '__package__' in locals():
    # Python 2.4 compatibility
    __package__ = __name__.rsplit('.', 1)[0]

loader = jinja2.PackageLoader(__package__)

class ComponentProjectGenerator(TopLevelGenerator):
    def projectMapper(self):
        return ComponentProjectMapper()

    def loader(self, project):
        return loader

    def templates(self, project):
        return [
            ShellTemplate('build.sh'),
            SpecfileTemplate('component.spec', project['specfile'])
            ]
