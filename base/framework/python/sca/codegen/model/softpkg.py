
import os
import sca.parsers

from sca.codegen.utils import strenum

import properties
from softwarecomponent import SoftwareComponent, ComponentTypes


class SoftpkgRef(object):
    def __init__(self, ref):
        self.spdfile = ref.localfile.name
        if ref.implref:
            self.impl = ref.implref.refid
        else:
            self.impl = None


class Implementation(object):
    def __init__(self, impl):
        self.__impl = impl
        self.__softpkgdeps = []
        #for dep in self.__impl.dependency:
            #if not dep.softpkgref:
                #continue
            #self.__softpkgdeps.append(SoftpkgRef(dep.softpkgref))

    def prfFile(self):
        if self.__impl.propertyfile:
            return self.__impl.propertyfile.localfile.name
        else:
            return None

    def identifier(self):
        return self.__impl._id

    def entrypoint(self):
        if not self.__impl.code.entrypoint:
            return self.__impl.code.localfile.name
        return self.__impl.code.entrypoint

    def isModule(self):
        return self.__impl.code.get_type() == 'SharedLibrary'

    def localfile(self):
        return self.__impl.code.localfile.name

    def programminglanguage(self):
        return self.__impl.programminglanguage.name

    def softpkgdeps(self):
        return self.__softpkgdeps


def softPkgRef(root_impl, name, localfile, implref):
    try:
        spd = sca.parsers.spd.parse(os.getenv('SCAROOT')+'/dom/'+localfile)
    except:
        spd = None
    return {'name':name, 'root_impl': root_impl, 'implref': implref, 'localfile':localfile, 'spd':spd }

def resolveSoftPkgDeps(spd=None, root_impl=None):
    softpkgdeps = []
    #if spd == None:
        #return softpkgdeps
    #for impl in spd.get_implementation():
        #if root_impl != None:
            #troot = root_impl
        #else:
            #troot = impl.get_id()
        #for dep in impl.get_dependency():
            #if dep.get_softpkgref() != None:
                #localfile = dep.get_softpkgref().get_localfile().name
                #implref=None
                #try:
                    #implref = dep.get_softpkgref().get_implref().get_refid()
                #except:
                    #pass
                #pkg_name = localfile.split('/')[-1].split('.')[0]
                #softpkgdeps.append(softPkgRef(troot, pkg_name, localfile,implref))
                #softpkgdeps += resolveSoftPkgDeps(softpkgdeps[-1]['spd'], troot)
    return softpkgdeps


class SoftPkg(object):
    def __init__(self, spdFile):
        self.__spdFile = os.path.basename(spdFile)
        self.__spd = sca.parsers.spd.parse(spdFile)
        self.__softpkgdeps = resolveSoftPkgDeps(self.__spd)
        self.__impls = dict((impl._id, Implementation(impl)) for impl in self.__spd.implementation)

        self.__path = os.path.dirname(os.path.abspath(spdFile))

        if self.__spd.get_descriptor():
            self.__scdFile = self.__spd.descriptor.localfile.name
            self.__desc = SoftwareComponent(os.path.join(self.__path, self.__scdFile))
        else:
            self.__scdFile = None
            self.__desc = None

        if self.__spd.get_propertyfile():
            self.__prfFile = self.__spd.propertyfile.localfile.name
            if os.path.exists(os.path.join(self.__path, self.__prfFile)):
                self.__props = properties.parse(os.path.join(self.__path, self.__prfFile))
            else:
                self.__props = []
        else:
            self.__props = []
            self.__prfFile = None

    def spdFile(self):
        return self.__spdFile

    def prfFile(self):
        return self.__prfFile

    def scdFile(self):
        return self.__scdFile

    def path(self):
        return self.__path

    def type(self):
        if self.__desc:
            return self.__desc.type()
        else:
            return ComponentTypes.SHAREDPACKAGE

    def isDevice(self):
        return self.type() == ComponentTypes.DEVICE

    def descriptor(self):
        return self.__desc

    def name(self):
        return self.__spd.name

    def namespace(self):
        return self.__spd.name.split('.')[:-1]

    def basename(self):
        return self.__spd.name.split('.')[-1]

    def version(self):
        if not self.__spd.version:
            return '1.0.0'
        else:
            return self.__spd.version

    def hasDescription(self):
        return self.description() is not None

    def description(self):
        return self.__spd.description

    def usesPorts(self):
        if self.__desc:
            return self.__desc.uses()
        else:
            return None

    def providesPorts(self):
        if self.__desc:
            return self.__desc.provides()
        else:
            return None

    def ports(self):
        if self.__desc:
            return self.__desc.ports()
        else:
            return None

    def properties(self):
        return self.__props

    def implementations(self):
        return self.__impls.values()

    def getImplementation(self, implId):
        return self.__impls[implId]

    def hasPorts(self):
        return len(self.ports()) > 0

    def hasProperties(self):
        return len(self.__props) > 0

    def hasStructProps(self):
        for prop in self.__props:
            if prop.isStruct():
                return True
        return False

    def getSoftPkgDeps(self):
        return self.__softpkgdeps

    def getStructDefinitions(self):
        structdefs = [s for s in self.getStructProperties()]
        structdefs += [s.struct() for s in self.getStructSequenceProperties()]
        return structdefs

    def getSimpleProperties(self):
        return [p for p in self.__props if not p.isStruct() and not p.isSequence()]

    def getSimpleSequenceProperties(self):
        return [p for p in self.__props if not p.isStruct() and p.isSequence()]

    def getStructProperties(self):
        return [p for p in self.__props if p.isStruct() and not p.isSequence()]

    def getStructSequenceProperties(self):
        return [p for p in self.__props if p.isStruct() and p.isSequence()]

    def hasSDDSPort(self):
        for port in self.ports():
            if port.repid().find('BULKIO/dataSDDS'):
                return True
        return False

    def getSdrPath(self):
        comptype = self.type()
        print '............', dir(comptype)
        print '............', type(comptype)
        print '............', comptype.lower()
        print ComponentTypes
        print ComponentTypes.RESOURCE, ComponentTypes.DEVICE
        if comptype == ComponentTypes.RESOURCE:
            return 'dom/components'
        elif comptype == ComponentTypes.DEVICE or comptype == ComponentTypes.LOADABLEDEVICE or comptype == ComponentTypes.EXECUTABLEDEVICE:
            return 'dev/devices'
        elif comptype == ComponentTypes.SERVICE:
            return 'dev/services'
        elif comptype == ComponentTypes.SHAREDPACKAGE:
            return 'dom/deps'
        raise ValueError, 'Unsupported software component type', comptype

