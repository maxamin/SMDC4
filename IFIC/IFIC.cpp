// IFIC.cpp : Defines the initialization routines for the DLL.
//
#include "stdafx.h"
#include <afxdllx.h>
#include "IFICImport.h"
#include "SRSImport.h"
#include "accesslevels.h"
#include "agreement.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static AFX_EXTENSION_MODULE IFICDLLEN = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("IFIC.DLL Initializing!\n");
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(IFICDLLEN, hInstance))
			return 0;

		// Insert this DLL into the resource chain
		// NOTE: If this Extension DLL is being implicitly linked to by
		//  an MFC Regular DLL (such as an ActiveX Control)
		//  instead of an MFC application, then you will want to
		//  remove this line from DllMain and put it in a separate
		//  function exported from this Extension DLL.  The Regular DLL
		//  that uses this Extension DLL should then explicitly call that
		//  function to initialize this Extension DLL.  Otherwise,
		//  the CDynLinkLibrary object will not be attached to the
		//  Regular DLL's resource chain, and serious problems will
		//  result.

		new CDynLinkLibrary(IFICDLLEN);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("IFIC.DLL Terminating!\n");
		// Terminate the library before destructors are called
		AfxTermExtensionModule(IFICDLLEN);
	}
	return 1;   // ok
}

extern "C" int WINAPI IFICImport(HWND hWndParent,CString DBSTR, CString Lang)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// All DLL entry points should have a top-level TRY/CATCH block.
	// Otherwise, it would be possible to throw an uncaught exception from
	//  an the DLL.  This would most likely cause a crash.

	TRY
	{
		CIFICImport dlg(CWnd::FromHandle(hWndParent));
		dlg.m_CDBSTR=DBSTR;
		dlg.m_Lang=Lang;
		if (dlg.DoModal() != IDOK)
			return FALSE;

		// update the data
	}
	CATCH_ALL(e)
	{
		// a failure caused an exception.
		return FALSE;
	}
	END_CATCH_ALL

	return TRUE;
}

extern "C" int WINAPI SRSImport(HWND hWndParent,CString DBSTR, CString Lang)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// All DLL entry points should have a top-level TRY/CATCH block.
	// Otherwise, it would be possible to throw an uncaught exception from
	//  an the DLL.  This would most likely cause a crash.

	TRY
	{
		AfxGetModuleState()->m_dwVersion = 0x0601; 
		CSRSImport dlg(CWnd::FromHandle(hWndParent));
		dlg.m_CDBSTR=DBSTR;
		dlg.m_Lang=Lang;
		if (dlg.DoModal() != IDOK)
			return FALSE;

		// update the data
	}
	CATCH_ALL(e)
	{
		// a failure caused an exception.
		return FALSE;
	}
	END_CATCH_ALL

	return TRUE;
}

extern "C" int WINAPI AccessLevels(HWND hWndParent,CString DBSTR, CString Lang)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// All DLL entry points should have a top-level TRY/CATCH block.
	// Otherwise, it would be possible to throw an uncaught exception from
	//  an the DLL.  This would most likely cause a crash.

	TRY
	{
		CAccessLevels dlg(CWnd::FromHandle(hWndParent));
		dlg.m_CDBSTR=DBSTR;
		dlg.m_Lang=Lang;
		if (dlg.DoModal() != IDOK)
			return FALSE;

		// update the data
	}
	CATCH_ALL(e)
	{
		// a failure caused an exception.
		return FALSE;
	}
	END_CATCH_ALL

	return TRUE;
}

extern "C" int WINAPI Agreements(HWND hWndParent,CString CDBSTR,CString SDBSTR, CString Lang)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// All DLL entry points should have a top-level TRY/CATCH block.
	// Otherwise, it would be possible to throw an uncaught exception from
	//  an the DLL.  This would most likely cause a crash.

	TRY
	{
		CAgreement dlg(CWnd::FromHandle(hWndParent));
		dlg.m_CDBSTR=CDBSTR;
		dlg.m_SDBSTR=SDBSTR;
		dlg.m_Lang=Lang;
		if (dlg.DoModal() != IDOK)
			return FALSE;

		// update the data
	}
	CATCH_ALL(e)
	{
		// a failure caused an exception.
		return FALSE;
	}
	END_CATCH_ALL

	return TRUE;
}
