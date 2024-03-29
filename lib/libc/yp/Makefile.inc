#	from: @(#)Makefile.inc	5.3 (Berkeley) 2/20/91
# $FreeBSD: stable/9/lib/libc/yp/Makefile.inc 231702 2012-02-14 19:36:35Z dim $

# yp sources
.PATH: ${.CURDIR}/yp

SRCS+=	xdryp.c yp.h yp_xdr.c yplib.c
CLEANFILES+=	yp.h yp_xdr.c

SYM_MAPS+=	${.CURDIR}/yp/Symbol.map

RPCSRC=	${DESTDIR}/usr/include/rpcsvc/yp.x
RPCGEN=	RPCGEN_CPP=${CPP:Q} rpcgen -C

yp_xdr.c: ${RPCSRC}
	${RPCGEN} -c -o ${.TARGET} ${RPCSRC}

yp.h: ${RPCSRC}
	${RPCGEN} -h -o ${.TARGET} ${RPCSRC}
