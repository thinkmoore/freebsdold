/*
 * Copyright (c) 1995 John Birrell <jb@cimlogic.com.au>.
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
 * 3. Neither the name of the author nor the names of any co-contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY JOHN BIRRELL AND CONTRIBUTORS ``AS IS'' AND
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
 * $FreeBSD: stable/9/lib/libkse/thread/thr_yield.c 174689 2007-12-16 23:29:57Z deischen $
 */
#include <pthread.h>
#include "thr_private.h"

int _sched_yield(void);

__weak_reference(_sched_yield, sched_yield);
__weak_reference(_pthread_yield, pthread_yield);

int
_sched_yield(void)
{
	struct pthread	*curthread = _get_curthread();

	if (curthread->attr.flags & PTHREAD_SCOPE_SYSTEM)
		return (__sys_sched_yield());

	/* Reset the accumulated time slice value for the current thread: */
	curthread->slice_usec = -1;

	/* Schedule the next thread: */
	_thr_sched_switch(curthread);
	/* Always return no error. */
	return(0);
}

/* Draft 4 yield */
void
_pthread_yield(void)
{
	struct pthread	*curthread = _get_curthread();

	if (curthread->attr.flags & PTHREAD_SCOPE_SYSTEM) {
		__sys_sched_yield();
		return;
	}

	/* Reset the accumulated time slice value for the current thread: */
	curthread->slice_usec = -1;

	/* Schedule the next thread: */
	_thr_sched_switch(curthread);
}
