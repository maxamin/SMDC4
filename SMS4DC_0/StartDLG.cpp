// StartDLG.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "StartDLG.h"

#include <afxdb.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStartDLG dialog


CStartDLG::CStartDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CStartDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStartDLG)
	m_UserName     = _T("sms4dc");
	m_UserPassword = _T("sms4dc");
	//}}AFX_DATA_INIT
}


void CStartDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStartDLG)
	DDX_Control(pDX, IDC_COMBO_Lang, m_COMBO_Lang);
	DDX_Text(pDX, IDC_EDIT_UserName, m_UserName);
	DDX_Text(pDX, IDC_EDIT_UserPassword, m_UserPassword);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStartDLG, CDialog)
	//{{AFX_MSG_MAP(CStartDLG)
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_COMBO_Lang, OnSelchangeCOMBOLang)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStartDLG message handlers

void CStartDLG::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	dc.SetBkMode(TRANSPARENT);

	dc.TextOut(10,10,_Z("INTERNATIONAL TELECOMMUNICATION UNION"));
	dc.TextOut(10,30,_Z("Bureau of Telecommunication Development"));
	dc.TextOut(10,50,_Z("Geneva, Switzerland"));

//	dc.TextOut(270,330,"Version 1.0");	dc.TextOut(285,350,"2005");
//	dc.TextOut(240,340,"Version 1.0   2006");
//	dc.TextOut(240,340,"Version 2.0   2007");
//	dc.TextOut(240,340,"Version 2.1   2008");
//	dc.TextOut(240,340,"Version 2.5   2008");
//	dc.TextOut(240,340,_Z("Version 3.0   2009"));
//	dc.TextOut(240,340,_Z("Version 4.0   2010"));
//	dc.TextOut(240,340,_Z("Version 4.1   2013"));
//	dc.TextOut(240,340,_Z("Version 4.2   2014"));
//	dc.TextOut(240,340,_Z("Version 5.0   2015"));
//	dc.TextOut(240,340,_Z("Version")+(" 5.1   2016"));	//950909
//	dc.TextOut(240,340,_Z("Version")+(" 5.2   2018"));	//970710
//	dc.TextOut(240,340,_Z("Version")+(" 5.2   2019"));	//970722
//	dc.TextOut(240,340,_Z("Version")+(" 5.2   2020"));	//990431
	dc.TextOut(240,340,_Z("Version")+(" 5.2   2021"));	//990927

	CFont m_LogoFont;
	CString sLogoString;
	RECT rect,m_rDataBox;
	GetClientRect(&rect);
	CopyRect(&m_rDataBox,&rect);

 	m_LogoFont.CreateFont(130, 0, 0, 0, FW_BOLD, 1, FALSE, FALSE,
	  ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
	  FIXED_PITCH | FF_ROMAN, "Times New Roman");

	sLogoString = "SMS4DC";

	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);
	CFont* oldFont = dc.SelectObject(&m_LogoFont);
	CSize sz = dc.GetTextExtent(sLogoString, sLogoString.GetLength());

	m_rDataBox.left = m_rDataBox.right  - sz.cx - tm.tmAveCharWidth/2-145;
	m_rDataBox.top  = m_rDataBox.bottom - sz.cy - tm.tmHeight/5-180;
	dc.SetBkMode(TRANSPARENT);
	
	COLORREF oldColor = dc.SetTextColor(RGB(0,0,0));
	dc.DrawText(sLogoString, sLogoString.GetLength(), &m_rDataBox, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
	
	m_rDataBox.left -= 6*tm.tmAveCharWidth/5;
//	dc.SetTextColor(RGB(255,255,0));
	dc.SetTextColor(RGB(255,255,255));
	dc.DrawText(sLogoString, sLogoString.GetLength(), &m_rDataBox, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
	
	m_rDataBox.left += 3*tm.tmAveCharWidth/5;
	dc.SetTextColor(RGB(0,0,255));
//	dc.SetTextColor(RGB(45,68,144));		//97/10/23		
	dc.DrawText(sLogoString, sLogoString.GetLength(), &m_rDataBox, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
	
	// restore the original properties and release resources...
	dc.SelectObject(oldFont);
	dc.SetTextColor(oldColor);

	m_LogoFont.DeleteObject();
	SetWindowText(_Z("SMS4DC Login"));	
}


void CStartDLG::OnOK() 
{
	UpdateData();
	CDatabase DB;
	CString  m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	DB.Open(_T(m_DB),false,false,_T("ODBC;"),false);
	CRecordset m_rs;
	CString m_Tbl =_T("select * from Users where UserName=\'") + m_UserName + _T("\'");
	m_rs.m_pDatabase=&DB;
	m_rs.Open( CRecordset::snapshot, m_Tbl);

	if (m_rs.GetRecordCount()==1)
	{
		CString str;
		m_rs.GetFieldValue(_T("UserPassword"),str);
		if(!str.CompareNoCase(m_UserPassword))
		{
			m_rs.GetFieldValue(_T("Enabled"),str);
			if(atoi(str)==1)
			{
				m_rs.GetFieldValue(_T("Level"),str);
				((CSMS4DCApp *)AfxGetApp())->m_UserLevel = atoi(str);
				CDialog::OnOK();
			}
			else
				MessageBox(_Z("Account is Disabled."),_Z("ERROR!!!"),MB_ICONERROR | MB_OK);
		}
		else
			MessageBox(_Z("Password is not Correct"),_Z("ERROR!!!"),MB_ICONERROR | MB_OK);
	}
	else
		MessageBox(_Z("User Name is not Correct"),_Z("ERROR!!!"),MB_ICONERROR | MB_OK);

	m_rs.Close();
	DB.Close();

	int L = m_COMBO_Lang.GetCurSel();
	if		(L==0)		((CSMS4DCApp *)AfxGetApp())->m_Lang = _T("En");
	else if (L==1)		((CSMS4DCApp *)AfxGetApp())->m_Lang = _T("Fr");
	else if (L==2)		((CSMS4DCApp *)AfxGetApp())->m_Lang = _T("Es");
	else if (L==3)		((CSMS4DCApp *)AfxGetApp())->m_Lang = _T("Ch");
	else if (L==4)		((CSMS4DCApp *)AfxGetApp())->m_Lang = _T("Ar");
	else if (L==5)		((CSMS4DCApp *)AfxGetApp())->m_Lang = _T("Ru");
	else				((CSMS4DCApp *)AfxGetApp())->m_Lang = _T("En");

	UpdateData(false);
}

BOOL CStartDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();

/*		//97/10/30
CBitmap bmp;	bmp.LoadBitmap(IDB_ITUBDT);
CDC dc;			dc.CreateCompatibleDC(NULL);
dc.SelectObject(&bmp);
m_c1 = dc.GetPixel(3,4);
//m_c1 = RGB(255,0,0);
dc.DeleteDC();	bmp.DeleteObject();
m_brush.CreateSolidBrush(m_c1); //971023
*/

	m_COMBO_Lang.AddString(_T("English"));
	m_COMBO_Lang.AddString(_T("Français"));    //	m_COMBO_Lang.AddString(_T("French"));
	m_COMBO_Lang.AddString(_T("Español"));		//940312
//	m_COMBO_Lang.AddString(_T("Ch"));			//940312
//	m_COMBO_Lang.AddString(_T("Ar"));			//940312
//	m_COMBO_Lang.AddString(_T("Ru"));			//940312
	m_COMBO_Lang.SetTopIndex(1);
//	m_COMBO_Lang.SetCurSel(0);	

	m_LanguageFile = ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("\\Texts\\Language.txt");
	LanguageQ();
	if		(((CSMS4DCApp *)AfxGetApp())->m_Lang == _T("En"))			m_COMBO_Lang.SetCurSel(0);	
	else if (((CSMS4DCApp *)AfxGetApp())->m_Lang == _T("Fr"))			m_COMBO_Lang.SetCurSel(1);
	else if (((CSMS4DCApp *)AfxGetApp())->m_Lang == _T("Es"))			m_COMBO_Lang.SetCurSel(2); //940312
//	else if (((CSMS4DCApp *)AfxGetApp())->m_Lang == _T("Ch"))			m_COMBO_Lang.SetCurSel(3); //940312
//	else if (((CSMS4DCApp *)AfxGetApp())->m_Lang == _T("Ar"))			m_COMBO_Lang.SetCurSel(4); //940312
//	else if (((CSMS4DCApp *)AfxGetApp())->m_Lang == _T("Ru"))			m_COMBO_Lang.SetCurSel(5); //940312
	else																
	{
		CreateLanguageFile("En");
		m_COMBO_Lang.SetCurSel(0);
	}
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);

	COLORREF c1 = GetSysColor(COLOR_BTNFACE);
	HBITMAP hBmp2 = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_ITUBDT));
	HBITMAP hBmp  = ReplaceColor(hBmp2, c1);
	hBmp2 = NULL;	DeleteObject(hBmp2);
	((CStatic*)GetDlgItem(IDC_STATICimg))->SetBitmap(hBmp);
	hBmp = NULL;	DeleteObject(hBmp);

	return TRUE;  
}

