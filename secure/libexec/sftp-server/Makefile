# $FreeBSD: stable/9/secure/libexec/sftp-server/Makefile 204340 2010-02-25 22:44:23Z des $

PROG=   sftp-server
SRCS=   sftp-server.c sftp-common.c sftp-server-main.c
MAN=	sftp-server.8
CFLAGS+=-I${SSHDIR} -include ssh_namespace.h

# required when linking with a dynamic libssh 
SRCS+=	roaming_dummy.c

DPADD=	${LIBSSH} ${LIBCRYPT} ${LIBCRYPTO} ${LIBZ}
LDADD=  -lssh -lcrypt -lcrypto -lz

.include <bsd.prog.mk>

.PATH:	${SSHDIR}

${OBJS} ${POBJS} ${SOBJS}: ssh_namespace.h
