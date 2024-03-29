/*-
 * Copyright (c) 2001 David E. O'Brien
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	from: @(#)param.h	5.8 (Berkeley) 6/28/91
 * $FreeBSD: stable/9/sys/arm/include/param.h 224207 2011-07-19 00:37:24Z attilio $
 */

#ifndef _ARM_INCLUDE_PARAM_H_
#define	_ARM_INCLUDE_PARAM_H_

/*
 * Machine dependent constants for StrongARM
 */

#include <machine/_align.h>

#define STACKALIGNBYTES	(8 - 1)
#define STACKALIGN(p)	((u_int)(p) & ~STACKALIGNBYTES)

#define __PCI_REROUTE_INTERRUPT

#ifndef MACHINE
#define	MACHINE		"arm"
#endif
#ifndef MACHINE_ARCH
#define	MACHINE_ARCH	"arm"
#endif
#define	MID_MACHINE	MID_ARM6 

#if defined(SMP) || defined(KLD_MODULE)
#ifndef MAXCPU
#define	MAXCPU		2
#endif
#else
#define	MAXCPU		1
#endif /* SMP || KLD_MODULE */

#define	ALIGNBYTES	_ALIGNBYTES
#define	ALIGN(p)	_ALIGN(p)
/*
 * ALIGNED_POINTER is a boolean macro that checks whether an address
 * is valid to fetch data elements of type t from on this architecture.
 * This does not reflect the optimal alignment, just the possibility
 * (within reasonable limits). 
 */
#define	ALIGNED_POINTER(p, t)	((((unsigned)(p)) & (sizeof(t)-1)) == 0)

/*
 * CACHE_LINE_SIZE is the compile-time maximum cache line size for an
 * architecture.  It should be used with appropriate caution.
 */
#define	CACHE_LINE_SHIFT	6
#define	CACHE_LINE_SIZE		(1 << CACHE_LINE_SHIFT)

#define	PAGE_SHIFT	12
#define	PAGE_SIZE	(1 << PAGE_SHIFT)	/* Page size */
#define	PAGE_MASK	(PAGE_SIZE - 1)
#define	NPTEPG		(PAGE_SIZE/(sizeof (pt_entry_t)))

#define PDR_SHIFT	20 /* log2(NBPDR) */
#define NBPDR		(1 << PDR_SHIFT)
#define NPDEPG          (1 << (32 - PDR_SHIFT))

#define	MAXPAGESIZES	1		/* maximum number of supported page sizes */

#ifndef KSTACK_PAGES
#define KSTACK_PAGES    2
#endif /* !KSTACK_PAGES */

#ifndef FPCONTEXTSIZE
#define FPCONTEXTSIZE	(0x100)
#endif

#ifndef KSTACK_GUARD_PAGES
#define KSTACK_GUARD_PAGES	1
#endif /* !KSTACK_GUARD_PAGES */

#define USPACE_SVC_STACK_TOP		KSTACK_PAGES * PAGE_SIZE
#define USPACE_SVC_STACK_BOTTOM		(USPACE_SVC_STACK_TOP - 0x1000)
#define USPACE_UNDEF_STACK_TOP		(USPACE_SVC_STACK_BOTTOM - 0x10)
#define USPACE_UNDEF_STACK_BOTTOM	(FPCONTEXTSIZE + 10)
/*
 * Mach derived conversion macros
 */
#define	trunc_page(x)		((x) & ~PAGE_MASK)
#define	round_page(x)		(((x) + PAGE_MASK) & ~PAGE_MASK)
#define	trunc_4mpage(x)		((unsigned)(x) & ~PDRMASK)
#define	round_4mpage(x)		((((unsigned)(x)) + PDRMASK) & ~PDRMASK)

#define	atop(x)			((unsigned)(x) >> PAGE_SHIFT)
#define	ptoa(x)			((unsigned)(x) << PAGE_SHIFT)

#define	arm32_btop(x)		((unsigned)(x) >> PAGE_SHIFT)
#define	arm32_ptob(x)		((unsigned)(x) << PAGE_SHIFT)

#define	pgtok(x)		((x) * (PAGE_SIZE / 1024))

#endif /* !_ARM_INCLUDE_PARAM_H_ */
