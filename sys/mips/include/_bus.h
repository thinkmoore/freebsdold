/*-
 * Copyright (c) 2005 M. Warner Losh.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modification, immediately at the beginning of the file.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * from: src/sys/i386/include/_bus.h,v 1.1 2005/04/18 21:45:33 imp
 * $FreeBSD: stable/9/sys/mips/include/_bus.h 210311 2010-07-20 19:25:11Z jmallett $
 */

#ifndef MIPS_INCLUDE__BUS_H
#define	MIPS_INCLUDE__BUS_H
/*
 * Bus address and size types
 */
#include "opt_cputype.h" 
#if !(defined(CPU_CNMIPS) && defined(ISA_MIPS32))
typedef uintptr_t bus_addr_t;
#else
typedef uint64_t bus_addr_t;
#endif
typedef uintptr_t bus_size_t;

/*
 * Access methods for bus resources and address space.
 */
typedef struct bus_space *bus_space_tag_t;
typedef bus_addr_t bus_space_handle_t;
#endif /* MIPS_INCLUDE__BUS_H */
