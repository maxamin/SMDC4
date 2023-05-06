// HTML_Report.cpp: implementation of the CHTML_Report class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HTML_Report.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHTML_Report::CHTML_Report(BOOL FOOTflag,CString sTitle, CString sAuthor, CString sTableCaption,
					 CString sMarqueeText, CString sLink, CString sLinkText,
					 CString sBkColor, CString sTextColor, 
					 CString sHeaderBkColor, CString sTableBkColor)
{
	m_HTML_sTitle = sTitle;
	m_HTML_sAuthor = sAuthor;
	m_HTML_MarqueeText = sMarqueeText;
	m_HTML_sBkColor = sBkColor;
	m_HTML_sTextColor = sTextColor;
	m_HTML_sTableCaption = sTableCaption;
	m_HTML_sHeaderBkColor = sHeaderBkColor;
	m_HTML_sTableBkColor = sTableBkColor;
	m_HTML_iColumns = 0;
	m_HTML_sLink = sLink;
	m_HTML_sLinkText = sLinkText;

	m_foot=FOOTflag;

	InitHTMLHEAD();
	if(!m_HTML_MarqueeText.IsEmpty())
		InitMARQUEE();

	InitTABLEBODY();
	InitTABLEFOOT(m_foot);
	GetTableHeadLine();
	GetTableBodyLine();
}

CHTML_Report::~CHTML_Report()
{
}

void CHTML_Report::GetTableHeadLine()
{
	int iTB = m_HTML_sTableBody.Find("<th valign");
	int iTE = m_HTML_sTableBody.Find("</th>");

	m_Tmp_sTableHeadLine = m_HTML_sTableBody.Mid(iTB, (iTE - iTB +5));
}

void CHTML_Report::GetTableBodyLine()
{
	int iTB = m_HTML_sTableBody.Find("<td valign");
	int iTE = m_HTML_sTableBody.Find("</td>");

	m_Tmp_sTableBodyLine = m_HTML_sTableBody.Mid(iTB, (iTE - iTB+5));
}


BOOL CHTML_Report::isEmail(CString &sString)
{
	CString sTmp;
	if(sString.Left(1) == "<" && sString.Right(1) == ">")
	{
		sString.Remove('<');
		sString.Remove('>');
		sTmp.Format("<a href=\"mailto:%%20%s\">%s</a>", sString, sString);
		sString = sTmp;
		return TRUE;
	}
	return FALSE;
}

void CHTML_Report::CreateFileHeader()
{
	m_HTML_sTableHead.Replace("#TITLE#", m_HTML_sTitle);
	m_HTML_sTableHead.Replace("#AUTHOR#", m_HTML_sAuthor);
	m_HTML_sTableHead.Replace("#BKCOLOR#", m_HTML_sBkColor);
	m_HTML_sTableHead.Replace("#TEXTCOLOR#", m_HTML_sTextColor);
	m_HTML_sTableHead.Replace("#CAPTION#", m_HTML_sTableCaption);

	// If there is some Marqueetext, put the whole marquee-stuff in the header:
	if(!m_HTML_sMarquee.IsEmpty())
		m_HTML_sTableHead.Replace("#MARQUEE#", m_HTML_sMarquee);
	else
		m_HTML_sTableHead.Replace("#MARQUEE#", "");

	m_HTML_sTemplateContainer = m_HTML_sTableHead + "\n";
}

// insert a full row to the Template container string:
int CHTML_Report::InsertTableHeader(int iItemNo, CString sFirstItem,...) 
{
	CreateFileHeader();
	m_HTML_iColumns = iItemNo;
	
	CString sItem, sTmp;
	sItem = sFirstItem;
	int iItemCount = 0;
	va_list marker;

   	m_HTML_sTemplateContainer += "\n<tr>\n";

	va_start(marker, sFirstItem);
	
	while(iItemNo > 0)	
	{
		sTmp = m_Tmp_sTableHeadLine;
		sTmp.Replace("#HEADLINE#", sItem);
		m_HTML_sTemplateContainer += sTmp + "\n";		
		// get the next variable argument(Item-String):
		sItem = va_arg(marker, char*);

		iItemCount++;
		iItemNo--;
	}
	va_end(marker);              /* Reset variable arguments.      */

   	m_HTML_sTemplateContainer += "\n</tr>\n";

return iItemCount;
}


