// HelloAtlServerEverything.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
// For custom assert and trace handling with WebDbg.exe
#ifdef _DEBUG
CDebugReportHook g_ReportHook;
#endif

#include "HelloAtlServerEverything.h"

class CHelloAtlServerEverythingModule : public CAtlDllModuleT<CHelloAtlServerEverythingModule>
{
public:
};

CHelloAtlServerEverythingModule _AtlModule;


// TODO: Add additional request handlers to the handler map

BEGIN_HANDLER_MAP()
	HANDLER_ENTRY("Default", CHelloAtlServerEverythingHandler)
END_HANDLER_MAP()

#ifdef _MANAGED
#pragma managed(push, off)
#endif

// DLL Entry Point
//
extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	hInstance;
	return _AtlModule.DllMain(dwReason, lpReserved); 
}

#ifdef _MANAGED
#pragma managed(pop)
#endif

