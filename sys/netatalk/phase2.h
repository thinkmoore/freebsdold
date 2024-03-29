/*-
 * Copyright (c) 1990,1991 Regents of The University of Michigan.
 * All Rights Reserved.
 *
 * Permission to use, copy, modify, and distribute this software and
 * its documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notice appears in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation, and that the name of The University
 * of Michigan not be used in advertising or publicity pertaining to
 * distribution of the software without specific, written prior
 * permission. This software is supplied as is without expressed or
 * implied warranties of any kind.
 *
 * This product includes software developed by the University of
 * California, Berkeley and its contributors.
 *
 *	Research Systems Unix Group
 *	The University of Michigan
 *	c/o Wesley Craig
 *	535 W. William Street
 *	Ann Arbor, Michigan
 *	+1-313-764-2278
 *	netatalk@umich.edu
 * $FreeBSD: stable/9/sys/netatalk/phase2.h 139827 2005-01-07 02:35:34Z imp $
 */

#include <net/if_llc.h>

#define llc_org_code llc_un.type_snap.org_code
#define llc_ether_type llc_un.type_snap.ether_type

#define SIOCPHASE1	_IOW('i', 100, struct ifreq)	/* AppleTalk phase 1 */
#define SIOCPHASE2	_IOW('i', 101, struct ifreq)	/* AppleTalk phase 2 */