void CStartDLG::OnSelchangeCOMBOLang() 
{
	int L = m_COMBO_Lang.GetCurSel();
	if		(L==0)		((CSMS4DCApp *)AfxGetApp())->m_Lang = _T("En");
	else if (L==1)		((CSMS4DCApp *)AfxGetApp())->m_Lang = _T("Fr");
	else if (L==2)		((CSMS4DCApp *)AfxGetApp())->m_Lang = _T("Es");
	else if (L==3)		((CSMS4DCApp *)AfxGetApp())->m_Lang = _T("Ch");
	else if (L==4)		((CSMS4DCApp *)AfxGetApp())->m_Lang = _T("Ar");
	else if (L==5)		((CSMS4DCApp *)AfxGetApp())->m_Lang = _T("Ru");
	else				((CSMS4DCApp *)AfxGetApp())->m_Lang = _T("En");

	CreateLanguageFile(((CSMS4DCApp *)AfxGetApp())->m_Lang);

	if(L==0)
	{
		SetDlgItemText(IDC_STATICb1,_T("Login : "));
		SetDlgItemText(IDC_STATICb2,_T("User Name :"));
		SetDlgItemText(IDC_STATICb3,_T("Password :"));
		SetDlgItemText(IDC_STATICb4,_T("Language :"));
		SetDlgItemText(IDCANCEL,_T("Cancel"));
		SetDlgItemText(IDOK,_T("OK"));
	}
	else if (L==1)
	{
		SetDlgItemText(IDC_STATICb1,_T("Login : "));
		SetDlgItemText(IDC_STATICb2,_T("Nom de l'utilisateur :"));
		SetDlgItemText(IDC_STATICb3,_T("Mot de passe :"));
		SetDlgItemText(IDC_STATICb4,_T("Langue :"));
		SetDlgItemText(IDCANCEL,_T("Annuler"));
		SetDlgItemText(IDOK,_T("OK"));
	}
	else if (L==2)
	{
		SetDlgItemText(IDC_STATICb1,_T("Registro : "));
		SetDlgItemText(IDC_STATICb2,_T("Nombre del usuario :"));
		SetDlgItemText(IDC_STATICb3,_T("Contraseña :"));
		SetDlgItemText(IDC_STATICb4,_T("Idioma :"));
		SetDlgItemText(IDCANCEL,_T("Anular"));
		SetDlgItemText(IDOK,_T("OK"));
	}

	Invalidate();
}


