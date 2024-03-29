#!/usr/sbin/dtrace -qs

/*-
 * Copyright (c) 2008-2012 Alexander Leidinger <netchild@FreeBSD.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer
 *    in this position and unchanged.
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
 * $FreeBSD: stable/9/sys/compat/linux/check_internal_locks.d 246290 2013-02-03 18:14:37Z dchagin $
 */

/**
 * Check if the internal locks are correctly acquired/released:
 *  - no recursive locking (mtx locks, write locks)
 *  - no unlocking of already unlocked one
 *
 * Print stacktrace if a lock is longer locked than about 10sec or more.
 */

#pragma D option dynvarsize=32m
#pragma D option specsize=32m

BEGIN
{
	check["emul_lock"] = 0;
	check["emul_shared_rlock"] = 0;
	check["emul_shared_wlock"] = 0;
	check["futex_mtx"] = 0;
}

linuxulator*:locks:emul_lock:locked,
linuxulator*:locks:emul_shared_wlock:locked,
linuxulator*:locks:futex_mtx:locked
/check[probefunc] > 0/
{
	printf("ERROR: recursive lock of %s (%p),", probefunc, arg0);
	printf("       or missing SDT probe in kernel. Stack trace follows:");
	stack();
}

linuxulator*:locks:emul_lock:locked,
linuxulator*:locks:emul_shared_rlock:locked,
linuxulator*:locks:emul_shared_wlock:locked,
linuxulator*:locks:futex_mtx:locked
{
	++check[probefunc];
	@stats[probefunc] = count();

	ts[probefunc] = timestamp;
	spec[probefunc] = speculation();
}

linuxulator*:locks:emul_lock:unlock,
linuxulator*:locks:emul_shared_rlock:unlock,
linuxulator*:locks:emul_shared_wlock:unlock,
linuxulator*:locks:futex_mtx:unlock
/check[probefunc] == 0/
{
	printf("ERROR: unlock attemt of unlocked %s (%p),", probefunc, arg0);
	printf("       missing SDT probe in kernel, or dtrace program started");
	printf("       while the %s was already held (race condition).", probefunc);
	printf("       Stack trace follows:");
	stack();
}

linuxulator*:locks:emul_lock:unlock,
linuxulator*:locks:emul_shared_rlock:unlock,
linuxulator*:locks:emul_shared_wlock:unlock,
linuxulator*:locks:futex_mtx:unlock
{
	discard(spec[probefunc]);
	spec[probefunc] = 0;
	--check[probefunc];
}

/* Timeout handling */

tick-10s
/spec["emul_lock"] != 0 && timestamp - ts["emul_lock"] >= 9999999000/
{
	commit(spec["emul_lock"]);
	spec["emul_lock"] = 0;
}

tick-10s
/spec["emul_shared_wlock"] != 0 && timestamp - ts["emul_shared_wlock"] >= 9999999000/
{
	commit(spec["emul_shared_wlock"]);
	spec["emul_shared_wlock"] = 0;
}

tick-10s
/spec["emul_shared_rlock"] != 0 && timestamp - ts["emul_shared_rlock"] >= 9999999000/
{
	commit(spec["emul_shared_rlock"]);
	spec["emul_shared_rlock"] = 0;
}

tick-10s
/spec["futex_mtx"] != 0 && timestamp - ts["futex_mtx"] >= 9999999000/
{
	commit(spec["futex_mtx"]);
	spec["futex_mtx"] = 0;
}


/* Statistics */

END
{
        printf("Number of locks per type:");
	printa(@stats);
}
