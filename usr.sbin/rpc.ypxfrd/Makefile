# $FreeBSD: stable/9/usr.sbin/rpc.ypxfrd/Makefile 231702 2012-02-14 19:36:35Z dim $

.PATH: ${.CURDIR}/../../usr.sbin/ypserv

PROG=	rpc.ypxfrd
MAN=	rpc.ypxfrd.8
SRCS=	ypxfrd_svc.c ypxfrd.h ypxfrd_server.c yp_error.c \
	yp_access.c ypxfrd_main.c

CFLAGS+= -I. -DXFRBLOCKSIZE=65535

WARNS?=	2

DPADD=	${LIBRPCSVC}
LDADD=	-lrpcsvc

CLEANFILES= ypxfrd_svc.c ypxfrd.h

RPCDIR=	${.CURDIR}/../../include/rpcsvc
RPCGEN= RPCGEN_CPP=${CPP:Q} rpcgen -I -C

# We need to remove the 'static' keyword from _rpcsvcstate so that
# ypxfrd_main.c can see it.
ypxfrd_svc.c: ${RPCDIR}/ypxfrd.x
	rm -f ${.TARGET}
	${RPCGEN} -m ${RPCDIR}/ypxfrd.x | \
	sed s/"static int _rpcsvcstate"/"int _rpcsvcstate"/g > ${.TARGET}

# ypxfrd_xdr.c: ${RPCDIR}/ypxfrd.x
#	rm -f ${.TARGET}
#	${RPCGEN} -c -o ${.TARGET} ${RPCDIR}/ypxfrd.x

ypxfrd.h: ${RPCDIR}/ypxfrd.x
	rm -f ${.TARGET}
	${RPCGEN} -h -o ${.TARGET} ${RPCDIR}/ypxfrd.x

.include <bsd.prog.mk>
