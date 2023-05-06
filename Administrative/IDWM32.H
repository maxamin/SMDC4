/*    This file, "idwm32.h", contains the prototypes for various
**    functions in the IDWM library.
**
**    Note that the IDWM functions are written in FORTRAN, and
**    that these prototypes are for calling the IDWM routines from
**    C on the following systems:
**
**       1.  Microsoft Visual C++, BORLAND C++ under Windows NT, 95
**	     (32 Bits version).
**           Among other things, this means:
**
**           A.  In C, the names of the functions must be lowercase
**               because of the function prototypes for the IDWM
**               in this file.
**           B.  All arguments are passed by reference.
**	     C.  The __fortran keyword (with MS) and __pascal (Borland)
**	         are replaced with __stdcall.
**
**    The prototypes in this file are in alphabetical order by the
**    FORTRAN name of the routine.
**
**    As mentioned, this include file is for a limited number of systems,
**    so it includes tests to make sure that we are running under one of
**    these systems.  If you wish to use this on another system,
**    modifications may be required.
*/

#ifndef IDWM32_H
#define IDWM32_H

// The following macro is used to indicate the mode of character
// passing between fortran and C.
// if defined, this means only character strings
// else this means character strings, followed by length
#define __BR_VBCHAR

#if !defined __BR_FORTRAN_TYPES_H
#include "brfortyp.h"
#endif

//*************  FUNCTION PROTOTYPES  *************//