int CHTML_Report::InsertTableHeader1(int iItemNo, CString *sFirstItem) 
{
	CreateFileHeader();
	m_HTML_iColumns = iItemNo;
	
	CString sItem, sTmp;
	int iItemCount = 0;

   	m_HTML_sTemplateContainer += "\n<tr>\n";
	for(int i=0;i<iItemNo ;i++)	
	{
		sTmp = m_Tmp_sTableHeadLine;
		sItem = sFirstItem[i];

		sTmp.Replace("#HEADLINE#", sItem);
		m_HTML_sTemplateContainer += sTmp + "\n";		

		sItem = sFirstItem[i];
		iItemCount++;
	}
   	m_HTML_sTemplateContainer += "\n</tr>\n";

	return iItemCount;
}



// insert a full row to the Template container string:
int CHTML_Report::InsertTableRow(CString sFirstItem,...)
{
	if(!m_HTML_iColumns) return 0;

	int iItemNo = m_HTML_iColumns;

	CString sItem, sTmp;
	sItem = sFirstItem;

	int iItemCount = 0;
	va_list marker;

   	m_HTML_sTemplateContainer += "\n<tr>\n";

	va_start(marker, sFirstItem);
	
	while(iItemNo > 0)	
	{
		sTmp = m_Tmp_sTableBodyLine;
		isEmail(sItem);
		sTmp.Replace("#CELLCONTENT#", sItem);
		m_HTML_sTemplateContainer += sTmp + "\n";		
		// get the next variable argument(Item-String):
		sItem = va_arg(marker, char*);

sItem = CString2UTF8(sItem);	//971212

		iItemCount++;
		iItemNo--;
	}
	va_end(marker);              /* Reset variable arguments.      */

   	m_HTML_sTemplateContainer += "\n</tr>\n";

	return iItemCount;
}

int CHTML_Report::InsertTableRow1(CString *sFirstItem)
{
	if(!m_HTML_iColumns) return 0;

	int iItemNo = m_HTML_iColumns;
	CString sItem, sTmp;
	int iItemCount = 0;

   	m_HTML_sTemplateContainer += "\n<tr>\n";
	for(int i=0;i<iItemNo ;i++)	
	{
		sTmp = m_Tmp_sTableBodyLine;
		sItem = sFirstItem[i];

sItem = CString2UTF8(sItem);	//971212

		isEmail(sItem);
		sTmp.Replace("#CELLCONTENT#", sItem);
		m_HTML_sTemplateContainer += sTmp + "\n";		

		iItemCount++;
	}
   	m_HTML_sTemplateContainer += "\n</tr>\n";

	return iItemCount;
}



void CHTML_Report::WriteHTMLFile(CString sFullPath)
{
	FILE *stream;

	m_HTML_sTemplateContainer += m_HTML_sTableFoot;

	if((stream = fopen(sFullPath, "wb")) != NULL)
	{
unsigned char BOM[3] = {0xEF, 0xBB, 0xBF};	//971212
fwrite(BOM,3,1,stream);

		// Get the File Length:
		UINT uiFileLength = (UINT) m_HTML_sTemplateContainer.GetLength();

		char *chMsg = m_HTML_sTemplateContainer.GetBuffer(uiFileLength);
	
		// write file
		m_num = (int) fwrite((const void *) m_HTML_sTemplateContainer, sizeof
							(char), m_HTML_sTemplateContainer.GetLength(), stream);

		m_HTML_sTemplateContainer.ReleaseBuffer(uiFileLength);
			
		fclose(stream);
	 }
}


// ***************** INITIALIZE CONSTANT HTML-STRINGS *****************

void CHTML_Report::InitHTMLHEAD()
{
	//	  <meta http-equiv=\"content-type\" content=\"text/html; charset=ISO-8859-1\">\n\	//971212

	m_HTML_sTableHead =
	"<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\"><html><head>\n\
	  <title>#TITLE#</title>\n\
	\n\
	  <meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\">\n\
	\n\
	  <meta name=\"author\" content=\"#AUTHOR#\">\n\
	</head><body bgcolor=\"#BKCOLOR#\" text=\"#TEXTCOLOR#\" link=\"#0000ee\" alink=\"#0000ee\" vlink=\"#551a8b\">\n\
	#MARQUEE#\
	<table width=\"95%\" border=\"1\" cellspacing=\"2\" cellpadding=\"2\" bgcolor=\"#ffffcc\" align=\"center\">\n\
	\n\
	\n\
	<caption><big><big><big><b><u><font color=\"#000000\">#CAPTION#</font><br></u></b></big></big></big><br></caption>\n\
	  <tbody>";
}

