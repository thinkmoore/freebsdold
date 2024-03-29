/*-
 * Copyright (c) 2004 Marcel Moolenaar
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $FreeBSD: stable/9/sys/ia64/include/kdb.h 200207 2009-12-07 06:41:27Z marcel $
 */

#ifndef _MACHINE_KDB_H_
#define _MACHINE_KDB_H_

#include <machine/cpufunc.h>
#include <machine/frame.h>
#include <machine/ia64_cpu.h>

#define	KDB_STOPPEDPCB(pc)	(&(pc)->pc_md.pcb)

static __inline void
kdb_cpu_clear_singlestep(void)
{
	kdb_frame->tf_special.psr &= ~IA64_PSR_SS;
}

static __inline void
kdb_cpu_set_singlestep(void)
{
	kdb_frame->tf_special.psr |= IA64_PSR_SS;
}

static __inline void
kdb_cpu_sync_icache(unsigned char *addr, size_t size)
{
	vm_offset_t cacheline;

	cacheline = (uintptr_t)addr & ~31;
	size += (uintptr_t)addr - cacheline;
	size = (size + 31) & ~31;
	while (size > 0) {
		__asm __volatile("fc %0;; sync.i;; srlz.i;;" :: "r"(cacheline));
		cacheline += 32;
		size -= 32;
	}
}

static __inline void
kdb_cpu_trap(int vector, int _)
{
	__asm __volatile("flushrs;;");

	if (vector == IA64_VEC_BREAK &&
	    kdb_frame->tf_special.ifa == IA64_FIXED_BREAK)
                kdb_frame->tf_special.psr += IA64_PSR_RI_1;
}

#endif /* _MACHINE_KDB_H_ */
