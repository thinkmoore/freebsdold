/*-
 * Copyright (c) 1996-1999 Distributed Processing Technology Corporation
 * All rights reserved.
 *
 * Redistribution and use in source form, with or without modification, are
 * permitted provided that redistributions of source code must retain the
 * above copyright notice, this list of conditions and the following disclaimer.
 *
 * This software is provided `as is' by Distributed Processing Technology and
 * any express or implied warranties, including, but not limited to, the
 * implied warranties of merchantability and fitness for a particular purpose,
 * are disclaimed. In no event shall Distributed Processing Technology be
 * liable for any direct, indirect, incidental, special, exemplary or
 * consequential damages (including, but not limited to, procurement of
 * substitute goods or services; loss of use, data, or profits; or business
 * interruptions) however caused and on any theory of liability, whether in
 * contract, strict liability, or tort (including negligence or otherwise)
 * arising in any way out of the use of this driver software, even if advised
 * of the possibility of such damage.
 *
 * $FreeBSD: stable/9/sys/dev/asr/sys_info.h 139749 2005-01-06 01:43:34Z imp $
 */

#ifndef		__SYS_INFO_H
#define		__SYS_INFO_H

/*File - SYS_INFO.H
 ****************************************************************************
 *
 *Description:
 *
 *	This file contains structure definitions for the OS dependent
 *layer system information buffers.
 *
 *Copyright Distributed Processing Technology, Corp.
 *	  140 Candace Dr.
 *	  Maitland, Fl. 32751	USA
 *	  Phone: (407) 830-5522	 Fax: (407) 260-5366
 *	  All Rights Reserved
 *
 *Author:	Don Kemper
 *Date:		5/10/94
 *
 *Editors:
 *
 *Remarks:
 *
 *
 *****************************************************************************/


/*Include Files ------------------------------------------------------------- */

#if (defined(KERNEL) && defined(__bsdi__))
# include	 "i386/isa/dpt_osd_util.h"
#elif ((defined(KERNEL) || defined(_KERNEL)) && defined(__FreeBSD__))
# if (KERN_VERSION < 3)
#  include	  "i386/isa/dpt_osd_util.h"
# else
#  include	  "dev/asr/osd_util.h"
# endif
#else
# include	 "osd_util.h"
#endif

#ifndef NO_PACK
#if defined(_DPT_AIX)
#pragma options align=packed
#else
#pragma pack(1)
#endif	/* aix */
#endif	/* no unpack */


/*struct - driveParam_S - start
 *===========================================================================
 *
 *Description:
 *
 *	This structure defines the drive parameters seen during
 *booting.
 *
 *---------------------------------------------------------------------------*/

#ifdef __cplusplus
   struct driveParam_S {
#else
   typedef struct  {
#endif

   uSHORT	cylinders;	/* Upto 1024 */
   uCHAR	heads;		/* Upto 255 */
   uCHAR	sectors;	/* Upto 63 */

#ifdef __cplusplus

/*---------- Portability Additions ----------- in sp_sinfo.cpp */
#ifdef DPT_PORTABLE
	uSHORT		netInsert(dptBuffer_S *buffer);
	uSHORT		netExtract(dptBuffer_S *buffer);
#endif /* DPT PORTABLE */
/*--------------------------------------------*/

   };
#else
   } driveParam_S;
#endif
/*driveParam_S - end */


/*struct - sysInfo_S - start
 *===========================================================================
 *
 *Description:
 *
 *	This structure defines the command system information that
 *should be returned by every OS dependent layer.
 *
 *---------------------------------------------------------------------------*/

/*flags - bit definitions */
#define	SI_CMOS_Valid		0x0001
#define	SI_NumDrivesValid	0x0002
#define	SI_ProcessorValid	0x0004
#define	SI_MemorySizeValid	0x0008
#define	SI_DriveParamsValid	0x0010
#define	SI_SmartROMverValid	0x0020
#define	SI_OSversionValid	0x0040
#define	SI_OSspecificValid	0x0080	/* 1 if OS structure returned */
#define	SI_BusTypeValid		0x0100

#define	SI_ALL_VALID		0x0FFF	/* All Std SysInfo is valid */
#define	SI_NO_SmartROM		0x8000

/*busType - definitions */
#define	SI_ISA_BUS	0x00
#define	SI_MCA_BUS	0x01
#define	SI_EISA_BUS	0x02
#define	SI_PCI_BUS	0x04

