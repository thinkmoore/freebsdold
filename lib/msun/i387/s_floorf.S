/*
 * Written by J.T. Conklin <jtc@netbsd.org>.
 * Public domain.
 */

#include <machine/asm.h>

__FBSDID("$FreeBSD: stable/9/lib/msun/i387/s_floorf.S 217108 2011-01-07 16:13:12Z kib $");
/* RCSID("$NetBSD: s_floorf.S,v 1.3 1995/05/09 00:04:32 jtc Exp $") */

ENTRY(floorf)
	pushl	%ebp
	movl	%esp,%ebp
	subl	$8,%esp

	fstcw	-4(%ebp)		/* store fpu control word */
	movw	-4(%ebp),%dx
	orw	$0x0400,%dx		/* round towards -oo */
	andw	$0xf7ff,%dx
	movw	%dx,-8(%ebp)
	fldcw	-8(%ebp)		/* load modfied control word */

	flds	8(%ebp);		/* round */
	frndint

	fldcw	-4(%ebp)		/* restore original control word */

	leave
	ret
END(floorf)

	.section .note.GNU-stack,"",%progbits
