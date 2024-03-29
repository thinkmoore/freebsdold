/*-
 * Copyright (c) 2002 Peter Grehan.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
/*      $NetBSD: ptrace.S,v 1.3 2000/02/23 20:16:57 kleink Exp $        */

#include <machine/asm.h>
__FBSDID("$FreeBSD: stable/9/lib/libc/powerpc64/sys/ptrace.S 218824 2011-02-18 21:44:53Z nwhitehorn $");

#include "SYS.h"

ENTRY(ptrace)
	mflr	%r0
	std	%r0,16(%r1)
	stdu	%r1,-80(%r1)
	stw	%r3,48(%r1)
	stw	%r4,52(%r1)
	std	%r5,56(%r1)
	stw	%r6,64(%r1)

	bl	CNAME(__error)
	nop
	li	%r7,0
	stw	%r7,0(%r3)

	lwz	%r3,48(%r1)
	lwz	%r4,52(%r1)
	ld	%r5,56(%r1)
	lwz	%r6,64(%r1)
	ld	%r1,0(%r1)
	ld	%r0,16(%r1)
	mtlr	%r0
	li	%r0,SYS_ptrace
	sc
	bso	1f
	blr
1:
	stdu	%r1,-48(%r1)		/* lr already saved */
	bl	HIDENAME(cerror)
	nop
	ld	%r1,0(%r1)
	ld	%r0,16(%r1)
	mtlr	%r0
	blr

	.section .note.GNU-stack,"",%progbits
