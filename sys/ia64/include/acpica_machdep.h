/*-
 * Copyright (c) 2002 Mitsuru IWASAKI
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
 * $FreeBSD: stable/9/sys/ia64/include/acpica_machdep.h 205713 2010-03-26 21:22:02Z marcel $
 */

/******************************************************************************
 *
 * Name: acpica_machdep.h - arch-specific defines, etc.
 *       $Revision$
 *
 *****************************************************************************/

#ifndef __ACPICA_MACHDEP_H__
#define	__ACPICA_MACHDEP_H__

#ifdef _KERNEL
#define	_IA64

/*
 * Calling conventions:
 *
 * ACPI_SYSTEM_XFACE        - Interfaces to host OS (handlers, threads)
 * ACPI_EXTERNAL_XFACE      - External ACPI interfaces 
 * ACPI_INTERNAL_XFACE      - Internal ACPI interfaces
 * ACPI_INTERNAL_VAR_XFACE  - Internal variable-parameter list interfaces
 */
#define	ACPI_SYSTEM_XFACE
#define	ACPI_EXTERNAL_XFACE
#define	ACPI_INTERNAL_XFACE
#define	ACPI_INTERNAL_VAR_XFACE

/* Asm macros */

#define	ACPI_ASM_MACROS
#define	BREAKPOINT3
#define	ACPI_DISABLE_IRQS()	ia64_disable_intr()
#define	ACPI_ENABLE_IRQS()	ia64_enable_intr()

#define	ACPI_FLUSH_CPU_CACHE()	/* XXX ia64_fc()? */

/* Section 5.2.9.1:  global lock acquire/release functions */
extern int	acpi_acquire_global_lock(uint32_t *lock);
extern int	acpi_release_global_lock(uint32_t *lock);
#define	ACPI_ACQUIRE_GLOBAL_LOCK(GLptr, Acq)	do {			\
	(Acq) = acpi_acquire_global_lock(&((GLptr)->GlobalLock));	\
} while (0)
#define	ACPI_RELEASE_GLOBAL_LOCK(GLptr, Acq)	do {			\
	(Acq) = acpi_release_global_lock(&((GLptr)->GlobalLock));	\
} while (0)

#endif /* _KERNEL */

#define	ACPI_MACHINE_WIDTH             64
#define	COMPILER_DEPENDENT_INT64       long
#define	COMPILER_DEPENDENT_UINT64      unsigned long

void	acpi_cpu_c1(void);

#endif /* __ACPICA_MACHDEP_H__ */
