# $FreeBSD: stable/9/gnu/usr.bin/groff/src/preproc/pic/Makefile 114412 2003-05-01 13:22:21Z ru $

PROG_CXX=	pic
SRCS=		lex.cpp main.cpp object.cpp pic.cpp pic_tab.h \
		common.cpp troff.cpp tex.cpp
CFLAGS+=	-I${DIST_DIR} -I.
DPADD=		${LIBGROFF} ${LIBM}
LDADD=		${LIBGROFF} -lm
CLEANFILES=	${MAN} pic.cpp pic_tab.h y.tab.c y.tab.h

pic_tab.h: pic.cpp

.include <bsd.prog.mk>
