// CustomReport.cpp : implementation file
//
#include "stdafx.h"
#define APSTUDIO_INVOKED
#undef APSTUDIO_READONLY_SYMBOLS
#include "administrative.h"
#include "CustomReport.h"
#include <math.h>
#include <direct.h>
#include "windows.h"
#include <winreg.h>
#include <stdio.h>
#include <process.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


int CCustomReport::DoModal()
{
	//By construction of class CSetExtensionDllState the order of resource access is switched
	//to DLL before EXE (default is EXE before DLL) 
	CSetExtensionDllState state;
	return CDialog::DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CCustomReport dialog


CCustomReport::CCustomReport(CWnd* pParent /*=NULL*/)
	: CDialog(CCustomReport::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCustomReport)
	//}}AFX_DATA_INIT
}


void CCustomReport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustomReport)
	DDX_Control(pDX, IDC_FreqRem, m_FreqRem);
	DDX_Control(pDX, IDC_LICENSED, m_Licensed);
	DDX_Control(pDX, IDC_UNLICENSED, m_Unlicensed);
	DDX_Control(pDX, IDC_ALL, m_All);
	DDX_Control(pDX, IDC_OWNER, m_Owner);
	DDX_Control(pDX, IDC_LICENSE, m_License);
	DDX_Control(pDX, IDC_FIXED, m_FS);
	DDX_Control(pDX, IDC_LANDMOBILE, m_LMS);
	DDX_Control(pDX, IDC_BROADCASTING, m_BS);
	DDX_Control(pDX, IDC_FreqCondSel, m_FreqCondSel);
	DDX_Control(pDX, IDC_FreqCond, m_FreqCond);
	DDX_Control(pDX, IDC_FreqAdd, m_FreqAdd);
	DDX_Control(pDX, IDC_F2U, m_F2U);
	DDX_Control(pDX, IDC_F2, m_F2);
	DDX_Control(pDX, IDC_F1U, m_F1U);
	DDX_Control(pDX, IDC_F1, m_F1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCustomReport, CDialog)
	//{{AFX_MSG_MAP(CCustomReport)
	ON_LBN_SELCHANGE(IDC_FreqCond, OnSelchangeFreqCond)
	ON_LBN_SELCHANGE(IDC_OWNER, OnSelchangeOwner)
	ON_BN_CLICKED(IDC_FreqAdd, OnFreqAdd)
	ON_BN_CLICKED(IDC_FreqRem, OnFreqRem)
	ON_BN_CLICKED(IDC_LICENSED, OnLicensed)
	ON_BN_CLICKED(IDC_UNLICENSED, OnUnlicensed)
	ON_BN_CLICKED(IDC_ALL, OnAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomReport message handlers

BOOL CCustomReport::OnInitDialog() 
{
	CDialog::OnInitDialog();

	//AfxGetModuleState()->m_dwVersion = 0x0601;

	m_Lang=((CSMS4DCApp *)AfxGetApp())->m_Lang;
	m_CDBSTR=((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase DB;
	DB.Open(m_CDBSTR,false,false,_T("ODBC;"),false);
	CRecordset RS;
	RS.m_pDatabase=&DB;
	RS.Open(CRecordset::snapshot,"select ID, AdmName from owner order by AdmName");
	CString SQL, AdmName;
	long ID;
	for(int i=0;!RS.IsEOF();i++)
	{
		RS.GetFieldValue((short)0,SQL);
		ID=atol(SQL);
		RS.GetFieldValue((short)1,AdmName);
		m_Owner.AddString(AdmName);
		m_Owner.SetItemData(i,ID);
		RS.MoveNext();
	}
	RS.Close();
	m_Licensed.SetCheck(1);

//	CDialog::OnInitDialog();
/*	m_rs.Open(CRecordset::snapshot, _T("select * from ref_adm"));
	CString Temp;
	while(1)
	{
		if(m_rs.IsEOF()) break;
		m_rs.GetFieldValue((int)0,Temp);
		m_AdmList.AddString(Temp);
		m_rs.MoveNext();
	}//end while
	m_rs.Close();*/

	m_FreqCond.AddString("F = F1");
	m_FreqCond.AddString("F <> F1");
	m_FreqCond.AddString("F > F1");
	m_FreqCond.AddString("F >= F1");
	m_FreqCond.AddString("F < F1");
	m_FreqCond.AddString("F <= F1");
	m_FreqCond.AddString("F > F1 and F < F2");
	m_FreqCond.AddString("F >= F1 and F <= F2");
	m_FreqCond.AddString("F1 <= F or F >= F2");
	m_FreqCond.AddString("F1 < F or F > F2");
	m_F2U.SelectString(0,"MHz");
	m_F1U.SelectString(0,"MHz");
	
	DB.Close();
	TranslateDialog(this);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCustomReport::OnSelchangeFreqCond() 
{
	if(m_FreqCond.GetCurSel()>5)
	{
		m_F2.EnableWindow(TRUE);
		m_F2U.EnableWindow(TRUE);
	}
	else
	{
		m_F2.EnableWindow(FALSE);
		m_F2U.EnableWindow(FALSE);
	}
}

void CCustomReport::OnSelchangeOwner() 
{
	while(m_License.GetCount()>0)
		m_License.DeleteString(0);
	CString SQL;
	CDatabase DB;
	DB.Open(m_CDBSTR,false,false,_T("ODBC;"),false);
	CRecordset RS;
	RS.m_pDatabase=&DB;
	SQL.Format("select LicID, LicNo from License where AdmID=%ld order by LicID",m_Owner.GetItemData(m_Owner.GetCurSel()));
	RS.Open(CRecordset::snapshot,SQL);
	CString LicNo;
	long ID;
	for(int i=0;!RS.IsEOF();i++)
	{
		RS.GetFieldValue((short)0,SQL);
		ID=atol(SQL);
		RS.GetFieldValue((short)1,LicNo);
		m_License.AddString(LicNo);
		m_License.SetItemData(i,ID);
		RS.MoveNext();
	}
	RS.Close();
	DB.Close();
}

void CCustomReport::OnFreqAdd() 
{
	CString	FreqCond, F1, F2, FreqU, Temp;
	if(m_FreqCond.GetCurSel()!=CB_ERR )
	{
		m_FreqCond.GetText(m_FreqCond.GetCurSel(),FreqCond);
		m_F1.GetWindowText(F1);
		m_F1U.GetWindowText(FreqU);
		Temp.Format("%.3lf MHz",atof(F1)*GetFreqUnit(FreqU));
		FreqCond.Replace(_T("F1"),Temp);
		m_F2.GetWindowText(F2);
		m_F2U.GetWindowText(FreqU);
		Temp.Format("%.3lf MHz",atof(F2)*GetFreqUnit(FreqU));
		FreqCond.Replace(_T("F2"),Temp);
		if(m_FreqCondSel.FindString(-1,FreqCond)==LB_ERR)
			m_FreqCondSel.AddString(FreqCond);
	}
}

double CCustomReport::GetFreqUnit(CString Unit)
{
	if(!Unit.Compare("kHz"))		return 0.001;
	if(!Unit.Compare("MHz"))		return 1.;
	if(!Unit.Compare("GHz"))		return 1000.;
	return 0.000001;
}


void CCustomReport::OnOK() 
{
	CString SQL1, Line, SQLp1, SQLp2, SQLp3, SQLp4;
	if(!m_FS.GetCheck() && !m_BS.GetCheck() && !m_LMS.GetCheck())
		AfxMessageBox(_Z("At least one service type should be selected!"));
	else
	{
		CDatabase DB;
		FILE *fp;
		DB.Open(m_CDBSTR,false,false,_T("ODBC;"),false);
		CRecordset RS;
		RS.m_pDatabase=&DB;
		mkdir("C:\\Temp");
		remove("C:\\Temp\\Header.txt");
		fp=fopen("C:\\Temp\\Header.txt","wt");
		if(m_Licensed.GetCheck())
		{
			fputs(_Z("Licensed"),fp);
			fputs("\n",fp);
			m_Owner.GetWindowText(Line);
			if(!Line.IsEmpty())
			{
				Line=_Z("Owner")+":"+Line;
				fputs((LPCTSTR)Line,fp);
				fputs("\n",fp);
			}
			m_License.GetWindowText(Line);
			if(!Line.IsEmpty())
			{
				Line=_Z("License")+":"+Line;
				fputs((LPCTSTR)Line,fp);
				fputs("\n",fp);
			}
		}
		else if(m_Unlicensed.GetCheck())
		{
			fputs(_Z("Unlicensed"),fp);
			fputs("\n",fp);
		}
		else
		{
			Line=_Z("Licensed")+" "+_Z("and")+" "+_Z("Unlicensed");
			fputs((LPCTSTR)Line,fp);
			fputs("\n",fp);
		}
		Line=_Z("Service")+": "; 
		if(m_BS.GetCheck())
		{
			Line+=_Z("Broadcasting")+", "; 
		}
		if(m_FS.GetCheck())
		{
			Line+=_Z("Fixed")+", ";
		}
		if(m_LMS.GetCheck())
		{
			Line+=_Z("Land mobile")+", ";
		}
		Line=Line.Left(Line.GetLength()-2);
		fputs((LPCTSTR)Line,fp);
		fputs("\n",fp);
		if(m_FreqCondSel.GetCount()>0)
		{
			Line=GetFreqCond();
			Line.Replace("Freq_Assgn",_Z("Frequency"));
			fputs(Line,fp);
			fputs("\n",fp);
			SQL1+=" and (" + GetFreqCond() + ")";
		}
		fclose(fp);

		if(m_Licensed.GetCheck())
		{
			if(m_BS.GetCheck())
			{
				SQLp1="SELECT ClassStation, SiteName, GeoLat, GeoLon, Frequency/1000000 as Freq_assgn, EmDes from BCStation, Owner, License, Frequency, Equipment where Equipment.BCID=BCStation.StID and Equipment.EqID=Frequency.EqID and owner.ID=License.AdmID and License.LicID=BCStation.LicID";
			}
			if(m_FS.GetCheck())
			{
				SQLp2="SELECT ClassStation, SiteName, GeoLat, GeoLon, Frequency/1000000 as Freq_assgn, EmDes from Station, Owner, License, Frequency, Equipment where Equipment.StID=Station.StID and Equipment.EqID=Frequency.EqID and owner.ID=License.AdmID and License.LicID=Station.LicID and Station.ClassStation='FX'";
			}
			if(m_LMS.GetCheck())
			{
				SQLp3="SELECT ClassStation, SiteName, GeoLat, GeoLon, Frequency/1000000 as Freq_assgn, EmDes from Station, Owner, License, Frequency, Equipment where Equipment.StID=Station.StID and Equipment.EqID=Frequency.EqID and owner.ID=License.AdmID and License.LicID=Station.LicID and Station.ClassStation='FB'";
				SQLp4="SELECT ClassStation, MobName, GeoLat, GeoLon, Frequency/1000000 as Freq_assgn, EmDes from Mobiles, Owner, License, Frequency, Equipment where Equipment.MobID=Mobiles.MobID and Equipment.EqID=Frequency.EqID and owner.ID=License.AdmID and License.LicID=Mobiles.LicID";
			}
			m_Owner.GetWindowText(Line);
			if(!Line.IsEmpty())
			{
				if(!SQLp1.IsEmpty()) SQLp1+= " and Owner.AdmName='"+Line+"'";
				if(!SQLp2.IsEmpty()) SQLp2+= " and Owner.AdmName='"+Line+"'";
				if(!SQLp3.IsEmpty()) SQLp3+= " and Owner.AdmName='"+Line+"'";
				if(!SQLp4.IsEmpty()) SQLp4+= " and Owner.AdmName='"+Line+"'";
			}
			m_License.GetWindowText(Line);
			if(!Line.IsEmpty())
			{
				if(!SQLp1.IsEmpty()) SQLp1+= " and License.LicNo='"+Line+"'";
				if(!SQLp2.IsEmpty()) SQLp2+= " and License.LicNo='"+Line+"'";
				if(!SQLp3.IsEmpty()) SQLp3+= " and License.LicNo='"+Line+"'";
				if(!SQLp4.IsEmpty()) SQLp4+= " and License.LicNo='"+Line+"'";
			}
		}
		else if(m_Unlicensed.GetCheck())
		{
			if(m_BS.GetCheck())
			{
				SQLp1="SELECT ClassStation, SiteName, GeoLat, GeoLon, Frequency/1000000 as Freq_assgn, EmDes from BCStation, Frequency, Equipment where Equipment.BCID=BCStation.StID and Equipment.EqID=Frequency.EqID and BCStation.LicID=-1";
			}
			if(m_FS.GetCheck())
			{
				SQLp2="SELECT ClassStation, SiteName, GeoLat, GeoLon, Frequency/1000000 as Freq_assgn, EmDes from Station, Frequency, Equipment where Equipment.StID=Station.StID and Equipment.EqID=Frequency.EqID and Station.LicID=-1 and Station.ClassStation='FX'";
			}
			if(m_LMS.GetCheck())
			{
				SQLp3="SELECT ClassStation, SiteName, GeoLat, GeoLon, Frequency/1000000 as Freq_assgn, EmDes from Station, Frequency, Equipment where Equipment.StID=Station.StID and Equipment.EqID=Frequency.EqID and Station.LicID=-1 and Station.ClassStation='FB'";
				SQLp4="SELECT ClassStation, MobName, GeoLat, GeoLon, Frequency/1000000 as Freq_assgn, EmDes from Mobiles, Frequency, Equipment where Equipment.MobID=Mobiles.MobID and Equipment.EqID=Frequency.EqID and Mobiles.LicID=-1";
			}
		}
		else
		{
			if(m_BS.GetCheck())
			{
				SQLp1="SELECT ClassStation, SiteName, GeoLat, GeoLon, Frequency/1000000 as Freq_assgn, EmDes from BCStation, Frequency, Equipment where Equipment.BCID=BCStation.StID and Equipment.EqID=Frequency.EqID";
			}
			if(m_FS.GetCheck())
			{
				SQLp2="SELECT ClassStation, SiteName, GeoLat, GeoLon, Frequency/1000000 as Freq_assgn, EmDes from Station, Frequency, Equipment where Equipment.StID=Station.StID and Equipment.EqID=Frequency.EqID and Station.ClassStation='FX'";
			}
			if(m_LMS.GetCheck())
			{
				SQLp3="SELECT ClassStation, SiteName, GeoLat, GeoLon, Frequency/1000000 as Freq_assgn, EmDes from Station, Frequency, Equipment where Equipment.StID=Station.StID and Equipment.EqID=Frequency.EqID and Station.ClassStation='FB'";
				SQLp4="SELECT ClassStation, MobName, GeoLat, GeoLon, Frequency/1000000 as Freq_assgn, EmDes from Mobiles, Frequency, Equipment where Equipment.MobID=Mobiles.MobID and Equipment.EqID=Frequency.EqID";
			}
		}
		if(!SQLp1.IsEmpty()) SQLp1+=" union all ";
		if(!SQLp2.IsEmpty()) SQLp2+=" union all ";
		if(!SQLp3.IsEmpty()) SQLp3+=" union all ";
		if(!SQLp4.IsEmpty()) SQLp4+=" union all ";
		SQL1=SQLp1+SQLp2+SQLp3+SQLp4;
		SQL1="Select * into [Text;HDR=NO;DATABASE=C:\\Temp\\].Content.txt from (" + SQL1.Left(SQL1.GetLength()-11) + ")";
		SQLp1=GetFreqCond();
		if(!SQLp1.IsEmpty())
			SQL1+=" where " + SQLp1;

		remove("C:\\Temp\\Content.txt");
		DB.ExecuteSQL(SQL1);
		DB.Close();

		

		HKEY keyHandle;
		char rgValue [1024];
		char fnlRes [1024];
		DWORD size1;
		DWORD Type;

        if( RegOpenKeyEx(    HKEY_LOCAL_MACHINE, 
            "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\MSACCESS.EXE\\",0, 
            KEY_QUERY_VALUE, &keyHandle) == ERROR_SUCCESS)
             {
                size1=1023;
                RegQueryValueEx( keyHandle, _T(""), NULL, &Type, 
                    (LPBYTE)rgValue,&size1);
                sprintf(fnlRes,"Path of MSACCESS.EXE is:: %s",rgValue);
             }     
        else strcpy(fnlRes,"Couldn't access system information!");
    
            RegCloseKey(keyHandle);


		CString szPath;
		szPath=GetCommandLine();
		CString Path=szPath, Cmd;
		Path=Path.Left(Path.GetLength()-16)+"texts";
		Path=Path.Right(Path.GetLength()-1);
//		Path="C:\\BDT_Soft\\SMS4DC\\texts"; 
		Cmd="Copy "+Path+"\\CustomReport.dat c:\\temp\\rep.mdb";
		system(Cmd);
		_flushall();
		Cmd=rgValue;
		if	(m_Lang==_T("En"))
			spawnl(_P_NOWAIT, rgValue, "c:\\temp\\rep.mdb", "c:\\temp\\rep.mdb", "/X CustomE", NULL);
		if	(m_Lang==_T("Fr"))
			spawnl(_P_NOWAIT, rgValue, "c:\\temp\\rep.mdb", "c:\\temp\\rep.mdb", "/X CustomF", NULL);
		if	(m_Lang==_T("Es"))
			spawnl(_P_NOWAIT, rgValue, "c:\\temp\\rep.mdb", "c:\\temp\\rep.mdb", "/X CustomS", NULL);
		if	(m_Lang==_T("Ch"))
			spawnl(_P_NOWAIT, rgValue, "c:\\temp\\rep.mdb", "c:\\temp\\rep.mdb", "/X CustomC", NULL);
		if	(m_Lang==_T("Ru"))
			spawnl(_P_NOWAIT, rgValue, "c:\\temp\\rep.mdb", "c:\\temp\\rep.mdb", "/X CustomR", NULL);
		if	(m_Lang==_T("Ar"))
			spawnl(_P_NOWAIT, rgValue, "c:\\temp\\rep.mdb", "c:\\temp\\rep.mdb", "/X CustomA", NULL);
		CDialog::OnOK();
	}
}

CString CCustomReport::GetFreqCond()
{
	CString List,Item;
	for(int i=0;i<m_FreqCondSel.GetCount();i++)
	{
		m_FreqCondSel.GetText(i,Item);
		Item.Replace("F ","Freq_Assgn ");
		Item.Replace(" MHz","");
		Item.Replace(" MHz","");
		List+="(" + Item + ") or ";
	}
	List=List.Left(List.GetLength()-3);
	return List;
}

void CCustomReport::OnFreqRem() 
{
	m_FreqCondSel.DeleteString(m_FreqCondSel.GetCurSel());	
}

void CCustomReport::OnLicensed() 
{
	m_Owner.EnableWindow();
	m_License.EnableWindow();
}

void CCustomReport::OnUnlicensed() 
{
	m_Owner.SetEditSel(0,-1);
	m_Owner.Clear();
	m_Owner.EnableWindow(false);
	while(m_License.GetCount()>0)
		m_License.DeleteString(0);
	m_License.SetEditSel(0,-1);
	m_License.Clear();
	m_License.EnableWindow(false);
}

void CCustomReport::OnAll() 
{
	OnUnlicensed();
}

void CCustomReport::RemoveQuote(CString *Str)
{
	while(true)
	{
		int place=Str->Find(_T("\'"));
		if(place!=-1)
			Str->SetAt(place,' ');
		else
			break;
	}
}

void CCustomReport::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CCustomReport::TranslateDialog(CDialog *pDialog)
{
	CString strOriginal(_T(""));
	for (int iID = 0; iID < 64000 /*_APS_NEXT_CONTROL_VALUE*/; iID++)
	{
		pDialog->GetDlgItemText(iID, strOriginal);
		if (!strOriginal.IsEmpty())
		{
			if(((pDialog->GetDlgItem(iID))->IsKindOf(RUNTIME_CLASS(CComboBox)))!=1)
			{
				CString s = GetTranslatedString(strOriginal, m_Lang);
				if (!s.IsEmpty())// && strOriginal != s)
					pDialog->SetDlgItemText(iID, s);
			}
		}
	}//for
	strOriginal = _T("");
	pDialog->GetWindowText(strOriginal);
	if (!strOriginal.IsEmpty())
	{
		CString s = GetTranslatedString(strOriginal, m_Lang);
		if (!s.IsEmpty() && strOriginal != s)
			pDialog->SetWindowText(s);
	}
}

CString CCustomReport::GetTranslatedString(CString strOriginal, CString Lang)
{
	static CString m_Lang;
//	m_Lang="CC";
	if(Lang!=m_Lang && !Lang.IsEmpty()) 
		m_Lang=Lang;
	if(m_Lang==_T("En"))	return strOriginal;
	int ID=-1;
	HMODULE	hMod = LoadLibrary("ResDLLen.dll");
	if(hMod)
	{
		LPCTSTR lpszName = MAKEINTRESOURCE(1);
		if (::FindResource(hMod,  lpszName, RT_STRING) != NULL)
		{
			TCHAR szTemp[1001];
			int n=0, nLen = ::LoadString(hMod, 0, szTemp, 1000);
			if(nLen!=0)		n = atoi(szTemp);

			for(int ids=1; ids<=n; ids++)
			{
				nLen = ::LoadString(hMod, ids, szTemp, 1000);
				if(strOriginal==szTemp)
				{
					ID = ids;
					break;
				}
			}
		}
		FreeLibrary(hMod);
	}//hMod

	CString str;
	if		(m_Lang==_T("Fr")) 	hMod = LoadLibrary("ResDLLfr.dll");
	else if	(m_Lang==_T("Es")) 	hMod = LoadLibrary("ResDLLes.dll");
	else if	(m_Lang==_T("Ch")) 	hMod = LoadLibrary("ResDLLch.dll");
	else if	(m_Lang==_T("Ar")) 	hMod = LoadLibrary("ResDLLar.dll");
	else if	(m_Lang==_T("Ru")) 	hMod = LoadLibrary("ResDLLru.dll");

	if(hMod)
	{
		LPCTSTR lpszName = MAKEINTRESOURCE(1);
		if (::FindResource(hMod,  lpszName, RT_STRING) != NULL)
		{
			TCHAR szTemp[1001];
			::LoadString(hMod, ID, szTemp, 1000);
			str = szTemp;
		}
		FreeLibrary(hMod);
	}//hMod

	return str;
}

