// DataBaseLDLG.h: interface for the CDataBaseLDLG class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATABASELDLG_H__C419AC58_E28A_49B6_834C_665DAD6300DA__INCLUDED_)
#define AFX_DATABASELDLG_H__C419AC58_E28A_49B6_834C_665DAD6300DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDataBaseLDLG  
{
public:
	CDataBaseLDLG();
	virtual ~CDataBaseLDLG();

	BOOL	m_ReportFlag , m_Heff1;
	CString m_Title;
	int DoModal();
private:	
	CString m_DB, m_Tbl, m_Lang;
	CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

#endif // !defined(AFX_DATABASELDLG_H__C419AC58_E28A_49B6_834C_665DAD6300DA__INCLUDED_)
