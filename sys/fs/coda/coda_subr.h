/*-
 *
 *             Coda: an Experimental Distributed File System
 *                              Release 3.1
 *
 *           Copyright (c) 1987-1998 Carnegie Mellon University
 *                          All Rights Reserved
 *
 * Permission  to  use, copy, modify and distribute this software and its
 * documentation is hereby granted,  provided  that  both  the  copyright
 * notice  and  this  permission  notice  appear  in  all  copies  of the
 * software, derivative works or  modified  versions,  and  any  portions
 * thereof, and that both notices appear in supporting documentation, and
 * that credit is given to Carnegie Mellon University  in  all  documents
 * and publicity pertaining to direct or indirect use of this code or its
 * derivatives.
 *
 * CODA IS AN EXPERIMENTAL SOFTWARE SYSTEM AND IS  KNOWN  TO  HAVE  BUGS,
 * SOME  OF  WHICH MAY HAVE SERIOUS CONSEQUENCES.  CARNEGIE MELLON ALLOWS
 * FREE USE OF THIS SOFTWARE IN ITS "AS IS" CONDITION.   CARNEGIE  MELLON
 * DISCLAIMS  ANY  LIABILITY  OF  ANY  KIND  FOR  ANY  DAMAGES WHATSOEVER
 * RESULTING DIRECTLY OR INDIRECTLY FROM THE USE OF THIS SOFTWARE  OR  OF
 * ANY DERIVATIVE WORK.
 *
 * Carnegie  Mellon  encourages  users  of  this  software  to return any
 * improvements or extensions that  they  make,  and  to  grant  Carnegie
 * Mellon the rights to redistribute these changes without encumbrance.
 *
 * 	@(#) src/sys/coda/coda_subr.h,v 1.1.1.1 1998/08/29 21:14:52 rvb Exp $
 * $FreeBSD: stable/9/sys/fs/coda/coda_subr.h 206210 2010-04-05 20:12:54Z rwatson $
 */

#ifndef _CODA_SUBR_H_
#define	_CODA_SUBR_H_

struct cnode	*coda_alloc(void);
void		 coda_free(struct cnode *cp);
struct cnode	*coda_find(struct CodaFid *fid);
void		 coda_flush(struct coda_mntinfo *mnt, enum dc_status dcstat);
void		 coda_testflush(void);
void		 coda_checkunmounting(struct mount *mp);
void		 coda_cacheprint(struct mount *whoIam);
void		 coda_debugon(void);
void		 coda_debugoff(void);
int		 coda_kill(struct mount *whoIam, enum dc_status dcstat);
void		 coda_save(struct cnode *cp);
void		 coda_unsave(struct cnode *cp);

#endif /* !_CODA_SUBR_H_ */