void CStartDLG::LanguageQ()
{
	CFileFind x1;
	BOOL cx1 = x1.FindFile(m_LanguageFile);
	if(!cx1)	CreateLanguageFile("En");
	else		ReadLanguageFile();
	x1.Close();
}
void CStartDLG::CreateLanguageFile(CString mLang)
{
	FILE *fid = fopen(m_LanguageFile,"wt");
	fprintf( fid, "%s", mLang);
	fclose(fid);
	((CSMS4DCApp *)AfxGetApp())->m_Lang = mLang;
}
void CStartDLG::ReadLanguageFile()
{
	char buftemp[10];
	FILE *fid = fopen(m_LanguageFile,"rt");
	fscanf( fid, "%s", buftemp);
	fclose(fid);
	((CSMS4DCApp *)AfxGetApp())->m_Lang = buftemp;
}

/*//971030

//971023
HBRUSH CStartDLG::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if(pWnd->GetDlgCtrlID()==IDC_STATICb1 || 
	   pWnd->GetDlgCtrlID()==IDC_STATICb2 ||
	   pWnd->GetDlgCtrlID()==IDC_STATICb3 ||
	   pWnd->GetDlgCtrlID()==IDC_STATICb4  )
			pDC->SetBkMode(TRANSPARENT);

	if(pWnd->GetDlgCtrlID()==IDC_EDIT_UserName     || 
	   pWnd->GetDlgCtrlID()==IDC_EDIT_UserPassword ||
	   pWnd->GetDlgCtrlID()==IDC_COMBO_Lang		   ||
	   nCtlColor==CTLCOLOR_LISTBOX)	
	{
		pDC->SetBkColor(RGB(255,255,255));	
		return hbr;
	}

	// TODO: Return a different brush if the default is not desired
	return hbr;
//	return m_brush;
}

//971023
void CStartDLG::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{

	if(nIDCtl==IDOK || nIDCtl==IDCANCEL)
	{
		CDC dc;			dc.Attach(lpDrawItemStruct->hDC);
		RECT rect;		rect = lpDrawItemStruct->rcItem;
		
		dc.Draw3dRect(&rect,RGB(255,255,255),RGB(0,0,0));
		dc.FillSolidRect(&rect, m_c1);
		UINT state=lpDrawItemStruct->itemState;

		if((state & ODS_SELECTED))	dc.DrawEdge(&rect,EDGE_SUNKEN,BF_RECT);
		else						dc.DrawEdge(&rect,EDGE_RAISED,BF_RECT);

		dc.SetBkColor(m_c1);

		TCHAR buffer[MAX_PATH];
		ZeroMemory(buffer,MAX_PATH );
		::GetWindowText(lpDrawItemStruct->hwndItem,buffer,MAX_PATH);
		dc.DrawText(buffer,&rect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		
		dc.Detach();
	}				

	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}
*/

