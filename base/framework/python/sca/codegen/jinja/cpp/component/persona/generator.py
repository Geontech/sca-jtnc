
from sca.codegen.jinja.cpp.component.pull.generator import PullComponentGenerator
from sca.codegen.jinja.loader import CodegenLoader
from sca.codegen.jinja.common import ShellTemplate, AutomakeTemplate, AutoconfTemplate
from sca.codegen.jinja.cpp import CppTemplate

from mapping import PersonaComponentMapper

if not '__package__' in locals():
    # Python 2.4 compatibility
    __package__ = __name__.rsplit('.', 1)[0]

loader = CodegenLoader(__package__,
                       {'pull'       : 'sca.codegen.jinja.cpp.component.pull',
                        'common'     : 'sca.codegen.jinja.common',
                        'base'       : 'sca.codegen.jinja.cpp.component.base',
                        'properties' : 'sca.codegen.jinja.cpp.properties'})

class PersonaComponentGenerator(PullComponentGenerator):
    def loader(self, component):
        return loader

    def componentMapper(self):
        return PersonaComponentMapper()

    def templates(self, component):
        templates = [
            CppTemplate('resource.cpp', component['userclass']['file'], userfile=True),
            CppTemplate('resource.h', component['userclass']['header'], userfile=True),
            CppTemplate('pull/resource_base.cpp', component['baseclass']['file']),
            CppTemplate('pull/resource_base.h', component['baseclass']['header']),
            CppTemplate('main.cpp', userfile=True),
            AutomakeTemplate('Makefile.am'),
            AutomakeTemplate('base/Makefile.am.ide', userfile=True),
            AutoconfTemplate('configure.ac'),
            ShellTemplate('base/build.sh'),
            ShellTemplate('common/reconf')
        ]

        is_device = True
        is_executable = False
        for superclass in component['superclasses']:
            if superclass['name'] == 'Resource_impl':
                is_device = False
            if superclass['name'] == 'ExecutableDeviceComponent':
                is_executable = True
        
        # Append programmable files if it's a persona device
        if is_device:
            templates.append(CppTemplate('persona_base.cpp', 
                                         component['reprogclass']['file'], 
                                         userfile=True))
            templates.append(CppTemplate('persona_base.h', 
                                         component['reprogclass']['header'], 
                                         userfile=True))

        # Append entry_point file if it's an executable device
        if is_executable:
            templates.append(CppTemplate('entry_point.h', userfile=True))

        # Add port implementations if required
        templates.extend(CppTemplate('pull/'+fn) for fn in self.getPortTemplates(component))

        if component['structdefs']:
            templates.append(CppTemplate('pull/struct_props.h'))

        return templates
