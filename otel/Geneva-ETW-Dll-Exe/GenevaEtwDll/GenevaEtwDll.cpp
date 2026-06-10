// GenevaEtwDll.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "GenevaEtwDll.h"


// This is an example of an exported variable
GENEVAETWDLL_API int nGenevaEtwDll=0;

// This is an example of an exported function.
GENEVAETWDLL_API int fnGenevaEtwDll(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CGenevaEtwDll::CGenevaEtwDll()
{
    return;
}
