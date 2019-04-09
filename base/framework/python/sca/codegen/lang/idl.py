import os
from sca.utils.sca import importIDL
from sca.utils.idllib import IDLLibrary

from sca.codegen.utils import strenum

CorbaTypes = strenum('octet','boolean','char','short','ushort','long','ulong',
                     'longlong','ulonglong','float','double','string','objref', 'utctime')

idlRepo = IDLLibrary()
idlRepo.addSearchPath(os.path.join(os.environ['SCAHOME'], 'share/idl'))

class IDLInterface(object):
    def __init__(self, repid):
        self.__repid = repid
        interface = self.__repid.split(':')[1]
        if '/' in interface:
            self.__namespace, self.__interface = interface.rsplit('/', 1)
        else:
            self.__namespace = ''
            self.__interface = interface
        self.__idl = None

    def repid(self):
        return self.__repid

    def namespace(self):
        return self.__namespace

    def interface(self):
        return self.__interface

    def idl(self):
        if not self.__idl:
            # NB: This may be a costly operation, as it can parse most of the
            #     IDL files known to SCA if the source file is not obvious;
            #     it's not strictly necessary unless looking at the operations
            #     or attributes.
            self.__idl = idlRepo.getInterface(self.repid())
        return self.__idl

    def operations(self):
        return self.idl().operations

    def attributes(self):
        return self.idl().attributes

    def filename(self):
        return self.idl().filename

class IDLStruct(object):
    def __init__(self, repid):
        self.__repid = repid
        interface = self.__repid.split(':')[1]
        if '/' in interface:
            self.__namespace, self.__interface = interface.rsplit('/', 1)
        else:
            self.__namespace = ''
            self.__interface = interface
        self.__idl = None

    def repid(self):
        return self.__repid

    def namespace(self):
        return self.__namespace

    def idl(self):
        if not self.__idl:
            # NB: This may be a costly operation, as it can parse most of the
            #     IDL files known to SCA if the source file is not obvious;
            #     it's not strictly necessary unless looking at the operations
            #     or attributes.
            self.__idl = idlRepo.getIdlStruct(self.repid())
        return self.__idl

    def members(self):
        return self.idl().members
