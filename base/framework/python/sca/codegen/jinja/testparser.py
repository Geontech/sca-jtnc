
from jinja2 import lexer
from jinja2.exceptions import TemplateError

def describe_token(token):
    from jinja2 import lexer
    if token.type == lexer.TOKEN_EOF:
        return 'end of statement'
    else:
        return lexer.describe_token(token)

class TestSyntaxError(TemplateError):
    def __init__(self, expected, token, test):
        got = describe_token(token)
        msg = "expected token '%s', got '%s' in test statement '%s'" % (expected, got,  test)
        super(TestSyntaxError,self).__init__(msg)

class TestNameError(TemplateError):
    def __init__(self, name, test):
        msg = "no test named '%s' in test statement '%s'" % (name, test)
        super(TestNameError,self).__init__(msg)

class TestParser(object):
    def __init__(self, environment, test):
        self.environment = environment
        self.test = test
        self.stream = environment._tokenize(test, 'test', state='block')

    def parse(self):
        try:
            test = self.parse_or()
        except Exception, exc:
            # Flatten the stack trace
            raise exc
        if not self.stream.eos:
            raise TestSyntaxError('end of statement', self.stream.current, self.test)
        return test

    def parse_or(self):
        test = self.parse_and()
        while self.stream.skip_if('name:or'):
            left = test
            right = self.parse_and()
            def _or(x):
                return left(x) or right(x)
            test = _or
        return test

    def parse_and(self):
        test = self.parse_not()
        while self.stream.skip_if('name:and'):
            left = test
            right = self.parse_not()
            def _and(x):
                return left(x) and right(x)
            test = _and
        return test

    def parse_not(self):
        if self.stream.skip_if('name:not'):
            test = self.parse_not()
            def _not(x):
                return not test(x)
            return _not
        return self.parse_test()

    def parse_test(self):
        if not self.stream.current.test('name'):
            raise TestSyntaxError('name', self.stream.current, self.test)
        token = self.stream.next()
        name = token.value
        try:
            return self.environment.tests[name]
        except KeyError:
            raise TestNameError(name, self.test)
