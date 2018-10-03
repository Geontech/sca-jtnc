// This file is generated by omniidl (C++ backend)- omniORB_4_2. Do not edit.
#ifndef __CFDeviceAttributes_hh__
#define __CFDeviceAttributes_hh__

#ifndef __CORBA_H_EXTERNAL_GUARD__
#include <omniORB4/CORBA.h>
#endif

#ifndef  USE_stub_in_nt_dll
# define USE_stub_in_nt_dll_NOT_DEFINED_CFDeviceAttributes
#endif
#ifndef  USE_core_stub_in_nt_dll
# define USE_core_stub_in_nt_dll_NOT_DEFINED_CFDeviceAttributes
#endif
#ifndef  USE_dyn_stub_in_nt_dll
# define USE_dyn_stub_in_nt_dll_NOT_DEFINED_CFDeviceAttributes
#endif



#ifndef __CFComponentIdentifier_hh_EXTERNAL_GUARD__
#define __CFComponentIdentifier_hh_EXTERNAL_GUARD__
#include <CFComponentIdentifier.h>
#endif



#ifdef USE_stub_in_nt_dll
# ifndef USE_core_stub_in_nt_dll
#  define USE_core_stub_in_nt_dll
# endif
# ifndef USE_dyn_stub_in_nt_dll
#  define USE_dyn_stub_in_nt_dll
# endif
#endif

#ifdef _core_attr
# error "A local CPP macro _core_attr has already been defined."
#else
# ifdef  USE_core_stub_in_nt_dll
#  define _core_attr _OMNIORB_NTDLL_IMPORT
# else
#  define _core_attr
# endif
#endif

#ifdef _dyn_attr
# error "A local CPP macro _dyn_attr has already been defined."
#else
# ifdef  USE_dyn_stub_in_nt_dll
#  define _dyn_attr _OMNIORB_NTDLL_IMPORT
# else
#  define _dyn_attr
# endif
#endif



_CORBA_MODULE CF

_CORBA_MODULE_BEG

#ifndef __CF_mDeviceAttributes__
#define __CF_mDeviceAttributes__
  class DeviceAttributes;
  class _objref_DeviceAttributes;
  class _impl_DeviceAttributes;
  
  typedef _objref_DeviceAttributes* DeviceAttributes_ptr;
  typedef DeviceAttributes_ptr DeviceAttributesRef;

  class DeviceAttributes_Helper {
  public:
    typedef DeviceAttributes_ptr _ptr_type;

    static _ptr_type _nil();
    static _CORBA_Boolean is_nil(_ptr_type);
    static void release(_ptr_type);
    static void duplicate(_ptr_type);
    static void marshalObjRef(_ptr_type, cdrStream&);
    static _ptr_type unmarshalObjRef(cdrStream&);
  };

  typedef _CORBA_ObjRef_Var<_objref_DeviceAttributes, DeviceAttributes_Helper> DeviceAttributes_var;
  typedef _CORBA_ObjRef_OUT_arg<_objref_DeviceAttributes,DeviceAttributes_Helper > DeviceAttributes_out;

