
import sys
from sca.codegen.model.softwarecomponent import ComponentTypes
from sca.codegen.lang.idl import IDLInterface

from sca.codegen.jinja.python.component.pull.mapping import PullComponentMapper

class ProgrammableComponentMapper(PullComponentMapper):
    def _mapComponent(self, softpkg):
        pycomp = PullComponentMapper._mapComponent(self, softpkg)
        pycomp['progclass'] = self.progClass(softpkg)
        return pycomp

    @staticmethod
    def progClass(softpkg):
        progclass = softpkg.basename() + '_prog_base'
        return {'name'  : progclass,
                'file'  : progclass+'.py'}
