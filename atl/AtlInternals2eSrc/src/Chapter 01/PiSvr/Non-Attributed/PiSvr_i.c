

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.01.0628 */
/* at Mon Jan 18 19:14:07 2038
 */
/* Compiler settings for PiSvr.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0628 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        EXTERN_C __declspec(selectany) const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif // !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_ICalcPi,0x1F50EB41,0x517E,0x492E,0xAE,0xB5,0x1B,0x6B,0x62,0xBE,0x45,0xEF);


MIDL_DEFINE_GUID(IID, IID_IAdvertiseMyself,0x7B568195,0xF63B,0x11D1,0x98,0x18,0x00,0x60,0x08,0x23,0xCF,0xFB);


MIDL_DEFINE_GUID(IID, LIBID_PiSvrLib,0xE20118C6,0x84AF,0x4002,0x9A,0x36,0x94,0x30,0x9C,0x2F,0x1B,0x42);


MIDL_DEFINE_GUID(IID, DIID__ICalcPiEvents,0x04959383,0xAFDD,0x4D13,0x81,0x3A,0x81,0x8B,0x10,0x2F,0x9A,0xDE);


MIDL_DEFINE_GUID(CLSID, CLSID_CalcPi,0x0FC2B4C2,0x0159,0x4ECC,0x89,0x7E,0x60,0xCA,0x30,0x51,0x99,0xC0);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



