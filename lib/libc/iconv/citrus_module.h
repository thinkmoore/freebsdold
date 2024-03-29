/* $FreeBSD: stable/9/lib/libc/iconv/citrus_module.h 219019 2011-02-25 00:04:39Z gabor $ */
/* $NetBSD: citrus_module.h,v 1.1 2002/03/17 22:14:20 tshiozak Exp $ */

/*-
 * Copyright (c)2002 Citrus Project,
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

#ifndef _CITRUS_MODULE_H_
#define _CITRUS_MODULE_H_

#define MATCH(x, act)						\
do {								\
	if (lenvar >= (sizeof(#x)-1) &&				\
	    _bcs_strncasecmp(p, #x, sizeof(#x)-1) == 0) {	\
		act;						\
		lenvar -= sizeof(#x)-1;				\
		p += sizeof(#x)-1;				\
	}							\
} while (0)

typedef struct _citrus_module_rec *_citrus_module_t;

__BEGIN_DECLS
void	*_citrus_find_getops(_citrus_module_t __restrict,
	    const char * __restrict, const char * __restrict);
int	 _citrus_load_module(_citrus_module_t * __restrict,
	    const char * __restrict);
void	 _citrus_unload_module(_citrus_module_t);
__END_DECLS

#endif
