// This file is generated by omniidl (C++ backend)- omniORB_4_2. Do not edit.
#ifndef __bio__dataVITA49_hh__
#define __bio__dataVITA49_hh__

#ifndef __CORBA_H_EXTERNAL_GUARD__
#include <omniORB4/CORBA.h>
#endif

#ifndef  USE_stub_in_nt_dll
# define USE_stub_in_nt_dll_NOT_DEFINED_bio__dataVITA49
#endif
#ifndef  USE_core_stub_in_nt_dll
# define USE_core_stub_in_nt_dll_NOT_DEFINED_bio__dataVITA49
#endif
#ifndef  USE_dyn_stub_in_nt_dll
# define USE_dyn_stub_in_nt_dll_NOT_DEFINED_bio__dataVITA49
#endif



#ifndef __CFProperties_hh_EXTERNAL_GUARD__
#define __CFProperties_hh_EXTERNAL_GUARD__
#include <sca/CF/CFProperties.h>
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
#ifndef __CFCommonTypes_hh_EXTERNAL_GUARD__
#define __CFCommonTypes_hh_EXTERNAL_GUARD__
#include <sca/CF/CFCommonTypes.h>
#endif
#ifndef __Port_hh_EXTERNAL_GUARD__
#define __Port_hh_EXTERNAL_GUARD__
#include <sca/CF/Port.h>
#endif
#ifndef __QueryablePort_hh_EXTERNAL_GUARD__
#define __QueryablePort_hh_EXTERNAL_GUARD__
#include <sca/CF/QueryablePort.h>
#endif
#ifndef __AdditionalTypes_hh_EXTERNAL_GUARD__
#define __AdditionalTypes_hh_EXTERNAL_GUARD__
#include <sca/CF/AdditionalTypes.h>
#endif
#ifndef __bulkioDataTypes_hh_EXTERNAL_GUARD__
#define __bulkioDataTypes_hh_EXTERNAL_GUARD__
#include <sca/BULKIO/bulkioDataTypes.h>
#endif
#ifndef __bio__runtimeStats_hh_EXTERNAL_GUARD__
#define __bio__runtimeStats_hh_EXTERNAL_GUARD__
#include <sca/BULKIO/bio_runtimeStats.h>
#endif
#ifndef __bio__updateSRI_hh_EXTERNAL_GUARD__
#define __bio__updateSRI_hh_EXTERNAL_GUARD__
#include <sca/BULKIO/bio_updateSRI.h>
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



_CORBA_MODULE BULKIO

