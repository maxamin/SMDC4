/**************************************************************************
*  Filename:    SPROEVAL.H
*
*  (C) Copyright 2005 SafeNet, Inc.All Rights Reserved
*
*  Description: INCLUDE FILE FOR WINDOWED VERSION OF SUPERPRO EVAL PROGRAM.
*
*  Revision 1.1 : Added new define statements corresponding to the new API's in SPN6.1
*       
*  Revision 1.2 : Added new define statements for EnumSrvr, HrdLmt and GetKeyInfo
*                 
**************************************************************************/
#ifndef _SPROEVAL_H
#define _SPROEVAL_H

#define IDC_SET_PORT_PARMS			125
#define IDC_GET_PORT_PARMS			126

#ifndef VERSION
#define VER    "NT-1.0"
#else
#include "ver.h"
#endif


#define MAX_PASSWORDS_LENGTH		        4;
#define MAX_DEVID_LENGTH			4;
#define MAX_ADDRESS_LENGTH			2;
#define MAX_ACCESS_CODE				3;
#define MIN_ACCESS_CODE				0;
#define MAX_DATA_LENGTH				4;
#define MAX_NUM_SERVER				10;
#define MIN_NUM_SERVER				1;
#define MIN_NUM_LICENESE			0;
#define MAX_PASSWORDS_LENGTH		        4;
//MAX_ACTI_PASSWORD_LENGTH			4;
#define MAX_QUERY_LENGTH			56;
#define MIN_QUERY_LENGTH			8;
#define MAX_SERVER_LENGTH			64;


#define GET_PORT_PARMS_DLG			(LPSTR)"GET_PORT_PARMS_DIALOG"
#define ACTIVATE_DLG				(LPSTR)"ACTIVATE_DIALOG"
#define READ_DLG					(LPSTR)"READ_DIALOG"
#define XREAD_DLG					(LPSTR)"XREAD_DIALOG"
#define WRITE_DLG					(LPSTR)"WRITE_DIALOG"
#define OWRITE_DLG					(LPSTR)"OWRITE_DIALOG"
#define MAIN_DLG					(LPSTR)"MAIN_DIALOG"
#define FIND_DLG					(LPSTR)"FIND_DIALOG"
#define QUERY_DLG					(LPSTR)"QUERY_DIALOG"
#define INFO_DLG					(LPSTR)"INFO_DIALOG"
#define VIEW_DLG					(LPSTR)"VIEW_DIALOG"
#define DEC_DLG						(LPSTR)"DEC_DIALOG"
#define VERSION_DLG					(LPSTR)"VERSION_DIALOG"
#define SET_CONTACT_DLG				(LPSTR)"SET_CONTACT_SRV_DIALOG"
#define GET_CONTACT_DLG				(LPSTR)"GET_CONTACT_SRV"
#define RELEASE_DLG					(LPSTR)"RELEASE_LIC_DIALOG"
#define GET_SUB_LIC_DLG				(LPSTR)"GET_SUB_LIC_DIALOG"
#define ENUMSRVR_DLG				(LPSTR)"ENUM_SRVR_DLG"
#define GETKEY_INFO_DLG				(LPSTR)"GET_KEY_INFO_DLG"
#define	SET_PROTOCOL_DLG			(LPSTR)"SET_PROTOCOL_DIALOG"
#define	SET_HEARTBEAT_DLG			(LPSTR)"SET_HEARTBEAT_DIALOG"
#define	GET_KEY_TYPE_DLG			(LPSTR)"GET_KEY_TYPE_DIALOG"
#define	SET_SHARED_LICENSE_DLG		(LPSTR)"SET_SHARED_LICENSE_DIALOG"

#define SP_API_FF                   111
#define SP_API_FN                   112
#define SP_API_RD                   113
#define SP_API_XRD                  114
#define SP_API_WT                   115
#define SP_API_OWT                  116
#define SP_API_DEC                  117
#define SP_API_QRY                  118
#define SP_API_ACT                  119
#define SP_API_FMT                  120

#define SP_DP                       125
#define SP_NFO                      130
#define SP_VW                       135
#define SP_HLP                      140
#define SP_API_GV                   160
#define SP_API_GFS                  161
#define SP_API_INIT                 163
#define SP_API_SET_CONTACT_SERVER   164
#define SP_API_GET_CONTACT_SERVER   165
#define SP_API_RELEASE              166
#define SP_API_GET_SUB_LIC          167
#define SP_API_GET_HARDLMT          168
#define SP_API_ENUM_SRVR            169
#define SP_API_GET_KEY_INFO         170
#define SP_API_SETPROTOCOL          171
//#define SP_API_SETHEARTBEAT       172    
//#define SP_API_ADV_PROT           171



