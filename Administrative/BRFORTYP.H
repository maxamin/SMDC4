/*********************************************************************
/* This file contains the definitions that are needed to properly call
/* Fortran routines from C/C++, taking into account the used compiler
/*********************************************************************/

#if !defined __BR_FORTRAN_TYPES_H
#define __BR_FORTRAN_TYPES_H

#if !defined __BR_TYPES_H

#if defined __WATCOMC__ || defined __osf__

    typedef short int     INT16;       // 16-bit integers
    typedef int           INT_32;       // 32-bit integers
    typedef unsigned char UCHAR;       // to save typing a lot
    typedef int           BOOL;        // values of TRUE or FALSE

#elif defined _MSC_VER || defined __BORLANDC__

 #ifndef WIN32
    typedef int           INT16;       // 16-bit integers
    typedef long int      INT_32;       // 32-bit integers
 #else
    typedef short int     INT16;       // 16-bit integers
    typedef long int      INT_32;       // 32-bit integers
 #endif

#else
#error Unanticipated Compiler
#endif

#endif // __BR_TYPES_H

//*********************** NEEDED FORTRAN DATA TYPES *****************//

typedef INT_32         FSTATUS;     // For status returns to/from FORTRAN
typedef INT_32         FINT;        // FORTRAN INTEGER
typedef INT_32         FINT4;       // FORTRAN INTEGER*4
typedef INT16         FINT2;       // FORTRAN INTEGER*2
typedef float         FREAL;       // FORTRAN real number
typedef double        FDOUBLE;     // FORTRAN double precision
typedef INT_32         FLOG;        // FORTRAN logical

// associated pointers
#if defined __WATCOMC__ || defined __osf__
   typedef FSTATUS        *  LPFSTATUS;
   typedef FINT           *  LPFINT;
   typedef FINT4          *  LPFINT4;
   typedef FINT2          *  LPFINT2;
   typedef FREAL          *  LPFREAL;
   typedef FDOUBLE        *  LPFDOUBLE;
   typedef FLOG           *  LPFLOG;

#elif defined _MSC_VER || defined __BORLANDC__
   typedef FSTATUS   far  *  LPFSTATUS;
   typedef FINT      far  *  LPFINT;
   typedef FINT4     far  *  LPFINT4;
   typedef FINT2     far  *  LPFINT2;
   typedef FREAL     far  *  LPFREAL;
   typedef FDOUBLE   far  *  LPFDOUBLE;
   typedef FLOG      far  *  LPFLOG;

#else
#error Unanticipated Compiler
#endif

// now working with fortran charcters
// Here, we define the C equivalent of FORTRAN characters
#if defined __WATCOMC__

//  With WATCOM, we pass a structure containing a pointer to the character string and its length
    typedef unsigned int  FCHAR_LEN;   // Length of FORTRAN character argument
    typedef struct {
        UCHAR       *addr;
        FCHAR_LEN    len;
    } FCHAR;

#elif defined __osf__

//  With OSF/1, we pass two arguments:  the character string and its length
    typedef int           FCHAR_LEN;   // Length of FORTRAN character argument
    typedef UCHAR         FCHAR;       // FORTRAN character

#elif defined _MSC_VER || defined __BORLANDC__

// with Microsoft
    typedef int           FCHAR_LEN;   // Length of FORTRAN character argument
    typedef UCHAR         FCHAR;       // FORTRAN character

#else
#error Unanticipated Compiler
#endif

#if defined __WATCOMC__ || defined __osf__
typedef FCHAR	    * LPFCHAR;

#elif defined _MSC_VER || defined __BORLANDC__
typedef FCHAR	far * LPFCHAR;

#else
#error Unanticipated Compiler
#endif

// the following macros are defined to overcome
// fortran character string parameters passing from C
// when using Microsoft visual C++
#ifdef _MSC_VER
 
  #ifndef __BR_VBCHAR
   LPFINT				_FOR_CHAR_LEN;
   #define __LPFCHAR	UCHAR* , LPFINT
   #undef  LPFCHAR
   #define LPFCHAR		__LPFCHAR
   #define FOR_CHAR(x)	x,_FOR_CHAR_LEN

  #else

   #define __LPFCHAR	LPFCHAR
   #define FOR_CHAR(x)	x

  #endif


#endif

#endif // __BR_FORTRAN_TYPES_H