#ifdef __cplusplus
   struct sysInfo_S {
#else
   typedef struct  {
#endif

   uCHAR	drive0CMOS;		/* CMOS Drive 0 Type */
   uCHAR	drive1CMOS;		/* CMOS Drive 1 Type */
   uCHAR	numDrives;		/* 0040:0075 contents */
   uCHAR	processorFamily;	/* Same as DPTSIG's definition */
   uCHAR	processorType;		/* Same as DPTSIG's definition */
   uCHAR	smartROMMajorVersion;
   uCHAR	smartROMMinorVersion;	/* SmartROM version */
   uCHAR	smartROMRevision;
   uSHORT	flags;			/* See bit definitions above */
   uSHORT	conventionalMemSize;	/* in KB */
   uLONG	extendedMemSize;	/* in KB */
   uLONG	osType;			/* Same as DPTSIG's definition */
   uCHAR	osMajorVersion;
   uCHAR	osMinorVersion;		/* The OS version */
   uCHAR	osRevision;
#ifdef _SINIX_ADDON
   uCHAR	busType;		/* See defininitions above */
   uSHORT	osSubRevision;
   uCHAR	pad[2];			/* For alignment */
#else
   uCHAR	osSubRevision;
   uCHAR	busType;		/* See defininitions above */
   uCHAR	pad[3];			/* For alignment */
#endif
   driveParam_S drives[16];		/* SmartROM Logical Drives */

#ifdef __cplusplus

/*---------- Portability Additions ----------- in sp_sinfo.cpp */
#ifdef DPT_PORTABLE
	uSHORT		netInsert(dptBuffer_S *buffer);
	uSHORT		netExtract(dptBuffer_S *buffer);
#endif /* DPT PORTABLE */
/*--------------------------------------------*/

   };
#else
   } sysInfo_S;
#endif
/*sysInfo_S - end */


/*struct - DOS_Info_S - start
 *===========================================================================
 *
 *Description:
 *
 *	This structure defines the system information specific to a
 *DOS workstation.
 *
 *---------------------------------------------------------------------------*/

/*flags - bit definitions */
#define	DI_DOS_HIGH		0x01	/* DOS is loaded high */
#define	DI_DPMI_VALID		0x02	/* DPMI version is valid */

#ifdef __cplusplus
   struct DOS_Info_S {
#else
   typedef struct {
#endif

   uCHAR	flags;		/* See bit definitions above */
   uSHORT	driverLocation; /* SmartROM BIOS address */
   uSHORT	DOS_version;
   uSHORT	DPMI_version;

#ifdef __cplusplus

/*---------- Portability Additions ----------- in sp_sinfo.cpp */
#ifdef DPT_PORTABLE
	uSHORT		netInsert(dptBuffer_S *buffer);
	uSHORT		netExtract(dptBuffer_S *buffer);
#endif /* DPT PORTABLE */
/*--------------------------------------------*/

   };
#else
   } DOS_Info_S;
#endif
/*DOS_Info_S - end */


/*struct - Netware_Info_S - start
 *===========================================================================
 *
 *Description:
 *
 *	This structure defines the system information specific to a
 *Netware machine.
 *
 *---------------------------------------------------------------------------*/

#ifdef __cplusplus
   struct Netware_Info_S {
#else
   typedef struct {
#endif

   uCHAR	driverName[13];		/* ie PM12NW31.DSK */
   uCHAR	serverName[48];
   uCHAR	netwareVersion;		/* The Netware OS version */
   uCHAR	netwareSubVersion;
   uCHAR	netwareRevision;
   uSHORT	maxConnections;		/* Probably  250 or 1000 */
   uSHORT	connectionsInUse;
   uSHORT	maxVolumes;
   uCHAR	unused;
   uCHAR	SFTlevel;
   uCHAR	TTSlevel;

   uCHAR	clibMajorVersion;	/* The CLIB.NLM version */
   uCHAR	clibMinorVersion;
   uCHAR	clibRevision;

#ifdef __cplusplus

/*---------- Portability Additions ----------- in sp_sinfo.cpp */
#ifdef DPT_PORTABLE
	uSHORT		netInsert(dptBuffer_S *buffer);
	uSHORT		netExtract(dptBuffer_S *buffer);
#endif /* DPT PORTABLE */
/*--------------------------------------------*/

   };
#else
   } Netware_Info_S;
#endif
/*Netware_Info_S - end */


/*struct - OS2_Info_S - start
 *===========================================================================
 *
 *Description:
 *
 *	This structure defines the system information specific to an
 *OS/2 machine.
 *
 *---------------------------------------------------------------------------*/

#ifdef __cplusplus
   struct OS2_Info_S {
#else
   typedef struct {
#endif

   uCHAR	something;

#ifdef __cplusplus

/*---------- Portability Additions ----------- in sp_sinfo.cpp */
#ifdef DPT_PORTABLE
	uSHORT		netInsert(dptBuffer_S *buffer);
	uSHORT		netExtract(dptBuffer_S *buffer);
#endif /* DPT PORTABLE */
/*--------------------------------------------*/

   };
#else
   } OS2_Info_S;
