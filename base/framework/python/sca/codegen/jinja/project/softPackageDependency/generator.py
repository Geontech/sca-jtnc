
from sca.codegen.jinja.common import ShellTemplate, SpecfileTemplate
from sca.codegen.jinja.generator import TopLevelGenerator
from sca.codegen.jinja.loader import CodegenLoader
from mapping import DependencyProjectMapper

if not '__package__' in locals():
    # Python 2.4 compatibility
    __package__ = __name__.rsplit('.', 1)[0]

loader = CodegenLoader(__package__)

class DependencyProjectGenerator(TopLevelGenerator):

    def loader(self, project):
        return loader

    def templates(self, project):
        return [
            ShellTemplate('build.sh'),
            SpecfileTemplate('dependency.spec', project['specfile'])
            ]

    def projectMapper(self):
        return DependencyProjectMapper()

