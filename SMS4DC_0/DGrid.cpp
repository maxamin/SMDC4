// DGrid.cpp : implementation file
//

#include "stdafx.h"
#include "sms4dc.h"
#include "DGrid.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDGrid

CDGrid::CDGrid()
{
	m_RowDirty = 0;
	m_RdOnly = 0;
	m_Entrance = 0;
	m_OldRow = 2;
	m_OldCol = 2;
	m_MaxColSel = 0;
	m_MaxRowSel = 0;
	m_Adding = 0;
	m_Entrance = 1;

//	m_DB="ODBC;DSN=WorkDB;";
//	m_Tbl="select * from STtable";

	m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	m_Tbl = ((CSMS4DCApp *)AfxGetApp())->m_CDataBaseSTR;
}

CDGrid::~CDGrid()
{
}


BEGIN_MESSAGE_MAP(CDGrid, CWnd)
	//{{AFX_MSG_MAP(CDGrid)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDGrid message handlers



BOOL CDGrid::LoadData()
{
	CODBCFieldInfo FldInfo;
	CDBVariant Fld;
    m_mydb.Open(m_DB,FALSE, FALSE, "ODBC;", FALSE);
//	CString t=m_mydb.GetConnect();
    m_rs.m_pDatabase=&m_mydb;
	m_rs.Open( CRecordset::snapshot, m_Tbl);

	long O = m_rs.GetRecordCount();
	if(O==0)
	{
		m_FlexGrid->SetRows(O + 1);
		return O;
	}

    while(!m_rs.IsEOF())
		m_rs.MoveNext();
	m_rs.MoveFirst();
    m_FlexGrid->SetCols(m_rs.GetODBCFieldCount()+ 1);
    m_FlexGrid->SetRows(m_rs.GetRecordCount() + 1);
    for(int i = 1 ; i<m_FlexGrid->GetCols() ; i++)
	{
		m_rs.GetODBCFieldInfo(i-1, FldInfo);
        m_FlexGrid->SetTextMatrix(0, i, FldInfo.m_strName );
        m_fields[i - 1].Name = m_FlexGrid->GetTextMatrix(0, i);
        m_fields[i - 1].Indexed = 0;
	}//end for
    for(i = 1 ; i<m_FlexGrid->GetRows() ; i++)
	{	m_RowStat[i].Selected=0;
        m_FlexGrid->SetRowData(i,i);
        for (int j = 1 ; j<m_FlexGrid->GetCols() ;j++)
		{
			CString buf;
			m_rs.GetODBCFieldInfo(j-1, FldInfo);
			m_rs.GetFieldValue(j - 1, Fld);

			m_fields[j-1].FType = Fld.m_dwType;

			switch(Fld.m_dwType)
			{
			case DBVT_SHORT:
				buf.Format("%d",Fld.m_iVal);
				break;
			case DBVT_LONG:
				buf.Format("%ld",Fld.m_lVal);
				break;
			case DBVT_UCHAR:
				buf.Format("%s",Fld.m_chVal);
				break;
			case DBVT_STRING:
				buf = *Fld.m_pstring;
				m_FlexGrid->SetColAlignment(j,2);
				break;
			case DBVT_SINGLE:
				buf.Format("%6.4f",Fld.m_fltVal);
	//			buf.Format("%g",Fld.m_fltVal);
				break;
			case DBVT_DOUBLE:
				buf.Format("%6.4lf",Fld.m_dblVal);
	//			buf.Format("%g",Fld.m_dblVal)
				break;

			}
			if(buf.IsEmpty())	m_FlexGrid->SetTextMatrix(i, j,_T(""));
            else				m_FlexGrid->SetTextMatrix(i, j,  buf );
		}//end for
        m_rs.MoveNext();
    }//end for
	m_FlexGrid->SetCol( 1);
	m_FlexGrid->SetRow( 1);
	m_FlexGrid->SetFocus();


	return O;
}

