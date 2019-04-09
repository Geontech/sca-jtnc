
from sca.codegen import libraries
from sca.codegen.model.softwarecomponent import ComponentTypes
from sca.codegen.jinja.mapping import ProjectMapper

_projectTypes = {
    ComponentTypes.RESOURCE: 'Component',
    ComponentTypes.DEVICE:   'Device',
    ComponentTypes.LOADABLEDEVICE: 'LoadableDevice',
    ComponentTypes.EXECUTABLEDEVICE: 'ExecutableDevice',
    ComponentTypes.SERVICE:  'Service',
    ComponentTypes.SHAREDPACKAGE: 'SharedPackage'
}

class ComponentProjectMapper(ProjectMapper):
    def _mapComponent(self, softpkg):
        component = {}
        component['type'] = _projectTypes[softpkg.type()]
        component['interfaces'] = [libraries.getRPMDependency(name) for name in self.getInterfaceNamespaces(softpkg)]
        component['specfile'] = softpkg.name()+'.spec'
        return component

    def _mapImplementation(self, impl, generator):
        impldict = {}
        impldict['requires'] = generator.rpmRequires()
        impldict['buildrequires'] = generator.rpmBuildRequires()
        return impldict
