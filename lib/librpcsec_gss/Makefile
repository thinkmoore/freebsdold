# $FreeBSD: stable/9/lib/librpcsec_gss/Makefile 201381 2010-01-02 09:58:07Z ed $

LIB=	rpcsec_gss
SHLIB_MAJOR= 1
SRCS+=	rpcsec_gss.c rpcsec_gss_prot.c rpcsec_gss_conf.c rpcsec_gss_misc.c \
	svc_rpcsec_gss.c

DPADD+=	${LIBGSSAPI}
LDADD+=	-lgssapi

VERSION_DEF=	${.CURDIR}/../libc/Versions.def
SYMBOL_MAPS=	${.CURDIR}/Symbol.map

CFLAGS+= -I${.CURDIR}/../../include
CFLAGS+= -I${.CURDIR}/../../libc_rpc
NO_PROFILE=

MAN=	rpcsec_gss.3
MAN+=	rpc_gss_seccreate.3
MAN+=	rpc_gss_set_defaults.3
MAN+=	rpc_gss_max_data_length.3
MAN+=	rpc_gss_get_error.3

MAN+=	rpc_gss_mech_to_oid.3
MAN+=	rpc_gss_oid_to_mech.3
MAN+=	rpc_gss_qop_to_num.3
MAN+=	rpc_gss_get_mechanisms.3
MAN+=	rpc_gss_get_mech_info.3
MAN+=	rpc_gss_get_versions.3
MAN+=	rpc_gss_is_installed.3

MAN+=	rpc_gss_set_svc_name.3
MAN+=	rpc_gss_getcred.3
MAN+=	rpc_gss_set_callback.3
MAN+=	rpc_gss_get_principal_name.3
MAN+=	rpc_gss_svc_max_data_length.3

.include <bsd.lib.mk>
