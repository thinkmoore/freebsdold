# $FreeBSD: stable/9/sys/modules/dummynet/Makefile 243401 2012-11-22 12:11:32Z glebius $

.include <bsd.own.mk>

.PATH:  ${.CURDIR}/../../netpfil/ipfw
KMOD=   dummynet
SRCS=   ip_dummynet.c
SRCS+= ip_dn_glue.c ip_dn_io.c
SRCS+= dn_heap.c dn_sched_fifo.c dn_sched_qfq.c dn_sched_rr.c dn_sched_wf2q.c 
SRCS+= dn_sched_prio.c
SRCS+=	opt_inet6.h

.if !defined(KERNBUILDDIR)
.if ${MK_INET6_SUPPORT} != "no"
opt_inet6.h:
	echo "#define INET6 1" > ${.TARGET}
.endif
.endif

.include <bsd.kmod.mk>
