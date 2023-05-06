// InterModDLG.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "InterModDLG.h"
#include "AddFreqDLG.h"
#include "DataBaseLDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInterModDLG dialog


CInterModDLG::CInterModDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CInterModDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInterModDLG)
	m_Horder = 2;
	//}}AFX_DATA_INIT
}


void CInterModDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInterModDLG)
	DDX_Control(pDX, IDC_LIST_Tx, m_LIST_Tx);
	DDX_Control(pDX, IDC_LIST_Rx, m_LIST_Rx);
	DDX_Control(pDX, IDC_LIST_OUT, m_LIST_OUT);
	DDX_Text(pDX, IDC_EDIT_Horder, m_Horder);
	DDV_MinMaxInt(pDX, m_Horder, 0, 10);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInterModDLG, CDialog)
	//{{AFX_MSG_MAP(CInterModDLG)
	ON_BN_CLICKED(IDC_AddTx, OnAddTx)
	ON_BN_CLICKED(IDC_AddRx, OnAddRx)
	ON_BN_CLICKED(IDC_DeleteTx, OnDeleteTx)
	ON_BN_CLICKED(IDC_DeleteRx, OnDeleteRx)
	ON_BN_CLICKED(IDC_RADIO_S2, OnRadioS2)
	ON_BN_CLICKED(IDC_RADIO_S3, OnRadioS3)
	ON_BN_CLICKED(IDC_RADIO_O3, OnRadioO3)
	ON_BN_CLICKED(IDC_RADIO_O5, OnRadioO5)
	ON_BN_CLICKED(IDC_RADIO_O7, OnRadioO7)
	ON_BN_CLICKED(IDC_Save, OnSave)
	ON_BN_CLICKED(IDC_AddTxDB, OnAddTxDB)
	ON_BN_CLICKED(IDC_AddRxDB, OnAddRxDB)
	ON_BN_CLICKED(IDC_AddTx2Rx, OnAddTx2Rx)
	ON_BN_CLICKED(IDC_AddRx2Tx, OnAddRx2Tx)
	ON_BN_CLICKED(IDC_DeleteTxAll, OnDeleteTxAll)
	ON_BN_CLICKED(IDC_DeleteRxAll, OnDeleteRxAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInterModDLG message handlers

BOOL CInterModDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_LIST_Tx.AddString("150.0");	
	m_LIST_Tx.AddString("151.0");	
	m_LIST_Tx.AddString("152.0");	

	m_LIST_Rx.AddString("149.0    ,    25.0");	
	m_LIST_Rx.AddString("150.0    ,    25.0");	
	m_LIST_Rx.AddString("151.0    ,    25.0");	
	m_LIST_Rx.AddString("152.0    ,    25.0");	
	m_LIST_Rx.AddString("300.0    ,    25.0");	
	m_LIST_Rx.AddString("450.0    ,    25.0");	

	m_Signal = TRUE;
	CButton* xx;
	xx=(CButton*)GetDlgItem(IDC_RADIO_S3);
	xx->SetCheck(m_Signal);
	xx=(CButton*)GetDlgItem(IDC_RADIO_S2);
	xx->SetCheck(!m_Signal);

	m_Order = 2;
	xx=(CButton*)GetDlgItem(IDC_RADIO_O3);
	xx->SetCheck(m_Order==0);
	xx=(CButton*)GetDlgItem(IDC_RADIO_O5);
	xx->SetCheck(m_Order==1);
	xx=(CButton*)GetDlgItem(IDC_RADIO_O7);
	xx->SetCheck(m_Order==2);

	CFont font;
	VERIFY(font.CreateFont(
	   16,                        // nHeight
	   0,                         // nWidth
	   0,                         // nEscapement
	   0,                         // nOrientation
	   FW_BOLD,					  // nWeight
	   FALSE,                     // bItalic
	   FALSE,                     // bUnderline
	   0,                         // cStrikeOut
	   ANSI_CHARSET,              // nCharSet
	   OUT_DEFAULT_PRECIS,        // nOutPrecision
	   CLIP_DEFAULT_PRECIS,       // nClipPrecision
	   DEFAULT_QUALITY,           // nQuality
	   DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
	   "Arial"));  
	m_LIST_OUT.SetFont(&font);
	font.DeleteObject();
	
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE; 
}

