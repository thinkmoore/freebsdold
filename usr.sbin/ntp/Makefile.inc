# $FreeBSD: stable/9/usr.sbin/ntp/Makefile.inc 201390 2010-01-02 11:07:44Z ed $

.include <bsd.own.mk>

DEFS_LOCAL= -DPARSE -DHAVE_CONFIG_H
NTPDEFS=   -DSYS_FREEBSD
# CLOCKDEFS=
#	-DLOCAL_CLOCK -DPST -DWWVB -DAS2201 -DGOES -DGPSTM -DOMEGA \
#	-DLEITCH -DTRAK -DACTS -DATOM -DDATUM -DHEATH -DMSFEES \
#	-DMX4200 -DNMEA -DBOEDER
CFLAGS+= ${NTPDEFS} ${DEFS_LOCAL} ${CLOCKDEFS}

.if ${MK_OPENSSL} != "no" && !defined(RELEASE_CRUNCH)
CFLAGS+= -DOPENSSL
.endif

LIBOPTS=	${.OBJDIR}/../libopts/libopts.a
LIBPARSE=	${.OBJDIR}/../libparse/libparse.a
LIBNTP=	${.OBJDIR}/../libntp/libntp.a

WARNS?=	0

.include "../Makefile.inc"