#endif
/*OS2_Info_S - end */


/*struct - WinNT_Info_S - start
 *===========================================================================
 *
 *Description:
 *
 *	This structure defines the system information specific to a
 *Windows NT machine.
 *
 *---------------------------------------------------------------------------*/

#ifdef __cplusplus
   struct WinNT_Info_S {
#else
   typedef struct {
#endif

   uCHAR	something;

#ifdef __cplusplus

/*---------- Portability Additions ----------- in sp_sinfo.cpp */
#ifdef DPT_PORTABLE
	uSHORT		netInsert(dptBuffer_S *buffer);
	uSHORT		netExtract(dptBuffer_S *buffer);
#endif /* DPT PORTABLE */
/*--------------------------------------------*/

   };
#else
   } WinNT_Info_S;
#endif
/*WinNT_Info_S - end */


/*struct - SCO_Info_S - start
 *===========================================================================
 *
 *Description:
 *
 *	This structure defines the system information specific to an
 *SCO UNIX machine.
 *
 *---------------------------------------------------------------------------*/

#ifdef __cplusplus
   struct SCO_Info_S {
#else
   typedef struct {
#endif

   uCHAR	something;

#ifdef __cplusplus

/*---------- Portability Additions ----------- in sp_sinfo.cpp */
#ifdef DPT_PORTABLE
	uSHORT		netInsert(dptBuffer_S *buffer);
	uSHORT		netExtract(dptBuffer_S *buffer);
#endif /* DPT PORTABLE */
/*--------------------------------------------*/

   };
#else
   } SCO_Info_S;
#endif
/*SCO_Info_S - end */


/*struct - USL_Info_S - start
 *===========================================================================
 *
 *Description:
 *
 *	This structure defines the system information specific to a
 *USL UNIX machine.
 *
 *---------------------------------------------------------------------------*/

#ifdef __cplusplus
   struct USL_Info_S {
#else
   typedef struct {
#endif

   uCHAR	something;

#ifdef __cplusplus

/*---------- Portability Additions ----------- in sp_sinfo.cpp */
#ifdef DPT_PORTABLE
	uSHORT		netInsert(dptBuffer_S *buffer);
	uSHORT		netExtract(dptBuffer_S *buffer);
#endif /* DPT PORTABLE */
/*--------------------------------------------*/

   };
#else
   } USL_Info_S;
#endif
/*USL_Info_S - end */


  /* Restore default structure packing */
#ifndef NO_UNPACK
#if defined(_DPT_AIX)
#pragma options align=reset
#elif defined(UNPACK_FOUR)
#pragma pack(4)
#else
#pragma pack()
#endif	/* aix */
#endif	/* no unpack */

#ifdef DPT_MEASURE_PERFORMANCE
typedef struct dpt_metrics {
	u_int32_t	command_count[256]; /* We assume MAX 256 SCSI commands */
	u_int32_t	max_command_time[256];
	u_int32_t	min_command_time[256];

	u_int32_t	min_intr_time;
	u_int32_t	max_intr_time;
	u_int32_t	max_intr_gap;
	u_int32_t	max_ht_time;
	u_int32_t	aborted_interrupts;
	u_int32_t	spurious_interrupts;
	u_int32_t	aborted_requests;
	u_int32_t	retried_requests;

	u_int32_t	max_waiting_count;
	u_int32_t	max_submit_count;
	u_int32_t	max_complete_count;

	u_int32_t	min_waiting_time;
	u_int32_t	min_submit_time;
	u_int32_t	min_complete_time;

	u_int32_t	max_waiting_time;
	u_int32_t	max_submit_time;
	u_int32_t	max_complete_time;

	u_int32_t	command_collisions;
	u_int32_t	command_too_busy;
	u_int32_t	max_eata_tries;
	u_int32_t	min_eata_tries;

	u_int32_t	read_by_size_count[10];
	u_int32_t	write_by_size_count[10];
	u_int32_t	read_by_size_min_time[10];
	u_int32_t	read_by_size_max_time[10];
	struct timeval	read_by_size_total_time[10];
	u_int32_t	write_by_size_min_time[10];
	u_int32_t	write_by_size_max_time[10];
	struct timeval	write_by_size_total_time[10];

#define	SIZE_512	0
#define	SIZE_1K		1
#define	SIZE_2K		2
#define	SIZE_4K		3
#define	SIZE_8K		4
#define	SIZE_16K	5
#define	SIZE_32K	6
#define	SIZE_64K	7
#define	SIZE_BIGGER	8
#define	SIZE_OTHER	9

	struct timeval	intr_started;
} dpt_perf_t;
#endif

#endif	/* __SYS_INFO_H */

