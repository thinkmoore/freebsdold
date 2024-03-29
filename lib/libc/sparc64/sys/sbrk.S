/*
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
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
 * from: Header: brk.s,v 1.3 92/06/25 12:56:05 mccanne Exp
 */

#if defined(SYSLIBC_SCCS) && !defined(lint)
	.asciz "@(#)sbrk.s	8.1 (Berkeley) 6/4/93"
#if 0
	RCSID("$NetBSD: sbrk.S,v 1.7 2000/07/25 15:14:46 mycroft Exp $")
#endif
#endif /* SYSLIBC_SCCS and not lint */
#include <machine/asm.h>
__FBSDID("$FreeBSD: stable/9/lib/libc/sparc64/sys/sbrk.S 165903 2007-01-09 00:28:16Z imp $");

#include "SYS.h"

	.data
	.globl	HIDENAME(curbrk)
	.globl	HIDENAME(minbrk)
	.type	HIDENAME(curbrk),@object
	.type	HIDENAME(minbrk),@object
	.align	8
HIDENAME(curbrk):
	.xword	CNAME(_end)
HIDENAME(minbrk):
	.xword	CNAME(_end)

_SYSENTRY(sbrk)
	PIC_PROLOGUE(%o3, %o2)
	SET(HIDENAME(curbrk), %o2, %o3)
	ldx	[%o3], %o4
	add	%o4, %o0, %o5
	mov	%o5, %o0
	mov	SYS_break, %g1
	ta	%xcc, ST_SYSCALL
	bcc,a,pt %xcc, 1f
	 mov	%o4, %o0
	ERROR()
1:	retl
	 stx	%o5, [%o3]
_SYSEND(sbrk)
