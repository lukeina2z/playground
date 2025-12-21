// Calculator.cpp : Implementation of CCalculator

#include "pch.h"
#include "Calculator.h"
#include <atlconv.h>


// CCalculator

STDMETHODIMP CCalculator::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* const arr[] = 
	{
		&IID_ICalculator
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void Test(LPCSTR str)
{
	// Use ATL debug trace to dump the incoming parameter.
	// Safe-print: handle null pointer.
	if (str == nullptr)
	{
		ATLTRACE("Test: parameter is NULL\n");
	}
	else
	{
		ATLTRACE("Test: parameter = \"%s\"\n", str);    
	}
}

void Test2(LPCSTR str)
{
    // Use ATL conversion helper to convert ANSI char string to OLE (wide) string
    if (str == nullptr)
    {
        ATLTRACE("Test2: parameter is NULL\n");
        return;
    }

    CA2CT tStr(str);

    CT2COLE oleStr(tStr);
    LPCOLESTR pOle = static_cast<LPCOLESTR>(oleStr);
    // Print the converted OLE string (wide) to the debugger output
    ATLTRACE("Test2: parameter (OLE) = \"%ls\"\n", pOle);
}

STDMETHODIMP CCalculator::Add(LONG a, LONG b, LONG* ret)
{
    // TODO: Add your implementation code here
    LONG result = a + b;
    if ((a > 0 && b > 0 && result <= 0) ||
        (a < 0 && b < 0 && result >= 0))
    {
        return E_FAIL;
    }

    Test2("test2, Hello from Add method!");
    Test("test, Hello from Add method!");

    *ret = result;
    return S_OK;
}