void CInterModDLG::OnOK() 
{
	UpdateData();
	m_LIST_OUT.ResetContent();

	int numTxFREQ = m_LIST_Tx.GetCount();
	int numRxFREQ = m_LIST_Rx.GetCount();

	double *TxFREQ;				TxFREQ = new double[numTxFREQ];
	double *RxFREQ;				RxFREQ = new double[numRxFREQ];
	double *RxBandWidth;		RxBandWidth = new double[numRxFREQ];

	CString str;
	int i,j,k,l;

	for( i=0;i<numTxFREQ;i++)
	{
		m_LIST_Tx.GetText(i,str);
		TxFREQ[i] = atof(str);	
	}
	for( i=0;i<numRxFREQ;i++)
	{
		m_LIST_Rx.GetText(i,str);
		k = str.Find(",",0);
		
		RxFREQ[i] = atof(str.Left(k));
		RxBandWidth[i] = atof(str.Mid(k+1))/1000.0;	
	}

//////////////////////////////HARMONIC ANALYSIS/////////////////////
////////////////////////////////////////////////////////////////////
	str.Format(_Z("HARMONIC :"));	m_LIST_OUT.AddString(str);	
	str.Format("===========");		m_LIST_OUT.AddString(str);	
	double HARMONIC;BOOL HARMONICflag = TRUE;
	for( i=0;i<numTxFREQ;i++)
		for( j=0;j<m_Horder;j++)
		{
			HARMONIC = (j+1)*TxFREQ[i];
			for( k=0;k<numRxFREQ;k++)
				if (HARMONIC>=RxFREQ[k]-RxBandWidth[k]/2.0 && HARMONIC<=RxFREQ[k]+RxBandWidth[k]/2.0)
				{
					HARMONICflag = FALSE;
					str.Format(" %d:     %d%c( %f ) = %f",(j+1),(j+1),_T(0xD7),TxFREQ[i],RxFREQ[k]);
					m_LIST_OUT.AddString(str);	
				}
		}
	if(HARMONICflag)
	{
		str.Format("         " + _Z("---------- NOT FOUND -------"));
		m_LIST_OUT.AddString(str);	
	}
//////////////////////////////TWO SIGNAL CASE///////////////////////
////////////////////////////////////////////////////////////////////
//	str.Format("INTERMODULATION TWO SIGNAL CASE :");
	str.Format(_Z("INTERMODULATION (TWO SIGNALS) :"));	m_LIST_OUT.AddString(str);	
	str.Format("===================================");	m_LIST_OUT.AddString(str);	
	double S2O3,S2O5,S2O7;BOOL S2flag = TRUE;
	for( i=0;i<numTxFREQ;i++)
		for( j=0;j<numTxFREQ;j++)
			if(i!=j)
			{
				S2O3=2.0*TxFREQ[i]-TxFREQ[j];
				S2O5=3.0*TxFREQ[i]-2.0*TxFREQ[j];
				S2O7=4.0*TxFREQ[i]-3.0*TxFREQ[j];
				for( k=0;k<numRxFREQ;k++)
				{
					//3rd order interference test.
					if (S2O3>=RxFREQ[k]-RxBandWidth[k]/2.0 && S2O3<=RxFREQ[k]+RxBandWidth[k]/2.0)
					{
						S2flag = FALSE;
						str.Format(_Z("Order 3:")+"     %d%c( %f ) %d%c( %f ) = %f",2,_T(0xD7),TxFREQ[i],-1,_T(0xD7),TxFREQ[j],RxFREQ[k]);
						m_LIST_OUT.AddString(str);	
					}
					if((m_Order==1)||(m_Order==2))
					{
						//5rd order interference test.
						if (S2O5>=RxFREQ[k]-RxBandWidth[k]/2.0 && S2O5<=RxFREQ[k]+RxBandWidth[k]/2.0)
						{
							S2flag = FALSE;
							str.Format(_Z("Order 5:")+"     %d%c( %f ) %d%c( %f ) = %f",3,_T(0xD7),TxFREQ[i],-2,_T(0xD7),TxFREQ[j],RxFREQ[k]);
							m_LIST_OUT.AddString(str);	
						}
						if(m_Order==2)
						{
							//7rd order interference test.
							if (S2O7>=RxFREQ[k]-RxBandWidth[k]/2.0 && S2O7<=RxFREQ[k]+RxBandWidth[k]/2.0)
							{
								S2flag = FALSE;
								str.Format(_Z("Order 7:")+"     %d%c( %f ) %d%c( %f ) = %f",4,_T(0xD7),TxFREQ[i],-3,_T(0xD7),TxFREQ[j],RxFREQ[k]);
								m_LIST_OUT.AddString(str);	
							}
						}
					}
				}

			}
	if(S2flag)
	{
		str.Format("         " + _Z("---------- NOT FOUND -------"));
		m_LIST_OUT.AddString(str);	
	}
//////////////////////////////THREE SIGNAL CASE///////////////////////
/////////////////////////////////////////////////////////////////////
	if(m_Signal)
	{
//		str.Format("INTERMODULATION THREE SIGNAL CASE :");
		str.Format(_Z("INTERMODULATION (THREE SIGNALS) :"));		m_LIST_OUT.AddString(str);	
		str.Format("=====================================");		m_LIST_OUT.AddString(str);	

		double S3O3,S3O5,S3O5A,S3O7,S3O7A,S3O7B;BOOL S3flag = TRUE;
		for( i=0;i<numTxFREQ;i++)
			for( j=0;j<numTxFREQ;j++)
				for( k=0;k<numTxFREQ;k++)
					if((i!=j)&&(i!=k)&&(k!=j))
					{
						S3O3  = 1.0 * TxFREQ[i] - 1.0 * TxFREQ[j] + 1.0 * TxFREQ[k];
						S3O5  = 2.0 * TxFREQ[i] - 2.0 * TxFREQ[j] + 1.0 * TxFREQ[k];
						S3O5A = 3.0 * TxFREQ[i] - 1.0 * TxFREQ[j] - 1.0 * TxFREQ[k];
						S3O7  = 2.0 * TxFREQ[i] - 3.0 * TxFREQ[j] + 2.0 * TxFREQ[k];
						S3O7A = 4.0 * TxFREQ[i] - 2.0 * TxFREQ[j] - 1.0 * TxFREQ[k];
						S3O7B = 3.0 * TxFREQ[i] - 3.0 * TxFREQ[j] + 1.0 * TxFREQ[k]; 
						for( l=0;l<numRxFREQ;l++)
						{
							//3rd order interference test.
							if (S3O3>=RxFREQ[l]-RxBandWidth[l]/2.0 && S3O3<=RxFREQ[l]+RxBandWidth[l]/2.0)
							{
								S3flag = FALSE;
								str.Format(_Z("Order 3:")+"     %d%c( %f ) %d%c( %f ) +%d%c( %f ) = %f",1,_T(0xD7),TxFREQ[i],-1,_T(0xD7),TxFREQ[j],1,_T(0xD7),TxFREQ[k],RxFREQ[l]);
								m_LIST_OUT.AddString(str);	
							}
							if((m_Order==1)||(m_Order==2))
							{
								//5rd order interference test.
								if (S3O5>=RxFREQ[l]-RxBandWidth[l]/2.0 && S3O5<=RxFREQ[l]+RxBandWidth[l]/2.0)
								{
									S3flag = FALSE;
									str.Format(_Z("Order 5:")+"     %d%c( %f ) %d%c( %f ) +%d%c( %f ) = %f",2,_T(0xD7),TxFREQ[i],-2,_T(0xD7),TxFREQ[j],1,_T(0xD7),TxFREQ[k],RxFREQ[l]);
									m_LIST_OUT.AddString(str);	
								}
								if (S3O5A>=RxFREQ[l]-RxBandWidth[l]/2.0 && S3O5A<=RxFREQ[l]+RxBandWidth[l]/2.0)
								{
									S3flag = FALSE;
									str.Format(_Z("Order 5:")+"     %d%c( %f ) %d%c( %f ) %d%c( %f ) = %f",3,_T(0xD7),TxFREQ[i],-1,_T(0xD7),TxFREQ[j],-1,_T(0xD7),TxFREQ[k],RxFREQ[l]);
									m_LIST_OUT.AddString(str);	
								}
								if(m_Order==2)
								{
									//7rd order interference test.
									if (S3O7>=RxFREQ[l]-RxBandWidth[l]/2.0 && S3O7<=RxFREQ[l]+RxBandWidth[l]/2.0)
									{
										S3flag = FALSE;
										str.Format(_Z("Order 7:")+"     %d%c( %f ) %d%c( %f ) +%d%c( %f ) = %f",2,_T(0xD7),TxFREQ[i],-3,_T(0xD7),TxFREQ[j],2,_T(0xD7),TxFREQ[k],RxFREQ[l]);
										m_LIST_OUT.AddString(str);	
									}
									if (S3O7A>=RxFREQ[l]-RxBandWidth[l]/2.0 && S3O7A<=RxFREQ[l]+RxBandWidth[l]/2.0)
									{
										S3flag = FALSE;
										str.Format(_Z("Order 7:")+"     %d%c( %f ) %d%c( %f ) %d%c( %f ) = %f",4,_T(0xD7),TxFREQ[i],-2,_T(0xD7),TxFREQ[j],-1,_T(0xD7),TxFREQ[k],RxFREQ[l]);
										m_LIST_OUT.AddString(str);	
									}
									if (S3O7B>=RxFREQ[l]-RxBandWidth[l]/2.0 && S3O7B<=RxFREQ[l]+RxBandWidth[l]/2.0)
									{
										S3flag = FALSE;
										str.Format(_Z("Order 7:")+"     %d%c( %f ) %d%c( %f ) +%d%c( %f ) = %f",3,_T(0xD7),TxFREQ[i],-3,_T(0xD7),TxFREQ[j],1,_T(0xD7),TxFREQ[k],RxFREQ[l]);
										m_LIST_OUT.AddString(str);	
									}
								}
							}

						}
					}
		if(S3flag)
		{
		str.Format("         " + _Z("---------- NOT FOUND -------"));
			m_LIST_OUT.AddString(str);	
		}
	}
	delete [] TxFREQ;
	delete [] RxFREQ;
	delete [] RxBandWidth;

	UpdateData(false);

//	CDialog::OnOK();
}