#endif

  // interface DeviceAttributes
  class DeviceAttributes {
  public:
    // Declarations for this interface type.
    typedef DeviceAttributes_ptr _ptr_type;
    typedef DeviceAttributes_var _var_type;

    static _ptr_type _duplicate(_ptr_type);
    static _ptr_type _narrow(::CORBA::Object_ptr);
    static _ptr_type _unchecked_narrow(::CORBA::Object_ptr);
    
    static _ptr_type _nil();

    static inline void _marshalObjRef(_ptr_type, cdrStream&);

    static inline _ptr_type _unmarshalObjRef(cdrStream& s) {
      omniObjRef* o = omniObjRef::_unMarshal(_PD_repoId,s);
      if (o)
        return (_ptr_type) o->_ptrToObjRef(_PD_repoId);
      else
        return _nil();
    }

    static inline _ptr_type _fromObjRef(omniObjRef* o) {
      if (o)
        return (_ptr_type) o->_ptrToObjRef(_PD_repoId);
      else
        return _nil();
    }

    static _core_attr const char* _PD_repoId;

    // Other IDL defined within this scope.
    enum OperationalType { ENABLED, DISABLED /*, __max_OperationalType=0xffffffff */ };
    typedef OperationalType& OperationalType_out;

    static _dyn_attr const ::CORBA::TypeCode_ptr _tc_OperationalType;

  
  };

  class _objref_DeviceAttributes :
    public virtual _objref_ComponentIdentifier
  {
  public:
    // IDL operations
    DeviceAttributes::OperationalType operationalState();

    // Constructors
    inline _objref_DeviceAttributes()  { _PR_setobj(0); }  // nil
    _objref_DeviceAttributes(omniIOR*, omniIdentity*);

  protected:
    virtual ~_objref_DeviceAttributes();

    
  private:
    virtual void* _ptrToObjRef(const char*);

    _objref_DeviceAttributes(const _objref_DeviceAttributes&);
    _objref_DeviceAttributes& operator = (const _objref_DeviceAttributes&);
    // not implemented

    friend class DeviceAttributes;
  };

  class _pof_DeviceAttributes : public _OMNI_NS(proxyObjectFactory) {
  public:
    inline _pof_DeviceAttributes() : _OMNI_NS(proxyObjectFactory)(DeviceAttributes::_PD_repoId) {}
    virtual ~_pof_DeviceAttributes();

    virtual omniObjRef* newObjRef(omniIOR*,omniIdentity*);
    virtual _CORBA_Boolean is_a(const char*) const;
  };

  class _impl_DeviceAttributes :
    public virtual _impl_ComponentIdentifier
  {
  public:
    virtual ~_impl_DeviceAttributes();

    virtual DeviceAttributes::OperationalType operationalState() = 0;
    
  public:  // Really protected, workaround for xlC
    virtual _CORBA_Boolean _dispatch(omniCallHandle&);

  private:
    virtual void* _ptrToInterface(const char*);
    virtual const char* _mostDerivedRepoId();
    
  };


  _CORBA_MODULE_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_DeviceAttributes;

_CORBA_MODULE_END



_CORBA_MODULE POA_CF
_CORBA_MODULE_BEG

  class DeviceAttributes :
    public virtual CF::_impl_DeviceAttributes,
    public virtual ComponentIdentifier
  {
  public:
    virtual ~DeviceAttributes();

    inline ::CF::DeviceAttributes_ptr _this() {
      return (::CF::DeviceAttributes_ptr) _do_this(::CF::DeviceAttributes::_PD_repoId);
    }
  };

_CORBA_MODULE_END



_CORBA_MODULE OBV_CF
_CORBA_MODULE_BEG

_CORBA_MODULE_END





#undef _core_attr
#undef _dyn_attr

inline void operator >>=(CF::DeviceAttributes::OperationalType _e, cdrStream& s) {
  ::operator>>=((::CORBA::ULong)_e, s);
}

inline void operator <<= (CF::DeviceAttributes::OperationalType& _e, cdrStream& s) {
  ::CORBA::ULong _0RL_e;
  ::operator<<=(_0RL_e,s);
  if (_0RL_e <= CF::DeviceAttributes::DISABLED) {
    _e = (CF::DeviceAttributes::OperationalType) _0RL_e;
  }
  else {
    OMNIORB_THROW(MARSHAL,_OMNI_NS(MARSHAL_InvalidEnumValue),
                  (::CORBA::CompletionStatus)s.completion());
  }
}

void operator<<=(::CORBA::Any& _a, CF::DeviceAttributes::OperationalType _s);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, CF::DeviceAttributes::OperationalType& _s);

void operator<<=(::CORBA::Any& _a, CF::DeviceAttributes_ptr _s);
void operator<<=(::CORBA::Any& _a, CF::DeviceAttributes_ptr* _s);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, CF::DeviceAttributes_ptr& _s);



inline void
CF::DeviceAttributes::_marshalObjRef(::CF::DeviceAttributes_ptr obj, cdrStream& s) {
  omniObjRef::_marshal(obj->_PR_getobj(),s);
}



#ifdef   USE_stub_in_nt_dll_NOT_DEFINED_CFDeviceAttributes
# undef  USE_stub_in_nt_dll
# undef  USE_stub_in_nt_dll_NOT_DEFINED_CFDeviceAttributes
#endif
#ifdef   USE_core_stub_in_nt_dll_NOT_DEFINED_CFDeviceAttributes
# undef  USE_core_stub_in_nt_dll
# undef  USE_core_stub_in_nt_dll_NOT_DEFINED_CFDeviceAttributes
#endif
#ifdef   USE_dyn_stub_in_nt_dll_NOT_DEFINED_CFDeviceAttributes
# undef  USE_dyn_stub_in_nt_dll
# undef  USE_dyn_stub_in_nt_dll_NOT_DEFINED_CFDeviceAttributes
#endif

#endif  // __CFDeviceAttributes_hh__

