/*-
 * Copyright 2007-2009 Solarflare Communications Inc.  All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS AND
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
 */

#include <sys/cdefs.h>
__FBSDID("$FreeBSD: stable/9/sys/dev/sfxge/common/efx_sram.c 228100 2011-11-28 20:28:23Z philip $");

#include "efsys.h"
#include "efx.h"
#include "efx_types.h"
#include "efx_regs.h"
#include "efx_impl.h"

	__checkReturn	int
efx_sram_buf_tbl_set(
	__in		efx_nic_t *enp,
	__in		uint32_t id,
	__in		efsys_mem_t *esmp,
	__in		size_t n)
{
	efx_qword_t qword;
	uint32_t start = id;
	uint32_t stop = start + n;
	efsys_dma_addr_t addr;
	efx_oword_t oword;
	unsigned int count;
	int rc;

	EFSYS_ASSERT3U(enp->en_magic, ==, EFX_NIC_MAGIC);
	EFSYS_ASSERT3U(enp->en_mod_flags, &, EFX_MOD_NIC);

	if (stop >= EFX_BUF_TBL_SIZE) {
		rc = EFBIG;
		goto fail1;
	}

	/* Add the entries into the buffer table */
	addr = EFSYS_MEM_ADDR(esmp);
	for (id = start; id != stop; id++) {
		EFX_POPULATE_QWORD_5(qword,
		    FRF_AZ_IP_DAT_BUF_SIZE, 0, FRF_AZ_BUF_ADR_REGION, 0,
		    FRF_AZ_BUF_ADR_FBUF_DW0,
		    (uint32_t)((addr >> 12) & 0xffffffff),
		    FRF_AZ_BUF_ADR_FBUF_DW1,
		    (uint32_t)((addr >> 12) >> 32),
		    FRF_AZ_BUF_OWNER_ID_FBUF, 0);

		EFX_BAR_TBL_WRITEQ(enp, FR_AZ_BUF_FULL_TBL,
				    id, &qword);

		addr += EFX_BUF_SIZE;
	}

	EFSYS_PROBE2(buf, uint32_t, start, uint32_t, stop - 1);

	/* Flush the write buffer */
	EFX_POPULATE_OWORD_2(oword, FRF_AZ_BUF_UPD_CMD, 1,
	    FRF_AZ_BUF_CLR_CMD, 0);
	EFX_BAR_WRITEO(enp, FR_AZ_BUF_TBL_UPD_REG, &oword);

	/* Poll for the last entry being written to the buffer table */
	EFSYS_ASSERT3U(id, ==, stop);
	addr -= EFX_BUF_SIZE;

	count = 0;
	do {
		EFSYS_PROBE1(wait, unsigned int, count);

		/* Spin for 1 ms */
		EFSYS_SPIN(1000);

		EFX_BAR_TBL_READQ(enp, FR_AZ_BUF_FULL_TBL,
				    id - 1, &qword);

		if (EFX_QWORD_FIELD(qword, FRF_AZ_BUF_ADR_FBUF_DW0) ==
		    (uint32_t)((addr >> 12) & 0xffffffff) &&
		    EFX_QWORD_FIELD(qword, FRF_AZ_BUF_ADR_FBUF_DW1) ==
		    (uint32_t)((addr >> 12) >> 32))
			goto verify;

	} while (++count < 100);

	rc = ETIMEDOUT;
	goto fail2;

verify:
	/* Verify the rest of the entries in the buffer table */
	while (--id != start) {
		addr -= EFX_BUF_SIZE;

		/* Read the buffer table entry */
		EFX_BAR_TBL_READQ(enp, FR_AZ_BUF_FULL_TBL,
				    id - 1, &qword);

		if (EFX_QWORD_FIELD(qword, FRF_AZ_BUF_ADR_FBUF_DW0) !=
		    (uint32_t)((addr >> 12) & 0xffffffff) ||
		    EFX_QWORD_FIELD(qword, FRF_AZ_BUF_ADR_FBUF_DW1) !=
		    (uint32_t)((addr >> 12) >> 32)) {
			rc = EFAULT;
			goto fail3;
		}
	}

	return (0);

fail3:
	EFSYS_PROBE(fail3);

	id = stop;

fail2:
	EFSYS_PROBE(fail2);

	EFX_POPULATE_OWORD_4(oword, FRF_AZ_BUF_UPD_CMD, 0,
	    FRF_AZ_BUF_CLR_CMD, 1, FRF_AZ_BUF_CLR_END_ID, id - 1,
	    FRF_AZ_BUF_CLR_START_ID, start);
	EFX_BAR_WRITEO(enp, FR_AZ_BUF_TBL_UPD_REG, &oword);

fail1:
	EFSYS_PROBE1(fail1, int, rc);

	return (rc);
}

		void
