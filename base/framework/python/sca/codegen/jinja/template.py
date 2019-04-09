
import os

class TemplateFile(object):
    # Most file types that we generate use hash for comment lines, but
    # subclasses can override if needed
    COMMENT_START = '#'
    COMMENT_LINE  = '#'
    COMMENT_END   = '#'

    def __init__(self, template, filename=None, executable=False, userfile=False):
        self.template = template
        if filename:
            self.filename = filename
        else:
            self.filename = os.path.basename(self.template)
        self.executable = executable
        self.userfile = userfile

    def options(self):
        return {}

    def filters(self):
        return {}

    def context(self):
        return {}

    def comment(self, text):
        """
        Generates a comment block from 'text' suitable for this template type.
        """
        def generate(t):
            yield self.COMMENT_START
            for line in t.split('\n'):
                # Add a space between the comment marker and the line, but only
                # if the line is non-empty
                if line:
                    line = ' ' + line
                yield self.COMMENT_LINE + line
            yield self.COMMENT_END
            yield ''
        return '\n'.join(generate(text))
