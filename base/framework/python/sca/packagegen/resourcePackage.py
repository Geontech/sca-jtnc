import subprocess
import os
from sca.parsers import spd, scd, prf
from sca.packagegen.softPackage import SoftPackage

SCAHOME=os.environ["SCAHOME"]
DEFAULT_SPD_TEMPLATE="/lib/python/sca/packagegen/templates/resourceTemplate.spd.xml"
DEFAULT_SCD_TEMPLATE="/lib/python/sca/packagegen/templates/resourceTemplate.scd.xml"
DEFAULT_PRF_TEMPLATE="/lib/python/sca/packagegen/templates/resourceTemplate.prf.xml"

def standardizeComplexFormat(input):
    """
    Takes complex numbers of the form:

        A+Bj

    And converts to:

        A+jB

    """

    # Standardize everything to use "j" for sqrt(-1)
    input = input.replace("i", "j")

    try:
        complexVal = complex(input)
        if complexVal.imag >= 0:
            sign = "+"
        else:
            sign = "-"
        return str(complexVal.real) + sign + "j" + str(complexVal.imag)
    except:
        # Assume input is already in A+jB form
        return input

class ResourcePackage(SoftPackage):
    '''
    Class for creating a set of XML models representing the resource.  To
    create a new resource type, inherit from this class.  See
    octaveComponent.py for an example of how to use this class.

    '''

    def __init__(
            self,
            name,
            implementation,
            outputDir=".",
            generator="cpp.component.pull",
            spdTemplateFile = SCAHOME+DEFAULT_SPD_TEMPLATE,
            scdTemplateFile = SCAHOME+DEFAULT_SCD_TEMPLATE,
            prfTemplateFile = SCAHOME+DEFAULT_PRF_TEMPLATE,
            loggingConfigUri = None):
        '''
        Create a resource with no ports/properties.  Use helper methods to add
        additional elements.

        Note, "implementation" argument must be "cpp", "java", or "python"

        '''

        SoftPackage.__init__(self, name, implementation, outputDir)

        self.spd = spd.parse(spdTemplateFile)
        self.scd = scd.parse(scdTemplateFile)
        self.prf = prf.parse(prfTemplateFile)

        self._setImplementation()
        self._setNameInSpd()
        self._setPropertyFileInSpd()
        self._setDescriptorInSpd()

        self._createWavedevContent(generator=generator)

        if loggingConfigUri:
            self.addSimpleProperty(
                id="LOGGING_CONFIG_URI",
                value=loggingConfigUri,
                type="string",
                complex=False,
                kindtypes=["configure", "execparam"])

    def _setPropertyFileInSpd(self):
        localfile = spd.localFile(name = self.name + ".prf.xml")
        propertyfile = spd.propertyFile(localfile = localfile)
        self.spd.propertyfile = propertyfile

    def _setDescriptorInSpd(self):
        localfile = spd.localFile(name = self.name + ".scd.xml")
        descriptor = spd.descriptor(localfile = localfile)
        self.spd.descriptor = descriptor

    def _setImplementation(self):
        if self.implementation == "cpp":
            self._setCppImplementation()
        elif self.implementation == "java":
            self._setJavaImplementation()
        elif self.implementation == "python":
            self._setPythonImplementation()

    def _setCppImplementation(self):
        localfile = spd.localFile(name=self.implementation)
        code = spd.code(
            type_="Executable",
            localfile = localfile,
            entrypoint=self.implementation+"/"+self.name)
        compiler = spd.compiler(version="4.1.2", name="/usr/bin/gcc")
        implementation = spd.implementation(
            id_ = self.implementation,
            code=code,
            compiler=compiler,
            programminglanguage = spd.programmingLanguage(name="C++"),
            humanlanguage = spd.humanLanguage(name="EN"))
        os = spd.os(name="Linux")
        implementation.add_os(value=os)
        implementation.add_processor(spd.processor(name="x86"))
        implementation.add_processor(spd.processor(name="x86_64"))
        self.spd.add_implementation(value = implementation)

    def _setJavaImplementation(self):
        localfile = spd.localFile(name=self.implementation)
        code = spd.code(
            type_="Executable",
            localfile = localfile,
            entrypoint="java/startJava.sh")

        implementation = spd.implementation(
            id_ = self.implementation,
            code = code,
            compiler = spd.compiler(version="1.5", name="/usr/bin/javac"),
            programminglanguage = spd.programmingLanguage(name = "Java"),
            humanlanguage = spd.humanLanguage(name="EN"),
            runtime = spd.runtime(name = "/usr/bin/java", version="1.5"))
        os = spd.os(name="Linux")
        implementation.add_os(value=os)

        self.spd.add_implementation(value = implementation)

    def _setPythonImplementation(self):
        localfile = spd.localFile(name=self.implementation)
        code = spd.code(
            type_="Executable",
            localfile = localfile,
            entrypoint="python/" + self.name + ".py")

        implementation = spd.implementation(
            id_ = self.implementation,
            code = code,
            programminglanguage = spd.programmingLanguage(name="Python"),
            humanlanguage = spd.humanLanguage(name = "EN"),
            runtime = spd.runtime(version="2.4.4", name="python"))
        os = spd.os(name="Linux")
        implementation.add_os(value=os)

        self.spd.add_implementation(value = implementation)

    def addUsesPort(self, name, type):
        ports = self.scd.componentfeatures.get_ports()
        if ports is None:
            # this is the first port to be added
            ports = scd.ports()
        ports.add_uses(scd.uses(usesname=name,
                                repid=type))
        self.scd.componentfeatures.set_ports(ports)

    def addProvidesPort(self, name, type):
        ports = self.scd.componentfeatures.get_ports()
        if ports is None:
            # this is the first port to be added
            ports = scd.ports()
        ports.add_provides(scd.provides(providesname=name,
                                        repid=type))
        self.scd.componentfeatures.set_ports(ports)

    def addSimpleProperty(
            self,
            id,
            value,
            complex=True,
            type="double",
            mode="readwrite",
            kindtypes=["configure"]):

        complexStr = "false"

        if complex:
            # convert from Octave complex to BulkIO complex
            value = standardizeComplexFormat(value)
            complexStr = "true"

        simple = prf.simple(
            complex=complexStr,
            type_=type,
            id_=id,
            mode=mode,
            value=value,
            action=prf.action(type_="external"))
        for kindtype in kindtypes:
            simple.add_kind(value=prf.kind(kindtype=kindtype))
        self.prf.add_simple(simple)

    def addSimpleSequencProperty(
            self,
            id,
            values,
            complex=True,
            type="double",
            mode="readwrite",
            kindtypes=["configure"]):

        complexStr = "false"

        if complex:
            # convert from Octave complex to BulkIO complex
            for index in range(len(values)):
                values[index] = standardizeComplexFormat(values[index])
            complexStr = "true"

        simplesequence = prf.simpleSequence(
            complex=complexStr,
            type_=type,
            id_=id,
            mode=mode,
            action=prf.action(type_="external"))

        if len(values) > 0:
            if values[0] != "":
                # only create value entries if there is actual content in the list
                valuesXml = prf.values()
                for value in values:
                    valuesXml.add_value(value=value)
                simplesequence.values=valuesXml

        for kindtype in kindtypes:
            simplesequence.add_kind(value=prf.kind(kindtype=kindtype))
        self.prf.add_simplesequence(simplesequence)

    def addStructSequencProperty(
            self,
            id,
            values={},
            struct_id="",
            type={},
            mode="readwrite",
            kindtypes=["configure"]):

        structseq = prf.structSequence(
            id_=id,
            mode=mode)

        struct = prf.struct(id_=struct_id,mode=None)
        for name in type:
            simp = prf.simple(id_=name,type_=type[name],complex=None,mode=None)
            struct.add_simple(simp)
        structseq.set_struct(struct)
        self.prf.add_structsequence(structseq)

