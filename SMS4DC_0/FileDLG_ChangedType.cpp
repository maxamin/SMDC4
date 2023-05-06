// FileDLG_ChangedType.cpp : implementation file
//

#include "stdafx.h"
#include "sms4dc.h"
#include "FileDLG_ChangedType.h"

#include <afxodlgs.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileDLG_ChangedType

IMPLEMENT_DYNAMIC(CFileDLG_ChangedType, CFileDialog)

CFileDLG_ChangedType::CFileDLG_ChangedType(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
	m_dwFlags  = dwFlags;
	m_ShowFlag = FALSE;

	m_ShowCheckBox = TRUE;		//98/05/06

	SetTemplate(0, _T("IDD_fileDIALOG_Check"));
}


BEGIN_MESSAGE_MAP(CFileDLG_ChangedType, CFileDialog)
	//{{AFX_MSG_MAP(CFileDLG_ChangedType)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_CHECK_ShowGoogle, OnCHECKShowGoogle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CFileDLG_ChangedType::OnTypeChange()
{
	// get current filename
	CWnd *fileNameBox;
	if		(m_ofn.lStructSize == 76)	fileNameBox = GetParent()->GetDlgItem(edt1);
	else if	(m_ofn.lStructSize == 88)	fileNameBox = GetParent()->GetDlgItem(cmb13);
																	ASSERT_VALID(fileNameBox);
	CString fileName;	fileNameBox->GetWindowText(fileName);

	// get current extension
	CWnd *typeNameBox = GetParent()->GetDlgItem(cmb1);				ASSERT_VALID(typeNameBox);
	CString typeName; typeNameBox->GetWindowText(typeName);
	char *tempBuffer = newdup(typeName);
	char *ptr[2];
	int n = Split( tempBuffer, ptr, 2, '*' );						ASSERT(n == 2);
		n = Split( ptr[1], ptr, 2, ')' );							ASSERT(n == 1);
	typeName = ptr[0];

	if (fileName.IsEmpty())		fileName = _T("*") + typeName;
	else
	{
		int i = fileName.Find('.');
		if (i == -1)	fileName = fileName + typeName;
		else			fileName = fileName.Left(i) + typeName;
	}
	fileNameBox->SetWindowText(fileName);
	delete tempBuffer;
}

char *CFileDLG_ChangedType::newdup(const char *str)
{
	char *ptr = new char[strlen(str) + 1];
	strcpy(ptr, str);
	return ptr;
}

int CFileDLG_ChangedType::Split(char *str,char *word[],int max,char c)
{
	int n = 0;
	if (!str) return n;
	for (;;)
	{
		char quote='\0';
		while (*str==c) str++;
		if (!*str || n==max) return n;
		if (!quote && (*str=='"' || *str=='\''))
		{
			quote = *str; str++;
		}
		word[n++] = str++;
		while (*str && (!quote && *str!=c || quote && *str!=quote)) str++;
		if (quote && *str==quote)
		{
			quote='\0'; *str='\0'; str++;
		}
		if (!*str) return n;
		if (n<max) *str++ ='\0';
	}
}

