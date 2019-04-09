
import os

from sca.codegen.jinja.generator import CodeGenerator

class CppCodeGenerator(CodeGenerator):
    def sourceFiles(self, component):
        for template in self.templates(component):
            filename, ext = os.path.splitext(template.filename)
            if ext in ('.h', '.cpp'):
                yield template.filename