#define FF                          200
#define FF_ID                       201
#define FN                          250
#define FN_ID                       251

#define RD                          300
#define RD_ID                       301
#define RD_VAL                      302

#define XR                          350
#define XR_ID                       351
#define XR_VAL                      352
#define XR_AC                       353

#define WR                          400
#define WR_ID                       401
#define WR_PW                       402
#define WR_VAL                      403
#define WR_AC                       404

#define OW                          450
#define OW_ID                       451
#define OW_VAL                      465
#define OW_AC                       466
#define OW_WP                       467
#define OW_WPW                      468
#define OW_PW_1                     469
#define OW_PW_2                     470
#define OW_PW_3                     471


#define DEC                         500
#define DEC_ID                      501
#define DEC_WP                      502

#define QRY                         550
#define QRY_ID                      551
#define QRY_WP                      552
#define QRY_QS                      553
#define QRY_RSLT                    554
#define QRY_RSLT_32                 555

#define ACT                         600
#define ACT_ID                      601
#define ACT_WP                      602
#define ACT_AP1                     714
#define ACT_AP2                     715

#define SP_VER_MAJOR                800
#define SP_VER_MINOR                801
#define SP_VER_REV                  802
#define SP_VER_OSTYPE               803

#define ID_SRV_NAME                 900
#define IDC_SRV_STATIC              901
#define ID_CONTACT_SRV              902

#define CELL_ADD                    1000
#define NO_OF_LIC                   1001

#define COMBO_ENSRVR_FLG            1050
#define IDC_DEVID                   1051
#define IDC_NUMSRVRS                1052
#define COMBO_SRVR_INFO             1053

#define IDC_HRD_LMT                 1060
#define IDC_LIC_INUSE               1061
#define IDC_NUM_TIMED_OUT           1062
#define IDC_HIGHEST_IN_USE          1063

#define IDC_CMBPROTOCOL				1015

#define HEARTBEAT_EDIT              1006


#define VIEW_TEXT                   100

