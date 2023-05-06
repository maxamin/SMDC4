// Allocations_DrawDoc.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "Allocations_DrawDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAllocations_DrawDoc

IMPLEMENT_DYNCREATE(CAllocations_DrawDoc, CDocument)

CAllocations_DrawDoc::CAllocations_DrawDoc()
{
	m_ReadyDoc = 0;
	m_Flo = 8025;	m_Fhi = 9200;
//	m_Flo = 25;	m_Fhi = 26;

	m_REGION = 3;
	m_Lin_Log = 0;
	m_Fu = 1;  //MHz
}

BOOL CAllocations_DrawDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CAllocations_DrawDoc::~CAllocations_DrawDoc()
{
	if(	m_ReadyDoc==1)
		delete[] m_Recs;

}


BEGIN_MESSAGE_MAP(CAllocations_DrawDoc, CDocument)
	//{{AFX_MSG_MAP(CAllocations_DrawDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAllocations_DrawDoc diagnostics

#ifdef _DEBUG
void CAllocations_DrawDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAllocations_DrawDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAllocations_DrawDoc serialization

void CAllocations_DrawDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CAllocations_DrawDoc commands

void CAllocations_DrawDoc::GetData()
{
//	CString  m_DB="ODBC;DSN=WorkDB;";
	CString  m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;

	CDatabase m_mydb;

	if (m_mydb.Open(_T(m_DB),FALSE,TRUE, "ODBC;", FALSE))
	{
		CODBCFieldInfo FldInfo;
		CDBVariant Fld;
		CRecordset m_rs;
		CString	m_Tbl , Filter;

		m_Tbl.Format("select * from ITU_PLAN_R%d",m_REGION);

		m_rs.m_pDatabase = &m_mydb;

		m_Flo = max(min(m_Flo,275000),0.003);
		m_Fhi = max(min(m_Fhi,300000),0.009);

		Filter.Format("(FRQ_LO>=%lf and FRQ_HI<=%lf)",m_Flo,m_Fhi);
		if(m_Tbl.Find(" where ")==-1)
			Filter=m_Tbl+" where "+Filter;
		else
			Filter=m_Tbl+" and "+Filter;

		Filter = Filter + " ORDER BY FRQ_LO";

		m_rs.Open( CRecordset::snapshot, Filter);

		int k=0;
		while(!m_rs.IsEOF())
		{
			m_rs.MoveNext();
			k++;
		}

		if (k>0)
		{
			m_rs.MoveFirst();
			m_RecsNUM = k;
			m_Recs = new PlanRecord[m_RecsNUM];

			int i,j,k1;
			CString PS,FOTPS;

			for ( i=0;i<m_RecsNUM;i++)
			{
				m_rs.GetFieldValue((short)1, Fld);		m_Recs[i].FRQ_LO= Fld.m_dblVal;
				m_rs.GetFieldValue((short)2, Fld);		m_Recs[i].FRQ_HI= Fld.m_dblVal;

				j=0;
				for ( k1=0;k1<12;k1++)
				{
					/////////////////////////////////////////////////////////////////////
					m_rs.GetFieldValue((short)(3+2*k1), PS);

					if (PS!="1")
					{
						m_Recs[i].SRV_p_s[j] = ( (k1<6) ? 1 : 0 );
						ID2NameColor(PS,m_Recs[i].SRV_p_s[j],
									   &(m_Recs[i].SRVname[j]), &(m_Recs[i].srvC[j]));

						m_Recs[i].SRV_sat[j] = FindSat(m_Recs[i].SRVname[j]);

						m_rs.GetFieldValue((short)(4+2*k1), FOTPS);
						m_Recs[i].SRV_fot[j] = FOTPS;
						
						j++;
					}
				}
				m_rs.GetFieldValue((short)27, FOTPS);
				m_Recs[i].SRV_fotT = FOTPS;
				
				m_rs.MoveNext();
				m_Recs[i].SRVnum = j;
			}
		}
		m_rs.Close();
		m_mydb.Close();
	}
}



int CAllocations_DrawDoc::FindSat(CString PS) 
{
	int flag = 0;
	PS.MakeUpper();
	 if ( PS.Find("SATELLITE") != -1) 
		flag = 1;
	return flag;
}

void CAllocations_DrawDoc::ID2NameColor(CString id_str,int psFlag,CString *SRVname,COLORREF *srvRGB)
{
	CODBCFieldInfo FldInfo;
	CDBVariant Fld;
	CDatabase m_mydb;
	CRecordset m_rs;
//	CString  m_DB="ODBC;DSN=WorkDB;";
	CString  m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;

	CString	Filter, m_Tbl = "select * from SRVCode_Color_Name";

	*SRVname = "";
	*srvRGB  = RGB(0,0,0);

	if (m_mydb.Open(_T(m_DB),FALSE,TRUE, "ODBC;", FALSE))
	{
		m_rs.m_pDatabase=&m_mydb;
		Filter.Format("(ID=%s)",id_str);

		if(m_Tbl.Find(" where ")==-1)	Filter=m_Tbl+" where "+Filter;
		else							Filter=m_Tbl+" and "  +Filter;

		m_rs.Open( CRecordset::snapshot, Filter);
		m_rs.MoveFirst();

		int srvR,srvG,srvB;
		m_rs.GetFieldValue((short)2, Fld);	srvR = Fld.m_lVal;
		m_rs.GetFieldValue((short)3, Fld);	srvG = Fld.m_lVal;
		m_rs.GetFieldValue((short)4, Fld);	srvB = Fld.m_lVal;
		*srvRGB = RGB(srvR,srvG,srvB);
		CString Fld1;

		CString m_LangApp = ((CSMS4DCApp *)AfxGetApp())->m_Lang;
		if(m_LangApp==_T("En"))
		{
			if(psFlag)		m_rs.GetFieldValue((short)5, Fld1);	
			else			m_rs.GetFieldValue((short)6, Fld1);
		}
		else if(m_LangApp==_T("Fr"))
		{
			if(psFlag)		m_rs.GetFieldValue((short)7, Fld1);	
			else			m_rs.GetFieldValue((short)8, Fld1);
		}
		else if(m_LangApp==_T("Es"))	//940312
		{
			if(psFlag)		m_rs.GetFieldValue((short)9, Fld1);	
			else			m_rs.GetFieldValue((short)10, Fld1);
		}
		else
		{
			if(psFlag)		m_rs.GetFieldValue((short)5, Fld1);	
			else			m_rs.GetFieldValue((short)6, Fld1);
		}

		*SRVname = Fld1;
	}
	m_rs.Close();
	m_mydb.Close();
}