_CORBA_MODULE_BEG

  enum VITA49DataDigraph { VITA49_1P, VITA49_2P, VITA49_4P, VITA49_8T, VITA49_8U, VITA49_16F, VITA49_16T, VITA49_16U, VITA49_32F, VITA49_32T, VITA49_32U, VITA49_64F, VITA49_64T, VITA49_64U /*, __max_VITA49DataDigraph=0xffffffff */ };
  typedef VITA49DataDigraph& VITA49DataDigraph_out;

  _CORBA_MODULE_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_VITA49DataDigraph;

  enum TransportProtocol { VITA49_UDP_TRANSPORT, VITA49_TCP_TRANSPORT, VITA49_UNKNOWN_TRANSPORT /*, __max_TransportProtocol=0xffffffff */ };
  typedef TransportProtocol& TransportProtocol_out;

  _CORBA_MODULE_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_TransportProtocol;

  enum VITA49DataComplexity { VITA49_REAL, VITA49_COMPLEX_CARTESIAN, VITA49_RESERVED1, VITA49_RESERVED2 /*, __max_VITA49DataComplexity=0xffffffff */ };
  typedef VITA49DataComplexity& VITA49DataComplexity_out;

  _CORBA_MODULE_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_VITA49DataComplexity;

  struct VITA49DataPacketPayloadFormat {
    typedef _CORBA_ConstrType_Fix_Var<VITA49DataPacketPayloadFormat> _var_type;

    
    ::CORBA::Boolean packing_method_processing_efficient;

    VITA49DataComplexity complexity;

    VITA49DataDigraph data_item_format;

    ::CORBA::Boolean repeating;

    ::CORBA::Long event_tag_size;

    ::CORBA::Long channel_tag_size;

    ::CORBA::Long item_packing_field_size;

    ::CORBA::Long data_item_size;

    ::CORBA::Long repeat_count;

    ::CORBA::Long vector_size;

  

    void operator>>= (cdrStream &) const;
    void operator<<= (cdrStream &);
  };

  typedef VITA49DataPacketPayloadFormat::_var_type VITA49DataPacketPayloadFormat_var;

  typedef VITA49DataPacketPayloadFormat& VITA49DataPacketPayloadFormat_out;

  _CORBA_MODULE_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_VITA49DataPacketPayloadFormat;

  struct VITA49StreamDefinition {
    typedef _CORBA_ConstrType_Variable_Var<VITA49StreamDefinition> _var_type;

    
    ::CORBA::String_member ip_address;

    ::CORBA::ULong vlan;

    ::CORBA::ULong port;

    TransportProtocol protocol;

    ::CORBA::String_member id;

    ::CORBA::Boolean valid_data_format;

    VITA49DataPacketPayloadFormat data_format;

  

    void operator>>= (cdrStream &) const;
    void operator<<= (cdrStream &);
  };

  typedef VITA49StreamDefinition::_var_type VITA49StreamDefinition_var;

  typedef _CORBA_ConstrType_Variable_OUT_arg< VITA49StreamDefinition,VITA49StreamDefinition_var > VITA49StreamDefinition_out;

  _CORBA_MODULE_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_VITA49StreamDefinition;

  _CORBA_MODULE_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_VITA49StreamSequence;

  class VITA49StreamSequence_var;

  class VITA49StreamSequence : public _CORBA_Unbounded_Sequence< VITA49StreamDefinition >  {
  public:
    typedef VITA49StreamSequence_var _var_type;
    inline VITA49StreamSequence() {}
    inline VITA49StreamSequence(const VITA49StreamSequence& _s)
      : _CORBA_Unbounded_Sequence< VITA49StreamDefinition > (_s) {}

    inline VITA49StreamSequence(_CORBA_ULong _max)
      : _CORBA_Unbounded_Sequence< VITA49StreamDefinition > (_max) {}
    inline VITA49StreamSequence(_CORBA_ULong _max, _CORBA_ULong _len, VITA49StreamDefinition* _val, _CORBA_Boolean _rel=0)
      : _CORBA_Unbounded_Sequence< VITA49StreamDefinition > (_max, _len, _val, _rel) {}

  

    inline VITA49StreamSequence& operator = (const VITA49StreamSequence& _s) {
      _CORBA_Unbounded_Sequence< VITA49StreamDefinition > ::operator=(_s);
      return *this;
    }
  };

  class VITA49StreamSequence_out;

  class VITA49StreamSequence_var {
  public:
    inline VITA49StreamSequence_var() : _pd_seq(0) {}
    inline VITA49StreamSequence_var(VITA49StreamSequence* _s) : _pd_seq(_s) {}
    inline VITA49StreamSequence_var(const VITA49StreamSequence_var& _s) {
      if (_s._pd_seq)  _pd_seq = new VITA49StreamSequence(*_s._pd_seq);
      else             _pd_seq = 0;
    }
    inline ~VITA49StreamSequence_var() { if (_pd_seq)  delete _pd_seq; }
      
    inline VITA49StreamSequence_var& operator = (VITA49StreamSequence* _s) {
      if (_pd_seq)  delete _pd_seq;
      _pd_seq = _s;
      return *this;
    }
    inline VITA49StreamSequence_var& operator = (const VITA49StreamSequence_var& _s) {
      if (_s._pd_seq) {
        if (!_pd_seq)  _pd_seq = new VITA49StreamSequence;
        *_pd_seq = *_s._pd_seq;
      } else if (_pd_seq) {
        delete _pd_seq;
        _pd_seq = 0;
      }
      return *this;
    }
    inline VITA49StreamDefinition& operator [] (_CORBA_ULong _s) {
      return (*_pd_seq)[_s];
    }

  

    inline VITA49StreamSequence* operator -> () { return _pd_seq; }
    inline const VITA49StreamSequence* operator -> () const { return _pd_seq; }
#if defined(__GNUG__)
    inline operator VITA49StreamSequence& () const { return *_pd_seq; }
#else
    inline operator const VITA49StreamSequence& () const { return *_pd_seq; }
    inline operator VITA49StreamSequence& () { return *_pd_seq; }
#endif
      
    inline const VITA49StreamSequence& in() const { return *_pd_seq; }
    inline VITA49StreamSequence&       inout()    { return *_pd_seq; }
    inline VITA49StreamSequence*&      out() {
      if (_pd_seq) { delete _pd_seq; _pd_seq = 0; }
      return _pd_seq;
    }
    inline VITA49StreamSequence* _retn() { VITA49StreamSequence* tmp = _pd_seq; _pd_seq = 0; return tmp; }
      
    friend class VITA49StreamSequence_out;
    
  private:
    VITA49StreamSequence* _pd_seq;
  };

  class VITA49StreamSequence_out {
  public:
    inline VITA49StreamSequence_out(VITA49StreamSequence*& _s) : _data(_s) { _data = 0; }
    inline VITA49StreamSequence_out(VITA49StreamSequence_var& _s)
      : _data(_s._pd_seq) { _s = (VITA49StreamSequence*) 0; }
    inline VITA49StreamSequence_out(const VITA49StreamSequence_out& _s) : _data(_s._data) {}
    inline VITA49StreamSequence_out& operator = (const VITA49StreamSequence_out& _s) {
      _data = _s._data;
      return *this;
    }
    inline VITA49StreamSequence_out& operator = (VITA49StreamSequence* _s) {
      _data = _s;
      return *this;
    }
    inline operator VITA49StreamSequence*&()  { return _data; }
    inline VITA49StreamSequence*& ptr()       { return _data; }
    inline VITA49StreamSequence* operator->() { return _data; }

    inline VITA49StreamDefinition& operator [] (_CORBA_ULong _i) {
      return (*_data)[_i];
    }

  

    VITA49StreamSequence*& _data;

  private:
    VITA49StreamSequence_out();
    VITA49StreamSequence_out& operator=(const VITA49StreamSequence_var&);
  };

