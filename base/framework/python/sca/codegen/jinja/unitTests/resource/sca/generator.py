from sca.codegen.jinja.generator import TopLevelGenerator
from sca.codegen.jinja.python import PythonTemplate
from sca.codegen.jinja.mapping import ProjectMapper

import jinja2

if not '__package__' in locals():
    # Python 2.4 compatibility
    __package__ = __name__.rsplit('.', 1)[0]

loader = jinja2.PackageLoader(__package__)

class TestGenerator(TopLevelGenerator):
    def projectMapper(self):
        return ProjectMapper()

    def loader(self, project):
        return loader

    def templates(self, project):
        return [
            PythonTemplate('test.py', 'test_' + project['basename'] + '.py')
            ]
