# $FreeBSD: stable/9/gnu/usr.bin/gdb/gdbtui/Makefile 141911 2005-02-14 12:10:14Z obrien $

PROG=	gdbtui${GDB_SUFFIX}
SRCS=	tui-main.c
NO_MAN=

BULIBS= ${OBJ_BU}/libbfd/libbfd.a ${OBJ_BU}/libopcodes/libopcodes.a \
	${OBJ_BU}/libiberty/libiberty.a
GDBLIBS= ${OBJ_GDB}/libgdb/libgdb.a

# libthread_db.so calls back into gdb for the proc services.  Make all the
# global symbols visible.
LDFLAGS+= -Wl,-E

DPADD=	${GDBLIBS} ${BULIBS} ${LIBM} ${LIBREADLINE} ${LIBTERMCAP} ${LIBGNUREGEX}
LDADD=	${GDBLIBS} ${BULIBS} -lm -lreadline -ltermcap -lgnuregex

.include <bsd.prog.mk>
