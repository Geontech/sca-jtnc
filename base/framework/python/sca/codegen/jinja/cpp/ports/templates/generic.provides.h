
//% set classname = portgen.className()
class ${classname} : public POA_${portgen.interfaceClass()}, public Port_Provides_base_impl
{
    public:
        ${classname}(std::string port_name, ${component.baseclass.name} *_parent);
        ~${classname}();

/*{% for op in portgen.operations() %}*/
        ${op.returns} ${op.name}(${op.arglist});
/*{% endfor %}*/
        std::string getRepid() const;

    protected:
        ${component.userclass.name} *parent;
        boost::mutex portAccess;
};
