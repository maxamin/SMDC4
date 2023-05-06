// HTML_Report.h: interface for the CHTML_Report class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HTML_REPORT_H__41C2F976_CD14_45B3_A3F2_C2B4D452A46B__INCLUDED_)
#define AFX_HTML_REPORT_H__41C2F976_CD14_45B3_A3F2_C2B4D452A46B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SMS4DC.h"

class CHTML_Report  
{
public:
	void WriteHTMLFile(CString sFullPath);
	int InsertTableHeader(int iItemNo, CString sFirstItem, ...);
	int InsertTableRow(CString sFirstItem,...);

	int InsertTableHeader1(int iItemNo, CString *sFirstItem) ;
	int InsertTableRow1(CString *sFirstItem);


	CHTML_Report(	BOOL FOOTflag,
					CString sTitle = "Default",			// Title of the HTML-File
					CString sAuthor = "N/A",			// Author of the HTML-File
					CString sTableCaption = "Caption",	// The caption of the Table
					CString sMarqueeText = "",			// The Scrolling Text
					CString sLink = "",					// A Link which will be placed in the Footer
					CString sLinkText= "",				// Text for the link above
					CString sBkColor = "#C0C0C0",		// Backgroundcolor of the HTML-File (HTML-Notation)
					CString sTextColor = "#000000",		// Textcolor of the HTML-File (HTML-Notation)
					CString sHeaderBkColor = "#C0C0C0",	// Backgroundcolor of the Header (HTML-Notation)
					CString sTableBkColor = "#ffffff");	// Backgroundcolor of the Table (HTML-Notation)
	virtual ~CHTML_Report();
	int m_num;
	BOOL m_foot;


private:
	CString m_HTML_MarqueeText;
	void InitTABLEFOOT(BOOL FOOTflag);
	void InitTABLEBODY();
	void InitHTMLHEAD();
	void InitMARQUEE();

	BOOL isEmail(CString &sString);
	void GetTableHeadLine();
	void GetTableBodyLine();
	void CreateFileHeader();
	
	CString m_HTML_sTemplateContainer;	// Variable which holds the contents of the Template
	CString m_HTML_sTitle;			
	CString m_HTML_sAuthor;			
	CString m_HTML_sBkColor;		
	CString m_HTML_sTextColor;		
	CString m_HTML_sTableCaption;	
	CString m_HTML_sHeaderBkColor;	
	CString m_HTML_sTableBkColor;	
	CString m_HTML_sLink;			
	CString m_HTML_sLinkText;		
	CString m_HTML_sMarquee;		

	CString m_HTML_sTableHead;
	CString m_Tmp_sTableHeadLine;
	CString m_HTML_sTableBody;
	CString m_Tmp_sTableBodyLine;
	CString m_HTML_sTableFoot;

	int m_HTML_iColumns;
	CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};

	char* CHTML_Report::CString2UTF8(CString& strSrc);
};

#endif // !defined(AFX_HTML_REPORT_H__41C2F976_CD14_45B3_A3F2_C2B4D452A46B__INCLUDED_)