void CInterModDLG::OnAddTx() 
{
	CAddFreqDLG dlg;
	dlg.m_Flag = FALSE;
	if(dlg.DoModal()==IDOK)
		if(dlg.m_Freq != 0)
		{
			CString str;
			str.Format("%f",dlg.m_Freq);
			m_LIST_Tx.AddString(str);
		}	
}

void CInterModDLG::OnAddRx() 
{
	CAddFreqDLG dlg;
	dlg.m_Flag = TRUE;
	if(dlg.DoModal()==IDOK)
		if((dlg.m_Freq != 0)&&(dlg.m_BW != 0))
		{
			CString str;
			str.Format("%f    ,    %f",dlg.m_Freq,dlg.m_BW);
			m_LIST_Rx.AddString(str);	
		}	
}

void CInterModDLG::OnDeleteTx() 
{
	int i = m_LIST_Tx.GetCurSel();	
	if(i>-1)
		m_LIST_Tx.DeleteString(i);	
}

void CInterModDLG::OnDeleteRx() 
{
	int i = m_LIST_Rx.GetCurSel();	
	if(i>-1)
		m_LIST_Rx.DeleteString(i);	
}

void CInterModDLG::OnRadioS2() 
{
	m_Signal = FALSE;
}

void CInterModDLG::OnRadioS3() 
{
	m_Signal = TRUE;	
}

