# $FreeBSD: stable/9/usr.sbin/bsnmpd/modules/snmp_hast/Makefile 251010 2013-05-26 18:54:05Z trociny $

.include <bsd.own.mk>

.PATH:	${.CURDIR}/../../../../sbin/hastd

MOD=	hast
SRCS=	ebuf.c
SRCS+=	hast_compression.c hast_proto.c hast_snmp.c
SRCS+=	lzf.c
SRCS+=	nv.c
SRCS+=	parse.y pjdlog.c
SRCS+=	proto.c proto_common.c proto_uds.c
SRCS+=	token.l
SRCS+=	y.tab.h
MAN=	snmp_hast.3

NO_WFORMAT=
NO_WCAST_ALIGN=
NO_WMISSING_VARIABLE_DECLARATIONS=
CFLAGS+=-I${.CURDIR}/../../../../sbin/hastd
CFLAGS+=-DHAVE_CAPSICUM
CFLAGS+=-DINET
.if ${MK_INET6_SUPPORT} != "no"
CFLAGS+=-DINET6
.endif
# This is needed to have WARNS > 1.
CFLAGS+=-DYY_NO_UNPUT
CFLAGS+=-DYY_NO_INPUT
CFLAGS+= -DSNMPTREE_TYPES

DPADD=	${LIBUTIL}
LDADD=	-lutil

XSYM=	begemotHast
DEFS=	${MOD}_tree.def
BMIBS=	BEGEMOT-HAST-MIB.txt

YFLAGS+=-v

CLEANFILES=y.tab.c y.tab.h y.output

.include <bsd.snmpmod.mk>
