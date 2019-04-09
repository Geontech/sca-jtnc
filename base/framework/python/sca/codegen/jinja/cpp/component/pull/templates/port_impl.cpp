
/*******************************************************************************************

    AUTO-GENERATED CODE. DO NOT MODIFY

    Source: ${component.profile.spd}

*******************************************************************************************/

#include "${component.userclass.header}"


/******************************************
 *
 * Logging:
 *      To log, use the _portLog member (not available in the constructor)
 *
 *      For example,
 *          RH_DEBUG(_portLog, "this is a debug message");
 *
 ******************************************/

/*{% for portgen in component.portgenerators if portgen.hasImplementation() %}*/
// ----------------------------------------------------------------------------------------
// ${portgen.className()} definition
// ----------------------------------------------------------------------------------------
/*{% include portgen.implementation() %}*/

/*{% endfor %}*/
