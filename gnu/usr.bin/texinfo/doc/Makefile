# $FreeBSD: stable/9/gnu/usr.bin/texinfo/doc/Makefile 56168 2000-01-17 10:59:30Z ru $

INFO=	info info-stnd texinfo
SRCDIR=	${TXIDIR}/doc

CLEANFILES=	texinfo.texi

texinfo.texi: texinfo.txi
	ln -fs ${.ALLSRC} ${.TARGET}

.include <bsd.info.mk>
