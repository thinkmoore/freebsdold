# From:	@(#)Makefile	8.3 (Berkeley) 4/2/94
# $FreeBSD: stable/9/usr.bin/passwd/Makefile 201386 2010-01-02 10:27:05Z ed $

.include <bsd.own.mk>

PROG	 = passwd
BINOWN	 = root
BINMODE	 = 4555
DPADD	 = ${LIBPAM}
LDADD	 = ${MINUSLPAM}
.if ${MK_NIS} != "no"
LINKS	 = ${BINDIR}/passwd ${BINDIR}/yppasswd
MLINKS	 = passwd.1 yppasswd.1
.endif

beforeinstall:
.for i in passwd yppasswd
	[ ! -e ${DESTDIR}${BINDIR}/$i ] || \
		chflags noschg ${DESTDIR}${BINDIR}/$i || true
.endfor

afterinstall:
	-chflags schg ${DESTDIR}${BINDIR}/passwd

.include <bsd.prog.mk>
