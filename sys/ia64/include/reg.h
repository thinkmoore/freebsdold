/*-
 * Copyright (c) 2000 Doug Rabson
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
 *
 *	$FreeBSD: stable/9/sys/ia64/include/reg.h 205014 2010-03-11 14:49:06Z nwhitehorn $
 */

#ifndef _MACHINE_REG_H_
#define _MACHINE_REG_H_

#include <machine/_regset.h>

#if defined(_KERNEL) && !defined(_STANDALONE)
#include "opt_compat.h"
#endif

struct reg {
	struct _special		r_special;
	struct _callee_saved	r_preserved;
	struct _caller_saved	r_scratch;
};

struct fpreg {
	struct _callee_saved_fp	fpr_preserved;
	struct _caller_saved_fp	fpr_scratch;
	struct _high_fp		fpr_high;
};

struct dbreg {
	unsigned long	dbr_data[8];
	unsigned long	dbr_inst[8];
};

#ifdef COMPAT_FREEBSD32
#include <machine/fpu.h>
#include <compat/ia32/ia32_reg.h>
#endif

#ifdef _KERNEL
struct thread;

/* XXX these interfaces are MI, so they should be declared in a MI place. */
int	fill_regs(struct thread *, struct reg *);
int	set_regs(struct thread *, struct reg *);
int	fill_fpregs(struct thread *, struct fpreg *);
int	set_fpregs(struct thread *, struct fpreg *);
int	fill_dbregs(struct thread *, struct dbreg *);
int	set_dbregs(struct thread *, struct dbreg *);
#endif

#endif /* _MACHINE_REG_H_ */
