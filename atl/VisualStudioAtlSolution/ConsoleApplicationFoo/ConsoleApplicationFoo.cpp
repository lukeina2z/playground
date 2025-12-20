// ConsoleApplicationFoo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>
#include <objbase.h>
#include <iostream>

// Include the generated IDL header from the ATL DLL project so CLSID/IID and the ICalculator
// interface are available. Adjust the relative path if your solution layout differs.
#include "../ATLProjectDLLFoo/ATLProjectDLLFoo_i.h"
#include "../ATLProjectDLLFoo/ATLProjectDLLFoo_i.c"

int main()
{
    HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    if (FAILED(hr))
    {
        std::cerr << "CoInitializeEx failed: 0x" << std::hex << hr << "\n";
        return 1;
    }

    ICalculator* pCalc = nullptr;
    hr = CoCreateInstance(CLSID_Calculator, nullptr, CLSCTX_INPROC_SERVER, IID_ICalculator, reinterpret_cast<void**>(&pCalc));
    if (FAILED(hr))
    {
        std::cerr << "CoCreateInstance failed: 0x" << std::hex << hr << "\n"
                  << "Make sure ATLProjectDLLFoo is built and the COM DLL is registered (e.g. regsvr32) or available to load.\n";
        CoUninitialize();
        return 1;
    }

    LONG result = 0;
    hr = pCalc->Add(5, 7, &result);
    if (SUCCEEDED(hr))
    {
        std::cout << "5 + 7 = " << result << "\n";
    }
    else
    {
        std::cerr << "ICalculator::Add failed: 0x" << std::hex << hr << "\n";
    }

    pCalc->Release();
    CoUninitialize();
    return SUCCEEDED(hr) ? 0 : 1;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
