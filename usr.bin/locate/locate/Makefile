#	@(#)Makefile	8.1 (Berkeley) 6/6/93
# $FreeBSD: stable/9/usr.bin/locate/locate/Makefile 201386 2010-01-02 10:27:05Z ed $

PROG=	locate
SRCS=	util.c locate.c
CFLAGS+= -I${.CURDIR} -DMMAP # -DDEBUG (print time) -O2 (10% faster)
SCRIPTS=updatedb.sh mklocatedb.sh concatdb.sh
MAN=	locate.1 locate.updatedb.8

WARNS?=	2

SCRIPTSDIR=	${LIBEXECDIR}
.for script in ${SCRIPTS}
SCRIPTSNAME_${script}=	locate.${script:R}
.endfor
MLINKS+= locate.updatedb.8 updatedb.8

# only /usr/src/etc/Makefile install files in /etc
#	${INSTALL} -o root -g wheel -m 644 \
#		${.CURDIR}/locate.rc ${DESTDIR}/etc

.include "../../Makefile.inc"
.include <bsd.prog.mk>
