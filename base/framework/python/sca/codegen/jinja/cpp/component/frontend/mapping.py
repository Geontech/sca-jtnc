
from sca.codegen.model.softwarecomponent import ComponentTypes
from sca.codegen.lang.idl import IDLInterface
from sca.codegen.jinja.cpp.component.pull.mapping import PullComponentMapper
from sca.codegen.jinja.cpp.properties.mapping import CppPropertyMapper

class FrontendComponentMapper(PullComponentMapper):
    def _mapComponent(self, softpkg):
        # Defer most mapping to base class
        cppcomp = super(FrontendComponentMapper,self)._mapComponent(softpkg)

        # Determine which FRONTEND interfaces this device implements (provides)
        cppcomp['implements'] = self.getImplementedInterfaces(softpkg)

        return cppcomp

    @staticmethod
    def getImplementedInterfaces(softpkg):
        deviceinfo = set()

        # Ensure that parent interfaces also gets added (so, e.g., a device
        # with a DigitalTuner should also report that it's an AnalogTuner
        # and FrontendTuner)
        inherits = { 'DigitalScanningTuner': ('ScanningTuner', 'DigitalTuner', 'AnalogTuner', 'FrontendTuner'),
                     'AnalogScanningTuner': ('ScanningTuner', 'AnalogTuner', 'FrontendTuner'),
                     'DigitalTuner': ('AnalogTuner', 'FrontendTuner'),
                     'AnalogTuner': ('FrontendTuner',) }

        for port in softpkg.providesPorts():
            idl = IDLInterface(port.repid())
            # Ignore non-FRONTEND intefaces
            if idl.namespace() != 'FRONTEND':
                continue
            interface = idl.interface()
            deviceinfo.add(interface)
            for parent in inherits.get(interface, []):
                deviceinfo.add(parent)
        
        return deviceinfo

    @staticmethod
    def superClasses(softpkg):
        # Start with the superclasses from the pull mapping, overriding only
        # what's different for FRONTEND devices
        classes = PullComponentMapper.superClasses(softpkg)

        # Only plain devices are supported for FRONTEND
        if softpkg.type() == ComponentTypes.DEVICE:
            deviceinfo = FrontendComponentMapper.getImplementedInterfaces(softpkg)
            # If this device is any type of tuner, replace the Device_impl base
            # class with the FRONTEND-specific tuner device class
            if 'FrontendTuner' in deviceinfo:
                for parent in classes:
                    if parent['name'] == 'Device_impl':
                        parent['name'] = 'frontend::FrontendTunerDevice<frontend_tuner_status_struct_struct>'
                        parent['header'] = '<frontend/frontend.h>'

                # Add the most specific tuner delegate interface:
                #   (Digital > Analog > Frontend)
                if 'DigitalScanningTuner' in deviceinfo:
                    classes.append({'name': 'virtual frontend::digital_scanning_tuner_delegation', 'header': ''})
                    parent['name'] = 'frontend::FrontendScanningTunerDevice<frontend_tuner_status_struct_struct>'
                elif 'AnalogScanningTuner' in deviceinfo:
                    classes.append({'name': 'virtual frontend::analog_scanning_tuner_delegation', 'header': ''})
                    parent['name'] = 'frontend::FrontendScanningTunerDevice<frontend_tuner_status_struct_struct>'
                elif 'DigitalTuner' in deviceinfo:
                    classes.append({'name': 'virtual frontend::digital_tuner_delegation', 'header': ''})
                elif 'AnalogTuner' in deviceinfo:
                    classes.append({'name': 'virtual frontend::analog_tuner_delegation', 'header': ''})
                else:
                    classes.append({'name': 'virtual frontend::frontend_tuner_delegation', 'header': ''})

            # Add additonal FRONTEND delegate interfaces
            if 'RFInfo' in deviceinfo:
                classes.append({'name': 'virtual frontend::rfinfo_delegation', 'header': ''})
            if 'RFSource' in deviceinfo:
                classes.append({'name': 'virtual frontend::rfsource_delegation', 'header': ''})
            if 'GPS' in deviceinfo:
                classes.append({'name': 'virtual frontend::gps_delegation', 'header': ''})
            if 'NavData' in deviceinfo:
                classes.append({'name': 'virtual frontend::nav_delegation', 'header': ''})

        return classes

class FrontendPropertyMapper(CppPropertyMapper):
    TUNER_STATUS_BASE_FIELDS = (
        'tuner_type',
        'allocation_id_csv',
        'center_frequency',
        'bandwidth',
        'sample_rate',
        'enabled',
        'group_id',
        'rf_flow_id'
    )

    FRONTEND_BUILTINS = (
        'FRONTEND::tuner_allocation',
        'FRONTEND::listener_allocation',
        'FRONTEND::scanner_allocation'
    )

    def mapStructProperty(self, prop, fields):
        cppprop = super(FrontendPropertyMapper,self).mapStructProperty(prop, fields)
        if prop.identifier() == 'FRONTEND::tuner_status_struct':
            cppprop['baseclass'] = 'frontend::default_frontend_tuner_status_struct_struct'
            for field in fields:
                if field['cppname'] in self.TUNER_STATUS_BASE_FIELDS:
                    field['inherited'] = True
        elif prop.identifier() in self.FRONTEND_BUILTINS:
            cppprop['builtin'] = True
        return cppprop

    def getStructPropertyType(self, prop):
        if prop.identifier() in self.FRONTEND_BUILTINS:
            return 'frontend::%s_struct' % prop.name()
        else:
            return super(FrontendPropertyMapper,self).getStructPropertyType(prop)
