
import os

from sca.codegen.jinja.cpp.component.pull.mapping import PullComponentMapper
from sca.codegen.lang import mfile

class MFunctionMapper(PullComponentMapper):
    def __init__(self, outputdir):
        PullComponentMapper.__init__(self)
        self._outputdir = outputdir

    def _mapComponent(self, softpkg):
        '''
        Extends the pull mapper _mapComponent method by defining the
        'mFunction' and 'license' key/value pairs to the component dictionary.

        '''

        component = PullComponentMapper._mapComponent(self, softpkg)

        mFunction = None
        for prop in softpkg.properties():
            if str(prop.identifier()) == "__mFunction":
                mFunction = prop.value()
                break

        if mFunction:
            # point towards the m file that has been copied
            # to the implementation directory
            mFilePath = os.path.join(softpkg.path(), self._outputdir, mFunction+".m")
            parameters = mfile.parse(mFilePath)
            name = parameters.functionName
            inputs = parameters.inputs
            outputs = parameters.outputs
        else:
            name = ""
            inputs = []
            outputs = []

        component['mFunction'] = {'name'      : name,
                                  'inputs'    : inputs,
                                  'numInputs' : len(inputs),
                                  'outputs'   : outputs}
        component['license'] = "GPL"

        return component
