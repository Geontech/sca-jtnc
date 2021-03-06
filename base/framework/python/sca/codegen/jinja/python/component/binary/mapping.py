
import sys
from sca.codegen.model.softwarecomponent import ComponentTypes
from sca.codegen.lang.idl import IDLInterface

from sca.codegen.jinja.python.component.pull.mapping import PullComponentMapper

class BinaryComponentMapper(PullComponentMapper):
    def _mapComponent(self, softpkg):
        pycomp = {}
        pycomp['baseclass'] = self.baseClass(softpkg)
        pycomp['userclass'] = self.userClass(softpkg)
        pycomp['superclasses'] = self.superClasses(softpkg)
        pycomp['poaclass'] = self.poaClass(softpkg)
        pycomp['interfacedeps'] = self.getInterfaceDependencies(softpkg)
        pycomp['hasmultioutport'] = self.hasMultioutPort(softpkg)
        return pycomp

    @staticmethod
    def userClass(softpkg):
        return {'name'  : softpkg.basename()+'_i',
                'file'  : softpkg.basename()+'.py'}

    @staticmethod
    def baseClass(softpkg):
        baseclass = softpkg.basename() + '_base'
        return {'name'  : baseclass,
                'file'  : baseclass+'.py'}

    @staticmethod
    def superClasses(softpkg):
        if softpkg.type() == ComponentTypes.RESOURCE:
            name = 'Resource'
            package = 'sca.resource'
        elif softpkg.type() == ComponentTypes.DEVICE:
            name = 'Device'
            package = 'sca.device'
            for port in softpkg.providesPorts():
                idl = IDLInterface(port.repid())
                if idl.namespace() == 'FRONTEND':
                    if idl.interface().find('DigitalTuner') != -1 or \
                       idl.interface().find('AnalogTuner') != -1 or \
                       idl.interface().find('FrontendTuner') != -1:
                        name = 'frontend.FrontendTunerDevice'
        elif softpkg.type() == ComponentTypes.LOADABLEDEVICE:
            name = 'LoadableDevice'
            package = 'sca.device'
        elif softpkg.type() == ComponentTypes.EXECUTABLEDEVICE:
            name = 'ExecutableDevice'
            package = 'sca.device'
        else:
            raise ValueError, 'Unsupported software component type', softpkg.type()
        classes = [{'name': name, 'package': package}]
        if softpkg.descriptor().supports('IDL:CF/AggregateDevice:1.0'):
            classes.append({'name': 'AggregateDevice', 'package': 'sca.device'})
        return classes

    @staticmethod
    def poaClass(softpkg):
        aggregate = softpkg.descriptor().supports('IDL:CF/AggregateDevice:1.0')
        if softpkg.type() == ComponentTypes.RESOURCE:
            return 'CF__POA.Resource'
        elif softpkg.type() == ComponentTypes.DEVICE:
            if aggregate:
                return 'CF__POA.AggregatePlainDevice'
            else:
                return 'CF__POA.Device'
        elif softpkg.type() == ComponentTypes.LOADABLEDEVICE:
            if aggregate:
                return 'CF__POA.AggregateLoadableDevice'
            else:
                return 'CF__POA.LoadableDevice'
        elif softpkg.type() == ComponentTypes.EXECUTABLEDEVICE:
            if aggregate:
                return 'CF__POA.AggregateExecutableDevice'
            else:
                return 'CF__POA.ExecutableDevice'
        else:
            raise ValueError, 'Unsupported software component type', softpkg.type()

    def hasFrontendPorts(self, softpkg):
        for port in softpkg.ports():
            if 'FRONTEND' in port.repid():
                return True
        return False

    def hasFrontendProvidesPorts(self, softpkg):
        for port in softpkg.providesPorts():
            if 'FRONTEND' in port.repid():
                return True
        return False

    def isAFrontendTuner(self,softpkg):
        return self.hasFrontendTunerProvidesPorts(softpkg) or \
               self.hasAnalogTunerProvidesPorts(softpkg) or \
               self.hasDigitalTunerProvidesPorts(softpkg)

    def hasFrontendTunerProvidesPorts(self, softpkg):
        for port in softpkg.providesPorts():
            idl = IDLInterface(port.repid())
            if idl.namespace() == 'FRONTEND':
                if idl.interface().find('FrontendTuner') != -1:
                    return True
        return False

    def hasDigitalTunerProvidesPorts(self, softpkg):
        for port in softpkg.providesPorts():
            idl = IDLInterface(port.repid())
            if idl.namespace() == 'FRONTEND':
                if idl.interface().find('DigitalTuner') != -1:
                    return True
        return False

    def hasAnalogTunerProvidesPorts(self, softpkg):
        for port in softpkg.providesPorts():
            idl = IDLInterface(port.repid())
            if idl.namespace() == 'FRONTEND':
                if idl.interface().find('AnalogTuner') != -1:
                    return True
        return False

