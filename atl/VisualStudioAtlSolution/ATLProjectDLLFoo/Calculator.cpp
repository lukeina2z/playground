// Calculator.cpp : Implementation of CCalculator

#include "pch.h"
#include "Calculator.h"


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

STDMETHODIMP CCalculator::Add(LONG a, LONG b, LONG* ret)
{
    // TODO: Add your implementation code here
    LONG result = a + b;
    if ((a > 0 && b > 0 && result <= 0) ||
        (a < 0 && b < 0 && result >= 0))
    {
        return E_FAIL;
    }

    *ret = result;
    return S_OK;
}
