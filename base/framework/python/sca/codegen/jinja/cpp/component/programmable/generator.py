
from sca.codegen.jinja.cpp.component.pull.generator import PullComponentGenerator
from sca.codegen.jinja.loader import CodegenLoader
from sca.codegen.jinja.common import ShellTemplate, AutomakeTemplate, AutoconfTemplate
from sca.codegen.jinja.cpp import CppTemplate

from mapping import ProgrammableComponentMapper

if not '__package__' in locals():
    # Python 2.4 compatibility
    __package__ = __name__.rsplit('.', 1)[0]

loader = CodegenLoader(__package__,
                       {'pull'       : 'sca.codegen.jinja.cpp.component.pull',
                        'common'     : 'sca.codegen.jinja.common',
                        'base'       : 'sca.codegen.jinja.cpp.component.base',
                        'properties' : 'sca.codegen.jinja.cpp.properties'})

class ProgrammableComponentGenerator(PullComponentGenerator):
    # Need to keep use_vector_impl, auto_start and queued_ports to handle legacy options 
    def parseopts (self, use_vector_impl=True,auto_start=True,queued_ports=False):
        pass

    def loader(self, component):
        return loader

    def componentMapper(self):
        return ProgrammableComponentMapper()

    def templates(self, component):
        templates = [
            CppTemplate('resource.cpp', component['userclass']['file'], userfile=True),
            CppTemplate('resource.h', component['userclass']['header'], userfile=True),
            CppTemplate('pull/resource_base.cpp', component['baseclass']['file']),
            CppTemplate('pull/resource_base.h', component['baseclass']['header']),
            CppTemplate('programmable_base.h', component['reprogclass']['header']),
            CppTemplate('entry_point.h'),
            CppTemplate('base/main.cpp'),
            AutomakeTemplate('base/Makefile.am'),
            AutomakeTemplate('base/Makefile.am.ide'),
            AutoconfTemplate('base/configure.ac'),
            ShellTemplate('base/build.sh'),
            ShellTemplate('common/reconf')
        ]

        for gen in component['portgenerators']:
            # Need to include port_impl if a non-bulkio port exists
            if str(type(gen)).find("BulkioPortGenerator") == -1:
                templates.append(CppTemplate('pull/port_impl.cpp'))
                templates.append(CppTemplate('pull/port_impl.h'))
                break

        if component['structdefs']:
            templates.append(CppTemplate('pull/struct_props.h'))

        return templates

    def map(self, softPkg):
        dict = PullComponentGenerator.map(self, softPkg)
        
        dict['hasHwLoadRequestProp'] = False
        dict['hasHwLoadStatusProp'] = False
        for prop in dict['properties']:
            if prop.has_key('structdef'):
                if str(prop['structdef']['cpptype']) == "hw_load_request_struct":
                    dict['hasHwLoadRequestProp'] = True
                if str(prop['structdef']['cpptype']) == "hw_load_status_struct":
                    dict['hasHwLoadStatusProp'] = True
                    

        return dict