#ifndef __BULKIO_mdataVITA49__
#define __BULKIO_mdataVITA49__
  class dataVITA49;
  class _objref_dataVITA49;
  class _impl_dataVITA49;
  
  typedef _objref_dataVITA49* dataVITA49_ptr;
  typedef dataVITA49_ptr dataVITA49Ref;

  class dataVITA49_Helper {
  public:
    typedef dataVITA49_ptr _ptr_type;

    static _ptr_type _nil();
    static _CORBA_Boolean is_nil(_ptr_type);
    static void release(_ptr_type);
    static void duplicate(_ptr_type);
    static void marshalObjRef(_ptr_type, cdrStream&);
    static _ptr_type unmarshalObjRef(cdrStream&);
  };

  typedef _CORBA_ObjRef_Var<_objref_dataVITA49, dataVITA49_Helper> dataVITA49_var;
  typedef _CORBA_ObjRef_OUT_arg<_objref_dataVITA49,dataVITA49_Helper > dataVITA49_out;

#endif

  // interface dataVITA49
  class dataVITA49 {
  public:
    // Declarations for this interface type.
    typedef dataVITA49_ptr _ptr_type;
    typedef dataVITA49_var _var_type;

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
    enum InputUsageState { IDLE, ACTIVE, BUSY /*, __max_InputUsageState=0xffffffff */ };
    typedef InputUsageState& InputUsageState_out;

    static _dyn_attr const ::CORBA::TypeCode_ptr _tc_InputUsageState;

    class AttachError : public ::CORBA::UserException {
    public:
      
      ::CORBA::String_member msg;

    

      inline AttachError() {
        pd_insertToAnyFn    = insertToAnyFn;
        pd_insertToAnyFnNCP = insertToAnyFnNCP;
      }
      AttachError(const AttachError&);
      AttachError(const char* i_msg);
      AttachError& operator=(const AttachError&);
      virtual ~AttachError();
      virtual void _raise() const;
      static AttachError* _downcast(::CORBA::Exception*);
      static const AttachError* _downcast(const ::CORBA::Exception*);
      static inline AttachError* _narrow(::CORBA::Exception* _e) {
        return _downcast(_e);
      }
      
      void operator>>=(cdrStream&) const ;
      void operator<<=(cdrStream&) ;

      static _core_attr insertExceptionToAny    insertToAnyFn;
      static _core_attr insertExceptionToAnyNCP insertToAnyFnNCP;

      virtual ::CORBA::Exception* _NP_duplicate() const;

      static _core_attr const char* _PD_repoId;
      static _core_attr const char* _PD_typeId;

    private:
      virtual const char* _NP_typeId() const;
      virtual const char* _NP_repoId(int*) const;
      virtual void _NP_marshal(cdrStream&) const;
    };

    static _dyn_attr const ::CORBA::TypeCode_ptr _tc_AttachError;

    class DetachError : public ::CORBA::UserException {
    public:
      
      ::CORBA::String_member msg;

    

      inline DetachError() {
        pd_insertToAnyFn    = insertToAnyFn;
        pd_insertToAnyFnNCP = insertToAnyFnNCP;
      }
      DetachError(const DetachError&);
      DetachError(const char* i_msg);
      DetachError& operator=(const DetachError&);
      virtual ~DetachError();
      virtual void _raise() const;
      static DetachError* _downcast(::CORBA::Exception*);
      static const DetachError* _downcast(const ::CORBA::Exception*);
      static inline DetachError* _narrow(::CORBA::Exception* _e) {
        return _downcast(_e);
      }
      
      void operator>>=(cdrStream&) const ;
      void operator<<=(cdrStream&) ;

      static _core_attr insertExceptionToAny    insertToAnyFn;
      static _core_attr insertExceptionToAnyNCP insertToAnyFnNCP;

      virtual ::CORBA::Exception* _NP_duplicate() const;

      static _core_attr const char* _PD_repoId;
      static _core_attr const char* _PD_typeId;

    private:
      virtual const char* _NP_typeId() const;
      virtual const char* _NP_repoId(int*) const;
      virtual void _NP_marshal(cdrStream&) const;
    };

    static _dyn_attr const ::CORBA::TypeCode_ptr _tc_DetachError;

    class StreamInputError : public ::CORBA::UserException {
    public:
      
      ::CORBA::String_member msg;

    

      inline StreamInputError() {
        pd_insertToAnyFn    = insertToAnyFn;
        pd_insertToAnyFnNCP = insertToAnyFnNCP;
      }
      StreamInputError(const StreamInputError&);
      StreamInputError(const char* i_msg);
      StreamInputError& operator=(const StreamInputError&);
      virtual ~StreamInputError();
      virtual void _raise() const;
      static StreamInputError* _downcast(::CORBA::Exception*);
      static const StreamInputError* _downcast(const ::CORBA::Exception*);
      static inline StreamInputError* _narrow(::CORBA::Exception* _e) {
        return _downcast(_e);
      }
      
      void operator>>=(cdrStream&) const ;
      void operator<<=(cdrStream&) ;

      static _core_attr insertExceptionToAny    insertToAnyFn;
      static _core_attr insertExceptionToAnyNCP insertToAnyFnNCP;

      virtual ::CORBA::Exception* _NP_duplicate() const;

      static _core_attr const char* _PD_repoId;
      static _core_attr const char* _PD_typeId;

    private:
      virtual const char* _NP_typeId() const;
      virtual const char* _NP_repoId(int*) const;
      virtual void _NP_marshal(cdrStream&) const;
    };

    static _dyn_attr const ::CORBA::TypeCode_ptr _tc_StreamInputError;

  
  };

  class _objref_dataVITA49 :
    public virtual _objref_ProvidesPortStatisticsProvider
  {
  public:
    // IDL operations
    dataVITA49::InputUsageState usageState();
    VITA49StreamSequence* attachedStreams();
    StringSequence* attachmentIds();
    char* attach(const ::BULKIO::VITA49StreamDefinition& stream, const char* userid);
    void detach(const char* attachId);
    VITA49StreamDefinition* getStreamDefinition(const char* attachId);
    char* getUser(const char* attachId);
    StreamSRISequence* attachedSRIs();
    void pushSRI(const ::BULKIO::StreamSRI& H, const ::BULKIO::PrecisionUTCTime& T);

    // Constructors
    inline _objref_dataVITA49()  { _PR_setobj(0); }  // nil
    _objref_dataVITA49(omniIOR*, omniIdentity*);

  protected:
    virtual ~_objref_dataVITA49();

    
  private:
    virtual void* _ptrToObjRef(const char*);

    _objref_dataVITA49(const _objref_dataVITA49&);
    _objref_dataVITA49& operator = (const _objref_dataVITA49&);
    // not implemented

    friend class dataVITA49;
  };

  class _pof_dataVITA49 : public _OMNI_NS(proxyObjectFactory) {
  public:
    inline _pof_dataVITA49() : _OMNI_NS(proxyObjectFactory)(dataVITA49::_PD_repoId) {}
    virtual ~_pof_dataVITA49();

    virtual omniObjRef* newObjRef(omniIOR*,omniIdentity*);
    virtual _CORBA_Boolean is_a(const char*) const;
  };

  class _impl_dataVITA49 :
    public virtual _impl_ProvidesPortStatisticsProvider
  {
  public:
    virtual ~_impl_dataVITA49();

    virtual dataVITA49::InputUsageState usageState() = 0;
    virtual VITA49StreamSequence* attachedStreams() = 0;
    virtual StringSequence* attachmentIds() = 0;
    virtual char* attach(const ::BULKIO::VITA49StreamDefinition& stream, const char* userid) = 0;
    virtual void detach(const char* attachId) = 0;
    virtual VITA49StreamDefinition* getStreamDefinition(const char* attachId) = 0;
    virtual char* getUser(const char* attachId) = 0;
    virtual StreamSRISequence* attachedSRIs() = 0;
    virtual void pushSRI(const ::BULKIO::StreamSRI& H, const ::BULKIO::PrecisionUTCTime& T) = 0;
    
  public:  // Really protected, workaround for xlC
    virtual _CORBA_Boolean _dispatch(omniCallHandle&);

  private:
    virtual void* _ptrToInterface(const char*);
    virtual const char* _mostDerivedRepoId();
    
  };


  _CORBA_MODULE_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_dataVITA49;