efx_sram_buf_tbl_clear(
	__in	efx_nic_t *enp,
	__in	uint32_t id,
	__in	size_t n)
{
	efx_oword_t oword;
	uint32_t start = id;
	uint32_t stop = start + n;

	EFSYS_ASSERT3U(enp->en_magic, ==, EFX_NIC_MAGIC);
	EFSYS_ASSERT3U(enp->en_mod_flags, &, EFX_MOD_NIC);

	EFSYS_ASSERT3U(stop, <, EFX_BUF_TBL_SIZE);

	EFSYS_PROBE2(buf, uint32_t, start, uint32_t, stop - 1);

	EFX_POPULATE_OWORD_4(oword, FRF_AZ_BUF_UPD_CMD, 0,
	    FRF_AZ_BUF_CLR_CMD, 1, FRF_AZ_BUF_CLR_END_ID, stop - 1,
	    FRF_AZ_BUF_CLR_START_ID, start);
	EFX_BAR_WRITEO(enp, FR_AZ_BUF_TBL_UPD_REG, &oword);
}


#if EFSYS_OPT_DIAG

static			void
efx_sram_byte_increment_set(
	__in		size_t row,
	__in		boolean_t negate,
	__out		efx_qword_t *eqp)
{
	size_t offset = row * FR_AZ_SRM_DBG_REG_STEP;
	unsigned int index;

	_NOTE(ARGUNUSED(negate))

	for (index = 0; index < sizeof (efx_qword_t); index++)
		eqp->eq_u8[index] = offset + index;
}

static			void
efx_sram_all_the_same_set(
	__in		size_t row,
	__in		boolean_t negate,
	__out		efx_qword_t *eqp)
{
	_NOTE(ARGUNUSED(row))

	if (negate)
		EFX_SET_QWORD(*eqp);
	else
		EFX_ZERO_QWORD(*eqp);
}

static			void
efx_sram_bit_alternate_set(
	__in		size_t row,
	__in		boolean_t negate,
	__out		efx_qword_t *eqp)
{
	_NOTE(ARGUNUSED(row))

	EFX_POPULATE_QWORD_2(*eqp,
	    EFX_DWORD_0, (negate) ? 0x55555555 : 0xaaaaaaaa,
	    EFX_DWORD_1, (negate) ? 0x55555555 : 0xaaaaaaaa);
}

static			void
efx_sram_byte_alternate_set(
	__in		size_t row,
	__in		boolean_t negate,
	__out		efx_qword_t *eqp)
{
	_NOTE(ARGUNUSED(row))

	EFX_POPULATE_QWORD_2(*eqp,
	    EFX_DWORD_0, (negate) ? 0x00ff00ff : 0xff00ff00,
	    EFX_DWORD_1, (negate) ? 0x00ff00ff : 0xff00ff00);
}

static			void
efx_sram_byte_changing_set(
	__in		size_t row,
	__in		boolean_t negate,
	__out		efx_qword_t *eqp)
{
	size_t offset = row * FR_AZ_SRM_DBG_REG_STEP;
	unsigned int index;

	for (index = 0; index < sizeof (efx_qword_t); index++) {
		uint8_t byte;

		if (offset / 256 == 0)
			byte = (uint8_t)((offset % 257) % 256);
		else
			byte = (uint8_t)(~((offset - 8) % 257) % 256);

		eqp->eq_u8[index] = (negate) ? ~byte : byte;
	}
}

static			void
efx_sram_bit_sweep_set(
	__in		size_t row,
	__in		boolean_t negate,
	__out		efx_qword_t *eqp)
{
	size_t offset = row * FR_AZ_SRM_DBG_REG_STEP;

	if (negate) {
		EFX_SET_QWORD(*eqp);
		EFX_CLEAR_QWORD_BIT(*eqp, (offset / sizeof (efx_qword_t)) % 64);
	} else {
		EFX_ZERO_QWORD(*eqp);
		EFX_SET_QWORD_BIT(*eqp, (offset / sizeof (efx_qword_t)) % 64);
	}
}

efx_sram_pattern_fn_t	__cs __efx_sram_pattern_fns[] = {
	efx_sram_byte_increment_set,
	efx_sram_all_the_same_set,
	efx_sram_bit_alternate_set,
	efx_sram_byte_alternate_set,
	efx_sram_byte_changing_set,
	efx_sram_bit_sweep_set
};

	__checkReturn	int
efx_sram_test(
	__in		efx_nic_t *enp,
	__in		efx_pattern_type_t type)
{
	efx_nic_ops_t *enop = enp->en_enop;
	efx_sram_pattern_fn_t func;

	EFSYS_ASSERT3U(enp->en_magic, ==, EFX_NIC_MAGIC);

	EFSYS_ASSERT3U(enp->en_mod_flags, &, EFX_MOD_NIC);

	EFSYS_ASSERT(!(enp->en_mod_flags & EFX_MOD_RX));
	EFSYS_ASSERT(!(enp->en_mod_flags & EFX_MOD_TX));
	EFSYS_ASSERT(!(enp->en_mod_flags & EFX_MOD_EV));

	/* Select pattern generator */
	EFSYS_ASSERT3U(type, <, EFX_PATTERN_NTYPES);
	func = __efx_sram_pattern_fns[type];

	return (enop->eno_sram_test(enp, func));
}

#endif	/* EFSYS_OPT_DIAG */
