/*	$NetBSD: vectors.S,v 1.4 2002/08/17 16:36:32 thorpej Exp $	*/

/*-
 * Copyright (C) 1994-1997 Mark Brinicombe
 * Copyright (C) 1994 Brini
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
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by Brini.
 * 4. The name of Brini may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY BRINI ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL BRINI BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <machine/asm.h>
__FBSDID("$FreeBSD: stable/9/sys/arm/arm/vectors.S 251866 2013-06-17 20:26:19Z scottl $");

/*
 * These are the exception vectors copied down to page 0.
 *
 * Note that FIQs are special; rather than using a level of
 * indirection, we actually copy the FIQ code down into the
 * vector page.
 */

	.text
	.align	0
	.global	_C_LABEL(page0), _C_LABEL(page0_data), _C_LABEL(page0_end)
	.global _C_LABEL(fiqvector)

_C_LABEL(page0):
	ldr	pc, .Lreset_target
	ldr	pc, .Lundefined_target
	ldr	pc, .Lswi_target
	ldr	pc, .Lprefetch_abort_target
	ldr	pc, .Ldata_abort_target
	ldr	pc, .Laddress_exception_target
	ldr	pc, .Lirq_target
#ifdef __ARM_FIQ_INDIRECT
	ldr	pc, .Lfiq_target
#else
.Lfiqvector:
	.set	_C_LABEL(fiqvector), . - _C_LABEL(page0)
	subs	pc, lr, #4
	.org	.Lfiqvector + 0x100
#endif

_C_LABEL(page0_data):
.Lreset_target:
	.word	reset_entry

.Lundefined_target:
	.word	undefined_entry

.Lswi_target:
	.word	swi_entry

.Lprefetch_abort_target:
	.word	prefetch_abort_entry

.Ldata_abort_target:
	.word	data_abort_entry

.Laddress_exception_target:
	.word	address_exception_entry

.Lirq_target:
	.word	irq_entry

#ifdef __ARM_FIQ_INDIRECT
.Lfiq_target:
	.word	_C_LABEL(fiqvector)
#else
	.word	0	/* pad it out */
#endif
_C_LABEL(page0_end):

#ifdef __ARM_FIQ_INDIRECT
	.data
	.align	0
_C_LABEL(fiqvector):
	subs	pc, lr, #4
	.org	_C_LABEL(fiqvector) + 0x100
#endif
