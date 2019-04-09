
#ifndef PORT_H
#define PORT_H

/*{% filter lines|unique|join('\n') %}*/
/*{% for portgen in component.portgenerators %}*/
/*{%   for header in portgen.dependencies() %}*/
#include ${header}
/*{%   endfor %}*/
/*{% endfor %}*/
/*{% endfilter %}*/

class ${component.baseclass.name};
class ${component.userclass.name};

#define CORBA_MAX_TRANSFER_BYTES omniORB::giopMaxMsgSize()

/*{% for portgen in component.portgenerators if portgen.hasDeclaration() %}*/
// ----------------------------------------------------------------------------------------
// ${portgen.className()} declaration
// ----------------------------------------------------------------------------------------
/*{% include portgen.declaration() %}*/

/*{% endfor %}*/
#endif // PORT_H
