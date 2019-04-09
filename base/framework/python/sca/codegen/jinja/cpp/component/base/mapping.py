
from sca.codegen.jinja.mapping import ComponentMapper
from sca.codegen import libraries

class BaseComponentMapper(ComponentMapper):
    def _mapComponent(self, softpkg):
        cppcomp = {}
        cppcomp['userclass'] = { 'name'  : softpkg.basename()+'_i',
                                 'header': softpkg.basename()+'.h' }
        cppcomp['interfacedeps'] = tuple(self.getInterfaceDependencies(softpkg))
        return cppcomp

    def _mapImplementation(self, impl):
        impldict = {}
        if impl.isModule():
            impldict['module'] = True
            impldict['target'] = impl.entrypoint().replace('.so', '.la')
        else:
            impldict['target'] = impl.entrypoint()
        return impldict

    def getInterfaceDependencies(self, softpkg):
        for namespace in self.getInterfaceNamespaces(softpkg):
            yield libraries.getPackageRequires(namespace)
