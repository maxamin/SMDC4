#include <windows.h>               /* for all Window apps                  */
#include <stdio.h>                 /* for sscanf()                         */
#include <string.h>                /* for strcpy()                         */
#include <ctype.h>                 /* for isxdigit() isascii()             */
#include "spromeps.h"              /* SuperPro API function prototypes     */
#include "sproeval.h"
#include  "resource.h"              /* resource defines                     */

#if (defined(WIN32) || defined(_WIN32) || defined(_WIN32_))
#undef _WIN32_
#define _WIN32_
#endif

#if     defined(_MSC_VER)          /* Microsoft C/C++ compiler             */
#ifdef _WIN32_
#define EXPORT
#else                              /* for WIN16                            */
#define EXPORT _export             /* for exported callback routines       */
#endif
#elif  defined(__BORLANDC__)       /* Borland C/C++ Compiler               */
#define EXPORT _export             /* for exported callback routines       */
#endif

#if    defined(__cplusplus)
#define EXPORT_PROC    extern "C"
#else
#define EXPORT_PROC    extern
#endif
#define LOCAL_PROC     static

#define START_EVAL      0x1234     /* Message to start eval program        */
#define PPROC           FARPROC    /* for MakeProcInstance()               */

#ifdef _WIN32_
#define MESSAGE         UINT
#define GET_LOWORD(param) LOWORD(param)
#define GET_HIWORD(param)  HIWORD(param)
#else                              /* Windows 16 bit                       */
#define MESSAGE         WORD
#define WPARAM          WORD
#define GET_LOWORD(param)  param
#define GET_HIWORD(param)   param
#endif

#define STR_BUF_SIZE     255

#ifdef _WIN32_
#define xFreeProcInstance( param )
#else
#define xFreeProcInstance( param )   FreeProcInstance( param )
#endif
// Constant Defination for input validation




RB_SPRO_APIPACKET      ApiPack;								 /* SuperPro packet						*/
RBP_SPRO_APIPACKET     ApiPacket	= &ApiPack; 

 
RB_WORD gKeySize							= 0;		 			   
RB_WORD gDevID								= 19777;			 /* Developer ID						 */
RB_WORD gWritePW							= 22924;			 /* Write password						 */
RB_WORD gOverwritePW1						= 0;			 /* Overwrite password1					 */
RB_WORD gOverwritePW2						= 0;			 /* Overwrite password2					 */
RB_WORD gActivatePW1						= 0;
RB_WORD gActivatePW2						= 0;
RB_WORD gActivateCell						= 0;
RB_WORD gDecCell							= 0;
RB_WORD gOwValue							= 0;
RB_WORD gOwCell								= 0;
RB_BYTE gOwAccessCode						= (RB_BYTE)-1;
RB_WORD gQCell								= (RB_WORD)-1;    
RB_WORD gQrySize							= 0;  
RB_BYTE gQData[ SPRO_MAX_QUERY_SIZE + 1]	= "";    
RB_BYTE gQResult[ SPRO_MAX_QUERY_SIZE + 1]	= "";  
RB_DWORD gQResult32							= 0;
RB_WORD gRCell								= (RB_WORD)-1;
RB_WORD gRData								= (RB_WORD)-1;
RB_WORD gWCell								= (RB_WORD)-1;
RB_WORD gWData								= (RB_WORD)-1;
RB_BYTE gWAccessCode						= (RB_BYTE)-1;
RB_WORD gXRCell								= (RB_WORD)-1;
RB_WORD gXRData								= (RB_WORD)-1;
RB_BYTE gXRAccessCode						= (RB_BYTE)-1;
RB_WORD gLCell								= (RB_WORD)-1;
RB_WORD gSCell								= (RB_WORD)-1;
HANDLE  ghInst;											     /* Current instance handle              */
HANDLE  ghHourGlassCursor;								     /* Handle to the hour glass cursor      */
HWND    ghWndMain;										     /* Main Window Handle                   */
HWND    ghMainDlg							= NULL;          /* Main Dialog window                   */
HWND    ghViewDlg							= NULL;          /* View Dialog window                   */
HWND	ghGetKeyTypeDlg						= NULL;			 /* GetKey Type Dialog Window	   	     */
HWND    ghCurrentDlg						= NULL;			 /* The current modeless dialog          */
char    gAppName[]							= "SUPERPRO";    /* Application name                     */
char    gString[STR_BUF_SIZE]				= "";			 /* generic string                       */
char    gMsg[STR_BUF_SIZE]					= ""; 
char tempstr[STR_BUF_SIZE]					= "";			 /* Another generic string				 */
char    gStatus[STR_BUF_SIZE]				= "";			 /* Status string						 */
char    gResult[STR_BUF_SIZE]				= "";			 /* Result string						 */
char    gFullStatus[STR_BUF_SIZE]			= "";			 /* Extended Status string				 */
char    gViewText[STR_BUF_SIZE]				= "";			 /* String for View dialog box			 */

