# $FreeBSD: stable/9/usr.sbin/tcpdump/tcpdump/Makefile 252283 2013-06-27 00:37:59Z delphij $

.include <bsd.own.mk>

TCPDUMP_DISTDIR?= ${.CURDIR}/../../../contrib/tcpdump
.PATH: ${TCPDUMP_DISTDIR}

PROG=	tcpdump

SRCS=	addrtoname.c \
	af.c \
	checksum.c \
	cpack.c \
	gmpls.c \
	gmt2local.c \
	in_cksum.c \
	ipproto.c \
	l2vpn.c \
	machdep.c \
	nlpid.c \
	oui.c \
	parsenfsfh.c \
	print-802_11.c \
	print-802_15_4.c \
	print-ah.c \
	print-aodv.c \
	print-ap1394.c \
	print-arcnet.c \
	print-arp.c \
	print-ascii.c \
	print-atalk.c \
	print-atm.c \
	print-beep.c \
	print-bfd.c \
	print-bgp.c \
	print-bootp.c \
	print-bt.c \
	print-carp.c \
	print-cdp.c \
	print-cfm.c \
	print-chdlc.c \
	print-cip.c \
	print-cnfp.c \
	print-dccp.c \
	print-decnet.c \
	print-domain.c \
	print-dtp.c \
	print-dvmrp.c \
	print-eap.c \
	print-egp.c \
	print-eigrp.c \
	print-enc.c \
	print-esp.c \
	print-ether.c \
	print-fddi.c \
	print-forces.c \
	print-fr.c \
	print-gre.c \
	print-hsrp.c \
	print-icmp.c \
	print-igmp.c \
	print-igrp.c \
	print-ip.c \
	print-ipcomp.c \
	print-ipfc.c \
	print-ipnet.c \
	print-ipx.c \
	print-isakmp.c \
	print-isoclns.c \
	print-juniper.c \
	print-krb.c \
	print-l2tp.c \
	print-lane.c \
	print-ldp.c \
	print-llc.c \
	print-lldp.c \
	print-lmp.c \
	print-lspping.c \
	print-lwapp.c \
	print-lwres.c \
	print-mobile.c \
	print-mpcp.c \
	print-mpls.c \
	print-msdp.c \
	print-msnlb.c \
	print-nfs.c \
	print-ntp.c \
	print-null.c \
	print-olsr.c \
	print-ospf.c \
	print-otv.c \
	print-pfsync.c \
	print-pgm.c \
	print-pim.c \
	print-ppi.c \
	print-ppp.c \
	print-pppoe.c \
	print-pptp.c \
	print-radius.c \
	print-raw.c \
	print-rip.c \
	print-rpki-rtr.c \
	print-rrcp.c \
	print-rsvp.c \
	print-rx.c \
	print-sctp.c \
	print-sflow.c \
	print-sip.c \
	print-sl.c \
	print-sll.c \
	print-slow.c \
	print-smb.c \
	print-snmp.c \
	print-stp.c \
	print-sunatm.c \
	print-sunrpc.c \
	print-symantec.c \
	print-syslog.c \
	print-tcp.c \
	print-telnet.c \
	print-tftp.c \
	print-timed.c \
	print-tipc.c \
	print-token.c \
	print-udld.c \
	print-udp.c \
	print-vjc.c \
	print-vqp.c \
	print-vrrp.c \
	print-vtp.c \
	print-vxlan.c \
	print-wb.c \
	print-zephyr.c \
	print-zeromq.c \
	setsignal.c \
	signature.c \
	smbutil.c \
	tcpdump.c \
	util.c \
	version.c
CLEANFILES+=	version.c

CFLAGS+= -I${.CURDIR} -I${TCPDUMP_DISTDIR}
CFLAGS+= -DHAVE_CONFIG_H
CFLAGS+= -D_U_="__attribute__((unused))"

.if ${MK_INET6_SUPPORT} != "no"
SRCS+=	print-babel.c \
	print-dhcp6.c \
	print-frag6.c \
	print-icmp6.c \
	print-ip6.c \
	print-ip6opts.c \
	print-mobility.c \
	print-ospf6.c \
	print-ripng.c \
	print-rt6.c
CFLAGS+=	-DINET6
.endif
.if ${MACHINE_CPUARCH} != "i386"
CFLAGS+=	-DLBL_ALIGN
.endif

DPADD=	${LIBL} ${LIBPCAP}
LDADD=	-ll -lpcap
.if ${MK_OPENSSL} != "no" && !defined(RELEASE_CRUNCH)
DPADD+= ${LIBCRYPTO}
LDADD+= -lcrypto
CFLAGS+= -I${DESTDIR}/usr/include/openssl
CFLAGS+= -DHAVE_LIBCRYPTO -DHAVE_OPENSSL_EVP_H
.endif

.if ${MK_PF} != "no"
SRCS+=	print-pflog.c
CFLAGS+= -DHAVE_NET_PFVAR_H
.endif

version.c: ${TCPDUMP_DISTDIR}/VERSION
	rm -f version.c ; \
	    sed 's/.*/char version[] = "&";/' ${TCPDUMP_DISTDIR}/VERSION \
		> version.c

.include <bsd.prog.mk>
