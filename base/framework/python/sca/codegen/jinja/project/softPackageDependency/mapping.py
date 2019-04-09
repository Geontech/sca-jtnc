
from sca.codegen.jinja.mapping import ProjectMapper

class DependencyProjectMapper(ProjectMapper):
    def _mapComponent(self, spd):
        component = {}
        component['specfile'] = spd.name()+'.spec'
        return component