WORD    xCommand							= IDC_SET_CFG_RB;
WORD    xFunc								= IDC_DRVR_TYPE_FUNC_RB;
RB_WORD RADIOCHECKED;
RB_BYTE IsInitialized						= 0;			 /* Will help to release the Memory if the pkt has been initialized. */

/* function prototypes */
LOCAL_PROC 
void FormatErrStr( LPSTR         theString,
                   int           idsIdx,
                   SP_STATUS     spStatus,
                   RB_WORD       spFullStatus );
LOCAL_PROC
void UpdateQueryDlg( HWND hWndDlg,
                     RB_WORD qCell,
                     RBP_BYTE qData,
                     RBP_BYTE qResult,
                     RB_DWORD qResult32,
                     RB_WORD  qrySize );

LOCAL_PROC
void UpdateViewLB( HWND hWndDlg );
LOCAL_PROC
void ToggleButton( HWND hWnd, WORD theButton );
LOCAL_PROC
BOOL InitApplication( HANDLE hInstance );
LOCAL_PROC
BOOL InitInstance( HANDLE hInstance, int nCmdShow );
LOCAL_PROC
void CenterWindow( HWND hWnd, int  top );
LOCAL_PROC
unsigned int ConvertBufferToHex( PSTR buffer, unsigned int bufLen );
LOCAL_PROC
WORD ValidateQryStr( LPSTR qData, WORD len );
LOCAL_PROC
void ErrorMsg( HWND hWnd, LPSTR msgText );
LOCAL_PROC
WORD GetDlgItemWord( HWND hWnd, WORD cntrlID, WORD *theData,WORD length );
LOCAL_PROC
BOOL GetCellAddress( HWND hWnd, WORD cntrlID, WORD *theCell , LPCTSTR title);
LOCAL_PROC
BOOL GetWritePassword( HWND hWnd, WORD cntrlID, WORD *thePW, LPCTSTR title,WORD length );
LOCAL_PROC
BOOL GetActivate1Password( HWND hWnd, WORD cntrlID, WORD *thePW , LPCTSTR title,WORD length);
LOCAL_PROC
BOOL GetActivate2Password( HWND hWnd, WORD cntrlID, WORD *thePW, LPCTSTR title ,WORD length);
LOCAL_PROC
BOOL GetOverwrite2Password( HWND hWnd, WORD cntrlID, WORD *thePW , LPCTSTR title,WORD length);
LOCAL_PROC
BOOL GetOverwrite1Password( HWND hWnd, WORD cntrlID, WORD *thePW , LPCTSTR title,WORD length);
LOCAL_PROC
BOOL GetNumLicValue( HWND hWnd, WORD cntrlID, WORD *theData, LPCTSTR title ,WORD length);
LOCAL_PROC
BOOL GetDataValue( HWND hWnd, WORD cntrlID, WORD *theData, LPCTSTR title );
LOCAL_PROC
BOOL GetWriteDataValue( HWND hWnd, WORD cntrlID, WORD *theData,LPCTSTR title,WORD length );
LOCAL_PROC
BOOL GetAccessCode( HWND hWnd, WORD cntrlID, BYTE *theAC , LPCTSTR title);
LOCAL_PROC
WORD GetNumSubLicValue( HWND hWnd, WORD cntrlID, WORD *theData,WORD length );
LOCAL_PROC
BOOL GetSetHeartBeatValue( HWND hWnd, WORD cntrlID, DWORD *theData,LPCTSTR title,WORD length );
LOCAL_PROC
WORD GetHeartBeatValue( HWND hWnd, WORD cntrlID, DWORD *theData,WORD length );
LOCAL_PROC
WORD GetNumServerValue( HWND hWnd, WORD cntrlID, WORD *theData,WORD length );
LOCAL_PROC
BOOL GetNumServer( HWND hWnd, WORD cntrlID, WORD *theData,LPCTSTR title,WORD length );

