// This file is generated by omniidl (C++ backend)- omniORB_4_2. Do not edit.
#ifndef __CFUShortSeq_hh__
#define __CFUShortSeq_hh__

#ifndef __CORBA_H_EXTERNAL_GUARD__
#include <omniORB4/CORBA.h>
#endif

#ifndef  USE_stub_in_nt_dll
# define USE_stub_in_nt_dll_NOT_DEFINED_CFUShortSeq
#endif
#ifndef  USE_core_stub_in_nt_dll
# define USE_core_stub_in_nt_dll_NOT_DEFINED_CFUShortSeq
#endif
#ifndef  USE_dyn_stub_in_nt_dll
# define USE_dyn_stub_in_nt_dll_NOT_DEFINED_CFUShortSeq
#endif



#ifndef __CFPrimitiveTypes_hh_EXTERNAL_GUARD__
#define __CFPrimitiveTypes_hh_EXTERNAL_GUARD__
#include <CFPrimitiveTypes.h>
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

  _CORBA_MODULE_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_UShortSeq;

  class UShortSeq_var;

  class UShortSeq : public _CORBA_Unbounded_Sequence_w_FixSizeElement< UShortType, 2, 2 >  {
  public:
    typedef UShortSeq_var _var_type;
    inline UShortSeq() {}
    inline UShortSeq(const UShortSeq& _s)
      : _CORBA_Unbounded_Sequence_w_FixSizeElement< UShortType, 2, 2 > (_s) {}

    inline UShortSeq(_CORBA_ULong _max)
      : _CORBA_Unbounded_Sequence_w_FixSizeElement< UShortType, 2, 2 > (_max) {}
    inline UShortSeq(_CORBA_ULong _max, _CORBA_ULong _len, UShortType* _val, _CORBA_Boolean _rel=0)
      : _CORBA_Unbounded_Sequence_w_FixSizeElement< UShortType, 2, 2 > (_max, _len, _val, _rel) {}

  

    inline UShortSeq& operator = (const UShortSeq& _s) {
      _CORBA_Unbounded_Sequence_w_FixSizeElement< UShortType, 2, 2 > ::operator=(_s);
      return *this;
    }
  };

  class UShortSeq_out;

  class UShortSeq_var {
  public:
    inline UShortSeq_var() : _pd_seq(0) {}
    inline UShortSeq_var(UShortSeq* _s) : _pd_seq(_s) {}
    inline UShortSeq_var(const UShortSeq_var& _s) {
      if (_s._pd_seq)  _pd_seq = new UShortSeq(*_s._pd_seq);
      else             _pd_seq = 0;
    }
    inline ~UShortSeq_var() { if (_pd_seq)  delete _pd_seq; }
      
    inline UShortSeq_var& operator = (UShortSeq* _s) {
      if (_pd_seq)  delete _pd_seq;
      _pd_seq = _s;
      return *this;
    }
    inline UShortSeq_var& operator = (const UShortSeq_var& _s) {
      if (_s._pd_seq) {
        if (!_pd_seq)  _pd_seq = new UShortSeq;
        *_pd_seq = *_s._pd_seq;
      } else if (_pd_seq) {
        delete _pd_seq;
        _pd_seq = 0;
      }
      return *this;
    }
    inline UShortType& operator [] (_CORBA_ULong _s) {
      return (*_pd_seq)[_s];
    }

  

    inline UShortSeq* operator -> () { return _pd_seq; }
    inline const UShortSeq* operator -> () const { return _pd_seq; }
#if defined(__GNUG__)
    inline operator UShortSeq& () const { return *_pd_seq; }
#else
    inline operator const UShortSeq& () const { return *_pd_seq; }
    inline operator UShortSeq& () { return *_pd_seq; }
#endif
      
    inline const UShortSeq& in() const { return *_pd_seq; }
    inline UShortSeq&       inout()    { return *_pd_seq; }
    inline UShortSeq*&      out() {
      if (_pd_seq) { delete _pd_seq; _pd_seq = 0; }
      return _pd_seq;
    }
    inline UShortSeq* _retn() { UShortSeq* tmp = _pd_seq; _pd_seq = 0; return tmp; }
      
    friend class UShortSeq_out;
    
  private:
    UShortSeq* _pd_seq;
  };

  class UShortSeq_out {
  public:
    inline UShortSeq_out(UShortSeq*& _s) : _data(_s) { _data = 0; }
    inline UShortSeq_out(UShortSeq_var& _s)
      : _data(_s._pd_seq) { _s = (UShortSeq*) 0; }
    inline UShortSeq_out(const UShortSeq_out& _s) : _data(_s._data) {}
    inline UShortSeq_out& operator = (const UShortSeq_out& _s) {
      _data = _s._data;
      return *this;
    }
    inline UShortSeq_out& operator = (UShortSeq* _s) {
      _data = _s;
      return *this;
    }
    inline operator UShortSeq*&()  { return _data; }
    inline UShortSeq*& ptr()       { return _data; }
    inline UShortSeq* operator->() { return _data; }

    inline UShortType& operator [] (_CORBA_ULong _i) {
      return (*_data)[_i];
    }

  

    UShortSeq*& _data;

  private:
    UShortSeq_out();
    UShortSeq_out& operator=(const UShortSeq_var&);
  };

_CORBA_MODULE_END



_CORBA_MODULE POA_CF
_CORBA_MODULE_BEG

_CORBA_MODULE_END



_CORBA_MODULE OBV_CF
_CORBA_MODULE_BEG

_CORBA_MODULE_END





#undef _core_attr
#undef _dyn_attr

void operator<<=(::CORBA::Any& _a, const CF::UShortSeq& _s);
void operator<<=(::CORBA::Any& _a, CF::UShortSeq* _sp);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, CF::UShortSeq*& _sp);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, const CF::UShortSeq*& _sp);





#ifdef   USE_stub_in_nt_dll_NOT_DEFINED_CFUShortSeq
# undef  USE_stub_in_nt_dll
# undef  USE_stub_in_nt_dll_NOT_DEFINED_CFUShortSeq
#endif
#ifdef   USE_core_stub_in_nt_dll_NOT_DEFINED_CFUShortSeq
# undef  USE_core_stub_in_nt_dll
# undef  USE_core_stub_in_nt_dll_NOT_DEFINED_CFUShortSeq
#endif
#ifdef   USE_dyn_stub_in_nt_dll_NOT_DEFINED_CFUShortSeq
# undef  USE_dyn_stub_in_nt_dll
# undef  USE_dyn_stub_in_nt_dll_NOT_DEFINED_CFUShortSeq
#endif

#endif  // __CFUShortSeq_hh__

