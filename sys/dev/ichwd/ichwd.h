/*-
 * Copyright (c) 2004 Texas A&M University
 * All rights reserved.
 *
 * Developer: Wm. Daryl Hawkins
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: stable/9/sys/dev/ichwd/ichwd.h 231153 2012-02-07 19:40:52Z jhb $
 */

#ifndef _ICHWD_H_
#define _ICHWD_H_

struct ichwd_device {
	uint16_t		 device;
	char			*desc;
	unsigned int		 version;
};

struct ichwd_softc {
	device_t		 device;
	device_t		 ich;
	int			 ich_version;

	int			 active;
	unsigned int		 timeout;

	int			 smi_enabled;
	int			 smi_rid;
	struct resource		*smi_res;

	int			 tco_rid;
	struct resource		*tco_res;

	int			 gcs_rid;
	struct resource		*gcs_res;

	eventhandler_tag	 ev_tag;
};

#define VENDORID_INTEL		0x8086
#define DEVICEID_CPT0		0x1c40
#define DEVICEID_CPT1		0x1c41
#define DEVICEID_CPT2		0x1c42
#define DEVICEID_CPT3		0x1c43
#define DEVICEID_CPT4		0x1c44
#define DEVICEID_CPT5		0x1c45
#define DEVICEID_CPT6		0x1c46
#define DEVICEID_CPT7		0x1c47
#define DEVICEID_CPT8		0x1c48
#define DEVICEID_CPT9		0x1c49
#define DEVICEID_CPT10		0x1c4a
#define DEVICEID_CPT11		0x1c4b
#define DEVICEID_CPT12		0x1c4c
#define DEVICEID_CPT13		0x1c4d
#define DEVICEID_CPT14		0x1c4e
#define DEVICEID_CPT15		0x1c4f
#define DEVICEID_CPT16		0x1c50
#define DEVICEID_CPT17		0x1c51
#define DEVICEID_CPT18		0x1c52
#define DEVICEID_CPT19		0x1c53
#define DEVICEID_CPT20		0x1c54
#define DEVICEID_CPT21		0x1c55
#define DEVICEID_CPT22		0x1c56
#define DEVICEID_CPT23		0x1c57
#define DEVICEID_CPT24		0x1c58
#define DEVICEID_CPT25		0x1c59
#define DEVICEID_CPT26		0x1c5a
#define DEVICEID_CPT27		0x1c5b
#define DEVICEID_CPT28		0x1c5c
#define DEVICEID_CPT29		0x1c5d
#define DEVICEID_CPT30		0x1c5e
#define DEVICEID_CPT31		0x1c5f
#define DEVICEID_PATSBURG_LPC1	0x1d40
#define DEVICEID_PATSBURG_LPC2	0x1d41
#define DEVICEID_PPT0		0x1e40
#define DEVICEID_PPT1		0x1e41
#define DEVICEID_PPT2		0x1e42
#define DEVICEID_PPT3		0x1e43
#define DEVICEID_PPT4		0x1e44
#define DEVICEID_PPT5		0x1e45
#define DEVICEID_PPT6		0x1e46
#define DEVICEID_PPT7		0x1e47
#define DEVICEID_PPT8		0x1e48
#define DEVICEID_PPT9		0x1e49
#define DEVICEID_PPT10		0x1e4a
#define DEVICEID_PPT11		0x1e4b
#define DEVICEID_PPT12		0x1e4c
#define DEVICEID_PPT13		0x1e4d
#define DEVICEID_PPT14		0x1e4e
#define DEVICEID_PPT15		0x1e4f
#define DEVICEID_PPT16		0x1e50
#define DEVICEID_PPT17		0x1e51
#define DEVICEID_PPT18		0x1e52
#define DEVICEID_PPT19		0x1e53
#define DEVICEID_PPT20		0x1e54
#define DEVICEID_PPT21		0x1e55
#define DEVICEID_PPT22		0x1e56
#define DEVICEID_PPT23		0x1e57
#define DEVICEID_PPT24		0x1e58
#define DEVICEID_PPT25		0x1e59
#define DEVICEID_PPT26		0x1e5a
#define DEVICEID_PPT27		0x1e5b
#define DEVICEID_PPT28		0x1e5c
#define DEVICEID_PPT29		0x1e5d
#define DEVICEID_PPT30		0x1e5e
#define DEVICEID_PPT31		0x1e5f
#define DEVICEID_DH89XXCC_LPC	0x2310
#define DEVICEID_82801AA	0x2410
#define DEVICEID_82801AB	0x2420
#define DEVICEID_82801BA	0x2440
#define DEVICEID_82801BAM	0x244c
#define DEVICEID_82801CA	0x2480
#define DEVICEID_82801CAM	0x248c
#define DEVICEID_82801DB	0x24c0
#define DEVICEID_82801DBM	0x24cc
#define DEVICEID_82801E		0x2450
#define DEVICEID_82801EB	0x24dc
#define DEVICEID_82801EBR	0x24d0
#define DEVICEID_6300ESB	0x25a1
#define DEVICEID_82801FBR	0x2640
#define DEVICEID_ICH6M		0x2641
#define DEVICEID_ICH6W		0x2642
#define DEVICEID_63XXESB	0x2670
#define DEVICEID_ICH7		0x27b8
#define DEVICEID_ICH7DH		0x27b0
#define DEVICEID_ICH7M		0x27b9
#define DEVICEID_NM10		0x27bc
#define DEVICEID_ICH7MDH	0x27bd
#define DEVICEID_ICH8		0x2810
#define DEVICEID_ICH8DH		0x2812
#define DEVICEID_ICH8DO		0x2814
#define DEVICEID_ICH8M		0x2815
#define DEVICEID_ICH8ME		0x2811
#define DEVICEID_ICH9		0x2918
#define DEVICEID_ICH9DH		0x2912
#define DEVICEID_ICH9DO		0x2914
#define DEVICEID_ICH9M		0x2919
#define DEVICEID_ICH9ME		0x2917
#define DEVICEID_ICH9R		0x2916
#define DEVICEID_ICH10		0x3a18
#define DEVICEID_ICH10D		0x3a1a
#define DEVICEID_ICH10DO	0x3a14
#define DEVICEID_ICH10R		0x3a16
#define DEVICEID_PCH		0x3b00
#define DEVICEID_PCHM		0x3b01
#define DEVICEID_P55		0x3b02
#define DEVICEID_PM55		0x3b03
#define DEVICEID_H55		0x3b06
#define DEVICEID_QM57		0x3b07
#define DEVICEID_H57		0x3b08
#define DEVICEID_HM55		0x3b09
#define DEVICEID_Q57		0x3b0a
#define DEVICEID_HM57		0x3b0b
#define DEVICEID_PCHMSFF	0x3b0d
#define DEVICEID_QS57		0x3b0f
#define DEVICEID_3400		0x3b12
#define DEVICEID_3420		0x3b14
#define DEVICEID_3450		0x3b16

