
import commands
import os

from sca.codegen.jinja.cpp.component.mFunction.generator import OctaveComponentGenerator, loader
from sca.codegen import versions

def factory(**opts):
    return OctaveComponentGenerator(**opts)

def _version_tuple(ver):
    return tuple(int(n) for n in ver.split('.'))

def _check_octave():
    # Attempt to determine if octave-devel v3.4 or greater is installed.
    (status, output) = commands.getstatusoutput('octave-config -v')
    if status:
        return False

    # Check the version against the minimum
    version = _version_tuple(output)
    if version < _version_tuple(versions.octave):
        return False

    incdir = commands.getoutput('octave-config -p OCTINCLUDEDIR')
    return os.path.exists(incdir)

def check():
    if _check_octave():
        return True
    else:
        print "Could not find suitable Octave installation.  Octave-devel v%s or greater is required." % versions.octave
        return False
