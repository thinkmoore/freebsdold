# $FreeBSD: stable/9/usr.sbin/bsdconfig/mouse/Makefile 252995 2013-07-07 19:13:34Z dteske $

NO_OBJ=

SUBDIR= include

FILESDIR=	${LIBEXECDIR}/bsdconfig/110.mouse
FILES=		INDEX USAGE

SCRIPTSDIR=	${FILESDIR}
SCRIPTS=	disable enable flags mouse port type

beforeinstall:
	mkdir -p ${DESTDIR}${FILESDIR}

.include <bsd.prog.mk>