//*****    LOWER CASE VERSIONS    ******//
#define allmap   ALLMAP
#define ap27aer  AP27AER
#define ap28rz   AP28RZ
#define ap28rzs  AP28RZS
#define ap30arz  AP30ARZ
#define ap30rz   AP30RZ
#define cdgrad4  CDGRAD4
#define cirafzl  CIRAFZL
#define cirafzp  CIRAFZP
#define cndmap   CNDMAP
#define craddg4  CRADDG4
#define crdchk1  CRDCHK1
#define crdchk2  CRDCHK2
#define crdunpn  CRDUNPN
#define ge75nz   GE75NZ
#define geo14sq  GEO14SQ
#define geo2am   GEO2AM
#define geoa123  GEOA123
#define geoaac2  GEOAAC2
#define geoaac3  GEOAAC3
#define geoaac8  GEOAAC8
#define geoaac9  GEOAAC9
#define geoaal   GEOAAL
#define geoacw   GEOACW
#define geoadp   GEOADP
#define geoalc   GEOALC
#define geoalc3  GEOALC3
#define geoaxp   GEOAXP
#define geobci   GEOBCI
#define geoc1l   GEOC1L
#define geoc2l   GEOC2L
#define geoc2lt  GEOC2LT
#define geoc3c   GEOC3C
#define geocac2  GEOCAC2
#define geocac3  GEOCAC3
#define geoccd   GEOCCD
#define geoccdc  GEOCCDC
#define geoccdi  GEOCCDI
#define geocdcp  GEOCDCP
#define geocfd   GEOCFD
#define geocia   GEOCIA
#define geociel  GEOCIEL
#define geociw   GEOCIW
#define geoclps  GEOCLPS
#define geocp8f  GEOCP8F
#define geocrdn  GEOCRDN
#define geoctw   GEOCTW
#define geoctya  GEOCTYA
#define geoctyr  GEOCTYR
#define geocwi   GEOCWI
#define geodaa   GEODAA
#define geodaa1  GEODAA1
#define geodaa2  GEODAA2
#define geodaa3  GEODAA3
#define geodam   GEODAM
#define geodam1  GEODAM1
#define geodam2  GEODAM2
#define geodam3  GEODAM3
#define geodbld  GEODBLD
#define geodblp  GEODBLP
#define geodc    GEODC
#define geodc1   GEODC1
#define geodc9   GEODC9
#define geodcc   GEODCC
#define geodcc1  GEODCC1
#define geodcm   GEODCM
#define geodcm1  GEODCM1
#define geodcm9  GEODCM9
#define geodcw   GEODCW
#define geodgrd  GEODGRD
#define geodst   GEODST
#define geodst3  GEODST3
#define geodstr  GEODSTR
#define geodta   GEODTA
#define geodta1  GEODTA1
#define geodta3  GEODTA3
#define geodtl   GEODTL
#define geodw    GEODW
#define geodw1   GEODW1
#define geodwa   GEODWA
#define geodwa1  GEODWA1
#define geodwa2  GEODWA2
#define geodwa3  GEODWA3
#define geodwd   GEODWD
#define geoeel   GEOEEL
#define geoelev  GEOELEV
#define geoellp  GEOELLP
#define geoema   GEOEMA
#define geofigc  GEOFIGC
#define geogcc3  GEOGCC3
#define geogcl   GEOGCL
#define geogcm   GEOGCM
#define geogcml  GEOGCML
#define geogcms  GEOGCMS
#define geogcp   GEOGCP
#define geogcp2  GEOGCP2
#define geogetf  GEOGETF
#define geoiaa   GEOIAA
#define geoiaa2  GEOIAA2
#define geoinm   GEOINM
#define geoldi   GEOLDI
#define geolin   GEOLIN
#define geolin2  GEOLIN2
#define geoliw   GEOLIW
#define geolop   GEOLOP
#define geolsd   GEOLSD
#define geomap   GEOMAP
#define geomnyp  GEOMNYP
#define geomv8   GEOMV8
#define geonwnd  GEONWND
#define geonxt   GEONXT
#define geopdap  GEOPDAP
#define geopeqp  GEOPEQP
#define geopia   GEOPIA
#define geopia2  GEOPIA2
#define geopim   GEOPIM
#define geopinf  GEOPINF
#define geopiw   GEOPIW
#define geopiw1  GEOPIW1
#define geopiw2  GEOPIW2
#define geoplc   GEOPLC
#define geoplc2  GEOPLC2
#define geoppda  GEOPPDA
#define geor837  GEOR837
#define georddg  GEORDDG
#define geordxx  GEORDXX
#define georgn   GEORGN
#define georgns  GEORGNS
#define geoset   GEOSET
#define geoset3  GEOSET3
#define geosm1   GEOSM1
#define geosmla  GEOSMLA
#define geosqr   GEOSQR
#define geoswp8  GEOSWP8
#define geotlcn  GEOTLCN
#define geotucn  GEOTUCN
#define geova1   GEOVA1
#define geova2   GEOVA2
#define geowiw   GEOWIW
#define geownd   GEOWND
#define geowndc  GEOWNDC
#define geowndl  GEOWNDL
#define geownds  GEOWNDS
#define geowtiw  GEOWTIW
#define idwm     IDWM
#define lclaac2  LCLAAC2
#define lclaac3  LCLAAC3
#define lclaac8  LCLAAC8
#define lclaac9  LCLAAC9
#define lcldam   LCLDAM
#define lcldam1  LCLDAM1
#define lcldam2  LCLDAM2
#define lcldam3  LCLDAM3
#define lcldla   LCLDLA
#define lcldla1  LCLDLA1
#define lcldla2  LCLDLA2
#define lcldla3  LCLDLA3
#define lclgal   LCLGAL
#define lclila   LCLILA
#define lclila2  LCLILA2
#define lcllin   LCLLIN
#define lclmap   LCLMAP
#define lclnxt   LCLNXT
#define rj81nz   RJ81NZ
#define rj88nz   RJ88NZ
#define wdbunit  WDBUNIT

//******  FUNCTIONS DECLARATIONS  ******//

void  __stdcall ALLMAP   (LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4     );

void  __stdcall AP27AER  (LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4     );

void  __stdcall AP28RZ   (LPFREAL    ,
                          LPFREAL    ,
                          LPFCHAR     );

void  __stdcall AP28RZS  (LPFREAL    ,
                          LPFREAL    ,
                          LPFCHAR     );

void  __stdcall AP30ARZ  (LPFREAL    ,
                          LPFREAL    ,
                          LPFCHAR     );

void  __stdcall AP30RZ   (LPFREAL    ,
                          LPFREAL    ,
                          LPFCHAR     );

void  __stdcall CDGRAD4  (LPFCHAR    ,
                          LPFREAL    ,
                          LPFREAL     );

void  __stdcall CIRAFZL  (LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4     );

void  __stdcall CIRAFZP  (LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4     );

void  __stdcall CNDMAP   (LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4     );

void  __stdcall CRADDG4  (LPFREAL    ,
                          LPFREAL    ,
                          LPFCHAR     );

void  __stdcall CRDCHK1  (LPFCHAR    ,
                          LPFLOG      );

void  __stdcall CRDCHK2  (LPFCHAR    ,
                          LPFLOG      );

