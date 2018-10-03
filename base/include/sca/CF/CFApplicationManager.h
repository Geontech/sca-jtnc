// This file is generated by omniidl (C++ backend)- omniORB_4_2. Do not edit.
#ifndef __CFApplicationManager_hh__
#define __CFApplicationManager_hh__

#ifndef __CORBA_H_EXTERNAL_GUARD__
#include <omniORB4/CORBA.h>
#endif

#ifndef  USE_stub_in_nt_dll
# define USE_stub_in_nt_dll_NOT_DEFINED_CFApplicationManager
#endif
#ifndef  USE_core_stub_in_nt_dll
# define USE_core_stub_in_nt_dll_NOT_DEFINED_CFApplicationManager
#endif
#ifndef  USE_dyn_stub_in_nt_dll
# define USE_dyn_stub_in_nt_dll_NOT_DEFINED_CFApplicationManager
#endif



#ifndef __CFPrimitiveTypes_hh_EXTERNAL_GUARD__
#define __CFPrimitiveTypes_hh_EXTERNAL_GUARD__
#include <CFPrimitiveTypes.h>
#endif
#ifndef __CFULongLongSeq_hh_EXTERNAL_GUARD__
#define __CFULongLongSeq_hh_EXTERNAL_GUARD__
#include <CFULongLongSeq.h>
#endif
#ifndef __CFBooleanSeq_hh_EXTERNAL_GUARD__
#define __CFBooleanSeq_hh_EXTERNAL_GUARD__
#include <CFBooleanSeq.h>
#endif
#ifndef __CFULongSeq_hh_EXTERNAL_GUARD__
#define __CFULongSeq_hh_EXTERNAL_GUARD__
#include <CFULongSeq.h>
#endif
#ifndef __CFLongLongSeq_hh_EXTERNAL_GUARD__
#define __CFLongLongSeq_hh_EXTERNAL_GUARD__
#include <CFLongLongSeq.h>
#endif
#ifndef __CFCharSeq_hh_EXTERNAL_GUARD__
#define __CFCharSeq_hh_EXTERNAL_GUARD__
#include <CFCharSeq.h>
#endif
#ifndef __CFUShortSeq_hh_EXTERNAL_GUARD__
#define __CFUShortSeq_hh_EXTERNAL_GUARD__
#include <CFUShortSeq.h>
#endif
#ifndef __CFLongSeq_hh_EXTERNAL_GUARD__
#define __CFLongSeq_hh_EXTERNAL_GUARD__
#include <CFLongSeq.h>
#endif
#ifndef __CFDoubleSeq_hh_EXTERNAL_GUARD__
#define __CFDoubleSeq_hh_EXTERNAL_GUARD__
#include <CFDoubleSeq.h>
#endif
#ifndef __CFShortSeq_hh_EXTERNAL_GUARD__
#define __CFShortSeq_hh_EXTERNAL_GUARD__
#include <CFShortSeq.h>
#endif
#ifndef __CFFloatSeq_hh_EXTERNAL_GUARD__
#define __CFFloatSeq_hh_EXTERNAL_GUARD__
#include <CFFloatSeq.h>
#endif
#ifndef __CFOctetSeq_hh_EXTERNAL_GUARD__
#define __CFOctetSeq_hh_EXTERNAL_GUARD__
#include <CFOctetSeq.h>
#endif
#ifndef __CFStringSeq_hh_EXTERNAL_GUARD__
#define __CFStringSeq_hh_EXTERNAL_GUARD__
#include <CFStringSeq.h>
#endif
#ifndef __CFProperties_hh_EXTERNAL_GUARD__
#define __CFProperties_hh_EXTERNAL_GUARD__
#include <CFProperties.h>
#endif
#ifndef __CFCommonTypes_hh_EXTERNAL_GUARD__
#define __CFCommonTypes_hh_EXTERNAL_GUARD__
#include <CFCommonTypes.h>
#endif
#ifndef __CFLifeCycle_hh_EXTERNAL_GUARD__
#define __CFLifeCycle_hh_EXTERNAL_GUARD__
#include <CFLifeCycle.h>
#endif
#ifndef __CFPortAccessor_hh_EXTERNAL_GUARD__
#define __CFPortAccessor_hh_EXTERNAL_GUARD__
#include <CFPortAccessor.h>
#endif
#ifndef __CFPropertySet_hh_EXTERNAL_GUARD__
#define __CFPropertySet_hh_EXTERNAL_GUARD__
#include <CFPropertySet.h>
#endif
#ifndef __CFTestableInterface_hh_EXTERNAL_GUARD__
#define __CFTestableInterface_hh_EXTERNAL_GUARD__
#include <CFTestableInterface.h>
#endif
#ifndef __CFControllableInterface_hh_EXTERNAL_GUARD__
#define __CFControllableInterface_hh_EXTERNAL_GUARD__
#include <CFControllableInterface.h>
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