/////////////////////////	97/10/30
#define COLORREF2RGB(Color) (Color & 0xff00) | ((Color >> 16) & 0xff) | ((Color << 16) & 0xff0000)

HBITMAP CStartDLG::ReplaceColor (HBITMAP hBmp, COLORREF cNewColor, HDC hBmpDC)
{
	HBITMAP RetBmp=NULL;
	if (hBmp)
	{	
		HDC BufferDC=CreateCompatibleDC(NULL);	// DC for Source Bitmap
		if (BufferDC)
		{
			HBITMAP hTmpBitmap = (HBITMAP) NULL;
			if (hBmpDC)
				if (hBmp == (HBITMAP)GetCurrentObject(hBmpDC, OBJ_BITMAP))
				{
					hTmpBitmap = CreateBitmap(1, 1, 1, 1, NULL);
					SelectObject(hBmpDC, hTmpBitmap);
				}
			HGDIOBJ PreviousBufferObject=SelectObject(BufferDC,hBmp);
			// here BufferDC contains the bitmap
			
			HDC DirectDC=CreateCompatibleDC(NULL);	// DC for working		
			if (DirectDC)
			{
				// Get bitmap size
				BITMAP bm;
				GetObject(hBmp, sizeof(bm), &bm);
				
				// create a BITMAPINFO with minimal initilisation for the CreateDIBSection
				BITMAPINFO RGB32BitsBITMAPINFO; 
				ZeroMemory(&RGB32BitsBITMAPINFO,sizeof(BITMAPINFO));
				RGB32BitsBITMAPINFO.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
				RGB32BitsBITMAPINFO.bmiHeader.biWidth=bm.bmWidth;
				RGB32BitsBITMAPINFO.bmiHeader.biHeight=bm.bmHeight;
				RGB32BitsBITMAPINFO.bmiHeader.biPlanes=1;
				RGB32BitsBITMAPINFO.bmiHeader.biBitCount=32;
				UINT * ptPixels;	// pointer used for direct Bitmap pixels access

				HBITMAP DirectBitmap = CreateDIBSection(DirectDC, (BITMAPINFO *)&RGB32BitsBITMAPINFO, DIB_RGB_COLORS,(void **)&ptPixels, NULL, 0);
				if (DirectBitmap)
				{
					// here DirectBitmap!=NULL so ptPixels!=NULL no need to test
					HGDIOBJ PreviousObject=SelectObject(DirectDC, DirectBitmap);
					BitBlt(DirectDC,0,0,bm.bmWidth,bm.bmHeight,BufferDC,0,0,SRCCOPY);					
					// here the DirectDC contains the bitmap

					// Convert COLORREF to RGB
		//			cOldColor=COLORREF2RGB(cOldColor);
					cNewColor=COLORREF2RGB(cNewColor);

					// After all the inits we can do the job : Replace Color

COLORREF cOldColor = ptPixels[0];
					for (int i=((bm.bmWidth*bm.bmHeight)-1);i>=0;i--)
					{
						if (ptPixels[i]==cOldColor) ptPixels[i] = cNewColor;
					}
					// little clean up
					// Don't delete the result of SelectObject because it's our modified bitmap (DirectBitmap)
					SelectObject(DirectDC,PreviousObject);
					
					// finish
					RetBmp=DirectBitmap;
				}
				// clean up
				DeleteDC(DirectDC);
			}			
			if (hTmpBitmap)
			{
				SelectObject(hBmpDC, hBmp);
				DeleteObject(hTmpBitmap);
			}
			SelectObject(BufferDC,PreviousBufferObject);
			// BufferDC is now useless
			DeleteDC(BufferDC);
		}
	}
	return RetBmp;
}


