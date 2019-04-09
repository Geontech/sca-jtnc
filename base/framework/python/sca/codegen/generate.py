
class GeneratorModule(object):
    def __init__(self, module):
        self.__module = module

    def factory(self, **opts):
        return self.__module.factory(**opts)

    def check(self):
        # If the module provides a check function, call it here
        if hasattr(self.__module, 'check'):
            return self.__module.check()
        else:
            return True

def importTemplate(template):
    """
    Imports a code generation module from the given fully-qualified name.
    """
    try:
        package = __import__(template)
    except Exception, e:
        print e
        raise

    # Since the module name probably has dots, get the most specific module
    # (e.g. 'component' from 'template.cpp.component').
    for name in template.split('.')[1:]:
        package = getattr(package, name)

    if not hasattr(package, 'factory'):
        raise TypeError('Invalid template ' + template)

    return GeneratorModule(package)
