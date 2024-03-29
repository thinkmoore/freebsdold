/*-
 * Copyright (C) 2010 Nathan Whitehorn
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
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL TOOLS GMBH BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $FreeBSD: stable/9/sys/powerpc/aim/mmu_oea64.h 216174 2010-12-04 02:42:52Z nwhitehorn $
 */

#ifndef _POWERPC_AIM_MMU_OEA64_H
#define _POWERPC_AIM_MMU_OEA64_H

#include <machine/mmuvar.h>

extern mmu_def_t oea64_mmu;

/*
 * Helper routines
 */

/* Allocate physical memory for use in moea64_bootstrap. */
vm_offset_t	moea64_bootstrap_alloc(vm_size_t, u_int);

/*
 * Bootstrap subroutines
 *
 * An MMU_BOOTSTRAP() implementation looks like this:
 *   moea64_early_bootstrap();
 *   Allocate Page Table
 *   moea64_mid_bootstrap();
 *   Add mappings for MMU resources
 *   moea64_late_bootstrap();
 */

void		moea64_early_bootstrap(mmu_t mmup, vm_offset_t kernelstart,
		    vm_offset_t kernelend);
void		moea64_mid_bootstrap(mmu_t mmup, vm_offset_t kernelstart,
		    vm_offset_t kernelend);
void		moea64_late_bootstrap(mmu_t mmup, vm_offset_t kernelstart,
		    vm_offset_t kernelend);

/*
 * Statistics
 */

extern u_int	moea64_pte_valid;
extern u_int	moea64_pte_overflow;

/*
 * State variables
 */

extern struct pvo_head *moea64_pvo_table;
extern int		moea64_large_page_shift;
extern u_int		moea64_pteg_count;
extern u_int		moea64_pteg_mask;

#endif /* _POWERPC_AIM_MMU_OEA64_H */