#ifndef __CF_mApplicationManager__
#define __CF_mApplicationManager__
  class ApplicationManager;
  class _objref_ApplicationManager;
  class _impl_ApplicationManager;
  
  typedef _objref_ApplicationManager* ApplicationManager_ptr;
  typedef ApplicationManager_ptr ApplicationManagerRef;

  class ApplicationManager_Helper {
  public:
    typedef ApplicationManager_ptr _ptr_type;

    static _ptr_type _nil();
    static _CORBA_Boolean is_nil(_ptr_type);
    static void release(_ptr_type);
    static void duplicate(_ptr_type);
    static void marshalObjRef(_ptr_type, cdrStream&);
    static _ptr_type unmarshalObjRef(cdrStream&);
  };

  typedef _CORBA_ObjRef_Var<_objref_ApplicationManager, ApplicationManager_Helper> ApplicationManager_var;
  typedef _CORBA_ObjRef_OUT_arg<_objref_ApplicationManager,ApplicationManager_Helper > ApplicationManager_out;

#endif

  // interface ApplicationManager
  class ApplicationManager {
  public:
    // Declarations for this interface type.
    typedef ApplicationManager_ptr _ptr_type;
    typedef ApplicationManager_var _var_type;

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
    
  };

  class _objref_ApplicationManager :
    public virtual _objref_LifeCycle,
    public virtual _objref_PortAccessor,
    public virtual _objref_PropertySet,
    public virtual _objref_TestableInterface,
    public virtual _objref_ControllableInterface
  {
  public:
    // IDL operations
    char* name();

    // Constructors
    inline _objref_ApplicationManager()  { _PR_setobj(0); }  // nil
    _objref_ApplicationManager(omniIOR*, omniIdentity*);

  protected:
    virtual ~_objref_ApplicationManager();

    
  private:
    virtual void* _ptrToObjRef(const char*);

    _objref_ApplicationManager(const _objref_ApplicationManager&);
    _objref_ApplicationManager& operator = (const _objref_ApplicationManager&);
    // not implemented

    friend class ApplicationManager;
  };

  class _pof_ApplicationManager : public _OMNI_NS(proxyObjectFactory) {
  public:
    inline _pof_ApplicationManager() : _OMNI_NS(proxyObjectFactory)(ApplicationManager::_PD_repoId) {}
    virtual ~_pof_ApplicationManager();

    virtual omniObjRef* newObjRef(omniIOR*,omniIdentity*);
    virtual _CORBA_Boolean is_a(const char*) const;
  };

  class _impl_ApplicationManager :
    public virtual _impl_LifeCycle,
    public virtual _impl_PortAccessor,
    public virtual _impl_PropertySet,
    public virtual _impl_TestableInterface,
    public virtual _impl_ControllableInterface
  {
  public:
    virtual ~_impl_ApplicationManager();

    virtual char* name() = 0;
    
  public:  // Really protected, workaround for xlC
    virtual _CORBA_Boolean _dispatch(omniCallHandle&);

  private:
    virtual void* _ptrToInterface(const char*);
    virtual const char* _mostDerivedRepoId();
    
  };


  _CORBA_MODULE_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_ApplicationManager;

_CORBA_MODULE_END



_CORBA_MODULE POA_CF
_CORBA_MODULE_BEG

  class ApplicationManager :
    public virtual CF::_impl_ApplicationManager,
    public virtual LifeCycle,
      public virtual PortAccessor,
      public virtual PropertySet,
      public virtual TestableInterface,
      public virtual ControllableInterface
  {
  public:
    virtual ~ApplicationManager();

    inline ::CF::ApplicationManager_ptr _this() {
      return (::CF::ApplicationManager_ptr) _do_this(::CF::ApplicationManager::_PD_repoId);
    }
  };

_CORBA_MODULE_END



_CORBA_MODULE OBV_CF
_CORBA_MODULE_BEG

_CORBA_MODULE_END





#undef _core_attr
#undef _dyn_attr

void operator<<=(::CORBA::Any& _a, CF::ApplicationManager_ptr _s);
void operator<<=(::CORBA::Any& _a, CF::ApplicationManager_ptr* _s);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, CF::ApplicationManager_ptr& _s);



inline void
CF::ApplicationManager::_marshalObjRef(::CF::ApplicationManager_ptr obj, cdrStream& s) {
  omniObjRef::_marshal(obj->_PR_getobj(),s);
}



#ifdef   USE_stub_in_nt_dll_NOT_DEFINED_CFApplicationManager
# undef  USE_stub_in_nt_dll
# undef  USE_stub_in_nt_dll_NOT_DEFINED_CFApplicationManager
#endif
#ifdef   USE_core_stub_in_nt_dll_NOT_DEFINED_CFApplicationManager
# undef  USE_core_stub_in_nt_dll
# undef  USE_core_stub_in_nt_dll_NOT_DEFINED_CFApplicationManager
#endif
#ifdef   USE_dyn_stub_in_nt_dll_NOT_DEFINED_CFApplicationManager
# undef  USE_dyn_stub_in_nt_dll
# undef  USE_dyn_stub_in_nt_dll_NOT_DEFINED_CFApplicationManager
#endif

#endif  // __CFApplicationManager_hh__

