#pragma once

#include <atlisapi.h>

#define _DATASOURCE_CACHE 1
#define _BROWSERCAPS 2

// CHelloAtlServerEverythingExtensionWorker - custom thread worker class
// for per-thread services

class CHelloAtlServerEverythingExtensionWorker : public CIsapiWorker
{
	// per thread datasource cache
	typedef CDataSourceCache<> ds_cache_type;
	CComObjectGlobal<ds_cache_type> m_dsCache;
	// per thread browser capabilities support
	CComObjectGlobal<CBrowserCapsSvc> m_BrowserCaps;		
	
public:

	CHelloAtlServerEverythingExtensionWorker()
	{
	}
	
	~CHelloAtlServerEverythingExtensionWorker()
	{
	}
	
    virtual BOOL Initialize(void *pvParam)
	{
		if (!CIsapiWorker::Initialize(pvParam))
            return FALSE;

		if (S_OK != m_BrowserCaps.Initialize(_pModule->GetModuleInstance()))
		{
			ATLTRACE("Failed to initialize browser capabilities service.\n");
			return FALSE;
		}

        return TRUE;
	}

	virtual BOOL GetWorkerData(DWORD dwParam, void **ppvData)
	{
		if (dwParam == _DATASOURCE_CACHE && ppvData)
		{
			*ppvData = (void *)&m_dsCache;
			m_dsCache.AddRef();
			return TRUE;
		}
		if (dwParam == _BROWSERCAPS && ppvData)
		{
			*ppvData = (void *)&m_BrowserCaps;
			m_BrowserCaps.AddRef();
			return TRUE;
		}
		return FALSE;
	}
}; // class CHelloAtlServerEverythingExtensionWorker

// CHelloAtlServerEverythingExtension - the ISAPI extension class
template <class ThreadPoolClass=CThreadPool<CHelloAtlServerEverythingExtensionWorker>, 
	class CStatClass=CNoRequestStats, 
	class HttpUserErrorTextProvider=CDefaultErrorProvider, 
	class WorkerThreadTraits=DefaultThreadTraits >
class CHelloAtlServerEverythingExtension : 
	public CIsapiExtension<ThreadPoolClass, 
		CStatClass, 
		HttpUserErrorTextProvider, 
		WorkerThreadTraits>
{

protected:

	typedef CIsapiExtension<ThreadPoolClass, CStatClass, HttpUserErrorTextProvider, 
		WorkerThreadTraits> baseISAPI;
	typedef CWorkerThread<WorkerThreadTraits> WorkerThreadClass;

	// blob cache support
	CBlobCache<WorkerThreadClass, CStdStatClass > m_BlobCache;

	// file cache support
	CFileCache<WorkerThreadClass, CStdStatClass > m_FileCache;

public:

	BOOL GetExtensionVersion(HSE_VERSION_INFO* pVer)
	{
		if (!baseISAPI::GetExtensionVersion(pVer))
		{
			return FALSE;
		}
		
		if (GetCriticalIsapiError() != 0)
		{
			return TRUE;
		}
		

		if (S_OK != m_BlobCache.Initialize(static_cast<IServiceProvider*>(this), &m_WorkerThread))
		{
			ATLTRACE("Blob cache service failed to initialize\n");
			TerminateExtension(0);
			return SetCriticalIsapiError(IDS_ATLSRV_CRITICAL_BLOBCACHEFAILED);
		}

		if (S_OK != m_FileCache.Initialize(&m_WorkerThread))
		{
			ATLTRACE("File cache service failed to initialize\n");
			TerminateExtension(0);
			return SetCriticalIsapiError(IDS_ATLSRV_CRITICAL_FILECACHEFAILED);
		}

		return TRUE;
	}

	BOOL TerminateExtension(DWORD dwFlags)
	{
		m_BlobCache.Uninitialize();
		m_FileCache.Uninitialize();
		BOOL bRet = baseISAPI::TerminateExtension(dwFlags);
		return bRet;
	}
	
	HRESULT STDMETHODCALLTYPE QueryService(REFGUID guidService, 
			REFIID riid, void** ppvObject)
	{
		if (InlineIsEqualGUID(guidService, IID_IFileCache))
			return m_FileCache.QueryInterface(riid, ppvObject);
		if (InlineIsEqualGUID(guidService, IID_IMemoryCache))
			return m_BlobCache.QueryInterface(riid, ppvObject);
		if (InlineIsEqualGUID(guidService, __uuidof(IDataSourceCache)))
		{
			CIsapiWorker *pWorker = GetThreadWorker();
			if (pWorker)
			{
				CDataSourceCache<> *pCache = NULL;
				if (pWorker->GetWorkerData(_DATASOURCE_CACHE, (void **)&pCache))
				{
					*ppvObject = static_cast<IDataSourceCache *>(pCache);
					return S_OK;
				}
			}
		}
		if (InlineIsEqualGUID(guidService, __uuidof(IBrowserCapsSvc)))
		{
			CIsapiWorker *pWorker = GetThreadWorker();
			if (pWorker)
			{
				CBrowserCapsSvc *pBrowserCaps = NULL;
				if (pWorker->GetWorkerData(_BROWSERCAPS, (void **)&pBrowserCaps))
				{
					*ppvObject = static_cast<IBrowserCapsSvc *>(pBrowserCaps);
					return S_OK;
				}
			}
		}
		return baseISAPI::QueryService(guidService, riid, ppvObject);
	}

	virtual void OnThreadTerminate(DWORD /*dwThreadId*/)
	{
	}
}; // class CHelloAtlServerEverythingExtension