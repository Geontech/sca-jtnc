
import sca.codegen.lang.cpp

from sca.codegen.jinja.template import TemplateFile

class CppTemplate(TemplateFile):
    COMMENT_START = '/*'
    COMMENT_LINE  = ' *'
    COMMENT_END   = ' */'

    def options(self):
        return {
            'trim_blocks':           True,
            'line_statement_prefix': '//%',
            'variable_start_string': '${',
            'variable_end_string':   '}',
            'block_start_string':    '/*{%',
            'block_end_string':      '%}*/',
            'comment_start_string':  '/*#',
            'comment_end_string':    '#*/'
        }

    def context(self):
        return {
            'cpp': sca.codegen.lang.cpp
        }