#define IDS_SP_SUCCESS                      1
#define IDS_SP_INVALID_FUNCTION_CODE        2
#define IDS_SP_INVALID_PACKET               3
#define IDS_SP_UNIT_NOT_FOUND               4
#define IDS_SP_ACCESS_DENIED                5
#define IDS_SP_INVALID_MEMORY_ADDRESS       6
#define IDS_SP_INVALID_ACCESS_CODE          7
#define IDS_SP_PORT_IS_BUSY                 8
#define IDS_SP_WRITE_NOT_READY              9
#define IDS_SP_NO_PORT_FOUND                10
#define IDS_SP_ALREADY_ZERO                 11
#define IDS_SP_DRIVER_OPEN_ERROR            12
#define IDS_SP_DRIVER_NOT_INSTALLED         13
#define IDS_SP_IO_COMMUNICATIONS_ERROR      14
#define IDS_SP_INVALID_VERSION              15
#define IDS_SP_PACKET_TOO_SMALL             16
#define IDS_SP_INVALID_PARAMETER            17
#define IDS_SP_MEM_ACCESS_ERROR             18
#define IDS_SP_VERSION_NOT_SUPPORTED        19
#define IDS_SP_OS_NOT_SUPPORTED             20
#define IDS_SP_QUERY_TOO_LONG               21
#define IDS_SP_INTERNAL_ERROR               22
#define IDS_ERR_NO_WRITE_PW					23
#define IDS_ERR_NO_OVERWRITE_PW1			24
#define IDS_ERR_NO_OVERWRITE_PW2			25
#define IDS_ERR_NO_ACTIVATE_PW1				26
#define IDS_ERR_NO_ACTIVATE_PW2				27
#define IDS_ERR_NO_ADDR						28
#define IDS_ERR_NO_VALUE					29
#define IDS_ERR_NO_ACCESS_CODE				30
#define IDS_ERR_INVALID_INPUT				31
#define IDS_ERR_ACTIVATE_FAILED				32
#define IDS_DECREMENT						33
#define IDS_ERR_DEC_FAILED					34
#define IDS_DEC_SUCCESS						35
#define IDS_ACTIVATE_ALGO					36
#define IDS_ACTIVATE_SUCCESS				37
#define IDS_ERR_NO_DEV_ID					38
#define IDS_FINDFIRST						39
#define IDS_ERR_FF_FAILED					40
#define IDS_FF_SUCCESS						41
#define IDS_OVERWRITE						42
#define IDS_OVERWRITE_SUCCESS				43
#define IDS_ERR_OVERWRITE_FAILED			44
#define IDS_QUERY							45
#define IDS_ERR_QUERY1						46
#define IDS_ERR_QUERY2						47
#define IDS_ERR_QUERY3						48
#define IDS_ERR_QUERY_FAILED				49
#define IDS_ERR_READ_FAILED					50
#define IDS_ERR_WRITE_FAILED				51
#define IDS_WRITE_SUCCESS					52
#define IDS_WRITE							53
#define IDS_ERR_XREAD_FAILED				54
#define IDS_ERR_FINDNEXT_FAILED				55
#define IDS_FINDNEXT						56
#define IDS_MORE_INFO						57
#define IDS_HELP							58
#define IDS_ERR_INIT_FAILED					59
#define IDS_SP_STATUS						60
#define IDS_SP_FULL_STATUS					61
#define IDS_GET_FULL_STATUS					62
#define IDS_RESULT							63
#define IDS_INIT							64
#define IDS_INIT_SUCCESS					65
#define IDS_WIN3x_LOCAL_DRVR				66
#define IDS_WINNT_SYS_DRVR					67
#define IDS_DRVR_UNDEFINED					68
#define IDS_ERR_VERSION_FAILED				69
#define IDS_SP_MEM_ALIGNMENT_ERROR			70
#define IDS_ERR_FMT_FAILED					71
#define IDS_FMT								72
#define IDS_FMT_SUCCESS						73
#define IDS_SP_INVALID_COMMAND				74
#define IDS_SP_PORT_ALLOCATION_FAILURE		75
#define IDS_SP_PORT_RELEASE_FAILURE			76
#define IDS_SP_ACQUIRE_PORT_TIMEOUT			77
#define IDS_SP_SIGNAL_NOT_SUPPORTED			79
#define IDS_SP_UNKNOWN_MACHINE				80
#define IDS_SP_SYS_API_ERROR				81
#define IDS_SP_UNIT_IS_BUSY					82
#define IDS_SP_INVALID_PORT_TYPE			83
#define IDS_SP_INVALID_MACH_TYPE			84
#define IDS_SP_INVALID_IRQ_MASK				85
#define IDS_SP_INVALID_CONT_METHOD			86
#define IDS_SP_INVALID_PORT_FLAGS			87
#define IDS_SP_INVALID_LOG_PORT_CFG			88
#define IDS_SP_INVALID_OS_TYPE				89
#define IDS_SP_INVALID_LOG_PORT_NUM			90
#define IDS_SP_INVALID_ROUTER_FLGS			91
#define IDS_CFG_LIB							92
#define IDS_SP_INIT_NOT_CALLED				93
#define IDS_WIN95_SYS_DRVR					94
#define IDS_OS2_SYS_DRVR					95
#define IDS_DOSRM_LOCAL_DRVR				96
#define IDS_WIN3x_SYS_DRVR					97
#define IDS_WIN32s_LOCAL_DRVR				98
#define IDS_SP_DRIVER_TYPE_NOT_SUPPORTED	99
#define IDS_SP_FAIL_ON_DRIVER_COMM			100
#define IDS_INVALID_OPERATION				102
#define IDS_ERR_GET_HRDLMT					103
#define IDS_GET_HRDLMT						104
#define IDS_ENSRVR_FAILED					105
#define IDS_GET_KEY_INFO_FAILED				106
#define IDS_SETPROTOCOL_FAILED				111
#define IDS_SETHEARTBEAT_FAILED				112

/* Configure Lib Params Dialog Controls */
#define CFG_LIB_PARMS_DLG					(LPSTR)"CFG_LIB_PARMS_DIALOG"
#define IDC_COMMAND_GRP						101
#define IDC_GET_CFG_RB						102
#define IDC_SET_CFG_RB						103
#define IDC_FUNCTION_GRP					104
#define IDC_MACH_TYPE_FUNC_RB				105
#define IDC_DELAY_FUNC_RB				    106
#define IDC_OS_PARMS_FUNC_RB				107
#define IDC_PORT_PARAMS_FUNC_RB				108
#define IDC_DRVR_TYPE_FUNC_RB				109
#define IDC_MASK_INTS_FUNC_RB				110
#define IDC_SET_GET							111		


