
//% set classname = portgen.className()
${classname}::${classname}(std::string port_name, ${component.baseclass.name} *_parent) : 
Port_Provides_base_impl(port_name)
{
    parent = static_cast<${component.userclass.name} *> (_parent);
}

${classname}::~${classname}()
{
}
/*{% for operation in portgen.operations() %}*/

${operation.returns} ${classname}::${operation.name}(${operation.arglist})
{
    boost::mutex::scoped_lock lock(portAccess);
//% set hasreturn = operation.returns != 'void'
/*{% if hasreturn %}*/
    ${operation.temporary} retval${' = %s' % operation.initializer if operation.initializer};
/*{% endif %}*/
    // TODO: Fill in this function
/*{% if hasreturn %}*/
/*{%   if operation.temporary.endswith('_var') %}*/
    return retval._retn();
/*{%   else %}*/
    return retval;
/*{%   endif %}*/
/*{% endif %}*/
}
/*{% endfor %}*/

std::string ${classname}::getRepid() const
{
    return ${portgen.interfaceClass()}::_PD_repoId;
}