_CORBA_MODULE_END



_CORBA_MODULE POA_BULKIO
_CORBA_MODULE_BEG

  class dataVITA49 :
    public virtual BULKIO::_impl_dataVITA49,
    public virtual ProvidesPortStatisticsProvider
  {
  public:
    virtual ~dataVITA49();

    inline ::BULKIO::dataVITA49_ptr _this() {
      return (::BULKIO::dataVITA49_ptr) _do_this(::BULKIO::dataVITA49::_PD_repoId);
    }
  };

_CORBA_MODULE_END



_CORBA_MODULE OBV_BULKIO
_CORBA_MODULE_BEG

_CORBA_MODULE_END





#undef _core_attr
#undef _dyn_attr

inline void operator >>=(BULKIO::VITA49DataDigraph _e, cdrStream& s) {
  ::operator>>=((::CORBA::ULong)_e, s);
}

inline void operator <<= (BULKIO::VITA49DataDigraph& _e, cdrStream& s) {
  ::CORBA::ULong _0RL_e;
  ::operator<<=(_0RL_e,s);
  if (_0RL_e <= BULKIO::VITA49_64U) {
    _e = (BULKIO::VITA49DataDigraph) _0RL_e;
  }
  else {
    OMNIORB_THROW(MARSHAL,_OMNI_NS(MARSHAL_InvalidEnumValue),
                  (::CORBA::CompletionStatus)s.completion());
  }
}

