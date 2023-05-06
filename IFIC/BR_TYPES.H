/*    This file, "br_types.h", contains some definitions of types
**    This is the version for use with OSF/1, WATCOM C/C++32,
**    Microsoft Visual C++, or BORLAND C++.
**
**    **************
**    * IMPORTARNT *
**    **************
**
**	THIS FILE, WHEN APPLICABLE, SHOULD BE INCLUDED AFTER ALL STANDARD
**      INCLUDE FILES (E.G., WINDOWS.H).
*/
#ifndef __BR_TYPES_H
#define __BR_TYPES_H

/* _WINDOWS is from MS and __WINDOWS_H from Borland */
#if defined _WINDOWS || defined __WINDOWS_H
	#define __BR_WINDOWS
#endif

#if defined __WATCOMC__ || defined __osf__

    typedef short int     INT16;       // 16-bit integers
    typedef int           INT32;       // 32-bit integers
    typedef unsigned char UCHAR;       // to save typing a lot
    typedef int           BOOL;        // values of TRUE or FALSE

#elif defined _MSC_VER || defined __BORLANDC__

 #ifndef _WIN32
    typedef int           INT16;       // 16-bit integers
    typedef long int      INT32;       // 32-bit integers
 #else
    typedef short int     INT16;       // 16-bit integers
    typedef int           INT32;       // 32-bit integers
 #endif

#else
#error Unanticipated Compiler
#endif

typedef INT32             CSTATUS;  // For status returns to/from C or C++

// pointers types
typedef INT16     *    PINT16;
typedef UCHAR     *    PUCHAR;
typedef CSTATUS   *    PCSTATUS;

#if defined __WATCOMC__ || defined __osf__
    typedef INT16       *  LPINT16;
    typedef UCHAR       *  LPUCHAR;
    typedef CSTATUS     *  LPCSTATUS;

#elif defined _MSC_VER || defined __BORLANDC__
    typedef INT16   far *  LPINT16;
    typedef UCHAR   far *  LPUCHAR;
    typedef CSTATUS far *  LPCSTATUS;

#else
#error Unanticipated Compiler
#endif

// including types for fortran
#if !defined __BR_FORTRAN_TYPES_H
#include "brfortyp.h"
#endif


#endif

/*    End of "br_types.h"     */
