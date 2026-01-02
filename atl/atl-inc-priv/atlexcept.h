// This is a part of the Active Template Library.
// Copyright (C) Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Active Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Active Template Library product.

#ifndef __ATLEXCEPT_H__
#define __ATLEXCEPT_H__

#pragma once

#include <atldef.h>
#include <atltrace.h>
#include <strsafe.h>


#pragma pack(push,_ATL_PACKING)
namespace ATL
{

/////////////////////////////////////////////////////////////////////////////
// Exception raise (for functions that cannot return an error code)

inline void __declspec(noreturn) _AtlRaiseException(
	_In_ DWORD dwExceptionCode,
	_In_ DWORD dwExceptionFlags = EXCEPTION_NONCONTINUABLE)
{
	RaiseException( dwExceptionCode, dwExceptionFlags, 0, NULL );
}

inline void __declspec(noreturn) _AtlRaiseException( LONG lExceptionCode, DWORD dwExceptionFlags = EXCEPTION_NONCONTINUABLE )
{
	RaiseException( lExceptionCode, dwExceptionFlags, 0, NULL );
}

class CAtlException
{
public:
    CAtlException() noexcept :
        m_hr( E_FAIL ),
        m_lLine(0)
    {
        m_szFilename[0] = '\0';
        ATLASSERT(false);
    }

    CAtlException(_In_ HRESULT hr, _In_ LPCSTR szFilename, _In_ long lLine) noexcept :
        m_hr(hr),
        m_lLine(lLine)
    {
        if (szFilename)
        {
            constexpr size_t maxLen = sizeof(m_szFilename) - 1;
            size_t len = strlen(szFilename);
            size_t iStart = len > maxLen ? len - maxLen : 0;
            StringCbCopyA(m_szFilename, sizeof(m_szFilename), szFilename + iStart);
        }
        else
        {
            m_szFilename[0] = '\0';
        }

        ATLASSERT(false);
    }

    operator HRESULT() const noexcept
    {
        return( m_hr );
    }

public:
    // we'd prefer to use CStringA here, but CString and even CSimpleString throw CAtlException, so there is a circular header dependency.
    // Instead, we just take the last MAX_BASE_NAME_LENGTH chars of the filename.
    static constexpr size_t MAX_BASE_NAME_LENGTH = 48;
    char m_szFilename[MAX_BASE_NAME_LENGTH];
    long m_lLine;
    HRESULT m_hr;
};

// see note at bottom of PassportException.h
static_assert(sizeof(CAtlException) < 100, "CAtlException has gotten too big");


#ifndef _ATL_NO_EXCEPTIONS

// Throw a CAtlException with the given HRESULT
#if defined( _ATL_CUSTOM_THROW )  // You can define your own AtlThrow to throw a custom exception.
#ifdef _AFX
#error MFC projects must use default implementation of Atlnoexcept
#endif
#else
ATL_NOINLINE __declspec(noreturn) inline void WINAPI AtlThrowImpl(_In_ HRESULT hr, _In_ LPCSTR szFileName, _In_ LONG lLineNumber)
{
	ATLTRACE(atlTraceException, 0, _T("AtlThrow: hr = 0x%x\n"), hr );
#ifdef _AFX
	if( hr == E_OUTOFMEMORY )
	{
		AfxThrowMemoryException();
	}
	else
	{
		AfxThrowOleException( hr );
	}
#else
	throw CAtlException( hr , szFileName, lLineNumber);
#endif
};
#endif

// Throw a CAtlException corresponding to the result of ::GetLastError
ATL_NOINLINE __declspec(noreturn) inline void WINAPI AtlThrowLastWin32()
{
	DWORD dwError = ::GetLastError();
	AtlThrow( HRESULT_FROM_WIN32( dwError ) );
}

#else  // no exception handling

// Throw a CAtlException with th given HRESULT
#if !defined( _ATL_CUSTOM_THROW )  // You can define your own AtlThrow

ATL_NOINLINE inline void WINAPI AtlThrowImpl(_In_ HRESULT hr, _In_ LPCSTR /*szFileName*/, _In_ LONG /*lLineNumber*/)
{
	ATLTRACE(atlTraceException, 0, _T("AtlThrow: hr = 0x%x\n"), hr );
	ATLASSERT( false );
	DWORD dwExceptionCode;
	switch(hr)
	{
	case E_OUTOFMEMORY:
		dwExceptionCode = STATUS_NO_MEMORY;
		break;
	default:
		dwExceptionCode = EXCEPTION_ILLEGAL_INSTRUCTION;
	}
	_AtlRaiseException((DWORD)dwExceptionCode);
}
#endif

// Throw a CAtlException corresponding to the result of ::GetLastError
ATL_NOINLINE inline void WINAPI AtlThrowLastWin32()
{
	DWORD dwError = ::GetLastError();
	AtlThrow( HRESULT_FROM_WIN32( dwError ));
}

#endif  // no exception handling

};  // namespace ATL
#pragma pack(pop)

#endif  // __ATLEXCEPT_H__