CString CDGrid::ExtractTable(CString Tb)
{
    char *x;
	CString temp;
	Tb.MakeLower();
    x = strstr( (LPCTSTR)Tb, " from ");
	if(x)
	{
		x+=6;
		while (*x && *x!=' ')
		{
			temp=temp+*x;
			x++;
		}//end while
		return temp;
	}//end if
	else
	{
		return Tb;
	}//end else
}
/*
void CDGrid::OnMouseUp(short Button, short Shift, long x, long y) 
{
    int temp, color, rstat;
    if( x<m_FlexGrid->GetColWidth(0)/15) 
	{
        m_Entrance = 0;
        temp = m_FlexGrid->GetCol();
        m_FlexGrid->SetCol(2);
        if(m_FlexGrid->GetCellBackColor()==RGB(255,255,0)) //yellow
		{
			color = RGB(255,255,255); //white
            rstat = 0;
		}
        else
		{
			color = RGB(255,255,0); //yellow
            rstat = 1;
		}
        m_RowStat[m_FlexGrid->GetRowData(m_FlexGrid->GetRow())].Selected = rstat;
        if(rstat == 1)
		{
            m_MaxRowSel = m_MaxRowSel + 1;
            m_RowStat[m_FlexGrid->GetRowData(m_FlexGrid->GetRow())].index = m_MaxRowSel;
		}
        for(int i = 1 ; i<m_FlexGrid->GetCols(); i++)
		{
			m_FlexGrid->SetCol(i);
            m_FlexGrid->SetCellBackColor(color);
		}//end for
        m_FlexGrid->SetCol(temp);
        m_Entrance = 1;
    }//end if
}
*/


void CDGrid::OnMouseUp(short Button, short Shift, long x, long y) 
{
    int temp, color, rstat;
    if( x<m_FlexGrid->GetColWidth(0)/15) 
	{
        m_Entrance = 0;
		int start=min(m_FlexGrid->GetRow(),m_FlexGrid->GetRowSel()),
			end=max(m_FlexGrid->GetRow(),m_FlexGrid->GetRowSel());
		temp = m_FlexGrid->GetCol();
		m_FlexGrid->SetCol(2);
		for(int j=start; j<=end;j++)
		{
			m_FlexGrid->SetRow(j);
			if(m_FlexGrid->GetCellBackColor()==RGB(255,255,0)) //yellow
			{
				color = RGB(255,255,255); //white
				rstat = 0;
			}
			else
			{
				color = RGB(255,255,0); //yellow
				rstat = 1;
			}
			m_RowStat[m_FlexGrid->GetRowData(j)].Selected = rstat;
			if(rstat == 1)
			{
				m_MaxRowSel ++;
				m_RowStat[m_FlexGrid->GetRowData(j)].index = m_MaxRowSel;
			}
			for(int i = 1 ; i<m_FlexGrid->GetCols(); i++)
			{
				m_FlexGrid->SetCol(i);
				m_FlexGrid->SetCellBackColor(color);
			}//end for
		}//end for
        m_FlexGrid->SetCol(temp);
        m_Entrance = 1;
    }//end if
}


void CDGrid::GetSelection()
{
	int i, j, k,Selcount = 0;

	//long tt=m_rs.GetRecordCount();
	long tt=m_FlexGrid->GetRows();

    k = 0;
    for(i = 1 ; i<=tt - 0; i++)
        if(m_RowStat[i].Selected)
			Selcount = Selcount + 1;
    for (i = 1 ; i<=m_MaxRowSel; i++)
	{
        if( k == Selcount)
			break;
        for( j = 1 ; j<=tt - 0; j++)
            if(m_RowStat[j].index == i && m_RowStat[j].Selected)
				break;
        if(j <= tt)
		{
			m_Sel[k] = GetRowText(FindOrigRow(j));
			k = k + 1;
        }//end if
    }//end for

	((CSMS4DCApp *)AfxGetApp())->Nrow = Selcount-1;

	((CSMS4DCApp *)AfxGetApp())->m_Sel = NULL;
	delete [] ((CSMS4DCApp *)AfxGetApp())->m_Sel;
	((CSMS4DCApp *)AfxGetApp())->m_Sel = new CString[Selcount-1];

    for (i = 0 ; i<Selcount-1; i++)
		((CSMS4DCApp *)AfxGetApp())->m_Sel[i] = m_Sel[i];
}

int CDGrid::FindOrigRow(int j)
{
	//long tt=m_rs.GetRecordCount();
	long tt=m_FlexGrid->GetRows();

    int i;
    for(i = 1 ; i<=tt - 1 ;i++)
        if(m_FlexGrid->GetRowData(i) == j) break;
    if(i == tt)
        return -1; //not found
    else
        return i;  // found
}

CString CDGrid::GetRowText(int j)
{
    CString tmp;
    m_Entrance = 0;
    tmp = "";
    for (int i = 1 ; i<=m_FlexGrid->GetCols() - 1; i++)
        tmp = tmp + m_FlexGrid->GetTextMatrix(j, i) + ",";
    tmp = tmp.Left(tmp.GetLength() - 1);
    m_Entrance = 1;
    return tmp;
}
