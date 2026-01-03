// AtlServerWebService.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
// For custom assert and trace handling with WebDbg.exe
#ifdef _DEBUG
CDebugReportHook g_ReportHook;
#endif

#include "AtlServerWebService.h"
[ module(name="MyAtlServerWebService", type=dll) ]
class CDllMainOverride
{
public:
};

[ emitidl(restricted) ];