void  __stdcall CRDUNPN  (LPFCHAR    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFLOG     ,
                          LPFINT4     );

void  __stdcall GE75NZ   (LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4     );

void  __stdcall GEO14SQ  (LPFINT4    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL     );

void  __stdcall GEO2AM   (LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFREAL     );

void  __stdcall GEOA123  (LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL     );

void  __stdcall GEOAAC2  (LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFINT4    ,
                          LPFINT4     );

void  __stdcall GEOAAC3  (LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFCHAR    ,
                          LPFINT4    ,
                          LPFINT4     );

void  __stdcall GEOAAC8  (LPFCHAR    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFINT4    ,
                          LPFINT4     );

void  __stdcall GEOAAC9  (LPFCHAR    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFCHAR    ,
                          LPFINT4    ,
                          LPFINT4     );

void  __stdcall GEOAAL   (LPFINT4    ,
                          LPFCHAR    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4     );

void  __stdcall GEOACW   (LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFINT4    ,
                          LPFLOG      );

void  __stdcall GEOADP   (LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFREAL     );

void  __stdcall GEOALC   (LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFINT4    ,
                          LPFINT4     );

void  __stdcall GEOALC3  (LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFCHAR    ,
                          LPFINT4    ,
                          LPFINT4     );

void  __stdcall GEOAXP   (LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4     );

void  __stdcall GEOBCI   (LPFINT4    ,
                          LPFCHAR    ,
                          LPFCHAR    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFLOG     ,
                          LPFINT4     );

void  __stdcall GEOC1L   (LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFLOG      );

void  __stdcall GEOC2L   (LPFREAL    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4     );

void  __stdcall GEOC2LT  (LPFREAL    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4     );

FINT4 __stdcall GEOC3C   (LPFCHAR    ,
                          LPFCHAR    ,
                          LPFINT4     );

void  __stdcall GEOCAC2  (LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4     );

void  __stdcall GEOCAC3  (LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4     );

void  __stdcall GEOCCD   (LPFCHAR    ,
                          LPFCHAR    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4     );

void  __stdcall GEOCCDC  (LPFCHAR    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4     );

void  __stdcall GEOCCDI  (LPFINT4     );

void  __stdcall GEOCDCP  (LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4     );

void  __stdcall GEOCFD   (LPFINT4     );

void  __stdcall GEOCIA   (LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFINT4     );

void  __stdcall GEOCIEL  (LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFINT4     );

void  __stdcall GEOCIW   (LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFLOG      );

void  __stdcall GEOCLPS  (LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFLOG      );

void  __stdcall GEOCP8F  (LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4     );

void  __stdcall GEOCRDN  (LPFINT4    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFINT2    ,
                          LPFINT4    ,
                          LPFINT4     );

void  __stdcall GEOCTW   (LPFREAL    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4     );

void  __stdcall GEOCTYA  (LPFCHAR    ,
                          LPFCHAR     );

void  __stdcall GEOCTYR  (LPFCHAR    ,
                          LPFCHAR     );

void  __stdcall GEOCWI   (LPFINT4    ,
                          LPFCHAR    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL     );

void  __stdcall GEODAA   (LPFREAL    ,
                          LPFREAL    ,
                          LPFCHAR    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4     );

void  __stdcall GEODAA1  (LPFREAL    ,
                          LPFREAL    ,
                          LPFCHAR    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL     );

void  __stdcall GEODAA2  (LPFREAL    ,
                          LPFREAL    ,
                          LPFCHAR    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4     );

void  __stdcall GEODAA3  (LPFREAL    ,
                          LPFREAL    ,
                          LPFCHAR    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL     );

void  __stdcall GEODAM   (LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFINT4     );

void  __stdcall GEODAM1  (LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFCHAR    ,
                          LPFINT4     );

void  __stdcall GEODAM2  (LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFINT4     );

void  __stdcall GEODAM3  (LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFCHAR    ,
                          LPFINT4     );

void  __stdcall GEODBLD  (LPFREAL    ,
                          LPFINT4     );

void  __stdcall GEODBLP  (LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFLOG      );

void  __stdcall GEODC    (LPFREAL    ,
                          LPFREAL    ,
                          LPFCHAR    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4     );

void  __stdcall GEODC1   (LPFREAL    ,
                          LPFREAL    ,
                          LPFCHAR    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL     );

