// EqCatSelect.cpp : implementation file
//

#include "stdafx.h"
#include "Administrative.h"
#include "CatSelect.h"
#include "LeftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCatSelect dialog


CCatSelect::CCatSelect(CWnd* pParent /*=NULL*/)
	: CDialog(CCatSelect::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCatSelect)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_CatID=-1;
}


void CCatSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCatSelect)
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_CatGrid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCatSelect, CDialog)
	//{{AFX_MSG_MAP(CCatSelect)
	ON_BN_CLICKED(IDC_AddPattern, OnAddPattern)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCatSelect message handlers

BOOL CCatSelect::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CDatabase DB;
	CRecordset RS;
	long i=1,Fields;
	DB.Open(m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	RS.m_pDatabase=&DB;
	m_CatGrid.SetRows(1);
	SetWindowText(m_Table+ _Z(" Catalog"));

	if(m_Table==_T("Equipment"))
	{
		RS.Open(CRecordset::snapshot,_T("select EqCatID, EqName, PowerType, RadPowerType, Madeby, Model, TranSys, TVSys, ColorSys, Sensitivity from eqcat order by eqcatid"));
		Fields=10;
		m_CatGrid.SetCols(0,Fields+1);
		for(int j=0;j<Fields;j++)
		{
			CODBCFieldInfo FldInfo;
			CString Unit,Format,Srv,Mask;
			RS.GetODBCFieldInfo(j,FldInfo);
			m_CatGrid.SetTextMatrix(0,j+1,GetFieldName(&DB, _T("EqCat"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask));
		}
	}
	else if(m_Table==_T("Antenna"))
	{
		RS.Open(CRecordset::snapshot,_T("select AntCatID, AntName, Pol, Gain, GainType, AntDir, BeamWidthH from antcat where lib=1 order by antcatid"));
		Fields=7;
		m_CatGrid.SetCols(0,Fields+1);
		for(int j=0;j<Fields;j++)
		{
			CODBCFieldInfo FldInfo;
			CString Unit,Format,Srv,Mask;
			RS.GetODBCFieldInfo(j,FldInfo);
			m_CatGrid.SetTextMatrix(0,j+1,GetFieldName(&DB, _T("AntCat"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask));
		}
	}
	else if(m_Table==_T("Eant"))
	{
		SetWindowText(_Z("Antenna Formula"));
		((CButton *)GetDlgItem(IDC_AddPattern))->ShowWindow(SW_SHOW);
		if(m_typ==EANTUP)
			RS.Open(CRecordset::snapshot,_T("select pattern_id, pattern, coefa, coefb, coefc, coefd, phi1 from ant_type where emi_rcp='E' order by pattern_id"));
		else
			RS.Open(CRecordset::snapshot,_T("select pattern_id, pattern, coefa, coefb, coefc, coefd, phi1 from ant_type where emi_rcp='R' order by pattern_id"));
		Fields=7;
		m_CatGrid.SetCols(0,Fields+1);
		for(int j=0;j<Fields;j++)
		{
			CODBCFieldInfo FldInfo;
			CString Unit,Format,Srv,Mask;
			RS.GetODBCFieldInfo(j,FldInfo);
			m_CatGrid.SetTextMatrix(0,j+1,GetFieldName(&DB, _T("Ant_Type"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask));
		}
	}
	else if(m_Table==_T("rrc_contour"))
	{
		SetWindowText(_Z("Contour"));
		((CButton *)GetDlgItem(IDC_AddPattern))->ShowWindow(SW_HIDE);
		RS.Open(CRecordset::snapshot,_T("select contourkey, adm, ctry, nb_test_pts, remarks from rrc_contour order by contourkey"));
		Fields=4;
		m_CatGrid.SetCols(0,Fields+1);
		for(int j=0;j<Fields;j++)
		{
			CODBCFieldInfo FldInfo;
			CString Unit,Format,Srv,Mask;
			RS.GetODBCFieldInfo(j,FldInfo);
			m_CatGrid.SetTextMatrix(0,j+1,GetFieldName(&DB, _T("rrc_contour"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask));
		}
	}

	while(true)
	{
		if(RS.IsEOF()) break;
		m_CatGrid.SetRows(m_CatGrid.GetRows()+1);
		for(int j=0;j<Fields;j++)
		{
			CString Value;
			RS.GetFieldValue(j,Value);
			m_CatGrid.SetTextMatrix(i,j+1,Value);
		}
		RS.MoveNext();
		i++;
	}	
	if(i>1) m_CatGrid.SetFixedRows(1);
	RS.Close();
	DB.Close();
	if(i==1)
	{
		AfxMessageBox(_Z("Library is empty!"));
		OnCancel();
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CString CCatSelect::GetFieldName(CDatabase *DB, CString Table, CString OrigName, CString LangCode, CString *Unit, CString *Format, CString *Srv, CString *Mask)
{
	CRecordset	RS;
	RS.m_pDatabase=DB;
	CString FieldName,SQL;
	SQL.Format(_T("Select * from Fields where TableName='%s' and FieldName='%s'"), Table, OrigName);
	RS.Open(CRecordset::dynaset,SQL);
//	LangCode=/*((CSMS4DCApp *)AfxGetApp())->*/m_Lang;
	if(RS.GetRecordCount()>0)
	{
		if(m_Lang==_T("En"))
			RS.GetFieldValue(2,FieldName);
		if(m_Lang==_T("Fr"))
			RS.GetFieldValue(3,FieldName);
		if(m_Lang==_T("Es"))
			RS.GetFieldValue(4,FieldName);
		if(m_Lang==_T("Ch"))
			RS.GetFieldValue(5,FieldName);
		if(m_Lang==_T("Ru"))
			RS.GetFieldValue(6,FieldName);
		if(m_Lang==_T("Ar"))
			RS.GetFieldValue(7,FieldName);
		RS.GetFieldValue(8,*Unit);
		RS.GetFieldValue(9,*Srv);
		RS.GetFieldValue(10,*Mask);
		RS.GetFieldValue(11,*Format);
	}
	else
	{
		*Srv=_T("-");
	}
	RS.Close();
	((CAdministrativeApp *)AfxGetApp())->TranslateDialog(this);

	if(!FieldName.IsEmpty()) 
		return FieldName;
	else
		return OrigName;
}

void CCatSelect::OnOK()
{
	if(m_CatGrid.GetRowSel()>-1)
	{
		CDatabase DB;
		CRecordset RS;
		DB.Open(m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
		RS.m_pDatabase=&DB;
		CString SQL,Srv,Value;

		if(m_Table!=_T("Eant") && m_Table!=_T("rrc_contour"))
		{
			if(m_typ==STATION)
				SQL.Format(_T("Select ClassStation from Station where StID=%ld "),m_ID);
			if(m_typ==BC)
				SQL.Format(_T("Select ClassStation from BCStation where StID=%ld "),m_ID);
			if(m_typ==MOBILE)
				SQL.Format(_T("Select ClassStation from Mobiles where MobID=%ld "),m_ID);
			RS.Open(CRecordset::snapshot,SQL);
			RS.GetFieldValue((short)0,Srv);
			RS.Close();
		}
		int i=0,j=0;
		if(m_Table==_T("Equipment"))
		{
			if(Srv==_T("BC"))
				SQL.Format(_T("select EqName,0,PowerType,MadeBy,Model,SerialNo,TranSys,ERP_h_dbw,ERP_v_dbw,EU_Ref,RefPlanCfg,MaxPowDens from EqCat where eqcatid=%s"), 
					m_CatGrid.GetTextMatrix(m_CatGrid.GetRowSel(),1));
			if(Srv==_T("BT"))
				SQL.Format(_T("select EqName,0,PowerType,MadeBy,Model,SerialNo,OsetV12,OsetV,OsetS12,OsetS,TVSys,ColorSys,ERP_h_dbw,ERP_v_dbw,PwrRatio,EU_Ref,FreqStabl,RefPlanCfg,SysVar,RXMode,MaxPowDens from EqCat where eqcatid=%s"), 
					m_CatGrid.GetTextMatrix(m_CatGrid.GetRowSel(),1));
			if(Srv==_T("FX"))
				SQL.Format(_T("select EqName,0,PowerType,0,RadPowerType,MadeBy,Model,SerialNo,Sensitivity,EnDisp,NoiseFactor,SystemType1,SystemType2,MaxPowDens from EqCat where eqcatid=%s"), 
					m_CatGrid.GetTextMatrix(m_CatGrid.GetRowSel(),1));
			if(Srv==_T("FB"))
				SQL.Format(_T("select EqName,0,PowerType,0,RadPowerType,MadeBy,Model,SerialNo,Sensitivity,SystemType1,SystemType2,MaxPowDens from EqCat where eqcatid=%s"), 
					m_CatGrid.GetTextMatrix(m_CatGrid.GetRowSel(),1));
			if(Srv==_T("ML"))
				SQL.Format(_T("select EqName,0,PowerType,0,RadPowerType,MadeBy,Model,SerialNo,Sensitivity,SystemType1,SystemType2,MaxPowDens from EqCat where eqcatid=%s"), 
					m_CatGrid.GetTextMatrix(m_CatGrid.GetRowSel(),1));
		}
		else 
			if(m_Table==_T("Antenna"))
			{
				i=3;
				j=4;
				if(Srv==_T("BC") || Srv==_T("BT"))
					SQL.Format(_T("select '','','',AntName, ClassOfAnt, AntType, Pol, Gain, GainType, AntDir, BeamWidthH, BeamWidthV, RefAnt, MaxEffHght, FreqFrom, FreqTo, XPD, InsLoss from AntCat where antcatid=%s"), 
						m_CatGrid.GetTextMatrix(m_CatGrid.GetRowSel(),1));
				if(Srv==_T("FX"))
				{
					SQL.Format(_T("select '','','','',AntName, ClassOfAnt, AntType, Pol, Gain, GainType, AntDir, BeamWidthH, BeamWidthV, RefAnt, FreqFrom, FreqTo, XPD, InsLoss from AntCat where antcatid=%s"), 
						m_CatGrid.GetTextMatrix(m_CatGrid.GetRowSel(),1));
					i++;
					j++;
				}
				if(Srv==_T("FB") || Srv==_T("ML"))
					SQL.Format(_T("select '','','',AntName, ClassOfAnt, AntType, Pol, Gain, GainType, AntDir, BeamWidthH, BeamWidthV, RefAnt, FreqFrom, FreqTo, XPD, InsLoss from AntCat where antcatid=%s"), 
						m_CatGrid.GetTextMatrix(m_CatGrid.GetRowSel(),1));
			}
			else
				if(m_Table==_T("Eant"))
				{
					j=6;
					i=1;
					SQL.Format(_T("select pattern_id, pattern, coefa, coefb, coefc, coefd, phi1 from ant_type where pattern_id=%s"),m_CatGrid.GetTextMatrix(m_CatGrid.GetRowSel(),1));
					if(m_EqGrid->GetRows()<8)
						m_EqGrid->SetRows(m_EqGrid->GetRows()+6);
				}

		if(m_Table==_T("rrc_contour"))
		{
		}
		else
		{
			RS.Open(CRecordset::snapshot,SQL);
			m_EqGrid->SetCol(1);
			for(;i<RS.GetODBCFieldCount();i++,j++)
			{
				m_EqGrid->SetRow(j+1);
				if(m_EqGrid->GetCellBackColor()==0x7F7F7F)
				{
					i--;
					continue;
				}
				RS.GetFieldValue(i,Value);
				if(m_Table!=_T("Equipment") || (i!=1 && i!=3))
					m_EqGrid->SetTextMatrix(j+1,1,Value);
				if(m_Table==_T("Eant"))
				{
					CODBCFieldInfo FldInfo;
					CString FName, Unit, Srv, Format, Mask;
					RS.GetODBCFieldInfo(i,FldInfo);
					FName=GetFieldName(&DB, _T("ant_type"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask);
					if(Srv==_T("-"))
					{
						j--;
						continue;
					}
					m_EqGrid->SetTextMatrix(j+1,0,FName);
					m_EqGrid->SetTextMatrix(j+1,2,Unit);
					m_EqGrid->SetCol(1);
					m_EqGrid->SetRow(j+1);
					m_EqGrid->SetCellBackColor(0xDFDFDF);
					m_EqGrid->SetCol(2);
					m_EqGrid->SetCellBackColor(0xDFDFDF);
				}
			}
			RS.Close();
			DB.Close();
		}
		m_CatID=atol(m_CatGrid.GetTextMatrix(m_CatGrid.GetRowSel(),1));
	}
	CDialog::OnOK();
}

void CCatSelect::OnAddPattern() 
{
	CESAntPat PattDlg;
	PattDlg.m_CDBSTR=m_CDBSTR;
	if(m_typ==EANTUP)
		PattDlg.m_ER=_T("E");
	else
		PattDlg.m_ER=_T("R");
	PattDlg.DoModal();
	OnInitDialog();
}
