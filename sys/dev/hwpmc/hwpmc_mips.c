/*-
 * Copyright (c) 2010, George V. Neville-Neil <gnn@freebsd.org>
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
 */

#include <sys/cdefs.h>
__FBSDID("$FreeBSD: stable/9/sys/dev/hwpmc/hwpmc_mips.c 204635 2010-03-03 15:05:58Z gnn $");

#include <sys/param.h>
#include <sys/pmc.h>
#include <sys/systm.h>

#include <machine/pmc_mdep.h>
#include <machine/md_var.h>

struct pmc_mdep *
pmc_md_initialize()
{
  /*	if (cpu_class == CPU_CLASS_MIPS24K)*/
		return pmc_mips24k_initialize();
		/*	else
			return NULL;*/
}

void
pmc_md_finalize(struct pmc_mdep *md)
{
  /*	if (cpu_class == CPU_CLASS_MIPS24K) */
		pmc_mips24k_finalize(md);
		/*	else
		KASSERT(0, ("[mips,%d] Unknown CPU Class 0x%x", __LINE__,
		cpu_class));*/
}

int
pmc_save_kernel_callchain(uintptr_t *cc, int maxsamples,
    struct trapframe *tf)
{
	(void) cc;
	(void) maxsamples;
	(void) tf;
	return (0);
}

int
pmc_save_user_callchain(uintptr_t *cc, int maxsamples,
    struct trapframe *tf)
{
	(void) cc;
	(void) maxsamples;
	(void) tf;
	return (0);
}
