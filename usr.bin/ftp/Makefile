# $FreeBSD: stable/9/usr.bin/ftp/Makefile 223328 2011-06-20 08:00:32Z gavin $
#	$NetBSD: Makefile,v 1.15 1997/10/18 15:31:20 lukem Exp $
#	from: @(#)Makefile	8.2 (Berkeley) 4/3/94

.include <bsd.own.mk>

# Uncomment the following to provide defaults for gate-ftp operation
#
#CFLAGS+=-DGATE_SERVER=\"ftp-gw.host\" # -DGATE_PORT=21

TNFTP=	${.CURDIR}/../../contrib/tnftp
.PATH: ${TNFTP}/src

PROG=	ftp
SRCS=	cmds.c cmdtab.c complete.c domacro.c fetch.c ftp.c main.c \
	progressbar.c ruserpass.c util.c

.if ${MK_INET6_SUPPORT} != "no"
CFLAGS+= -DINET6
.endif

CFLAGS+= -I${.CURDIR} -I${TNFTP}
LDADD=	-ledit -ltermcap -lutil
DPADD=	${LIBEDIT} ${LIBTERMCAP} ${LIBUTIL}

WARNS?=	2

LINKS=	${BINDIR}/ftp ${BINDIR}/pftp \
	${BINDIR}/ftp ${BINDIR}/gate-ftp
MLINKS=	ftp.1 pftp.1 \
	ftp.1 gate-ftp.1

.include <bsd.prog.mk>
