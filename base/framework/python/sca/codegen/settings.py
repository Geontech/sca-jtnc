
from xml.dom import minidom

_templateMapping = {
    'gov.sca.ide.codegen.jet.cplusplus.PullPortDataTemplate': 'sca.codegen.jinja.cpp.component.pull',
    'gov.sca.ide.codegen.jet.python.pattern.PullPortDataTemplate': 'sca.codegen.jinja.python.component.pull',
    'gov.sca.ide.codegen.jet.java.JavaGenerator': 'sca.codegen.jinja.java.component.pull',
    'gov.sca.ide.codegen.jet.python.pattern.MinimalServiceTemplate': 'sca.codegen.jinja.python.service',
    'gov.sca.ide.codegen.jet.java.MinimalServiceTemplate': 'sca.codegen.jinja.java.service'
}

def _xmlElementsToDict(node, tagname, key, value):
    return dict((str(n.getAttribute(key)), n.getAttribute(value)) for n in node.getElementsByTagName(tagname))

class ImplementationSettings(object):
    def __init__(self, name=None, outputDir=None, template=None, properties={}, crcs={}):
        self.name = name
        self.outputDir = outputDir
        self.template = template
        self.properties = properties
        self.generatedFileCRCs = crcs

    def override(self, other):
        if other.name is not None:
            self.name = other.name
        if other.outputDir is not None:
            self.outputDir = other.outputDir
        if other.template is not None:
            self.template = other.template
        self.properties.update(other.properties)
        self.generatedFileCRCs.update(other.generatedFileCRCs)

def _importWavedevImplSettings(node):
    if node.getAttribute('generatorId').startswith('gov.sca.ide.codegen.jinja') or node.getAttribute('generatorId').startswith('sca.codegen.jinja'):
        template = node.getAttribute('template')
    else:
        template = _templateMapping[node.getAttribute('template')]
    return ImplementationSettings(name=node.getAttribute('name'),
                                  outputDir=node.getAttribute('outputDir'),
                                  template=template,
                                  properties=_xmlElementsToDict(node, 'properties', 'id', 'value'),
                                  crcs=_xmlElementsToDict(node, 'generatedFileCRCs', 'file', 'crc'))

def importWavedevSettings(filename):
    dom = minidom.parse(filename)
    settings = {}
    for node in dom.getElementsByTagName('implSettings'):
        implId = node.getAttribute('key')
        settings[implId] = _importWavedevImplSettings(node.getElementsByTagName('value')[0])
    dom.unlink()
    return settings