void  __stdcall GEODC9   (LPFREAL    ,
                          LPFREAL    ,
                          LPFCHAR    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL     );

void  __stdcall GEODCC   (LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFCHAR     );

void  __stdcall GEODCC1  (LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFCHAR     );

void  __stdcall GEODCM   (LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFINT4     );

void  __stdcall GEODCM1  (LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFCHAR    ,
                          LPFINT4     );

void  __stdcall GEODCM9  (LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFCHAR    ,
                          LPFINT4     );

void  __stdcall GEODCW   (LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFCHAR     );

void  __stdcall GEODGRD  (LPFCHAR    ,
                          LPFREAL    ,
                          LPFREAL     );

void  __stdcall GEODST   (LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4     );

FREAL __stdcall GEODST3  (LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL     );

void  __stdcall GEODSTR  (LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL     );

void  __stdcall GEODTA   (LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4     );

void  __stdcall GEODTA1  (LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4     );

void  __stdcall GEODTA3  (LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL     );

void  __stdcall GEODTL   (LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL     );

void  __stdcall GEODW    (LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFINT4    ,
                          LPFINT4     );

void  __stdcall GEODW1   (LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFCHAR    ,
                          LPFREAL    ,
                          LPFREAL     );

void  __stdcall GEODWA   (LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFINT4     );

void  __stdcall GEODWA1  (LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFREAL     );

void  __stdcall GEODWA2  (LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFINT4     );

void  __stdcall GEODWA3  (LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFREAL     );

void  __stdcall GEODWD   (LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFCHAR     );

void  __stdcall GEOEEL   (LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFINT4     );

void  __stdcall GEOELEV  (LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4     );

void  __stdcall GEOELLP  (LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4     );

void  __stdcall GEOEMA   (LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4     );

void  __stdcall GEOFIGC  (LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4     );

void  __stdcall GEOGCC3  (LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4     );

void  __stdcall GEOGCL   (LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFREAL     );

void  __stdcall GEOGCM   (LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4     );

void  __stdcall GEOGCML  (LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFLOG      );

void  __stdcall GEOGCMS  (LPFINT4    ,
                          LPFINT4     );

void  __stdcall GEOGCP   (LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL     );

void  __stdcall GEOGCP2  (LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL     );

void  __stdcall GEOGETF  (LPFINT4    ,
                          LPFCHAR    ,
                          LPFLOG      );

void  __stdcall GEOIAA   (LPFREAL    ,
                          LPFREAL    ,
                          LPFCHAR     );

void  __stdcall GEOIAA2  (LPFREAL    ,
                          LPFREAL    ,
                          LPFCHAR     );

void  __stdcall GEOINM   (LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4     );

void  __stdcall GEOLDI   (LPFINT4    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4     );

void  __stdcall GEOLIN   (LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFLOG      );

void  __stdcall GEOLIN2  (LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFLOG      );

void  __stdcall GEOLIW   (LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFLOG      );

void  __stdcall GEOLOP   (LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4     );

void  __stdcall GEOLSD   (LPFINT4    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFINT4    ,
                          LPFINT4     );

void  __stdcall GEOMAP   (LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4     );

void  __stdcall GEOMNYP  (LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFLOG      );

void  __stdcall GEOMV8   (LPFINT4    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4     );

FLOG  __stdcall GEONWND  (LPFREAL     );

void  __stdcall GEONXT   (LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFLOG      );

void  __stdcall GEOPDAP  (LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL     );

FLOG  __stdcall GEOPEQP  (LPFREAL    ,
                          LPFREAL     );

FLOG  __stdcall GEOPIA   (LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4     );

FLOG  __stdcall GEOPIA2  (LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4     );

FLOG  __stdcall GEOPIM   (LPFREAL    ,
                          LPFREAL     );

void  __stdcall GEOPINF  (LPFCHAR    ,
                          LPFCHAR    ,
                          LPFINT4     );

FLOG  __stdcall GEOPIW   (LPFREAL    ,
                          LPFINT4    ,
                          LPFREAL     );

void  __stdcall GEOPIW1  (LPFREAL    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4     );

void  __stdcall GEOPIW2  (LPFREAL    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4     );

void  __stdcall GEOPLC   (LPFREAL    ,
                          LPFREAL    ,
                          LPFCHAR     );

void  __stdcall GEOPLC2  (LPFREAL    ,
                          LPFREAL    ,
                          LPFCHAR     );

