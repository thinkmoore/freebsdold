/*	$NetBSD: pipe.S,v 1.11 2005/04/22 06:58:01 simonb Exp $	*/

/*-
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
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
 */

#include <machine/asm.h>
__FBSDID("$FreeBSD: stable/9/lib/libc/mips/sys/pipe.S 209231 2010-06-16 12:55:14Z jchandra $");
#include "SYS.h"

#if defined(LIBC_SCCS) && !defined(lint)
	ASMSTR("from: @(#)pipe.s	8.1 (Berkeley) 6/4/93")
	ASMSTR("$NetBSD: pipe.S,v 1.11 2005/04/22 06:58:01 simonb Exp $")
#endif /* LIBC_SCCS and not lint */

LEAF(__sys_pipe)
	WEAK_ALIAS(pipe, __sys_pipe)
	WEAK_ALIAS(_pipe, __sys_pipe)
	PIC_PROLOGUE(__sys_pipe)
	li	v0, SYS_pipe	# pipe(fildes) int fildes[2];
	syscall
	bne	a3, zero, 1f
	sw	v0, 0(a0)	# store the two file descriptors
	sw	v1, 4(a0)
	move	v0, zero
	PIC_RETURN()
1:
	PIC_TAILCALL(__cerror)
END(__sys_pipe)