void operator<<=(::CORBA::Any& _a, BULKIO::VITA49DataDigraph _s);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, BULKIO::VITA49DataDigraph& _s);

inline void operator >>=(BULKIO::TransportProtocol _e, cdrStream& s) {
  ::operator>>=((::CORBA::ULong)_e, s);
}

inline void operator <<= (BULKIO::TransportProtocol& _e, cdrStream& s) {
  ::CORBA::ULong _0RL_e;
  ::operator<<=(_0RL_e,s);
  if (_0RL_e <= BULKIO::VITA49_UNKNOWN_TRANSPORT) {
    _e = (BULKIO::TransportProtocol) _0RL_e;
  }
  else {
    OMNIORB_THROW(MARSHAL,_OMNI_NS(MARSHAL_InvalidEnumValue),
                  (::CORBA::CompletionStatus)s.completion());
  }
}

void operator<<=(::CORBA::Any& _a, BULKIO::TransportProtocol _s);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, BULKIO::TransportProtocol& _s);

inline void operator >>=(BULKIO::VITA49DataComplexity _e, cdrStream& s) {
  ::operator>>=((::CORBA::ULong)_e, s);
}

inline void operator <<= (BULKIO::VITA49DataComplexity& _e, cdrStream& s) {
  ::CORBA::ULong _0RL_e;
  ::operator<<=(_0RL_e,s);
  if (_0RL_e <= BULKIO::VITA49_RESERVED2) {
    _e = (BULKIO::VITA49DataComplexity) _0RL_e;
  }
  else {
    OMNIORB_THROW(MARSHAL,_OMNI_NS(MARSHAL_InvalidEnumValue),
                  (::CORBA::CompletionStatus)s.completion());
  }
}

void operator<<=(::CORBA::Any& _a, BULKIO::VITA49DataComplexity _s);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, BULKIO::VITA49DataComplexity& _s);