/* ICH LPC Interface Bridge Registers (ICH5 and older) */
#define ICH_GEN_STA		0xd4
#define ICH_GEN_STA_NO_REBOOT	0x02
#define ICH_PMBASE		0x40 /* ACPI base address register */
#define ICH_PMBASE_MASK		0x7f80 /* bits 7-15 */

/* ICH Chipset Configuration Registers (ICH6 and newer) */
#define ICH_RCBA		0xf0
#define ICH_GCS_OFFSET		0x3410
#define ICH_GCS_SIZE		0x4
#define ICH_GCS_NO_REBOOT	0x20

/* register names and locations (relative to PMBASE) */
#define SMI_BASE		0x30 /* base address for SMI registers */
#define SMI_LEN			0x08
#define SMI_EN			0x00 /* SMI Control and Enable Register */
#define SMI_STS			0x04 /* SMI Status Register */
#define TCO_BASE		0x60 /* base address for TCO registers */
#define TCO_LEN			0x20
#define TCO_RLD			0x00 /* TCO Reload and Current Value */
#define TCO_TMR1		0x01 /* TCO Timer Initial Value
					(ICH5 and older, 8 bits) */
#define TCO_TMR2		0x12 /* TCO Timer Initial Value
					(ICH6 and newer, 16 bits) */
#define TCO_DAT_IN		0x02 /* TCO Data In (DO NOT USE) */
#define TCO_DAT_OUT		0x03 /* TCO Data Out (DO NOT USE) */
#define TCO1_STS		0x04 /* TCO Status 1 */
#define TCO2_STS		0x06 /* TCO Status 2 */
#define TCO1_CNT		0x08 /* TCO Control 1 */
#define TCO2_CNT		0x08 /* TCO Control 2 */
#define TCO_MESSAGE1		0x0c /* TCO Message 1 */
#define TCO_MESSAGE2		0x0d /* TCO Message 2 */

/* bit definitions for SMI_EN and SMI_STS */
#define SMI_TCO_EN		0x2000
#define SMI_TCO_STS		0x2000
#define SMI_GBL_EN		0x0001

/* timer value mask for TCO_RLD and TCO_TMR */
#define TCO_TIMER_MASK		0x1f

/* status bits for TCO1_STS */
#define TCO_NEWCENTURY		0x80 /* set for RTC year roll over (99 to 00) */
#define TCO_TIMEOUT		0x08 /* timed out */
#define TCO_INT_STS		0x04 /* data out (DO NOT USE) */
#define TCO_SMI_STS		0x02 /* data in (DO NOT USE) */

/* status bits for TCO2_STS */
#define TCO_BOOT_STS		0x04 /* failed to come out of reset */
#define TCO_SECOND_TO_STS	0x02 /* ran down twice */

/* control bits for TCO1_CNT */
#define TCO_TMR_HALT		0x0800		/* clear to enable WDT */
#define TCO_NMI2SMI_EN		0x0200		/* convert NMIs to SMIs */
#define TCO_CNT_PRESERVE	TCO_NMI2SMI_EN	/* preserve these bits */
#define TCO_NMI_NOW		0x0100		/* trigger an NMI */

/*
 * Masks for the TCO timer value field in TCO_RLD.
 * If the datasheets are to be believed, the minimum value actually varies
 * from chipset to chipset - 4 for ICH5 and 2 for all other chipsets.
 * I suspect this is a bug in the ICH5 datasheet and that the minimum is
 * uniformly 2, but I'd rather err on the side of caution.
 */
#define TCO_RLD_TMR_MIN		0x0004
#define TCO_RLD1_TMR_MAX	0x003f
#define TCO_RLD2_TMR_MAX	0x03ff

/* approximate length in nanoseconds of one WDT tick (about 0.6 sec) */
#define ICHWD_TICK		600000000

#endif
