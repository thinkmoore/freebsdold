/* bootptest.h */
/* $FreeBSD: stable/9/libexec/bootpd/tools/bootptest/bootptest.h 97419 2002-05-28 18:39:53Z alfred $ */
/*
 * Hacks for sharing print-bootp.c between tcpdump and bootptest.
 */
#define ESRC(p) (p)
#define EDST(p) (p)

#ifndef	USE_BFUNCS
/* Use mem/str functions */
/* There are no overlapped copies, so memcpy is OK. */
#define bcopy(a,b,c)    memcpy(b,a,c)
#define bzero(p,l)      memset(p,0,l)
#define bcmp(a,b,c)     memcmp(a,b,c)
#endif

extern int vflag; /* verbose flag */

/* global pointers to beginning and end of current packet (during printing) */
extern unsigned char *packetp;
extern unsigned char *snapend;

extern char *ipaddr_string(struct in_addr *);
