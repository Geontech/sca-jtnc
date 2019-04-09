import subprocess
import os
import shutil
from sca.parsers import spd
from sca.packagegen.softPackage import SoftPackage

SCAHOME=os.environ["SCAHOME"]
DEFAULT_RESOURCE_TEMPLATE="/lib/python/sca/packagegen/templates/resourceTemplate.spd.xml"

class DirectoryPackageDependency(SoftPackage):

    def __init__(
            self,
            name,
            implementation,
            libraryLocation,
            outputDir=".",
            sharedLibraries  = [],
            spdTemplateFile = SCAHOME + DEFAULT_RESOURCE_TEMPLATE,
            variant = ""):

        SoftPackage.__init__(self, name, implementation, outputDir)

        # intantiate the class object representing the spd file
        self.spd = spd.parse(spdTemplateFile)

        self._setNameInSpd()
        self._setImplementation()

        self._createWavedevContent(generator="project.softPackageDependency.directory")

        # Create the output directory strucutre.  A share directory will be
        # created in the implemetation directory.  The share directory is
        # a symbolic link to the target directory.
        fullOutputDir = outputDir+"/" + name + "/"
        if not os.path.exists(fullOutputDir + implementation):
            os.makedirs(fullOutputDir + implementation)
        if not os.path.exists(fullOutputDir + implementation + "/share"):
            if not os.path.isabs(libraryLocation):
                libraryLocation = os.path.join(os.getcwd(), libraryLocation)
            shutil.copytree(libraryLocation, fullOutputDir + implementation + "/share")

        # Add soft package dependencies to the package being created (in the
        # case that the soft package dependency being created has its own
        # soft package dependencies).
        for sharedLibrary in sharedLibraries:
            self.addSoftPackageDependency(sharedLibrary)


    def _setImplementation(self):
        '''
        Enter the appropriate values into the implementation element of the
        spd file.

        '''

        localfile = spd.localFile(name = self.implementation + "/share")
        code = spd.code(type_= "SharedLibrary", localfile = localfile)
        compiler = spd.compiler(version="4.1.2", name="/usr/bin/gcc")

        implementation = spd.implementation(
            id_=self.implementation,
            description="",
            code = code,
            compiler = compiler,
            programminglanguage = spd.programmingLanguage(name="Octave"),
            humanlanguage = spd.humanLanguage(name="EN"))
        os = spd.os(name="Linux")
        implementation.add_os(value=os)
        self.spd.add_implementation(value=implementation)