/* Set OS Params Dialog Controls */
#define SET_OS_PARMS_DLG					(LPSTR)"SET_OS_PARMS_DIALOG"
#define IDC_OS_VER							101
#define IDC_OS_TYPES_GRP					102
#define IDC_OS_TYPE_AUTO_RB					103      
#define IDC_OS_TYPE_WIN32s_RB				104
#define IDC_OS_TYPE_WIN95_RB				105
#define IDC_OS_TYPE_WINNT_RB				106
#define IDC_OS_TYPE_OS2_RB					107
#define IDC_OS_TYPE_WIN3x_RB				108
#define IDC_VER_ST							109 
			

/* Driver Types Dialog Controls */
#define SET_DRVR_TYPE_DLG					(LPSTR)"SET_DRVR_TYPE_DIALOG"
#define IDC_DRVR_TYPES_GRP					101
#define IDC_DRVR_TYPE_LOCAL_RB				102
#define IDC_DRVR_TYPE_SYS_RB				103
#define IDC_DRVR_TYPE_AUTO_RB				104
		


/* Get Driver Type Dialog Controls */
#define GET_DRVR_TYPE_DLG					(LPSTR)"GET_DRVR_TYPE_DIALOG"
#define IDC_GET_DRVR_TYPE_RB				101



/* Set Port Configuration Dialog Controls */

#define SET_PORT_PARMS_DLG					(LPSTR)"SET_PORT_PARMS_DIALOG"
#define IDC_PHY_PORT_ADDR					101
#define IDC_PORT_CONT_MET_GRP				102
#define IDC_PORT_CONT_MET_RBW_CB			103
#define IDC_PORT_CONT_MET_HW_CB				104
#define IDC_PORT_TYPES_GRP					105
#define IDC_PORT_TYPE_IBM_RB				106
#define IDC_PORT_TYPE_IBM_DMA_RB			107
#define IDC_PORT_TYPE_NEC_RB				108
#define IDC_PORT_TYPE_FMR_RB				109
#define IDC_PORT_TYPE_AUTO_RB				110		
#define IDC_PORT_CONT_MET_SYS_CB			111
#define IDC_PORT_CONT_MET_MASK_INTS_CB		112
#define IDC_PORT_CONT_MET_SYS_INTS_CB		113
#define IDC_PORT_CONT_MET_WCS_CB			114
#define IDC_PORT_CONT_MET_NT_RIRQL_CB		128
#define IDC_DEV_RC							115
#define IDC_PORT_CONT_RC					116
#define IDC_PORT_CONT_RI					117
#define IDC_LOG_PORT_NUM					118
#define IDC_PORT_CONT_MET_AUTO_CB			119
#define IDC_VALIDATE_PORT_CB				120
#define IDC_FLAGS_GB						121
#define IDC_USER_DEF_PORT_CB				122
#define IDC_CONT_HNDLR_INST_CB				123
#define IDC_MAPPED_ADDR						127
#define IDC_SYS_PORT_NUM					124


/* Set Interrupt Mask Dialog Controls */
#define SET_MASK_INTS_DLG					(LPSTR)"SET_MASK_INTS_DIALOG"
#define IDC_INTS_GRP						101
#define IDC_MASK_INT_LPT2_CB				102
#define IDC_MASK_INT_LPT1_CB				103
#define IDC_MASK_INT_TIMER_CB				104


/* Set Machine Type Dialog Controls */

#define SET_MACH_TYPE_DLG					(LPSTR)"SET_MACH_TYPE_DIALOG"
#define IDC_MACH_TYPES_GRP					101
#define IDC_MACH_TYPE_IBM_RB				102
#define IDC_MACH_TYPE_NEC_RB				103
#define IDC_MACH_TYPE_FMR_RB				104
#define IDC_MACH_TYPE_AUTO_RB				105
	

/* Get Machine Type Dialog Controls */
#define GET_MACH_TYPE_DLG					(LPSTR)"GET_MACH_TYPE_DIALOG"
#define IDC_GET_MACH_TYPE					101


/* Set Delay Dialog Controls */

#define SET_DELAY_DLG						(LPSTR)"SET_DELAY_DIALOG"
#define IDC_SET_DELAY_VALUE					101


/* Get Delay Dialog Controls */
#define GET_DELAY_DLG						(LPSTR)"GET_DELAY_DIALOG"
#define IDC_GET_DELAY_VALUE					101
#define GET_OS_PARMS_DLG					(LPSTR)"GET_OS_PARMS_DIALOG"

/* Get OS Parameters Dialog Controls */
#define IDC_GET_OS_TYPE						101
#define IDC_GET_OS_VER						102


/* Get Mask Int Dialog Controls */
#define GET_MASK_INTS_DLG					(LPSTR)"GET_MASK_INTS_DIALOG"
#endif                                 

/* _SPROEVAL_H                      */
