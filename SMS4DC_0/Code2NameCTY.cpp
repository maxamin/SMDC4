// Code2NameCTY.cpp: implementation of the CCode2NameCTY class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SMS4DC.h"
#include "Code2NameCTY.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


extern "C" char * WINAPI AllCodes_lang(CString CTYCOD[], int *NOCTY);	//CNT_lang.lib
extern "C" char * WINAPI Code2NameCTY_lang(CString co, CString mLang);	//CNT_lang.lib
CCode2NameCTY::CCode2NameCTY()
{
	////////////////////////////////   IDWM new  ////////////////
	AllCodes_lang(countryCODEidwm, &m_num);
	for (int i=0;i<m_num;i++)
		countryNAMEidwm[i] = Code2NameCTY_lang(countryCODEidwm[i], ((CSMS4DCApp *)AfxGetApp())->m_Lang);
}

CCode2NameCTY::~CCode2NameCTY()
{

}

CString CCode2NameCTY::Code2Name_idwm(CString co)
{
	for (int i=0;i<m_num;i++)
	{
		if (co == countryCODEidwm[ i ])
			break;
	}
	if (i==m_num)
		return "";
	else
		return countryNAMEidwm[ i ];
}