extern void operator<<=(::CORBA::Any& _a, const BULKIO::VITA49DataPacketPayloadFormat& _s);
extern void operator<<=(::CORBA::Any& _a, BULKIO::VITA49DataPacketPayloadFormat* _sp);
extern _CORBA_Boolean operator>>=(const ::CORBA::Any& _a, BULKIO::VITA49DataPacketPayloadFormat*& _sp);
extern _CORBA_Boolean operator>>=(const ::CORBA::Any& _a, const BULKIO::VITA49DataPacketPayloadFormat*& _sp);

extern void operator<<=(::CORBA::Any& _a, const BULKIO::VITA49StreamDefinition& _s);
extern void operator<<=(::CORBA::Any& _a, BULKIO::VITA49StreamDefinition* _sp);
extern _CORBA_Boolean operator>>=(const ::CORBA::Any& _a, BULKIO::VITA49StreamDefinition*& _sp);
extern _CORBA_Boolean operator>>=(const ::CORBA::Any& _a, const BULKIO::VITA49StreamDefinition*& _sp);

void operator<<=(::CORBA::Any& _a, const BULKIO::VITA49StreamSequence& _s);
void operator<<=(::CORBA::Any& _a, BULKIO::VITA49StreamSequence* _sp);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, BULKIO::VITA49StreamSequence*& _sp);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, const BULKIO::VITA49StreamSequence*& _sp);

inline void operator >>=(BULKIO::dataVITA49::InputUsageState _e, cdrStream& s) {
  ::operator>>=((::CORBA::ULong)_e, s);
}

inline void operator <<= (BULKIO::dataVITA49::InputUsageState& _e, cdrStream& s) {
  ::CORBA::ULong _0RL_e;
  ::operator<<=(_0RL_e,s);
  if (_0RL_e <= BULKIO::dataVITA49::BUSY) {
    _e = (BULKIO::dataVITA49::InputUsageState) _0RL_e;
  }
  else {
    OMNIORB_THROW(MARSHAL,_OMNI_NS(MARSHAL_InvalidEnumValue),
                  (::CORBA::CompletionStatus)s.completion());
  }
}

void operator<<=(::CORBA::Any& _a, BULKIO::dataVITA49::InputUsageState _s);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, BULKIO::dataVITA49::InputUsageState& _s);

void operator<<=(::CORBA::Any& _a, const BULKIO::dataVITA49::AttachError& _s);
void operator<<=(::CORBA::Any& _a, const BULKIO::dataVITA49::AttachError* _sp);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, const BULKIO::dataVITA49::AttachError*& _sp);

void operator<<=(::CORBA::Any& _a, const BULKIO::dataVITA49::DetachError& _s);
void operator<<=(::CORBA::Any& _a, const BULKIO::dataVITA49::DetachError* _sp);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, const BULKIO::dataVITA49::DetachError*& _sp);

void operator<<=(::CORBA::Any& _a, const BULKIO::dataVITA49::StreamInputError& _s);
void operator<<=(::CORBA::Any& _a, const BULKIO::dataVITA49::StreamInputError* _sp);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, const BULKIO::dataVITA49::StreamInputError*& _sp);

void operator<<=(::CORBA::Any& _a, BULKIO::dataVITA49_ptr _s);
void operator<<=(::CORBA::Any& _a, BULKIO::dataVITA49_ptr* _s);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, BULKIO::dataVITA49_ptr& _s);



inline void
BULKIO::dataVITA49::_marshalObjRef(::BULKIO::dataVITA49_ptr obj, cdrStream& s) {
  omniObjRef::_marshal(obj->_PR_getobj(),s);
}



#ifdef   USE_stub_in_nt_dll_NOT_DEFINED_bio__dataVITA49
# undef  USE_stub_in_nt_dll
# undef  USE_stub_in_nt_dll_NOT_DEFINED_bio__dataVITA49
#endif
#ifdef   USE_core_stub_in_nt_dll_NOT_DEFINED_bio__dataVITA49
# undef  USE_core_stub_in_nt_dll
# undef  USE_core_stub_in_nt_dll_NOT_DEFINED_bio__dataVITA49
#endif
#ifdef   USE_dyn_stub_in_nt_dll_NOT_DEFINED_bio__dataVITA49
# undef  USE_dyn_stub_in_nt_dll
# undef  USE_dyn_stub_in_nt_dll_NOT_DEFINED_bio__dataVITA49
#endif

#endif  // __bio__dataVITA49_hh__

