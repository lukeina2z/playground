// AtlServerWebService.h : Defines the ATL Server request handler class
//
#pragma once

namespace AtlServerWebServiceService
{
// all struct, enum, and typedefs for your webservice should go inside the namespace

// IAtlServerWebServiceService - web service interface declaration
//
[
	uuid("A044F9BD-5FFF-4889-9D1A-26095CDA5910"), 
	object
]
__interface IAtlServerWebServiceService
{
	// HelloWorld is a sample ATL Server web service method.  It shows how to
	// declare a web service method and its in-parameters and out-parameters
	[id(1)] HRESULT HelloWorld([in] BSTR bstrInput, [out, retval] BSTR *bstrOutput);
	// TODO: Add additional web service methods here
};


// AtlServerWebServiceService - web service implementation
//
[
	request_handler(name="Default", sdl="GenAtlServerWebServiceWSDL"),
	soap_handler(
		name="AtlServerWebServiceService", 
		namespace="urn:AtlServerWebServiceService",
		protocol="soap"
	)
]
class CAtlServerWebServiceService :
	public IAtlServerWebServiceService
{
public:
	// This is a sample web service method that shows how to use the 
	// soap_method attribute to expose a method as a web method
	[ soap_method ]
	HRESULT HelloWorld(/*[in]*/ BSTR bstrInput, /*[out, retval]*/ BSTR *bstrOutput)
	{
		CComBSTR bstrOut(L"Hello ");
		bstrOut += bstrInput;
		bstrOut += L"!";
		*bstrOutput = bstrOut.Detach();
		
		return S_OK;
	}
	// TODO: Add additional web service methods here
}; // class CAtlServerWebServiceService

} // namespace AtlServerWebServiceService
