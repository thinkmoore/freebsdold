/*-
 * Copyright (c) 2005 Peter Wemm
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

#include <sys/cdefs.h>
__FBSDID("$FreeBSD: stable/9/sys/ia64/ia32/ia32_reg.c 149923 2005-09-10 01:13:33Z marcel $");

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/procfs.h>

#include <compat/ia32/ia32_reg.h>

int
fill_regs32(struct thread *td, struct reg32 *regs)
{

	bzero(regs, sizeof(*regs));
	return (EOPNOTSUPP);
}

int
set_regs32(struct thread *td, struct reg32 *regs)
{

	return (EOPNOTSUPP);
}

int
fill_fpregs32(struct thread *td, struct fpreg32 *regs)
{

	bzero(regs, sizeof(*regs));
	return (EOPNOTSUPP);
}

int
set_fpregs32(struct thread *td, struct fpreg32 *regs)
{

	return (EOPNOTSUPP);
}

int
fill_dbregs32(struct thread *td, struct dbreg32 *regs)
{

	bzero(regs, sizeof(*regs));
	return (EOPNOTSUPP);
}

int
set_dbregs32(struct thread *td, struct dbreg32 *regs)
{

	return (EOPNOTSUPP);
}