/*
// Test Saman  1400/04/20
#include "TxRxFilterDLG.h"
void CStartDLG::OnButton1() 
{
	int TxRx = 1;

	CTxRxFilterDLG	xx;
	xx.m_TxRx = TxRx;
	if(TxRx==1)	xx.m_title = "Transmitter spectrum mask";
	else		xx.m_title = "Receiver selectivity mask";
	{
		xx.m_f[0]  = -28;	xx.m_a[0]  = 41;
		xx.m_f[1]  = -22;	xx.m_a[1]  = 40;
		xx.m_f[2]  = -20;	xx.m_a[2]  = 26.7;
		xx.m_f[3]  = -14;	xx.m_a[3]  = 17.8;
		xx.m_f[4]  = -12;	xx.m_a[4]  = 17.8;
		xx.m_f[5]  =  -8;	xx.m_a[5]  =  0;
		xx.m_f[6]  =   0;	xx.m_a[6]  =  0;
		xx.m_f[7]  =   8;	xx.m_a[7]  =  0;
		xx.m_f[8]  =  12;	xx.m_a[8]  = 17.8;
		xx.m_f[9]  =  14;	xx.m_a[9]  = 17.8;
		xx.m_f[10] =  20;	xx.m_a[10] = 26.7;
		xx.m_f[11] =  22;	xx.m_a[11] = 40;
		xx.m_f[12] =  28;	xx.m_a[12] = 41;
	}
	xx.DoModal();
}
*/