
from sca.codegen.lang import automake
from sca.codegen.jinja.template import TemplateFile

class ShellTemplate(TemplateFile):
    def __init__(self, *args, **kwargs):
        if 'executable' not in kwargs:
            kwargs['executable'] = True
        super(ShellTemplate,self).__init__(*args, **kwargs)

    def options(self):
        return {
            'trim_blocks':           True,
            'line_statement_prefix': '#%',
            'block_start_string':    '#{%',
            'comment_start_string':  '#{#'
        }

class AutomakeTemplate(TemplateFile):
    def options(self):
        return {
            'trim_blocks':           True,
            'line_statement_prefix': '#%',
            'block_start_string':    '#{%',
            'comment_start_string':  '#{#'
        }

    def context(self):
        return {
            'automake': automake
        }

class AutoconfTemplate(TemplateFile):
    def options(self):
        return {
            'trim_blocks':           True,
            'line_statement_prefix': '#%',
            'block_start_string':    '#{%',
            'comment_start_string':  '#{#'
        }

class SpecfileTemplate(TemplateFile):
    def options(self):
        return {
            'trim_blocks':           True,
            'line_statement_prefix': '#$',
            'block_start_string':    '#{$',
            'block_end_string':      '$}',
            'comment_start_string':  '#{#'
        }

class PkgconfigTemplate(TemplateFile):
    def options(self):
        return {
            'trim_blocks':           True,
            'line_statement_prefix': '#$',
            'block_start_string':    '#{$',
            'block_end_string':      '$}',
            'comment_start_string':  '#{#'
        }
