
#% set className = component.userclass.name
#% set baseClass = component.baseclass.name
#% set artifactType = component.artifacttype
#!/usr/bin/env python
#
#% block license
#% endblock
#
# AUTO-GENERATED
#
# Source: ${component.profile.spd}
#{% if component is device %}
from sca.device import start_device
#{% else %}
from sca.resource import Resource, start_component
#{% endif %}
import logging
from sca.utils import uuid

from ${baseClass} import *

class ${className}(${baseClass}):
#{% if component.description %}
    """${component.description()}"""
#{% else %}
    """<DESCRIPTION GOES HERE>"""
#{% endif %}
    def initialize(self):
        """
        This is called by the framework immediately after your ${artifactType} registers with the NameService.
        
        In general, you should add customization here and not in the __init__ constructor.  If you have 
        a custom port implementation you can override the specific implementation here with a statement
        similar to the following:
          self.some_port = MyPortImplementation()
        """
        ${baseClass}.initialize(self)
        # TODO add customization here.
        
#{% if component is device %}
    def updateUsageState(self):
        """
        This is called automatically after allocateCapacity or deallocateCapacity are called.
        Your implementation should determine the current state of the device:
           self._usageState = CF.Device.IDLE   # not in use
           self._usageState = CF.Device.ACTIVE # in use, with capacity remaining for allocation
           self._usageState = CF.Device.BUSY   # in use, with no capacity remaining for allocation
        """
        return NOOP

#{% endif %}

    def process(self):
        retval = self.checkInputs()
        if not retval and self.bufferingEnabled:
            return NOOP
        retval = self.run_binary()
        if not self.bufferingEnabled:
            self.data = []
        if retval != None:
            self.sendOutput(retval)
        return NORMAL

  
if __name__ == '__main__':
    logging.getLogger().setLevel(logging.WARN)
#{% if component is device %}
    logging.debug("Starting Device")
    start_device(${className})
#{% else %}
    logging.debug("Starting Component")
    start_component(${className})
#{% endif %}
