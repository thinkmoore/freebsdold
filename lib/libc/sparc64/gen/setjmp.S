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
 *	from: Header: _setjmp.s,v 1.1 91/07/06 16:45:53 torek Exp
 */

#if defined(LIBC_SCCS) && !defined(lint)
	.asciz "@(#)_setjmp.s	8.1 (Berkeley) 6/4/93"
#if 0
	RCSID("$NetBSD: _setjmp.S,v 1.4 1998/10/08 02:27:59 eeh Exp $")
#endif
#endif /* LIBC_SCCS and not lint */
#include <machine/asm.h>
__FBSDID("$FreeBSD: stable/9/lib/libc/sparc64/gen/setjmp.S 165903 2007-01-09 00:28:16Z imp $");

#include "assym.s"

	.register %g2,#ignore
	.register %g3,#ignore

/*
 * C library -- setjmp, longjmp
 *
 *	longjmp(a,v)
 * will generate a "return(v?v:1)" from
 * the last call to
 *	setjmp(a)
 * by restoring the previous context.
 */

ENTRY(setjmp)
	save	%sp, -CCFSZ, %sp
	mov	SIG_BLOCK, %o0
	clr	%o1
	call	CNAME(sigprocmask)
	 add	%i0, _JB_SIGMASK, %o2
	restore
	stx	%sp, [%o0 + _JB_SP]
	stx	%o7, [%o0 + _JB_PC]
	retl
	 clr	%o0
END(setjmp)

	.weak	CNAME(longjmp)
	.set	CNAME(longjmp),CNAME(__longjmp)
ENTRY(__longjmp)
	save	%sp, -CCFSZ, %sp
	flushw
	mov	SIG_SETMASK, %o0
	add	%i0, _JB_SIGMASK, %o1
	call	CNAME(sigprocmask)
	 clr	%o2
	ldx	[%i0 + _JB_SP], %fp
	ldx	[%i0 + _JB_PC], %i7
	mov	1, %i0
	movrnz	%i1, %i1, %i0
	ret
	 restore
END(__longjmp)