LOCAL_PROC
void KeyView( HWND hWndDlg, RB_WORD rKeySize );
LOCAL_PROC
void ResetPW( void );
LOCAL_PROC
BOOL ProcessPhyAddr( HWND hWndDlg, WORD * portAddr );
LOCAL_PROC
BOOL ProcessLogPort( HWND hWndDlg, WORD * logPortNum );
LOCAL_PROC
BOOL ProcessSysPort( HWND hWndDlg, WORD * sysPortNum );
LOCAL_PROC
BOOL ProcessDevRetryCount( HWND hWndDlg, WORD * drc);
LOCAL_PROC
BOOL ProcessContRetryCount( HWND hWndDlg, WORD * prc);
LOCAL_PROC
BOOL ProcessContRetryInterval( HWND hWndDlg, DWORD * pri);

EXPORT_PROC
BOOL WINAPI GetKeyTypeMsgProc(HWND    hWndDlg,
                               MESSAGE Message,
                               WPARAM  wParam,
                               LPARAM  lParam ); 
EXPORT_PROC
BOOL WINAPI VERSIONMsgProc( HWND    hWndDlg,
                               MESSAGE Message,
                               WPARAM  wParam,
                               LPARAM  lParam );
EXPORT_PROC
BOOL WINAPI ACTIVEMsgProc( HWND    hWndDlg,
                               MESSAGE Message,
                               WPARAM  wParam,
                               LPARAM  lParam );
EXPORT_PROC
BOOL WINAPI DECREMsgProc( HWND    hWndDlg,
                              MESSAGE Message,
                              WPARAM  wParam,
                              LPARAM  lParam );
EXPORT_PROC
BOOL WINAPI FINDMsgProc( HWND    hWndDlg,
                             MESSAGE Message,
                             WPARAM  wParam,
                             LPARAM  lParam );
EXPORT_PROC
BOOL WINAPI OWRITEMsgProc( HWND    hWndDlg,
                               MESSAGE Message,
                               WPARAM  wParam,
                               LPARAM  lParam );
EXPORT_PROC
BOOL WINAPI QUERYMsgProc( HWND    hWndDlg,
                              MESSAGE Message,
                              WPARAM  wParam,
                              LPARAM  lParam );
EXPORT_PROC
BOOL WINAPI SETContactSrvProc( HWND    hWndDlg,
                              MESSAGE Message,
                              WPARAM  wParam,
                              LPARAM  lParam );
EXPORT_PROC
BOOL WINAPI GETContactSrvProc( HWND    hWndDlg,
                              MESSAGE Message,
                              WPARAM  wParam,
                              LPARAM  lParam );
EXPORT_PROC
BOOL WINAPI SETProtocolProc(HWND hWndDlg,
								MESSAGE message,
								WPARAM wParam,
								LPARAM lParam);

EXPORT_PROC
BOOL WINAPI RELEASEMsgProc( HWND    hWndDlg,
                             MESSAGE Message,
                             WPARAM  wParam,
                             LPARAM  lParam );


EXPORT_PROC
BOOL WINAPI GetSubLicMsgProc( HWND    hWndDlg,
                             MESSAGE Message,
                             WPARAM  wParam,
                             LPARAM  lParam );
EXPORT_PROC
BOOL WINAPI ENUMSRVRMsgProc( HWND    hWndDlg,
                             MESSAGE Message,
                             WPARAM  wParam,
                             LPARAM  lParam );

EXPORT_PROC
BOOL WINAPI GetKeyInfoMsgProc( HWND    hWndDlg,
                               MESSAGE Message,
                               WPARAM  wParam,
                               LPARAM  lParam );

EXPORT_PROC
BOOL WINAPI READMsgProc( HWND    hWndDlg,
                             MESSAGE Message,
                             WPARAM  wParam,
                             LPARAM  lParam );

EXPORT_PROC
BOOL WINAPI WRITEMsgProc( HWND    hWndDlg,
                              MESSAGE Message,
                              WPARAM  wParam,
                              LPARAM  lParam );
EXPORT_PROC
BOOL WINAPI XREADMsgProc( HWND    hWndDlg,
                              MESSAGE Message,
                              WPARAM  wParam,
                              LPARAM  lParam );
EXPORT_PROC
BOOL WINAPI VIEWMsgProc( HWND    hWndDlg,
                             MESSAGE Message,
                             WPARAM  wParam,
                             LPARAM  lParam );

EXPORT_PROC
BOOL WINAPI MAINMsgProc( HWND    hWndDlg,
                             MESSAGE Message,
                             WPARAM  wParam,
                             LPARAM  lParam );
EXPORT_PROC
LRESULT WINAPI WndProc( HWND    hWnd,
                         MESSAGE Message,
                         WPARAM  wParam,
                         LPARAM  lParam );
int PASCAL WinMain( HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR  lpszCmdLine,
                    int    nCmdShow );
