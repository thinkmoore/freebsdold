#
# $FreeBSD: stable/9/sys/modules/cxgbe/t4_firmware/Makefile 252814 2013-07-05 18:27:38Z np $
#

T4FW = ${.CURDIR}/../../../dev/cxgbe/firmware
.PATH: ${T4FW}

KMOD = t4fw_cfg
FIRMWS = ${KMOD}.txt:${KMOD}:1.0.0.0

# You can have additional configuration files in the ${T4FW} directory.
# t4fw_cfg_<name>.txt
CFG_FILES != cd ${T4FW} && echo ${KMOD}_*.txt
.for F in ${CFG_FILES}
.if exists(${F})
FIRMWS += ${F}:${F:C/.txt//}:1.0.0.0
.endif
.endfor

T4FW_VER = 1.8.11.0
FIRMWS += t4fw.fw:t4fw:${T4FW_VER}
CLEANFILES += t4fw.fw

t4fw.fw: t4fw-${T4FW_VER}.bin.uu
	uudecode -o ${.TARGET} ${.ALLSRC}

.include <bsd.kmod.mk>