void CInterModDLG::OnRadioO3() 
{
	m_Order=0;		
}

void CInterModDLG::OnRadioO5() 
{
	m_Order=1;		
}

void CInterModDLG::OnRadioO7() 
{
	m_Order=2;		
}

void CInterModDLG::OnSave() 
{
	CString str;	str.Format("%s.txt","INTERMOD");
//	char strFilter[] = { "text Files (*.txt)|*.txt|All Files (*.*)|*.*||"};
	CString strFilter =  _Z("text Files") + " (*.txt)|*.txt|" + _Z("All Files") + " (*.*)|*.*||";

	CFileDialog FileDLG(FALSE, ".txt", str, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter);
	if (FileDLG.DoModal() == IDOK)
	{
		FILE *fp=fopen(FileDLG.GetPathName(),"wt");
		if(fp)
		{
			fputs(_Z("HARMONIC - INTERMODULATION ANALYSIS OUTPUT REPORT \n"),fp);
			fputs("-------------------------------------------------------------------------------------\n",fp);
			fputs(_T("                      ") + _Z("Calculation Parameters :\n"),fp);
			fputs("-------------------------------------------------------------------------------------\n",fp);
			int numTxFREQ = m_LIST_Tx.GetCount();
			int numRxFREQ = m_LIST_Rx.GetCount();
			int numOUT = m_LIST_OUT.GetCount();

			int i,k;CString str;
			fputs(_Z("Transmitter frequency(MHz) :") + "\n",fp);
			for( i=0;i<numTxFREQ;i++)
			{
				m_LIST_Tx.GetText(i,str);
				fprintf(fp,"%s    ",str);
			}
			fputs(" \n",fp);
			fputs(_Z("Receiver frequency(MHz) :") + "\n",fp);
			for( i=0;i<numRxFREQ;i++)
			{
				m_LIST_Rx.GetText(i,str);
				k = str.Find(",",0);
				fprintf(fp,"%s    ",str.Left(k));
			}
			fputs(" \n",fp);
			fputs(_Z("Receiver bandwidth(kHz) :") + "\n",fp);
			for( i=0;i<numRxFREQ;i++)
			{
				m_LIST_Rx.GetText(i,str);
				k = str.Find(",",0);
				fprintf(fp,"%s    ",str.Mid(k+1));
			}
			fputs(" \n",fp);
			fputs("-------------------------------------------------------------------------------------\n",fp);
			fputs("                      "+_Z("Results :")+"\n",fp);
			fputs("-------------------------------------------------------------------------------------\n",fp);

			for( i=0;i<numOUT;i++)
			{
				m_LIST_OUT.GetText(i,str);
				fprintf(fp,"%s\n",str);
			}
			fclose(fp);
		}
		ShellExecute(m_hWnd, "open", FileDLG.GetPathName(), NULL, NULL, SW_SHOWNORMAL);
	}	
}

