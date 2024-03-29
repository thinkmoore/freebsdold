/* $FreeBSD: stable/9/sys/ia64/include/intrcnt.h 205234 2010-03-17 00:37:15Z marcel $ */
/* $NetBSD: intrcnt.h,v 1.17 1998/11/19 01:48:04 ross Exp $ */

/*-
 * Copyright (c) 1995, 1996 Carnegie-Mellon University.
 * All rights reserved.
 *
 * Author: Chris G. Demetriou
 *
 * Permission to use, copy, modify and distribute this software and
 * its documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 *
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND
 * FOR ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 *
 * Carnegie Mellon requests users of this software to return to
 *
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 *
 * any improvements or extensions that they make and grant Carnegie the
 * rights to redistribute these changes.
 */

#define	INTRCNT_CLOCK		0
#define	INTRCNT_COUNT		256

/*
 * Maximum name length in intrnames table (including terminating '\0'.
 * Since vmstat(8) assumes a maximum length of 13 (including '\0'), we're
 * pretty much limited to that (unless we don't care about the alignment
 * of the columns :-)
 */
#define INTRNAME_LEN		13
