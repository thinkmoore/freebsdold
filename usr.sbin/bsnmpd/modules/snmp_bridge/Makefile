#
# $FreeBSD: stable/9/usr.sbin/bsnmpd/modules/snmp_bridge/Makefile 164997 2006-12-07 22:36:17Z syrinx $
#

MOD=	bridge
SRCS=	bridge_snmp.c bridge_if.c bridge_port.c bridge_addrs.c \
	bridge_pf.c bridge_sys.c
CFLAGS+= -DSNMPTREE_TYPES

XSYM=	dot1dBridge newRoot topologyChange begemotBridgeNewRoot \
	begemotBridgeTopologyChange begemotBridgeBaseName

MAN=	snmp_bridge.3

BMIBS=	BRIDGE-MIB.txt BEGEMOT-BRIDGE-MIB.txt RSTP-MIB.txt
DEFS=	${MOD}_tree.def
INCS=	${MOD}_snmp.h

.include <bsd.snmpmod.mk>