void CInterModDLG::OnAddTxDB() 
{
	CDataBaseLDLG datadlg;
	if (datadlg.DoModal()==IDOK)
	{
		int Nrow = ((CSMS4DCApp *)AfxGetApp())->Nrow;
		if(Nrow>=1)
		{
			CString m_Sel;
			for (int i=0;i<Nrow;i++)
			{
				m_Sel = ((CSMS4DCApp *)AfxGetApp())->m_Sel[i];
				m_LIST_Tx.AddString(GetFld(m_Sel,6));

			}
		}
	}
}

void CInterModDLG::OnAddRxDB() 
{
	CDataBaseLDLG datadlg;
	if (datadlg.DoModal()==IDOK)
	{
		int Nrow = ((CSMS4DCApp *)AfxGetApp())->Nrow;
		if(Nrow>=1)
		{
			CString m_Sel,str;
			for (int i=0;i<Nrow;i++)
			{
				m_Sel = ((CSMS4DCApp *)AfxGetApp())->m_Sel[i];

				str.Format("%s    ,    %f",GetFld(m_Sel,6),25.0);
				m_LIST_Rx.AddString(str);
			}

		}
	}

}

CString CInterModDLG::GetFld(CString Src,int N)
{
	CString Fld = "";
	int place=0,Cnt=0;
	while( place <= Src.GetLength())
	{
		Fld="";
		for(int j = place ; j<=Src.GetLength();j++)
		{
			if(Src.Mid(j, 1) == ",") break;
			Fld = Fld + Src.Mid(j, 1);
		}//end for
		Cnt++;
		place = j + 1;
		if(Cnt==N) break;
	}//end while
	return Fld;
}

void CInterModDLG::OnAddTx2Rx() 
{
	int numTxFREQ = m_LIST_Tx.GetCount();
	CString strTx,strRx;
	for(int i=0;i<numTxFREQ;i++)
	{
		m_LIST_Tx.GetText(i,strTx);
		strRx.Format("%s    ,    %f",strTx,25.0);
		m_LIST_Rx.AddString(strRx);
	}
}

void CInterModDLG::OnAddRx2Tx() 
{
	int k;
	int numRxFREQ = m_LIST_Rx.GetCount();
	CString strTx,strRx;
	for(int i=0;i<numRxFREQ;i++)
	{
		m_LIST_Rx.GetText(i,strRx);
		k = strRx.Find(",",0);
		strTx.Format("%s",strRx.Left(k));
		m_LIST_Tx.AddString(strTx);
	}
}

void CInterModDLG::OnDeleteTxAll() 
{
	m_LIST_Tx.ResetContent();
}

void CInterModDLG::OnDeleteRxAll() 
{
	m_LIST_Rx.ResetContent();
}
