#	$NetBSD: Makefile.inc,v 1.27 2005/10/07 17:16:40 tsutsui Exp $
# $FreeBSD: stable/9/lib/libc/mips/gen/Makefile.inc 231981 2012-02-21 21:18:59Z kib $

SRCS+=	infinity.c fabs.c ldexp.c modf.c

# SRCS+=	flt_rounds.c fpgetmask.c fpgetround.c fpgetsticky.c fpsetmask.c \
#	fpsetround.c fpsetsticky.c

SRCS+=	_ctx_start.S _set_tp.c _setjmp.S getcontextx.c makecontext.c \
	setjmp.S signalcontext.c sigsetjmp.S
