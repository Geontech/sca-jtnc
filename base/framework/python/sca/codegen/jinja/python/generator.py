
from sca.codegen.jinja.generator import CodeGenerator

class PythonCodeGenerator(CodeGenerator):
    def sourceFiles(self, component):
        for template in self.templates(component):
            if template.filename.endswith('.py'):
                yield template.filename
