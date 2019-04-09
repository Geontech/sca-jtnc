
#% set className = portgen.className()
class ${className}(${component.baseclass.name}.${portgen.templateClass()}):
    def __init__(self, parent, name):
        self.parent = parent
        self.name = name
        self.sri = None
        self.queue = Queue.Queue()
        self.port_lock = threading.Lock()
#{% for operation in portgen.operations() %}

#{% set arglist = ['self'] + operation.args %}
    def ${operation.name}(${arglist|join(', ')}):
        # TODO:
        pass
#{% endfor %}
