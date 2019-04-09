
import zlib
try:
    from hashlib import md5
except ImportError:
    from md5 import md5

def strenum(*values):
    return type('StringEnum', (), dict([(v.upper(), v) for v in values]))

def parseBoolean(value):
    if isinstance(value, basestring):
        if value.lower() in ('true', 'yes', '1'):
            return True
        elif value.lower() in ('false', 'no', '0'):
            return False
        else:
            raise ValueError, "Invalid literal '%s' for boolean value" % value
    else:
        return value

def fileCRC(filename, stripnewlines=False):
    value = 0
    for line in open(filename, 'r'):
        # If requested, strip newlines (for backwards-compatibility with the IDE).
        if stripnewlines and line.endswith('\n'):
            line = line[:-1]
        value = zlib.crc32(line, value)
    # Return an unsigned value; zlib.crc32 typically returns a signed value, but
    # this may differ across Python versions or platforms. Note that this may
    # cause promotion to 'long' on 32-bit systems.
    return value & 0xffffffff

def fileMD5(filename):
    # On FIPS-enabled systems, MD5 is disabled because it's not cryptologically
    # secure; the "usedforsecurity" flag assures the library that it's not used
    # in that way, since in this case it's just a hash for tracking when a file
    # has changed. 
    m = md5(usedforsecurity=False)
    for line in open(filename, 'r'):
        m.update(line)
    return m.hexdigest()
