#	From: @(#)Makefile	8.1 (Berkeley) 6/8/93
# $FreeBSD: stable/9/share/doc/usd/19.memacros/Makefile 106143 2002-10-29 14:56:09Z ru $

VOLUME=		usd/19.memacros
SRCS=		meintro.me-sed
MACROS=		-me
GROFFDIR=	${.CURDIR}/../../../../contrib/groff
SRCDIR=		${GROFFDIR}/doc

version=`cat ${GROFFDIR}/VERSION`
revision=`sed -e 's/^0$$//' -e 's/^[1-9].*$$/.&/' ${GROFFDIR}/REVISION`

meintro.me-sed: meintro.me
	sed -e "s;@VERSION@;$(version)$(revision);" ${.ALLSRC} > ${.TARGET}

CLEANFILES=	${SRCS}

.include <bsd.doc.mk>
