/*	$NetBSD: shmat.S,v 1.1 2000/07/07 08:20:52 itohy Exp $	*/

#include <machine/asm.h>
__FBSDID("$FreeBSD: stable/9/lib/libc/mips/sys/shmat.S 178580 2008-04-26 12:08:02Z imp $");
#include "SYS.h"

RSYSCALL(shmat)
