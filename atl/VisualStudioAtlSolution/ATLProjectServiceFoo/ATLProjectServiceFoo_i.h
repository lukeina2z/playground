

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0628 */
/* at Mon Jan 18 19:14:07 2038
 */
/* Compiler settings for ATLProjectServiceFoo.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0628 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __ATLProjectServiceFoo_i_h__
#define __ATLProjectServiceFoo_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef DECLSPEC_XFGVIRT
#if defined(_CONTROL_FLOW_GUARD_XFG)
#define DECLSPEC_XFGVIRT(base, func) __declspec(xfg_virtual(base, func))
#else
#define DECLSPEC_XFGVIRT(base, func)
#endif
#endif

/* Forward Declarations */ 

#ifndef __IATLSimpleObjectFoo_FWD_DEFINED__
#define __IATLSimpleObjectFoo_FWD_DEFINED__
typedef interface IATLSimpleObjectFoo IATLSimpleObjectFoo;

#endif 	/* __IATLSimpleObjectFoo_FWD_DEFINED__ */


#ifndef __ATLSimpleObjectFoo_FWD_DEFINED__
#define __ATLSimpleObjectFoo_FWD_DEFINED__

#ifdef __cplusplus
typedef class ATLSimpleObjectFoo ATLSimpleObjectFoo;
#else
typedef struct ATLSimpleObjectFoo ATLSimpleObjectFoo;
#endif /* __cplusplus */

#endif 	/* __ATLSimpleObjectFoo_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "shobjidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IATLSimpleObjectFoo_INTERFACE_DEFINED__
#define __IATLSimpleObjectFoo_INTERFACE_DEFINED__

/* interface IATLSimpleObjectFoo */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IATLSimpleObjectFoo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("16b42ef3-867f-4e49-a267-3436acf5e00e")
    IATLSimpleObjectFoo : public IDispatch
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct IATLSimpleObjectFooVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IATLSimpleObjectFoo * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IATLSimpleObjectFoo * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IATLSimpleObjectFoo * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IATLSimpleObjectFoo * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IATLSimpleObjectFoo * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IATLSimpleObjectFoo * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IATLSimpleObjectFoo * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IATLSimpleObjectFooVtbl;

    interface IATLSimpleObjectFoo
    {
        CONST_VTBL struct IATLSimpleObjectFooVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IATLSimpleObjectFoo_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IATLSimpleObjectFoo_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IATLSimpleObjectFoo_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IATLSimpleObjectFoo_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IATLSimpleObjectFoo_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IATLSimpleObjectFoo_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IATLSimpleObjectFoo_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IATLSimpleObjectFoo_INTERFACE_DEFINED__ */



#ifndef __ATLProjectServiceFooLib_LIBRARY_DEFINED__
#define __ATLProjectServiceFooLib_LIBRARY_DEFINED__

/* library ATLProjectServiceFooLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_ATLProjectServiceFooLib;

EXTERN_C const CLSID CLSID_ATLSimpleObjectFoo;

#ifdef __cplusplus

class DECLSPEC_UUID("d29dc9d0-612f-46e1-aada-34de4a35c8b6")
ATLSimpleObjectFoo;
#endif
#endif /* __ATLProjectServiceFooLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


