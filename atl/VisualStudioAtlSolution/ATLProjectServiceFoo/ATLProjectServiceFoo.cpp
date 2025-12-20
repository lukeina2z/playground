// ATLProjectServiceFoo.cpp : Implementation of WinMain


#include "pch.h"
#include "framework.h"
#include "resource.h"
#include "ATLProjectServiceFoo_i.h"


using namespace ATL;

#include <stdio.h>

class CATLProjectServiceFooModule : public ATL::CAtlServiceModuleT< CATLProjectServiceFooModule, IDS_SERVICENAME >
{
public :
	DECLARE_LIBID(LIBID_ATLProjectServiceFooLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_ATLPROJECTSERVICEFOO, "{09677ce9-f0b1-48d4-8f45-558a437582f7}")
	HRESULT InitializeSecurity() throw()
	{
		// TODO : Call CoInitializeSecurity and provide the appropriate security settings for your service
		// Suggested - PKT Level Authentication,
		// Impersonation Level of RPC_C_IMP_LEVEL_IDENTIFY
		// and an appropriate non-null Security Descriptor.

		return S_OK;
	}
};

CATLProjectServiceFooModule _AtlModule;



//
extern "C" int WINAPI _tWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/,
								LPTSTR /*lpCmdLine*/, int nShowCmd)
{
	return _AtlModule.WinMain(nShowCmd);
}

