#	$FreeBSD: stable/9/sbin/ipf/ipnat/Makefile 162199 2006-09-10 08:58:47Z obrien $

PROG=		ipnat
SRCS=		${GENHDRS} ipnat.c ipnat_y.c ipnat_l.c
MAN=		ipnat.8 ipnat.4 ipnat.5
MLINKS=		ipnat.5 ipnat.conf.5
CFLAGS+=	-I.

GENHDRS=	ipnat_l.h ipnat_y.h
DPSRCS+=	${GENHDRS}

CLEANFILES+=	${GENHDRS} ipnat_y.c ipnat_l.c

ipnat_y.c: ipnat_y.y
	${YACC} -d ${.ALLSRC}
	sed -e 's/yy/ipnat_yy/g' \
	    -e 's/y.tab.c/ipnat_y.c/' \
	    -e s/\"ipnat_y.y\"/\"..\\/tools\\/ipnat_y.y\"/ \
	    y.tab.c > ${.TARGET}
	sed -e 's/yy/ipnat_yy/g' \
	    -e 's/y.tab.h/ipnat_y.h/' \
	    y.tab.h > ${.TARGET:.c=.h}

ipnat_y.h: ipnat_y.c

ipnat_l.c: lexer.c
	sed -e 's/yy/ipnat_yy/g' \
	    -e 's/y.tab.h/ipnat_y.h/' \
	    -e 's/lexer.h/ipnat_l.h/' \
	    ${.ALLSRC} > ${.TARGET}

ipnat_l.h: lexer.h
	sed -e 's/yy/ipnat_yy/g' \
	    ${.ALLSRC} > ${.TARGET}

.include <bsd.prog.mk>
