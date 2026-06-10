// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the GENEVAETWDLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// GENEVAETWDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef GENEVAETWDLL_EXPORTS
#define GENEVAETWDLL_API __declspec(dllexport)
#else
#define GENEVAETWDLL_API __declspec(dllimport)
#endif

// This class is exported from the dll
class GENEVAETWDLL_API CGenevaEtwDll {
public:
	CGenevaEtwDll(void);
	// TODO: add your methods here.
};

extern GENEVAETWDLL_API int nGenevaEtwDll;

GENEVAETWDLL_API int fnGenevaEtwDll(void);
