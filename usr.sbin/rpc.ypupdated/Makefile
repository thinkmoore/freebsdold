# $FreeBSD: stable/9/usr.sbin/rpc.ypupdated/Makefile 231702 2012-02-14 19:36:35Z dim $

.PATH: ${.CURDIR}/../ypserv ${.CURDIR}/../../libexec/ypxfr

PROG=	rpc.ypupdated
NO_MAN=
SRCS=	ypupdate_prot_svc.c ypupdate_prot.h ypupdated_main.c \
	yp_error.c update.c ypupdated_server.c \
	yp_dblookup.c yp_dbwrite.c yp_dbdelete.c yp_dbupdate.c

#CFLAGS+= -DYP
CFLAGS+= -I${.CURDIR}/../ypserv -I. -I${.CURDIR}/../../libexec/ypxfr

WARNS?=	1

DPADD=	${LIBRPCSVC}
LDADD=	-lrpcsvc

CLEANFILES= ypupdate_prot_svc.c ypupdate_prot.h

RPCDIR=	${DESTDIR}/usr/include/rpcsvc
RPCGEN= RPCGEN_CPP=${CPP:Q} rpcgen -I -C

# We need to remove the 'static' keyword from _rpcsvcstate so that
# ypupdated_main.c can see it.
ypupdate_prot_svc.c: ${RPCDIR}/ypupdate_prot.x
	rm -f ${.TARGET}
	${RPCGEN} -m ${RPCDIR}/ypupdate_prot.x | \
	sed s/"static int _rpcsvcstate"/"int _rpcsvcstate"/g > ${.TARGET}

ypupdate_prot.h: ${RPCDIR}/ypupdate_prot.x
	${RPCGEN} -h -o ${.TARGET} ${RPCDIR}/ypupdate_prot.x

.include <bsd.prog.mk>
