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


unsigned int ConvertBufferToHex( PSTR buffer, unsigned int bufLen )
{
  unsigned int i,j;
   char                  hexBuffer[SPRO_MAX_QUERY_SIZE+2];

   /** Check for even length buffer **/
   if ( !(bufLen & 0xFFFE) || (bufLen/2) > sizeof(hexBuffer) )  return( 0 );

   for ( i = j = 0; i <= bufLen; j++)
   {
        sscanf( &buffer[i], "%2hx", (unsigned short int *)&(hexBuffer[ j ]) ) ;
        i = i + 2 ;
   }
   for( i=0; i < j; i++ ) buffer[ i ] = hexBuffer[ i ];
   i--;
   return( i );
} /* end ConvertBufferToHex */

BOOL CheckLock()
{
	RB_SPRO_APIPACKET      ApiPack;								 /* SuperPro packet						*/
	RBP_SPRO_APIPACKET     ApiPacket	= &ApiPack; 

 
	RB_WORD gDevID								= 4601;			 /* Developer ID						 */
	char Alg[100][2][10]={
	{"B45E3F30", "B5F41D49"},
	{"0D1AF58E", "254BE730"},
	{"B323245D", "5C07C564"},
	{"72A98F66", "8CB0A407"},
	{"BAE5D9CF", "88E9DEB0"},
	{"EB4FEAEF", "CA53FF0E"},
	{"CF119561", "DA30B574"},
	{"68BB7757", "E97567CD"},
	{"ED382231", "6E08030D"},
	{"0F017B4F", "1BB6E026"},
	{"80906023", "73775C10"},
	{"B6188E8A", "C81D944C"},
	{"ED73C25C", "7BF54DBB"},
	{"6B5C1F41", "C59BA206"},
	{"07DED0C7", "3D643B32"},
	{"EC0CEEB2", "35D4B50D"},
	{"9BF3A494", "6DD093B8"},
	{"2FCD919D", "0B76F809"},
	{"E5786DB3", "48782F0C"},
	{"DB26F0C5", "026E2B36"},
	{"1855EF5D", "9AFF86CB"},
	{"CD02C975", "F26903AE"},
	{"DA19018C", "963E333B"},
	{"94312CF9", "51013558"},
	{"C6760E7E", "6BFEE84A"},
	{"F6E620E9", "CA33EA97"},
	{"C1943669", "030E50BB"},
	{"3A7CC145", "271DA929"},
	{"73A8FB9A", "C389EEE4"},
	{"A8AF3351", "B4C12392"},
	{"AB70D7E9", "10FEDC7D"},
	{"90F9D376", "B0A7D3CC"},
	{"A9A819EA", "159AFEE9"},
	{"B58F8194", "08AF13BA"},
	{"541DD4E6", "92BC8D7D"},
	{"BEFB237B", "162A2C65"},
	{"B5355E59", "5FD2759A"},
	{"B89A2273", "EC11374A"},
	{"7A65D172", "4703776B"},
	{"921DE8B4", "A7F1A8DA"},
	{"74B98D95", "8F788404"},
	{"A00868EE", "7371F326"},
	{"1950B4DC", "8D1E5555"},
	{"193696C3", "5060B94A"},
	{"03DDAD92", "C6CD3B67"},
	{"9952EA48", "4F748DD2"},
	{"6F28A2B7", "2BDD0D05"},
	{"9F5FE187", "7814A716"},
	{"BF8B027F", "5A18259D"},
	{"10317CF8", "E818C982"},
	{"75FFD2B3", "3484EDC0"},
	{"F2C02445", "4072FCF0"},
	{"EA11CDB3", "E62FE06B"},
	{"9F34D872", "11DE201D"},
	{"71402088", "AB3ECE13"},
	{"66F87264", "1FA4B306"},
	{"9F2E6ED4", "352184DE"},
	{"66D1DAD3", "F784D8FF"},
	{"DC51F4FA", "077F13A3"},
	{"49A663A2", "4DB99F88"},
	{"B1936E49", "BF633373"},
	{"A82C6C37", "9823CBFA"},
	{"66967B60", "0CF9AAFA"},
	{"1E0E758D", "69A2D9C4"},
	{"8C2C20B7", "7B47A4FC"},
	{"CE69A5B3", "C10A44EB"},
	{"74E04415", "D2E14329"},
	{"DA51454E", "E4F49C48"},
	{"B66B3217", "2BDC9BD0"},
	{"ED4B4313", "FE678DE5"},
	{"AB401AAF", "3462EE7B"},
	{"B2D1B04E", "6F71C270"},
	{"F20190A3", "EDFB990F"},
	{"5AD1435D", "7DEDFEF9"},
	{"EF070B0A", "2B079C40"},
	{"1B2ED435", "B161B904"},
	{"47DE67D2", "52BF1546"},
	{"AC3DE1DD", "1635CF42"},
	{"65C6633D", "58CB47BA"},
	{"C9490CEE", "CC8076B9"},
	{"F933245F", "98CDF5B8"},
	{"B5109A19", "BB01EED0"},
	{"744EB1A2", "69CDC3CA"},
	{"B344F6A1", "CCF00A34"},
	{"8D737542", "E5DF251D"},
	{"8C0B2CDC", "4E6CE08C"},
	{"BFB1C0D2", "BCFC0183"},
	{"0C7F6FB7", "347CC011"},
	{"C84C46B5", "C5965D67"},
	{"852E942F", "7F0FDE7C"},
	{"2B3E9EA5", "9013647D"},
	{"4B9B94D8", "A595EDAC"},
	{"AFB2C42F", "E705C67C"},
	{"36BC0E5A", "2A58F990"},
	{"DF879835", "75A8F53E"},
	{"237AC3EF", "67215246"},
	{"88D45D6B", "BF01D7F5"},
	{"733418E6", "D96771DF"},
	{"3D5E3ADB", "AA453612"},
	{"8A3C9723", "9237CC9D"}
	};
   BOOL status = FALSE;
   static bool FirstTime=true;
   RB_WORD   qCell=0x0A;
   RB_BYTE   qResult[ SPRO_MAX_QUERY_SIZE + 1 ];
   RB_DWORD  qResult32;
   RB_WORD   qrySize=8;
   if(FirstTime)
   {
	   srand(5000);
	   FirstTime=false;
   }
   status = RNBOsproFormatPacket( ApiPacket, sizeof( ApiPack ));  
   if ( status == SP_SUCCESS )  
   {
	   status = RNBOsproInitialize( ApiPacket );
	   if ( status == SP_SUCCESS )
	   {
		   status = RNBOsproFindFirstUnit( ApiPacket, gDevID );
		   if ( status == SP_SUCCESS )
		   {
			   int row=rand()/330, i;
			   char * cp, gString[100];
               qrySize = (WORD)ConvertBufferToHex( (PSTR)Alg[row][0], qrySize );
			   status = RNBOsproQuery( ApiPacket,qCell,(RBP_VOID)Alg[row][0],(RBP_VOID)qResult,&qResult32,qrySize );
			   for ( i = 0, cp = gString; i < qrySize; i++, cp += 2 )
				   wsprintf( cp, "%02X", qResult[i] );
			   gString[(qrySize<<2)+1] = '\0';
			   if ( status == SP_SUCCESS )
			   {
					status=strcmp((char *)gString,Alg[row][1]);
			   }
		   }
	   }
	}
   return status;
}