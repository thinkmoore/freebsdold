# $FreeBSD: stable/9/secure/usr.bin/sftp/Makefile 197679 2009-10-01 17:12:52Z des $

PROG=	sftp
SRCS=   sftp.c sftp-client.c sftp-common.c sftp-glob.c progressmeter.c
CFLAGS+=-I${SSHDIR} -include ssh_namespace.h

# required when linking with a dynamic libssh 
SRCS+=	roaming_dummy.c

DPADD=	${LIBSSH} ${LIBCRYPT} ${LIBCRYPTO} ${LIBZ} ${LIBEDIT} ${LIBNCURSES}
LDADD=	-lssh -lcrypt -lcrypto -lz -ledit -lncurses

.include <bsd.prog.mk>

.PATH:	${SSHDIR}

${OBJS} ${POBJS} ${SOBJS}: ssh_namespace.h
