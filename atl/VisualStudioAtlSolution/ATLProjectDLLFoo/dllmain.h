// dllmain.h : Declaration of module class.

class CATLProjectDLLFooModule : public ATL::CAtlDllModuleT< CATLProjectDLLFooModule >
{
public :
	DECLARE_LIBID(LIBID_ATLProjectDLLFooLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_ATLPROJECTDLLFOO, "{99ca2513-6901-43c3-88d7-cba9b4d17a8f}")
};

extern class CATLProjectDLLFooModule _AtlModule;
