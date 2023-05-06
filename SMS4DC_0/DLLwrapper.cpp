#include <stdafx.h>
#include "DLLWrapper.h"


DLLwrapper::DLLwrapper(CString filename)
{
	m_DLLhInstance = NULL ;				// no DLL loaded
	m_filename = _T("") ;					// no filename

	DLLDocumentTemplate = NULL ;		// no functions setup
	
//	if (filename != "")
//		LoadDLL(filename) ;
}

DLLwrapper::~DLLwrapper()
{
	// release any loaded DLL
	if (m_DLLhInstance != NULL)
		FreeLibrary(m_DLLhInstance) ;		// release library
}


bool DLLwrapper::LoadDLL(CString filename , CString addressname)
{
	m_filename = filename ;
	m_DLLhInstance = LoadLibrary(filename) ;

	if (m_DLLhInstance != NULL)
		{
		// get pointers to functions
		// add others here
//		DLLDocumentTemplate = (DLLDOCTEMPLATE)GetProcAddress(m_DLLhInstance, "DLLNewDocTemplate") ;
		DLLDocumentTemplate = (DLLDOCTEMPLATE)GetProcAddress(m_DLLhInstance, addressname) ;
		}
	return (m_DLLhInstance != NULL) ;
}

bool DLLwrapper::FreeDLL()
{
	// release any loaded DLL
	if (m_DLLhInstance != NULL)
		{
		FreeLibrary(m_DLLhInstance) ;		// release library
		m_DLLhInstance = NULL ;
		m_filename = _T("") ;
		// kill any function pointers
		DLLDocumentTemplate = NULL ;
		}
	return true ;
}
