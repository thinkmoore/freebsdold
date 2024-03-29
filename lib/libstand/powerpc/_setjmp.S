/*	$NetBSD: _setjmp.S,v 1.1 1997/03/29 20:55:53 thorpej Exp $	*/

#include <machine/asm.h>

#if (defined(LIBC_SCCS) || defined(LIBC_RCS)) && !defined(lint)
	.text
	.asciz "$FreeBSD: stable/9/lib/libstand/powerpc/_setjmp.S 68544 2000-11-10 06:10:28Z benno $"
#endif

/*
 * C library -- _setjmp, _longjmp
 *
 *	_longjmp(a,v)
 * will generate a "return(v?v:1)" from the last call to
 *	_setjmp(a)
 * by restoring registers from the stack.
 * The previous signal state is NOT restored.
 */

ENTRY(_setjmp)
	mflr	11
	mfcr	12
	mr	10,1
	mr	9,2
	stmw	9,8(3)
	li	3,0
	blr

ENTRY(_longjmp)
	lmw	9,8(3)
	mtlr	11
	mtcr	12
	mr	2,9
	mr	1,10
	mr	3,4
	blr
