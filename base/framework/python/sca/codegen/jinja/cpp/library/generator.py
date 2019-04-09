
import os

from sca.codegen.jinja.loader import CodegenLoader
from sca.codegen.jinja.common import ShellTemplate, AutomakeTemplate, AutoconfTemplate, PkgconfigTemplate
from sca.codegen.jinja.cpp import CppCodeGenerator, CppTemplate
from sca.codegen.jinja.mapping import SoftpkgMapper

from sca.codegen.lang.automake import libtoolName

if not '__package__' in locals():
    # Python 2.4 compatibility
    __package__ = __name__.rsplit('.', 1)[0]

loader = CodegenLoader(__package__,
                       {'common': 'sca.codegen.jinja.common',
                        'base':   'sca.codegen.jinja.cpp.component.base'})

class CppLibraryMapper(SoftpkgMapper):
    def _mapComponent(self, softpkg):
        cpplib = {}
        libname = softpkg.basename()
        cpplib['libname'] = libname
        cpplib['ltlibname'] = libtoolName(libname)
        cpplib['incfile'] = libname + '.h'
        cpplib['srcfile'] = libname + '.cpp'
        cpplib['pcfile'] = softpkg.name() + '.pc'
        return cpplib

class CppLibraryGenerator(CppCodeGenerator):
    def parseopts(self, includedir='include', sourcedir='src'):
        self.includedir = includedir
        self.sourcedir = sourcedir

    def loader(self, component):
        return loader

    def componentMapper(self):
        return CppLibraryMapper()

    def propertyMapper(self):
        return None

    def portMapper(self):
        return None

    def templates(self, library):
        userHeader = os.path.join(self.includedir, library['incfile'])
        userSource = os.path.join(self.sourcedir, library['srcfile'])

        templates = [
            CppTemplate('library.h', userHeader, userfile=True),
            CppTemplate('library.cpp', userSource, userfile=True),
            AutomakeTemplate('Makefile.am'),
            AutomakeTemplate('base/Makefile.am.ide', userfile=True),
            AutoconfTemplate('configure.ac'),
            ShellTemplate('base/build.sh'),
            ShellTemplate('common/reconf'),
            PkgconfigTemplate('library.pc.in', library['pcfile']+'.in')
        ]

        return templates
