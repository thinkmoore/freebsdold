# $FreeBSD: stable/9/kerberos5/libexec/ipropd-master/Makefile 178828 2008-05-07 13:53:12Z dfr $

PROG=	ipropd-master
NO_MAN=
SRCS=	ipropd_common.c ipropd_master.c kadm5_err.h
CFLAGS+=-I${KRB5DIR}/lib/krb5 -I${KRB5DIR}/lib/asn1 -I${KRB5DIR}/lib/roken \
	-I. ${LDAPCFLAGS}
DPADD=	${LIBKADM5SRV} ${LIBHDB} ${LIBKRB5} ${LIBHX509} ${LIBROKEN} ${LIBVERS} \
	${LIBASN1} ${LIBCRYPTO} ${LIBCRYPT} ${LIBCOM_ERR} ${LDAPDPADD}
LDADD=	-lkadm5srv -lhdb -lkrb5 -lhx509 -lroken ${LIBVERS} \
	-lasn1 -lcrypto -lcrypt -lcom_err ${LDAPLDADD}
LDFLAGS=${LDAPLDFLAGS}

foo::
	echo ${LIBHX509}

.include <bsd.prog.mk>

.PATH: ${KRB5DIR}/lib/kadm5
