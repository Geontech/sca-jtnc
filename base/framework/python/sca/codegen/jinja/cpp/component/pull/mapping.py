
from sca.codegen.model.softwarecomponent import ComponentTypes
from sca.codegen.lang.idl import IDLInterface

from sca.codegen.jinja.cpp.component.base import BaseComponentMapper

class PullComponentMapper(BaseComponentMapper):
    def _mapComponent(self, softpkg):
        cppcomp = {}
        cppcomp['baseclass'] = self.baseClass(softpkg)
        cppcomp['userclass'] = self.userClass(softpkg)
        cppcomp['superclasses'] = self.superClasses(softpkg)
        cppcomp['interfacedeps'] = tuple(self.getInterfaceDependencies(softpkg))
        cppcomp['hasmultioutport'] = self.hasMultioutPort(softpkg)
        return cppcomp

    @staticmethod
    def userClass(softpkg):
        return {'name'  : softpkg.basename()+'_i',
                'header': softpkg.basename()+'.h',
                'file'  : softpkg.basename()+'.cpp'}

    @staticmethod
    def baseClass(softpkg):
        baseclass = softpkg.basename() + '_base'
        return {'name'  : baseclass,
                'header': baseclass+'.h',
                'file'  : baseclass+'.cpp'}

    @staticmethod
    def superClasses(softpkg):
        aggregate = ''
        header = ''
        if softpkg.type() == ComponentTypes.RESOURCE:
            name = 'Component'
            header = '<sca/'+name+'.h>'
        elif softpkg.type() == ComponentTypes.DEVICE:
            name = 'DeviceComponent'
            aggregate = 'virtual POA_CF::AggregatePlainDevice'
            header = '<sca/'+name+'.h>'
        elif softpkg.type() == ComponentTypes.LOADABLEDEVICE:
            name = 'LoadableDevice_impl'
            aggregate = 'virtual POA_CF::AggregateLoadableDevice'
            header = '<sca/'+name+'.h>'
        elif softpkg.type() == ComponentTypes.EXECUTABLEDEVICE:
            name = 'ExecutableDeviceComponent'
            aggregate = 'virtual POA_CF::AggregateExecutableDevice'
            header = '<sca/'+name+'.h>'
        else:
            raise ValueError, 'Unsupported software component type', softpkg.type()
        if softpkg.descriptor().supports('IDL:CF/AggregateDevice:1.0'):
            if 'Executable' in aggregate:
                name = 'AggregateExecutableDeviceComponent'
                header = '<sca/AggregateDeviceComponent.h>'
            else:
                name = 'AggregateDeviceComponent'
                header = '<sca/AggregateDeviceComponent.h>'

        classes = [{'name': name, 'header': header}]

        if softpkg.descriptor().supports('IDL:CF/AggregateDevice:1.0'):
            classes.append({'name': aggregate, 'header': '<CF/AggregateDevices.h>'})
        return classes
