
/*{% block license %}*/
/*# Allow child templates to include license #*/
/*{% endblock %}*/
/*{% block header %}*/
#ifndef STRUCTPROPS_H
#define STRUCTPROPS_H

/*******************************************************************************************

    AUTO-GENERATED CODE. DO NOT MODIFY

*******************************************************************************************/
/*{% endblock %}*/

/*{% block includes %}*/
#include <sca/CorbaUtils.h>
#include <CF/CF.h>
#include <sca/PropertyMap.h>
/*{% set isSet = False %}*/
/*{% for struct in component.structdefs %}*/
/*{%   for field in struct.fields %}*/
/*{%     if field.isOptional and isSet == False %}*/
#include <sca/OptionalProperty.h>
#include <sca/AnyUtils.h>
/*{%       set isSet = True %}*/
/*{%     endif %}*/
/*{%   endfor %}*/
/*{% endfor %}*/
/*{% if component['hasmultioutport'] %}*/
#include <bulkio/bulkio.h>
typedef bulkio::connection_descriptor_struct connection_descriptor_struct;
/*{% endif %}*/
/*{% endblock %}*/

/*{% block struct %}*/
/*{% from "properties/properties.cpp" import structdef with context %}*/
/*{% for struct in component.structdefs if not struct.builtin %}*/
${structdef(struct)}

/*{% endfor %}*/
/*{% endblock %}*/
#endif // STRUCTPROPS_H