void  __stdcall GEOPPDA  (LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL     );

void  __stdcall GEOR837  (LPFREAL    ,
                          LPFREAL    ,
                          LPFCHAR    ,
                          LPFREAL     );

void  __stdcall GEORDDG  (LPFREAL    ,
                          LPFREAL    ,
                          LPFCHAR     );

void  __stdcall GEORDXX  (LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4     );

void  __stdcall GEORGN   (LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4     );

void  __stdcall GEORGNS  (LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4     );

void  __stdcall GEOSET   (LPFINT4    ,
                          LPFINT4     );

void  __stdcall GEOSET3  (LPFINT4    ,
                          LPFCHAR     );

void  __stdcall GEOSM1   (LPFREAL    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4     );

void  __stdcall GEOSMLA  (LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFLOG      );

void  __stdcall GEOSQR   (LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL     );

void  __stdcall GEOSWP8  (LPFREAL    ,
                          LPFINT4     );

void  __stdcall GEOTLCN  (LPFCHAR    ,
                          LPFINT4     );

void  __stdcall GEOTUCN  (LPFCHAR    ,
                          LPFINT4     );

void  __stdcall GEOVA1   (LPFINT4    ,
                          LPFINT4     );

void  __stdcall GEOVA2   (LPFINT4    ,
                          LPFREAL     );

FLOG  __stdcall GEOWIW   (LPFREAL    ,
                          LPFREAL     );

void  __stdcall GEOWND   (LPFREAL    ,
                          LPFINT4    ,
                          LPFREAL     );

void  __stdcall GEOWNDC  (LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL     );

void  __stdcall GEOWNDL  (LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4     );

void  __stdcall GEOWNDS  (LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4     );

FLOG  __stdcall GEOWTIW  (LPFREAL    ,
                          LPFREAL     );

void  __stdcall IDWM     (LPFINT4     );

void  __stdcall LCLAAC2  (LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFINT4    ,
                          LPFINT4     );

void  __stdcall LCLAAC3  (LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFCHAR    ,
                          LPFINT4    ,
                          LPFINT4     );

void  __stdcall LCLAAC8  (LPFCHAR    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFINT4    ,
                          LPFINT4     );

void  __stdcall LCLAAC9  (LPFCHAR    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFCHAR    ,
                          LPFINT4    ,
                          LPFINT4     );

void  __stdcall LCLDAM   (LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFINT4     );

void  __stdcall LCLDAM1  (LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFCHAR    ,
                          LPFINT4     );

void  __stdcall LCLDAM2  (LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFINT4     );

void  __stdcall LCLDAM3  (LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFINT4    ,
                          LPFCHAR    ,
                          LPFINT4    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFCHAR    ,
                          LPFINT4     );

void  __stdcall LCLDLA   (LPFREAL    ,
                          LPFREAL    ,
                          LPFCHAR    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4     );

void  __stdcall LCLDLA1  (LPFREAL    ,
                          LPFREAL    ,
                          LPFCHAR    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL     );

void  __stdcall LCLDLA2  (LPFREAL    ,
                          LPFREAL    ,
                          LPFCHAR    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4     );

void  __stdcall LCLDLA3  (LPFREAL    ,
                          LPFREAL    ,
                          LPFCHAR    ,
                          LPFREAL    ,
                          LPFREAL    ,
                          LPFREAL     );

void  __stdcall LCLGAL   (LPFINT4    ,
                          LPFCHAR    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4     );

void  __stdcall LCLILA   (LPFREAL    ,
                          LPFREAL    ,
                          LPFCHAR     );

void  __stdcall LCLILA2  (LPFREAL    ,
                          LPFREAL    ,
                          LPFCHAR     );

void  __stdcall LCLLIN   (LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFLOG      );

void  __stdcall LCLMAP   (LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4     );

void  __stdcall LCLNXT   (LPFINT4    ,
                          LPFREAL    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFINT4    ,
                          LPFLOG      );

void  __stdcall RJ81NZ   (LPFREAL    ,
                          LPFREAL    ,
                          LPFINT4     );

void  __stdcall RJ88NZ   (LPFREAL    ,
                          LPFREAL    ,
                          LPFCHAR    ,
                          LPFINT4     );

void  __stdcall WDBUNIT  (LPFINT4     );

#endif

//*************  End of "idwm32.h"  *************//
