// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the NOHIBERNATION_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// NOHIBERNATION_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef NOHIBERNATION_EXPORTS
#define NOHIBERNATION_API __declspec(dllexport)
#else
#define NOHIBERNATION_API __declspec(dllimport)
#endif

// This class is exported from the dll
class NOHIBERNATION_API CNoHibernation {
public:
	CNoHibernation(void);
	void Run();
};

extern NOHIBERNATION_API int nNoHibernation;

NOHIBERNATION_API int fnNoHibernation(void);
