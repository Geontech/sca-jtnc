
import sys
from sca.codegen.model.softwarecomponent import ComponentTypes
from sca.codegen.lang.idl import IDLInterface

from sca.codegen.jinja.python.component.pull.mapping import PullComponentMapper

class PersonaComponentMapper(PullComponentMapper):
    def _mapComponent(self, softpkg):
        pycomp = PullComponentMapper._mapComponent(self, softpkg)
        pycomp['personaclass'] = self.personaClass(softpkg)
        return pycomp

    @staticmethod
    def personaClass(softpkg):
        personaclass = softpkg.basename() + '_persona_base'
        return {'name'  : personaclass,
                'file'  : personaclass+'.py'}
