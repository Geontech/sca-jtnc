
//% set classname = portgen.className()
//% set vartype = portgen.interfaceClass() + '_var'
PREPARE_ALT_LOGGING(${classname},${component.userclass.name})
${classname}::${classname}(std::string port_name, ${component.baseclass.name} *_parent) :
Port_Uses_base_impl(port_name)
{
    parent = static_cast<${component.userclass.name} *> (_parent);
    recConnectionsRefresh = false;
    recConnections.length(0);
}

${classname}::~${classname}()
{
}
/*{% for operation in portgen.operations() %}*/
//% set hasreturn = operation.returns != 'void'
/*{% if hasreturn %}*/
/*{%     set returnstate='true' %}*/
/*{% else %}*/
/*{%     set returnstate='false' %}*/
/*{% endif %}*/
//% set hasout = operation.hasout
/*{% if hasout %}*/
/*{%     set _hasout='true' %}*/
/*{% else %}*/
/*{%     set _hasout='false' %}*/
/*{% endif %}*/
//% set hasinout = operation.hasinout
/*{% if hasinout %}*/
/*{%     set _hasinout='true' %}*/
/*{% else %}*/
/*{%     set _hasinout='false' %}*/
/*{% endif %}*/
/*{%  if operation.readwrite_attr %}*/
${operation.returns} ${classname}::${operation.name}() {
    return _get_${operation.name}("");
}

${operation.returns} ${classname}::_get_${operation.name}(const std::string __connection_id__)
/*{%  else %}*/
/*{%   if operation.arglist %}*/
${operation.returns} ${classname}::${operation.name}(${operation.arglist}, const std::string __connection_id__)
/*{%   else %}*/
${operation.returns} ${classname}::${operation.name}(const std::string __connection_id__)
/*{%   endif %}*/
/*{%  endif %}*/
{
/*{% if hasreturn %}*/
    ${operation.temporary} retval${' = %s' % operation.initializer if operation.initializer};
/*{% endif %}*/
    std::vector < std::pair < ${vartype}, std::string > >::iterator i;

    boost::mutex::scoped_lock lock(updatingPortsLock);   // don't want to process while command information is coming in

    __evaluateRequestBasedOnConnections(__connection_id__, ${returnstate}, ${_hasinout}, ${_hasout});
    if (this->active) {
        for (i = this->outConnections.begin(); i != this->outConnections.end(); ++i) {
            if (not __connection_id__.empty() and __connection_id__ != (*i).second)
                continue;
            try {
                ${"retval = " if hasreturn}((*i).first)->${operation.name}(${operation.argnames});
            } catch (...) {
                LOG_ERROR(${classname},"Call to ${operation.name} by ${classname} failed");
                throw;
            }
        }
    }

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
