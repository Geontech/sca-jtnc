
from sca.codegen.model.softwarecomponent import ComponentTypes
from sca.codegen.lang.idl import IDLInterface

from sca.codegen.jinja.cpp.component.pull.mapping import PullComponentMapper
import sys

class ProgrammableComponentMapper(PullComponentMapper):
    def _mapComponent(self, softpkg):
        cppcomp = PullComponentMapper._mapComponent(self, softpkg)
        cppcomp['programmable'] = True
        cppcomp['reprogclass'] = self.reprogClass(softpkg)
        cppcomp['executesHWComponents'] = False # TODO: Implement this 
        self._validateAggregateDevice(cppcomp)
        return cppcomp

    def _validateAggregateDevice(self, comp):
        if not comp.has_key('superclasses'):
            print >> sys.stderr, "WARNING: Programmable device MUST be an aggregate device!"
            return

        missingAggDevice = True
        for superclass in comp['superclasses']:
            if not superclass.has_key('name'):
                continue
            if "Aggregate" in superclass['name']:
                missingAggDevice = False
                break
        if missingAggDevice:
            print >> sys.stderr, "WARNING: Programmable device MUST be an aggregate device!"

    @staticmethod
    def reprogClass(softpkg):
        reprogclass = softpkg.basename() + '_prog_base'
        return {'name'  : reprogclass,
                'header': reprogclass+'.h',
                'file'  : reprogclass+'.cpp'}
