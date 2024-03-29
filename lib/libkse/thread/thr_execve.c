/*
 * Copyright (C) 2004 Daniel Eischen <deischen@freebsd.org>
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice(s), this list of conditions and the following disclaimer as
 *    the first lines of this file unmodified other than the possible
 *    addition of one or more copyright notices.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice(s), this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $FreeBSD: stable/9/lib/libkse/thread/thr_execve.c 174689 2007-12-16 23:29:57Z deischen $
 */

#include "namespace.h"
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#include "un-namespace.h"
#include "thr_private.h"

__weak_reference(_execve, execve);

int 
_execve(const char *name, char *const *argv, char *const *envp)
{
	struct kse_execve_args args;
	struct pthread *curthread = _get_curthread();
	int ret;

	if (curthread->attr.flags & PTHREAD_SCOPE_SYSTEM)
		ret = __sys_execve(name, argv, envp);
	else {
		/*
		 * When exec'ing, set the kernel signal mask to the thread's
	 	 * signal mask to satisfy POSIX requirements.
		 */
		args.sigmask = curthread->sigmask;
		args.sigpend = curthread->sigpend;
		args.path = (char *)name;
		args.argv = (char **)argv;
		args.envp = (char **)envp;
		args.reserved = NULL;
		ret = kse_thr_interrupt(NULL, KSE_INTR_EXECVE, (long)&args);
	}

	return (ret);
}
