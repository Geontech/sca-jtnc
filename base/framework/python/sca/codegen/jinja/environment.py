
import jinja2

class CodegenEnvironment(jinja2.Environment):
    def __init__(self, *args, **kwargs):
        super(CodegenEnvironment,self).__init__(*args, **kwargs)

        import filters
        self.filters['lines'] = filters.do_lines
        self.filters['prepend'] = filters.do_prepend
        self.filters['append'] = filters.do_append
        self.filters['relpath'] = filters.do_relpath
        self.filters['unique'] = filters.do_unique
        self.filters['filter'] = filters.do_filter
        self.filters['test'] = filters.do_test
        self.filters['quote'] = filters.do_quote
        self.filters['codealign'] = filters.do_codealign

        import tests
        self.tests['sometimes'] = tests.is_sometimes
        self.tests['always'] = tests.is_always
        self.tests['never'] = tests.is_never
        self.tests['resource'] = tests.is_resource
        self.tests['device'] = tests.is_device
        self.tests['loadabledevice'] = tests.is_loadabledevice
        self.tests['executabledevice'] = tests.is_executabledevice
        self.tests['aggregatedevice'] = tests.is_aggregatedevice
        self.tests['programmabledevice'] = tests.is_programmabledevice
        self.tests['service'] = tests.is_service
        self.tests['simple'] = tests.is_simple
        self.tests['simplesequence'] = tests.is_simplesequence
        self.tests['struct'] = tests.is_struct
        self.tests['structsequence'] = tests.is_structsequence
        self.tests['enumerated'] = tests.is_enumerated
        self.tests['provides'] = tests.is_provides
        self.tests['uses'] = tests.is_uses
        self.tests['bidir'] = tests.is_bidir