void CHTML_Report::InitMARQUEE()
{
/*
	m_HTML_sMarquee =
	"\n\
	<!--The scrolling text definition:   -->\n\
	<MARQUEE id=m1 direction=left BEHAVIOR=SCROLL SCROLLAMOUNT=2 SCROLLDELAY=5 \"width=\"95%\" height=25>\n\
	<!--The scrolling text: -->\n\
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;#SCROLLTEXT#</MARQUEE>\n\
	\n\n\
	<!--Here are Buttons to stop and restart the scrolling   -->\n\
	<CENTER>\n\
	<BUTTON onclick=\"m1.stop();\">Pause scrolling Text</BUTTON>\n\
	<BUTTON onclick=\"m1.start();\">Continue scrolling</BUTTON>\n\
	<hr>\n\
	</CENTER>\n\n";

	m_HTML_sMarquee.Replace("#SCROLLTEXT#", m_HTML_MarqueeText);
*/
	m_HTML_sMarquee =
	"<CENTER>\n\n\
	<caption><big><big><big><b><font color=\"#000000\">#SCROLLTEXT#</font><br></b></big></big></big></caption>\n\n\
	</CENTER>";

	m_HTML_sMarquee.Replace("#SCROLLTEXT#", m_HTML_MarqueeText);
}

void CHTML_Report::InitTABLEBODY()
{
	m_HTML_sTableBody =
	"              <tr>\n\
					<th valign=\"bottom\" bgcolor=\"#sHeaderBkColor#\" align=\"center\"><big>#HEADLINE#<br></big></th>\n\
				  </tr>\n\
				  <tr>\n\
					<td valign=\"middle\" bgcolor=\"#sTableBkColor#\" align=\"center\">#CELLCONTENT#<br></td>\n\
				  </tr>\n\
	\n\n";

	m_HTML_sTableBody.Replace("#sHeaderBkColor#", m_HTML_sHeaderBkColor);
	m_HTML_sTableBody.Replace("#sTableBkColor#", m_HTML_sTableBkColor);
}

void CHTML_Report::InitTABLEFOOT(BOOL FOOTflag)
{
	if(FOOTflag)
	{
		m_HTML_sTableFoot=
		"</tbody>\n\
		</table>\n\
		<br>\n\
		<br>\n\
		<br>\n\
		<br>\n\
		<br>\n\
		<font size=-3>\n\
		<CENTER>\n\
		<p><a href=\"#LINK#\">#LINKTEXT#</a></p>\n\
		<hr width = \"20%\"; heigth = \"5\">\n\
		#TIME#\n\
		</CENTER>\n\
		</body>\n</html>";

		CString sDateTime, sFooter;
		COleDateTime CurrentDate;
		CurrentDate = COleDateTime::GetCurrentTime();

		sDateTime = CurrentDate.Format(_Z("Date :  %d/%m/20%y    ,   Time :  %H:%M:%S"));
		sFooter.Format("%s", sDateTime);

		if(!m_HTML_sLink.IsEmpty())
		{
			m_HTML_sTableFoot.Replace("#LINK#", m_HTML_sLink);
			m_HTML_sTableFoot.Replace("#LINKTEXT#", m_HTML_sLinkText);
		}
		else	m_HTML_sTableFoot.Replace("<p><a href=\"#LINK#\">#LINKTEXT#</a></p>","");
		m_HTML_sTableFoot.Replace("#TIME#", sFooter);
	}
	else
	{
		m_HTML_sTableFoot=
		"</tbody>\n\
		</table>\n\
		<br>\n\
		</body>\n</html>";
	}
}

//971212
char* CHTML_Report::CString2UTF8(CString& strSrc)		
{   
	long lSrcLen      =  strSrc.GetLength()  ;     
	long lBufferSize  =  lSrcLen*  3  +  1  ;  

   //Don't forget to release the buffer   
	char  *pCharUtf8  =  new  char[lBufferSize]  ;   
	
	//Translate  using  code  page  65001(UTF-8).     
	long lResult =  WideCharToMultiByte(CP_UTF8,  0,strSrc.AllocSysString(),  lSrcLen,  pCharUtf8, lBufferSize,  NULL,  0)  ;      
	pCharUtf8[lResult ]  =  NULL  ;    
	return pCharUtf8;
}