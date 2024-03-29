/*-
 * Copyright (c) 2010 Pawel Jakub Dawidek <pjd@FreeBSD.org>
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
 * THIS SOFTWARE IS PROVIDED BY THE AUTHORS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: stable/9/sys/boot/common/util.h 219083 2011-02-27 12:25:47Z pjd $
 */

#ifndef _UTIL_H_
#define	_UTIL_H_

#include <sys/types.h>

#include <stdarg.h>

void memcpy(void *dst, const void *src, int len);
void memset(void *b, int c, size_t len);
int memcmp(const void *b1, const void *b2, size_t len);

#define	bcopy(src, dst, len)	memcpy((dst), (src), (len))
#define	bzero(buf, size)	memset((buf), 0, (size))
#define	bcmp(b1, b2, len)	(memcmp((b1), (b2), (len)) != 0)

int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t len);
void strcpy(char *dst, const char *src);
void strcat(char *dst, const char *src);
char *strchr(const char *s, char ch);
size_t strlen(const char *s);

void printf(const char *fmt, ...);

#endif	/* !_UTIL_H_ */
