# $FreeBSD: stable/9/libexec/atrun/Makefile 201380 2010-01-02 09:50:19Z ed $

MAINSRC=${.CURDIR}/../../usr.bin/at

.include "${MAINSRC}/Makefile.inc"

PROG=	atrun
SRCS=	atrun.c gloadavg.c
MAN=	atrun.8

BINDIR=	${ATLIB_DIR}
CLEANFILES= ${MAN}

CFLAGS+=-I${MAINSRC} -I${.CURDIR}
CFLAGS+=-DLOGIN_CAP -DPAM

WARNS?=	2
WFORMAT=0

DPADD=	${LIBPAM} ${LIBUTIL}
LDADD=	${MINUSLPAM} -lutil

atrun.8: atrun.man
	@${ECHO} Making ${.TARGET:T} from ${.ALLSRC:T}; \
	sed -e \
		"s@_ATSPOOL_DIR@$(ATSPOOL_DIR)@g; \
		s@_ATJOB_DIR@$(ATJOB_DIR)@g; \
		s@_ATLIB_DIR@$(ATLIB_DIR)@g; \
		s@_LOADAVG_MX@$(LOADAVG_MX)@g;" \
		< ${.ALLSRC} > ${.TARGET}

.include <bsd.prog.mk>
