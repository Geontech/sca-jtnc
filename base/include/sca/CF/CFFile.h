// This file is generated by omniidl (C++ backend)- omniORB_4_2. Do not edit.
#ifndef __CFFile_hh__
#define __CFFile_hh__

#ifndef __CORBA_H_EXTERNAL_GUARD__
#include <omniORB4/CORBA.h>
#endif

#ifndef  USE_stub_in_nt_dll
# define USE_stub_in_nt_dll_NOT_DEFINED_CFFile
#endif
#ifndef  USE_core_stub_in_nt_dll
# define USE_core_stub_in_nt_dll_NOT_DEFINED_CFFile
#endif
#ifndef  USE_dyn_stub_in_nt_dll
# define USE_dyn_stub_in_nt_dll_NOT_DEFINED_CFFile
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

  class FileException : public ::CORBA::UserException {
  public:
    
    ErrorNumberType errorNumber;

    ::CORBA::String_member msg;

  

    inline FileException() {
      pd_insertToAnyFn    = insertToAnyFn;
      pd_insertToAnyFnNCP = insertToAnyFnNCP;
    }
    FileException(const FileException&);
    FileException(ErrorNumberType i_errorNumber, const char* i_msg);
    FileException& operator=(const FileException&);
    virtual ~FileException();
    virtual void _raise() const;
    static FileException* _downcast(::CORBA::Exception*);
    static const FileException* _downcast(const ::CORBA::Exception*);
    static inline FileException* _narrow(::CORBA::Exception* _e) {
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

  _CORBA_MODULE_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_FileException;

#ifndef __CF_mFile__
#define __CF_mFile__
  class File;
  class _objref_File;
  class _impl_File;
  
  typedef _objref_File* File_ptr;
  typedef File_ptr FileRef;

  class File_Helper {
  public:
    typedef File_ptr _ptr_type;

    static _ptr_type _nil();
    static _CORBA_Boolean is_nil(_ptr_type);
    static void release(_ptr_type);
    static void duplicate(_ptr_type);
    static void marshalObjRef(_ptr_type, cdrStream&);
    static _ptr_type unmarshalObjRef(cdrStream&);
  };

  typedef _CORBA_ObjRef_Var<_objref_File, File_Helper> File_var;
  typedef _CORBA_ObjRef_OUT_arg<_objref_File,File_Helper > File_out;

#endif

  // interface File
  class File {
  public:
    // Declarations for this interface type.
    typedef File_ptr _ptr_type;
    typedef File_var _var_type;

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
    class IOException : public ::CORBA::UserException {
    public:
      
      ErrorNumberType errorNumber;

      ::CORBA::String_member msg;

    

      inline IOException() {
        pd_insertToAnyFn    = insertToAnyFn;
        pd_insertToAnyFnNCP = insertToAnyFnNCP;
      }
      IOException(const IOException&);
      IOException(ErrorNumberType i_errorNumber, const char* i_msg);
      IOException& operator=(const IOException&);
      virtual ~IOException();
      virtual void _raise() const;
      static IOException* _downcast(::CORBA::Exception*);
      static const IOException* _downcast(const ::CORBA::Exception*);
      static inline IOException* _narrow(::CORBA::Exception* _e) {
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

    static _dyn_attr const ::CORBA::TypeCode_ptr _tc_IOException;

    class InvalidFilePointer : public ::CORBA::UserException {
    public:
      
      

      inline InvalidFilePointer() {
        pd_insertToAnyFn    = insertToAnyFn;
        pd_insertToAnyFnNCP = insertToAnyFnNCP;
      }
      InvalidFilePointer(const InvalidFilePointer&);
      
      InvalidFilePointer& operator=(const InvalidFilePointer&);
      virtual ~InvalidFilePointer();
      virtual void _raise() const;
      static InvalidFilePointer* _downcast(::CORBA::Exception*);
      static const InvalidFilePointer* _downcast(const ::CORBA::Exception*);
      static inline InvalidFilePointer* _narrow(::CORBA::Exception* _e) {
        return _downcast(_e);
      }
      
      inline void operator>>=(cdrStream&) const { }
      inline void operator<<=(cdrStream&) { }

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

    static _dyn_attr const ::CORBA::TypeCode_ptr _tc_InvalidFilePointer;

  
  };

  class _objref_File :
    public virtual ::CORBA::Object,
    public virtual omniObjRef
  {
  public:
    // IDL operations
    char* fileName();
    ::CORBA::ULong filePointer();
    void read(::CF::OctetSequence_out data, ::CORBA::ULong length);
    void write(const ::CF::OctetSequence& data);
    ::CORBA::ULong sizeOf();
    void close();
    void setFilePointer(::CORBA::ULong filePointer);

    // Constructors
    inline _objref_File()  { _PR_setobj(0); }  // nil
    _objref_File(omniIOR*, omniIdentity*);

  protected:
    virtual ~_objref_File();

    
  private:
    virtual void* _ptrToObjRef(const char*);

    _objref_File(const _objref_File&);
    _objref_File& operator = (const _objref_File&);
    // not implemented

    friend class File;
  };

  class _pof_File : public _OMNI_NS(proxyObjectFactory) {
  public:
    inline _pof_File() : _OMNI_NS(proxyObjectFactory)(File::_PD_repoId) {}
    virtual ~_pof_File();

    virtual omniObjRef* newObjRef(omniIOR*,omniIdentity*);
    virtual _CORBA_Boolean is_a(const char*) const;
  };

  class _impl_File :
    public virtual omniServant
  {
  public:
    virtual ~_impl_File();

    virtual char* fileName() = 0;
    virtual ::CORBA::ULong filePointer() = 0;
    virtual void read(::CF::OctetSequence_out data, ::CORBA::ULong length) = 0;
    virtual void write(const ::CF::OctetSequence& data) = 0;
    virtual ::CORBA::ULong sizeOf() = 0;
    virtual void close() = 0;
    virtual void setFilePointer(::CORBA::ULong filePointer) = 0;
    
  public:  // Really protected, workaround for xlC
    virtual _CORBA_Boolean _dispatch(omniCallHandle&);

  private:
    virtual void* _ptrToInterface(const char*);
    virtual const char* _mostDerivedRepoId();
    
  };


  _CORBA_MODULE_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_File;

_CORBA_MODULE_END



_CORBA_MODULE POA_CF
_CORBA_MODULE_BEG

  class File :
    public virtual CF::_impl_File,
    public virtual ::PortableServer::ServantBase
  {
  public:
    virtual ~File();

    inline ::CF::File_ptr _this() {
      return (::CF::File_ptr) _do_this(::CF::File::_PD_repoId);
    }
  };

_CORBA_MODULE_END



_CORBA_MODULE OBV_CF
_CORBA_MODULE_BEG

_CORBA_MODULE_END





#undef _core_attr
#undef _dyn_attr

void operator<<=(::CORBA::Any& _a, const CF::FileException& _s);
void operator<<=(::CORBA::Any& _a, const CF::FileException* _sp);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, const CF::FileException*& _sp);

void operator<<=(::CORBA::Any& _a, const CF::File::IOException& _s);
void operator<<=(::CORBA::Any& _a, const CF::File::IOException* _sp);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, const CF::File::IOException*& _sp);

void operator<<=(::CORBA::Any& _a, const CF::File::InvalidFilePointer& _s);
void operator<<=(::CORBA::Any& _a, const CF::File::InvalidFilePointer* _sp);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, const CF::File::InvalidFilePointer*& _sp);

void operator<<=(::CORBA::Any& _a, CF::File_ptr _s);
void operator<<=(::CORBA::Any& _a, CF::File_ptr* _s);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, CF::File_ptr& _s);



inline void
CF::File::_marshalObjRef(::CF::File_ptr obj, cdrStream& s) {
  omniObjRef::_marshal(obj->_PR_getobj(),s);
}



#ifdef   USE_stub_in_nt_dll_NOT_DEFINED_CFFile
# undef  USE_stub_in_nt_dll
# undef  USE_stub_in_nt_dll_NOT_DEFINED_CFFile
#endif
#ifdef   USE_core_stub_in_nt_dll_NOT_DEFINED_CFFile
# undef  USE_core_stub_in_nt_dll
# undef  USE_core_stub_in_nt_dll_NOT_DEFINED_CFFile
#endif
#ifdef   USE_dyn_stub_in_nt_dll_NOT_DEFINED_CFFile
# undef  USE_dyn_stub_in_nt_dll
# undef  USE_dyn_stub_in_nt_dll_NOT_DEFINED_CFFile
#endif

#endif  // __CFFile_hh__

