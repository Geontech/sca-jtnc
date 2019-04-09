
import jinja2

def CodegenPackageLoader(package):
    module = __import__(package)
    for name in package.split('.')[1:]:
        module = getattr(module, name)
    if hasattr(module, "loader"):
        return module.loader
    else:
        return jinja2.PackageLoader(package)

def CodegenLoader(default, depends=None):
    default = jinja2.PackageLoader(default)
    if not depends:
        return default
    prefix = jinja2.PrefixLoader(dict((n, CodegenPackageLoader(p)) for n, p in depends.iteritems()))
    return jinja2.ChoiceLoader([prefix, default])
