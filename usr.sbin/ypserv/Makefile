# $FreeBSD: stable/9/usr.sbin/ypserv/Makefile 231702 2012-02-14 19:36:35Z dim $

RPCDIR=	${.CURDIR}/../../include/rpcsvc
.PATH: ${RPCDIR}

PROG=	ypserv
MAN=	ypserv.8 ypinit.8
SRCS=	yp_svc.c yp_server.c yp_dblookup.c yp_dnslookup.c \
	ypxfr_clnt.c yp.h yp_main.c yp_error.c yp_access.c yp_svc_udp.c

CFLAGS+= -DDB_CACHE -DTCP_WRAPPER -I.

WARNS?=	0

DPADD=	${LIBWRAP}
LDADD=	-lwrap

CLEANFILES= yp_svc.c ypxfr_clnt.c yp.h

RPCGEN= RPCGEN_CPP=${CPP:Q} rpcgen -I -C

# We need to remove the 'static' keyword from _rpcsvcstate so that
# yp_main.c can see it.
yp_svc.c: yp.x
	rm -f ${.TARGET}
	${RPCGEN} -DYPSERV_ONLY -m ${RPCDIR}/yp.x | \
	sed s/"static int _rpcsvcstate"/"int _rpcsvcstate"/g > ${.TARGET}

ypxfr_clnt.c: yp.x
	${RPCGEN} -DYPPUSH_ONLY -l -o ${.TARGET} ${RPCDIR}/yp.x

yp.h: yp.x
	${RPCGEN} -h -o ${.TARGET} ${RPCDIR}/yp.x

FILES=	Makefile.yp
FILESNAME= Makefile.dist
FILESDIR= /var/yp
SCRIPTS= ypinit.sh

.if !exists(${DESTDIR}${FILESDIR}/Makefile)
SYMLINKS= ${FILESNAME} ${FILESDIR}/Makefile
.endif

.include <bsd.prog.mk>
