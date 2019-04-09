
from sca.codegen.model.softwarecomponent import ComponentTypes
from sca.codegen.lang.idl import IDLInterface

from sca.codegen.jinja.cpp.component.pull.mapping import PullComponentMapper

class PersonaComponentMapper(PullComponentMapper):
    def _mapComponent(self, softpkg):
        cppcomp = PullComponentMapper._mapComponent(self, softpkg)
        cppcomp['reprogclass'] = self.reprogClass(softpkg)
        return cppcomp
    
    @staticmethod
    def reprogClass(softpkg):
        reprogclass = softpkg.basename() + '_persona_base'
        return {'name'  : reprogclass,
                'header': reprogclass+'.h',
                'file'  : reprogclass+'.cpp'}