BOOL CFileDLG_ChangedType::OnInitDialog() 
{
	CFileDialog::OnInitDialog();
	
	// save left margin for combo boxes
	CWnd *pWndFileNameCombo;
	if (m_ofn.lStructSize==88)	pWndFileNameCombo = GetParent()->GetDlgItem(cmb13);
	else						pWndFileNameCombo = GetParent()->GetDlgItem(edt1);

	CRect rectFileNameCombo;
	pWndFileNameCombo->GetWindowRect(&rectFileNameCombo);
	GetParent()->ScreenToClient(&rectFileNameCombo);
	m_nComboLeftMargin = rectFileNameCombo.left;
	

//98/05/06			???????????
CString strOriginal;
GetParent()->GetDlgItemText(IDOK, strOriginal);
CString s = ((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(strOriginal);
if (!s.IsEmpty() && strOriginal != s)	SetControlText (IDOK, s);


	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);

	((CSMS4DCApp *)AfxGetApp())->TranslateDialog((CDialog*)GetParent());		//98/05/06
	GetDlgItem(IDC_CHECK_ShowGoogle)->ShowWindow(m_ShowCheckBox);				//98/05/06

	return TRUE;
}

void CFileDLG_ChangedType::OnSize(UINT nType, int cx, int cy) 
{
	CFileDialog::OnSize(nType, cx, cy);
	// original dialog box
	CWnd *pWndParent = GetParent();
	ASSERT(pWndParent);
	if (!pWndParent)	return;

	// File name combobox
	CWnd *pWndFileNameCombo;
	if (m_ofn.lStructSize==88)	pWndFileNameCombo = GetParent()->GetDlgItem(cmb13);
	else						pWndFileNameCombo = GetParent()->GetDlgItem(edt1);

	CRect rectFileNameCombo;
	pWndFileNameCombo->GetWindowRect(&rectFileNameCombo);
	GetParent()->ScreenToClient(&rectFileNameCombo);
/*
	rectFileNameCombo.left = m_nComboLeftMargin;
//	pWndFileNameCombo->MoveWindow(&rectFileNameCombo);
*/
	int mshift = 30;										//98/05/06
	int W = rectFileNameCombo.right-rectFileNameCombo.left;	//98/05/06

	rectFileNameCombo.left  = m_nComboLeftMargin + mshift;	//98/05/06
	rectFileNameCombo.right = rectFileNameCombo.left + W;	//98/05/06
	pWndFileNameCombo->MoveWindow(&rectFileNameCombo);		//98/05/06

	// File name static
	CWnd *pWndFileNameStatic = GetParent()->GetDlgItem(stc3);
	ASSERT(pWndFileNameStatic);
	CRect rectFileNameStatic;
	pWndFileNameStatic->GetWindowRect(&rectFileNameStatic);
	GetParent()->ScreenToClient(&rectFileNameStatic);
/*
	rectFileNameStatic.right = m_nComboLeftMargin - 2;
//	pWndFileNameStatic->MoveWindow(&rectFileNameStatic);
*/
	rectFileNameStatic.right = m_nComboLeftMargin + mshift;		//98/05/06
	pWndFileNameStatic->MoveWindow(&rectFileNameStatic);		//98/05/06

	// Files of type combobox
	CWnd *pWndFilesOfTypeCombo = GetParent()->GetDlgItem(cmb1);
	ASSERT(pWndFilesOfTypeCombo);
	CRect rectFilesOfTypeCombo;
	pWndFilesOfTypeCombo->GetWindowRect(&rectFilesOfTypeCombo);
	GetParent()->ScreenToClient(&rectFilesOfTypeCombo);
/*
	rectFilesOfTypeCombo.left = m_nComboLeftMargin;
//	pWndFilesOfTypeCombo->MoveWindow(&rectFilesOfTypeCombo);
*/
	rectFilesOfTypeCombo.left  = m_nComboLeftMargin + mshift;	//98/05/06
	rectFilesOfTypeCombo.right = rectFilesOfTypeCombo.left + W;	//98/05/06
	pWndFilesOfTypeCombo->MoveWindow(&rectFilesOfTypeCombo);	//98/05/06

	// Files of type static
	CWnd *pWndFilesOfTypeStatic = GetParent()->GetDlgItem(stc2);
	ASSERT(pWndFilesOfTypeStatic);
	CRect rectFilesOfTypeStatic;
	pWndFilesOfTypeStatic->GetWindowRect(&rectFilesOfTypeStatic);
	GetParent()->ScreenToClient(&rectFilesOfTypeStatic);
/*
	rectFilesOfTypeStatic.right = m_nComboLeftMargin - 2;
//	pWndFilesOfTypeStatic->MoveWindow(&rectFilesOfTypeStatic);
*/
	rectFilesOfTypeStatic.right = m_nComboLeftMargin + mshift;	//98/05/06
	pWndFilesOfTypeStatic->MoveWindow(&rectFilesOfTypeStatic);	//98/05/06


	int nDeltaYCombo = rectFilesOfTypeCombo.top - rectFileNameCombo.bottom;
	int nDeltaYStatic = rectFilesOfTypeStatic.top - rectFileNameStatic.bottom;

	// Recent folders combobox
	CWnd *pWndRecentFoldersCombo = GetDlgItem(IDC_CHECK_ShowGoogle);
	ASSERT(pWndRecentFoldersCombo);
	CRect rectRecentFoldersCombo;
	pWndRecentFoldersCombo->GetWindowRect(&rectRecentFoldersCombo);
	GetParent()->ScreenToClient(&rectRecentFoldersCombo);
	rectRecentFoldersCombo.left = rectFilesOfTypeCombo.left;
	rectRecentFoldersCombo.right = rectFilesOfTypeCombo.right;
	int h = rectRecentFoldersCombo.Height();
	rectRecentFoldersCombo.top = rectFilesOfTypeCombo.bottom + nDeltaYCombo;
	rectRecentFoldersCombo.bottom = rectRecentFoldersCombo.top + h;
	pWndRecentFoldersCombo->MoveWindow(&rectRecentFoldersCombo);

	// Read only checkbox
	if ((m_dwFlags & OFN_HIDEREADONLY) == 0)
	{
		CWnd *pWndReadOnlyCheckbox = GetParent()->GetDlgItem(chx1);
		ASSERT(pWndReadOnlyCheckbox);
		CRect rectReadOnlyCheckbox;
		pWndReadOnlyCheckbox->GetWindowRect(&rectReadOnlyCheckbox);
		GetParent()->ScreenToClient(&rectReadOnlyCheckbox);
		rectReadOnlyCheckbox.left = rectFilesOfTypeCombo.left;
		rectReadOnlyCheckbox.right = rectFilesOfTypeCombo.right;
		int h = rectReadOnlyCheckbox.Height();
		rectReadOnlyCheckbox.top = rectRecentFoldersCombo.bottom + nDeltaYCombo;
		rectReadOnlyCheckbox.bottom = rectReadOnlyCheckbox.top + h;
		pWndReadOnlyCheckbox->MoveWindow(&rectReadOnlyCheckbox);
	}	
}

void CFileDLG_ChangedType::OnCHECKShowGoogle() 
{
	UpdateData();
	CButton *pWndB = (CButton *)GetDlgItem(IDC_CHECK_ShowGoogle);
	m_ShowFlag = pWndB->GetCheck();
	UpdateData(false);
}
