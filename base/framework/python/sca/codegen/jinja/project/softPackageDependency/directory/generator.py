
from sca.codegen.jinja.common import ShellTemplate, AutomakeTemplate, AutoconfTemplate
from sca.codegen.jinja.loader import CodegenLoader
from sca.codegen.jinja.mapping import ComponentMapper
from sca.codegen.jinja.generator import CodeGenerator

if not '__package__' in locals():
    # Python 2.4 compatibility
    __package__ = __name__.rsplit('.', 1)[0]

loader = CodegenLoader(__package__,
                       {'common'     : 'sca.codegen.jinja.common',
                        'base'       : 'sca.codegen.jinja.cpp.component.base'})

class DependencyDirectoryProjectGenerator(CodeGenerator):

    def loader(self, project):
        return loader

    def templates(self, project):
        return [
            AutomakeTemplate('Makefile.am'),
            AutoconfTemplate('configure.ac'),
            ShellTemplate('base/build.sh'),
            ShellTemplate('common/reconf')
            ]

    def componentMapper(self):
        return ComponentMapper()

    def propertyMapper(self):
        return None

    def portMapper(self):
        return None

