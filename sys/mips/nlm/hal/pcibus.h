/*-
 * Copyright 2003-2011 Netlogic Microsystems (Netlogic). All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY Netlogic Microsystems ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL NETLOGIC OR CONTRIBUTORS BE 
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 * NETLOGIC_BSD
 * $FreeBSD: stable/9/sys/mips/nlm/hal/pcibus.h 225394 2011-09-05 10:45:29Z jchandra $
 */

#ifndef __XLP_PCIBUS_H__
#define __XLP_PCIBUS_H__

#define MSI_MIPS_ADDR_BASE              0xfee00000
/* MSI support */
#define MSI_MIPS_ADDR_DEST		0x000ff000
#define MSI_MIPS_ADDR_RH		0x00000008
#define MSI_MIPS_ADDR_RH_OFF		0x00000000
#define MSI_MIPS_ADDR_RH_ON		0x00000008
#define MSI_MIPS_ADDR_DM		0x00000004
#define MSI_MIPS_ADDR_DM_PHYSICAL	0x00000000
#define MSI_MIPS_ADDR_DM_LOGICAL	0x00000004

/* Fields in data for Intel MSI messages. */
#define MSI_MIPS_DATA_TRGRMOD		0x00008000	/* Trigger mode */
#define MSI_MIPS_DATA_TRGREDG		0x00000000	/* edge */
#define MSI_MIPS_DATA_TRGRLVL		0x00008000	/* level */

#define MSI_MIPS_DATA_LEVEL		0x00004000	/* Polarity. */
#define MSI_MIPS_DATA_DEASSERT		0x00000000
#define MSI_MIPS_DATA_ASSERT		0x00004000

#define MSI_MIPS_DATA_DELMOD		0x00000700	/* Delivery Mode */
#define MSI_MIPS_DATA_DELFIXED		0x00000000	/* fixed */
#define MSI_MIPS_DATA_DELLOPRI		0x00000100	/* lowest priority */

#define MSI_MIPS_DATA_INTVEC		0x000000ff

/*
 * Build Intel MSI message and data values from a source.  AMD64 systems
 * seem to be compatible, so we use the same function for both.
 */
#define MIPS_MSI_ADDR(cpu)					       \
        (MSI_MIPS_ADDR_BASE | (cpu) << 12 |			       \
	 MSI_MIPS_ADDR_RH_OFF | MSI_MIPS_ADDR_DM_PHYSICAL)

#define MIPS_MSI_DATA(irq)					       \
        (MSI_MIPS_DATA_TRGRLVL | MSI_MIPS_DATA_DELFIXED |	       \
	 MSI_MIPS_DATA_ASSERT | (irq))

#define PCIE_BRIDGE_CMD		0x1
#define PCIE_BRIDGE_MSI_CAP	0x14
#define PCIE_BRIDGE_MSI_ADDRL	0x15
#define PCIE_BRIDGE_MSI_ADDRH	0x16
#define PCIE_BRIDGE_MSI_DATA	0x17

/* XLP Global PCIE configuration space registers */
#define PCIE_MSI_STATUS		0x25A
#define PCIE_MSI_EN		0x25B
#define PCIE_INT_EN0		0x261

/* PCIE_MSI_EN */
#define PCIE_MSI_VECTOR_INT_EN		0xFFFFFFFF

/* PCIE_INT_EN0 */
#define PCIE_MSI_INT_EN			(1 << 9)

#endif /* __XLP_PCIBUS_H__ */
