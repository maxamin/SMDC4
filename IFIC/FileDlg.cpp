// FileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IFICImport.h"
#include "FileDlg.h"
#include "direct.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileDlg dialog


CFileDlg::CFileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CFileDlg::CFileDlg(BOOL bOpenFileDialog, LPCTSTR lpszDefExt = NULL, 
				   LPCTSTR lpszFileName = NULL, 
				   DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
				   LPCTSTR lpszFilter = NULL, CWnd* pParentWnd = NULL )
	: CDialog(CFileDlg::IDD, NULL)
{
	if(bOpenFileDialog)
		m_DlgType=true;
	else
		m_DlgType=false;
	m_Filter=lpszFilter;
	char buf[500];
	m_Path=_tgetcwd(buf,300);
	m_Path+="\\";
}


void CFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileDlg)
	DDX_Control(pDX, IDC_LIST_Directoties, m_DirListCtrl);
	DDX_Control(pDX, IDC_EDIT_Path, m_FileName);
	DDX_Control(pDX, IDC_COMBO_Drive, m_Drive);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileDlg, CDialog)
	//{{AFX_MSG_MAP(CFileDlg)
	ON_CBN_SELCHANGE(IDC_COMBO_Drive, OnSelchangeCOMBODrive)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_Directoties, OnDblclkLISTDirectoties)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileDlg message handlers


BOOL CFileDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
//	Dialog title	

	((CButton *)GetDlgItem(IDOK))->EnableWindow(false);
	if(m_DlgType)
	{
		((CButton *)GetDlgItem(IDOK))->SetWindowText("Open");
		SetWindowText("Open File");
	}
	else
	{
		((CButton *)GetDlgItem(IDOK))->SetWindowText("Save");
		SetWindowText("Save File");
	}//end else
//	Drive list
	char buf[1001];
	GetLogicalDriveStrings(1000,buf);
   for (char* s=buf; *s; s+=_tcslen(s)+1) {
      LPCTSTR sDrivePath = s;
		m_Drive.AddString(s);
   }

//  Directory and file list
	m_Path="c:\\";
	m_Drive.SetCurSel(1);
	GetDirectories(m_Path);

	m_FileName.SetWindowText(m_Path);
	
	CRect           rect;
	m_ListIcons.Create(16,16,ILC_COLOR8,1,10);
//	m_ListIcons.Add(AfxGetApp()->LoadIcon(IDI_FOLDER));
	m_DirListCtrl.SetImageList(&m_ListIcons,LVSIL_SMALL);
	m_DirListCtrl.GetWindowRect(&rect);
	m_DirListCtrl.InsertColumn(0, "", LVCFMT_LEFT,rect.Width()-16, 0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CFileDlg::GetDirectories(CString Path) 
{
	   int i=0;
   CFileFind finder;
   BOOL bWorking ;
   bWorking = finder.FindFile(Path+"\\*.*");
   m_DirListCtrl.DeleteAllItems();

   while (bWorking)
   {
      bWorking = finder.FindNextFile();
      CString str = finder.GetFileName();
      if(!finder.IsHidden() && !finder.IsSystem())
	  {
		  if (finder.IsDirectory())
		  {
			m_DirListCtrl.InsertItem(i++,str);

		  }
	  }//end if
   }

   finder.Close();
   return true;
}

void CFileDlg::OnSelchangeCOMBODrive() 
{
	CString SelStr;
	m_Drive.GetLBText(m_Drive.GetCurSel(),SelStr);
	m_Path=SelStr;
	GetDirectories(m_Path);
	m_FileName.SetWindowText(m_Path);
	((CButton *)GetDlgItem(IDOK))->EnableWindow(false);
	m_FName="";

}

void CFileDlg::DelLastDir()
{
	for(int i=m_Path.GetLength()-2;i>0;i--)
	{
		if(m_Path.Mid(i,1)=="\\")
			break;
		else
			m_Path.Delete(m_Path.GetLength()-1);
	}//end for
	m_Path.Delete(m_Path.GetLength()-1);
}


void CFileDlg::OnOK() 
{
	m_FileName.GetWindowText(m_Path);
	CDialog::OnOK();
}

void CFileDlg::OnDblclkLISTDirectoties(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CString SelStr;
	POSITION pos = m_DirListCtrl.GetFirstSelectedItemPosition();
	
	if(pos)
	{
		m_FName="";
		SelStr=m_DirListCtrl.GetItemText(m_DirListCtrl.GetNextSelectedItem(pos),0);
		if(!SelStr.Compare("."))
			return;
		if(!SelStr.Compare(".."))
			DelLastDir();
		else
			m_Path+=SelStr+"\\";
		GetDirectories(m_Path);
		m_FileName.SetWindowText(m_Path);
		((CButton *)GetDlgItem(IDOK))->EnableWindow(false);
	}//end if	
	
	*pResult = 0;
}
