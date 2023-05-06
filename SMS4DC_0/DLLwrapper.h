// this structure deals with allowing us to call loaded DLL functions

#ifndef DLLWrapper_included
#define DLLWrapper_included 1

#include "stdafx.h"
#include "MyMultiDocTemplate.h"

// function pointer declarations
typedef CMyMultiDocTemplate* (* DLLDOCTEMPLATE)() ;

class DLLwrapper
{
public:
	DLLwrapper(CString filename = "") ;	// constructor
	~DLLwrapper() ;					// destructor

	bool		LoadDLL(CString filename , CString addressname) ;
	bool		FreeDLL() ;
	// member vars
	CString			m_filename;		// filename of DLL
	HINSTANCE		m_DLLhInstance ;// pointer to Instance of DLL

	// function pointers
	// document template support
	DLLDOCTEMPLATE		DLLDocumentTemplate ;

} ;

#endif // DLLWrapper_included

