# $FreeBSD: stable/9/gnu/usr.bin/sort/Makefile 172595 2007-10-12 18:15:40Z obrien $

SORTDIR= ${.CURDIR}/../../../contrib/gnu-sort
.PATH: ${SORTDIR}/lib ${SORTDIR}/src ${SORTDIR}/man

PROG=	sort
SRCS=   sort.c \
	__fpending.c \
	argmatch.c \
	closeout.c \
	dup-safer.c \
	error.c \
	exitfail.c \
	fopen-safer.c \
	hard-locale.c \
	human.c \
	long-options.c \
	memcoll.c \
	physmem.c \
	posixver.c \
	quote.c \
	quotearg.c \
	strnlen.c \
	umaxtostr.c \
	version-etc.c \
	xalloc-die.c \
	xmalloc.c \
	xmemcoll.c \
	xstrtoul.c \
	xstrtoumax.c

CFLAGS+=-DHAVE_CONFIG_H -DHAVE_LANGINFO_H=1 -DHAVE_NL_LANGINFO=1 \
	-I${.CURDIR} -I${SORTDIR}/lib

.include <bsd.prog.mk>
