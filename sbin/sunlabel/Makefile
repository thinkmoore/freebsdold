# $FreeBSD: stable/9/sbin/sunlabel/Makefile 211725 2010-08-23 22:24:11Z imp $

.PATH: ${.CURDIR}/../../sys/geom

PROG=	sunlabel
SRCS=	sunlabel.c geom_sunlabel_enc.c
MAN=	sunlabel.8

.if ${MACHINE_CPUARCH} == "sparc64"
LINKS=	${BINDIR}/sunlabel ${BINDIR}/disklabel
MLINKS=	sunlabel.8 disklabel.8
.endif

DPADD=	${LIBGEOM}
LDADD=	-lgeom

.include <bsd.prog.mk>

test:	${PROG}
	sh ${.CURDIR}/runtest.sh

testx: ${PROG}
	sh -x ${.CURDIR}/runtest.sh
