/*-
 * Copyright (c) 2002, 2003 Wasabi Systems, Inc.
 * All rights reserved.
 *
 * Written by Jason R. Thorpe for Wasabi Systems, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed for the NetBSD Project by
 *	Wasabi Systems, Inc.
 * 4. The name of Wasabi Systems, Inc. may not be used to endorse
 *    or promote products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY WASABI SYSTEMS, INC. ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL WASABI SYSTEMS, INC
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * from: FreeBSD: //depot/projects/arm/src/sys/arm/xscale/pxa2x0/pxa2x0var.h, rev 1
 *
 * $FreeBSD: stable/9/sys/arm/mv/mvvar.h 209131 2010-06-13 13:28:53Z raj $
 */

#ifndef _MVVAR_H_
#define _MVVAR_H_

#include <sys/rman.h>
#include <vm/vm.h>
#include <vm/pmap.h>
#include <machine/pmap.h>
#include <machine/vm.h>

#define	MV_TYPE_PCI		0
#define	MV_TYPE_PCIE		1

struct gpio_config {
	int		gc_gpio;	/* GPIO number */
	uint32_t	gc_flags;	/* GPIO flags */
	int		gc_output;	/* GPIO output value */
};

struct decode_win {
	int		target;		/* Mbus unit ID */
	int		attr;		/* Attributes of the target interface */
	vm_paddr_t	base;		/* Physical base addr */
	uint32_t	size;
	int		remap;
};

extern const struct pmap_devmap pmap_devmap[];
extern const struct gpio_config mv_gpio_config[];
extern const struct decode_win *idma_wins;
extern const struct decode_win *xor_wins;
extern int idma_wins_no;
extern int xor_wins_no;

/* Function prototypes */
int mv_gpio_setup_intrhandler(const char *name, driver_filter_t *filt,
    void (*hand)(void *), void *arg, int pin, int flags, void **cookiep);
void mv_gpio_intr_mask(int pin);
void mv_gpio_intr_unmask(int pin);
void mv_gpio_out(uint32_t pin, uint8_t val, uint8_t enable);
uint8_t mv_gpio_in(uint32_t pin);
int platform_gpio_init(void);

int soc_decode_win(void);
void soc_id(uint32_t *dev, uint32_t *rev);
void soc_dump_decode_win(void);
uint32_t soc_power_ctrl_get(uint32_t mask);
void soc_power_ctrl_set(uint32_t mask);

int decode_win_cpu_set(int target, int attr, vm_paddr_t base, uint32_t size,
    int remap);
int decode_win_overlap(int, int, const struct decode_win *);
int win_cpu_can_remap(int);

int ddr_is_active(int i);
uint32_t ddr_base(int i);
uint32_t ddr_size(int i);
uint32_t ddr_attr(int i);
uint32_t ddr_target(int i);

uint32_t cpu_extra_feat(void);
uint32_t get_tclk(void);
uint32_t read_cpu_ctrl(uint32_t);
void write_cpu_ctrl(uint32_t, uint32_t);

#endif /* _MVVAR_H_ */
