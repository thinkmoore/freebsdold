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
__FBSDID("$FreeBSD: stable/9/sys/dev/sfxge/common/efx_ev.c 228100 2011-11-28 20:28:23Z philip $");

#include "efsys.h"
#include "efx.h"
#include "efx_types.h"
#include "efx_regs.h"
#include "efx_impl.h"

#if EFSYS_OPT_QSTATS
#define	EFX_EV_QSTAT_INCR(_eep, _stat)					\
	do {								\
		(_eep)->ee_stat[_stat]++;				\
	_NOTE(CONSTANTCONDITION)					\
	} while (B_FALSE)
#else
#define	EFX_EV_QSTAT_INCR(_eep, _stat)
#endif

	__checkReturn	int
efx_ev_init(
	__in		efx_nic_t *enp)
{
	efx_oword_t oword;
	int rc;

	EFSYS_ASSERT3U(enp->en_magic, ==, EFX_NIC_MAGIC);
	EFSYS_ASSERT3U(enp->en_mod_flags, &, EFX_MOD_INTR);

	if (enp->en_mod_flags & EFX_MOD_EV) {
		rc = EINVAL;
		goto fail1;
	}

	EFSYS_ASSERT3U(enp->en_ev_qcount, ==, 0);

	/*
	 * Program the event queue for receive and transmit queue
	 * flush events.
	 */
	EFX_BAR_READO(enp, FR_AZ_DP_CTRL_REG, &oword);
	EFX_SET_OWORD_FIELD(oword, FRF_AZ_FLS_EVQ_ID, 0);
	EFX_BAR_WRITEO(enp, FR_AZ_DP_CTRL_REG, &oword);

	enp->en_mod_flags |= EFX_MOD_EV;
	return (0);

fail1:
	EFSYS_PROBE1(fail1, int, rc);

	return (rc);
}

static  __checkReturn   boolean_t
efx_ev_rx_not_ok(
	__in		efx_evq_t *eep,
	__in		efx_qword_t *eqp,
	__in		uint32_t label,
	__in		uint32_t id,
	__inout		uint16_t *flagsp)
{
	boolean_t ignore = B_FALSE;

	if (EFX_QWORD_FIELD(*eqp, FSF_AZ_RX_EV_TOBE_DISC) != 0) {
		EFX_EV_QSTAT_INCR(eep, EV_RX_TOBE_DISC);
		EFSYS_PROBE(tobe_disc);
		/* Assume this is a unicast address mismatch, unless below
		 * we find either FSF_AZ_RX_EV_ETH_CRC_ERR or
		 * EV_RX_PAUSE_FRM_ERR is set.
		 */
		(*flagsp) |= EFX_ADDR_MISMATCH;
	}

	if (EFX_QWORD_FIELD(*eqp, FSF_AZ_RX_EV_FRM_TRUNC) != 0) {
		EFSYS_PROBE2(frm_trunc, uint32_t, label, uint32_t, id);
		EFX_EV_QSTAT_INCR(eep, EV_RX_FRM_TRUNC);
		(*flagsp) |= EFX_DISCARD;

#if (EFSYS_OPT_RX_HDR_SPLIT || EFSYS_OPT_RX_SCATTER)
		/* Lookout for payload queue ran dry errors and ignore them.
		 *
		 * Sadly for the header/data split cases, the descriptor
		 * pointer in this event refers to the header queue and
		 * therefore cannot be easily detected as duplicate.
		 * So we drop these and rely on the receive processing seeing
		 * a subsequent packet with FSF_AZ_RX_EV_SOP set to discard
		 * the partially received packet.
		 */
		if ((EFX_QWORD_FIELD(*eqp, FSF_AZ_RX_EV_SOP) == 0) &&
		    (EFX_QWORD_FIELD(*eqp, FSF_AZ_RX_EV_JUMBO_CONT) == 0) &&
		    (EFX_QWORD_FIELD(*eqp, FSF_AZ_RX_EV_BYTE_CNT) == 0))
			ignore = B_TRUE;
#endif	/* EFSYS_OPT_RX_HDR_SPLIT || EFSYS_OPT_RX_SCATTER */
	}

	if (EFX_QWORD_FIELD(*eqp, FSF_AZ_RX_EV_ETH_CRC_ERR) != 0) {
		EFX_EV_QSTAT_INCR(eep, EV_RX_ETH_CRC_ERR);
		EFSYS_PROBE(crc_err);
		(*flagsp) &= ~EFX_ADDR_MISMATCH;
		(*flagsp) |= EFX_DISCARD;
	}

	if (EFX_QWORD_FIELD(*eqp, FSF_AZ_RX_EV_PAUSE_FRM_ERR) != 0) {
		EFX_EV_QSTAT_INCR(eep, EV_RX_PAUSE_FRM_ERR);
		EFSYS_PROBE(pause_frm_err);
		(*flagsp) &= ~EFX_ADDR_MISMATCH;
		(*flagsp) |= EFX_DISCARD;
	}

	if (EFX_QWORD_FIELD(*eqp, FSF_AZ_RX_EV_BUF_OWNER_ID_ERR) != 0) {
		EFX_EV_QSTAT_INCR(eep, EV_RX_BUF_OWNER_ID_ERR);
		EFSYS_PROBE(owner_id_err);
		(*flagsp) |= EFX_DISCARD;
	}

	if (EFX_QWORD_FIELD(*eqp, FSF_AZ_RX_EV_IP_HDR_CHKSUM_ERR) != 0) {
		EFX_EV_QSTAT_INCR(eep, EV_RX_IPV4_HDR_CHKSUM_ERR);
		EFSYS_PROBE(ipv4_err);
		(*flagsp) &= ~EFX_CKSUM_IPV4;
	}

	if (EFX_QWORD_FIELD(*eqp, FSF_AZ_RX_EV_TCP_UDP_CHKSUM_ERR) != 0) {
		EFX_EV_QSTAT_INCR(eep, EV_RX_TCP_UDP_CHKSUM_ERR);
		EFSYS_PROBE(udp_chk_err);
		(*flagsp) &= ~EFX_CKSUM_TCPUDP;
	}

	if (EFX_QWORD_FIELD(*eqp, FSF_AZ_RX_EV_IP_FRAG_ERR) != 0) {
		EFX_EV_QSTAT_INCR(eep, EV_RX_IP_FRAG_ERR);

		/*
		 * If IP is fragmented FSF_AZ_RX_EV_IP_FRAG_ERR is set. This
		 * causes FSF_AZ_RX_EV_PKT_OK to be clear. This is not an error
		 * condition.
		 */
		(*flagsp) &= ~(EFX_PKT_TCP | EFX_PKT_UDP | EFX_CKSUM_TCPUDP);
	}

	return (ignore);
}

static	__checkReturn	boolean_t
efx_ev_rx(
	__in		efx_evq_t *eep,
	__in		efx_qword_t *eqp,
	__in		const efx_ev_callbacks_t *eecp,
	__in_opt	void *arg)
{
	efx_nic_t *enp = eep->ee_enp;
	uint32_t id;
	uint32_t size;
	uint32_t label;
	boolean_t ok;
#if (EFSYS_OPT_RX_HDR_SPLIT || EFSYS_OPT_RX_SCATTER)
	boolean_t sop;
	boolean_t jumbo_cont;
#endif	/* EFSYS_OPT_RX_HDR_SPLIT || EFSYS_OPT_RX_SCATTER */
	uint32_t hdr_type;
	boolean_t is_v6;
	uint16_t flags;
	boolean_t ignore;
	boolean_t should_abort;

	EFX_EV_QSTAT_INCR(eep, EV_RX);

	/* Basic packet information */
	id = EFX_QWORD_FIELD(*eqp, FSF_AZ_RX_EV_DESC_PTR);
	size = EFX_QWORD_FIELD(*eqp, FSF_AZ_RX_EV_BYTE_CNT);
	label = EFX_QWORD_FIELD(*eqp, FSF_AZ_RX_EV_Q_LABEL);
	ok = (EFX_QWORD_FIELD(*eqp, FSF_AZ_RX_EV_PKT_OK) != 0);

#if (EFSYS_OPT_RX_HDR_SPLIT || EFSYS_OPT_RX_SCATTER)
	sop = (EFX_QWORD_FIELD(*eqp, FSF_AZ_RX_EV_SOP) != 0);
	jumbo_cont = (EFX_QWORD_FIELD(*eqp, FSF_AZ_RX_EV_JUMBO_CONT) != 0);
#endif	/* EFSYS_OPT_RX_HDR_SPLIT || EFSYS_OPT_RX_SCATTER */

	hdr_type = EFX_QWORD_FIELD(*eqp, FSF_AZ_RX_EV_HDR_TYPE);

	is_v6 = (enp->en_family != EFX_FAMILY_FALCON &&
		    EFX_QWORD_FIELD(*eqp, FSF_CZ_RX_EV_IPV6_PKT) != 0);

	/*
	 * If packet is marked as OK and packet type is TCP/IP or
	 * UDP/IP or other IP, then we can rely on the hardware checksums.
	 */
	switch (hdr_type) {
	case FSE_AZ_RX_EV_HDR_TYPE_IPV4V6_TCP:
		flags = EFX_PKT_TCP | EFX_CKSUM_TCPUDP;
		if (is_v6) {
			EFX_EV_QSTAT_INCR(eep, EV_RX_TCP_IPV6);
			flags |= EFX_PKT_IPV6;
		} else {
			EFX_EV_QSTAT_INCR(eep, EV_RX_TCP_IPV4);
			flags |= EFX_PKT_IPV4 | EFX_CKSUM_IPV4;
		}
		break;

	case FSE_AZ_RX_EV_HDR_TYPE_IPV4V6_UDP:
		flags = EFX_PKT_UDP | EFX_CKSUM_TCPUDP;
		if (is_v6) {
			EFX_EV_QSTAT_INCR(eep, EV_RX_UDP_IPV6);
			flags |= EFX_PKT_IPV6;
		} else {
			EFX_EV_QSTAT_INCR(eep, EV_RX_UDP_IPV4);
			flags |= EFX_PKT_IPV4 | EFX_CKSUM_IPV4;
		}
		break;

	case FSE_AZ_RX_EV_HDR_TYPE_IPV4V6_OTHER:
		if (is_v6) {
			EFX_EV_QSTAT_INCR(eep, EV_RX_OTHER_IPV6);
			flags = EFX_PKT_IPV6;
		} else {
			EFX_EV_QSTAT_INCR(eep, EV_RX_OTHER_IPV4);
			flags = EFX_PKT_IPV4 | EFX_CKSUM_IPV4;
		}
		break;

	case FSE_AZ_RX_EV_HDR_TYPE_OTHER:
		EFX_EV_QSTAT_INCR(eep, EV_RX_NON_IP);
		flags = 0;
		break;

	default:
		EFSYS_ASSERT(B_FALSE);
		flags = 0;
		break;
	}

#if EFSYS_OPT_RX_SCATTER || EFSYS_OPT_RX_HDR_SPLIT
	/* Report scatter and header/lookahead split buffer flags */
	if (sop)
		flags |= EFX_PKT_START;
	if (jumbo_cont)
		flags |= EFX_PKT_CONT;
#endif	/* EFSYS_OPT_RX_SCATTER || EFSYS_OPT_RX_HDR_SPLIT */

	/* Detect errors included in the FSF_AZ_RX_EV_PKT_OK indication */
	if (!ok) {
		ignore = efx_ev_rx_not_ok(eep, eqp, label, id, &flags);
		if (ignore) {
			EFSYS_PROBE4(rx_complete, uint32_t, label, uint32_t, id,
			    uint32_t, size, uint16_t, flags);

			return (B_FALSE);
		}
	}

	/* If we're not discarding the packet then it is ok */
	if (~flags & EFX_DISCARD)
		EFX_EV_QSTAT_INCR(eep, EV_RX_OK);

	/* Detect multicast packets that didn't match the filter */
	if (EFX_QWORD_FIELD(*eqp, FSF_AZ_RX_EV_MCAST_PKT) != 0) {
		EFX_EV_QSTAT_INCR(eep, EV_RX_MCAST_PKT);

		if (EFX_QWORD_FIELD(*eqp, FSF_AZ_RX_EV_MCAST_HASH_MATCH) != 0) {
			EFX_EV_QSTAT_INCR(eep, EV_RX_MCAST_HASH_MATCH);
		} else {
			EFSYS_PROBE(mcast_mismatch);
			flags |= EFX_ADDR_MISMATCH;
		}
	} else {
		flags |= EFX_PKT_UNICAST;
	}

	/*
	 * The packet parser in Siena can abort parsing packets under
	 * certain error conditions, setting the PKT_NOT_PARSED bit
	 * (which clears PKT_OK). If this is set, then don't trust
	 * the PKT_TYPE field.
	 */
	if (enp->en_family != EFX_FAMILY_FALCON && !ok) {
		uint32_t parse_err;

		parse_err = EFX_QWORD_FIELD(*eqp, FSF_CZ_RX_EV_PKT_NOT_PARSED);
		if (parse_err != 0)
			flags |= EFX_CHECK_VLAN;
	}

	if (~flags & EFX_CHECK_VLAN) {
		uint32_t pkt_type;

		pkt_type = EFX_QWORD_FIELD(*eqp, FSF_AZ_RX_EV_PKT_TYPE);
		if (pkt_type >= FSE_AZ_RX_EV_PKT_TYPE_VLAN)
			flags |= EFX_PKT_VLAN_TAGGED;
	}

	EFSYS_PROBE4(rx_complete, uint32_t, label, uint32_t, id,
	    uint32_t, size, uint16_t, flags);

	EFSYS_ASSERT(eecp->eec_rx != NULL);
	should_abort = eecp->eec_rx(arg, label, id, size, flags);

	return (should_abort);
}

static	__checkReturn	boolean_t
efx_ev_tx(
	__in		efx_evq_t *eep,
	__in		efx_qword_t *eqp,
	__in		const efx_ev_callbacks_t *eecp,
	__in_opt	void *arg)
{
	uint32_t id;
	uint32_t label;
	boolean_t should_abort;

	EFX_EV_QSTAT_INCR(eep, EV_TX);

	if (EFX_QWORD_FIELD(*eqp, FSF_AZ_TX_EV_COMP) != 0 &&
	    EFX_QWORD_FIELD(*eqp, FSF_AZ_TX_EV_PKT_ERR) == 0 &&
	    EFX_QWORD_FIELD(*eqp, FSF_AZ_TX_EV_PKT_TOO_BIG) == 0 &&
	    EFX_QWORD_FIELD(*eqp, FSF_AZ_TX_EV_WQ_FF_FULL) == 0) {

		id = EFX_QWORD_FIELD(*eqp, FSF_AZ_TX_EV_DESC_PTR);
		label = EFX_QWORD_FIELD(*eqp, FSF_AZ_TX_EV_Q_LABEL);

		EFSYS_PROBE2(tx_complete, uint32_t, label, uint32_t, id);

		EFSYS_ASSERT(eecp->eec_tx != NULL);
		should_abort = eecp->eec_tx(arg, label, id);

		return (should_abort);
	}

	if (EFX_QWORD_FIELD(*eqp, FSF_AZ_TX_EV_COMP) != 0)
		EFSYS_PROBE3(bad_event, unsigned int, eep->ee_index,
			    uint32_t, EFX_QWORD_FIELD(*eqp, EFX_DWORD_1),
			    uint32_t, EFX_QWORD_FIELD(*eqp, EFX_DWORD_0));

	if (EFX_QWORD_FIELD(*eqp, FSF_AZ_TX_EV_PKT_ERR) != 0)
		EFX_EV_QSTAT_INCR(eep, EV_TX_PKT_ERR);

	if (EFX_QWORD_FIELD(*eqp, FSF_AZ_TX_EV_PKT_TOO_BIG) != 0)
		EFX_EV_QSTAT_INCR(eep, EV_TX_PKT_TOO_BIG);

	if (EFX_QWORD_FIELD(*eqp, FSF_AZ_TX_EV_WQ_FF_FULL) != 0)
		EFX_EV_QSTAT_INCR(eep, EV_TX_WQ_FF_FULL);

	EFX_EV_QSTAT_INCR(eep, EV_TX_UNEXPECTED);
	return (B_FALSE);
}

static	__checkReturn	boolean_t
efx_ev_global(
	__in		efx_evq_t *eep,
	__in		efx_qword_t *eqp,
	__in		const efx_ev_callbacks_t *eecp,
	__in_opt	void *arg)
{
	efx_nic_t *enp = eep->ee_enp;
	efx_port_t *epp = &(enp->en_port);
	boolean_t should_abort;

	EFX_EV_QSTAT_INCR(eep, EV_GLOBAL);
	should_abort = B_FALSE;

	/* Check for a link management event */
	if (EFX_QWORD_FIELD(*eqp, FSF_BZ_GLB_EV_XG_MNT_INTR) != 0) {
		EFX_EV_QSTAT_INCR(eep, EV_GLOBAL_MNT);

		EFSYS_PROBE(xg_mgt);

		epp->ep_mac_poll_needed = B_TRUE;
	}

	return (should_abort);
}

static	__checkReturn	boolean_t
efx_ev_driver(
	__in		efx_evq_t *eep,
	__in		efx_qword_t *eqp,
	__in		const efx_ev_callbacks_t *eecp,
	__in_opt	void *arg)
{
	boolean_t should_abort;

	EFX_EV_QSTAT_INCR(eep, EV_DRIVER);
	should_abort = B_FALSE;

	switch (EFX_QWORD_FIELD(*eqp, FSF_AZ_DRIVER_EV_SUBCODE)) {
	case FSE_AZ_TX_DESCQ_FLS_DONE_EV: {
		uint32_t label;

		EFX_EV_QSTAT_INCR(eep, EV_DRIVER_TX_DESCQ_FLS_DONE);

		label = EFX_QWORD_FIELD(*eqp, FSF_AZ_DRIVER_EV_SUBDATA);

		EFSYS_PROBE1(tx_descq_fls_done, uint32_t, label);

		EFSYS_ASSERT(eecp->eec_txq_flush_done != NULL);
		should_abort = eecp->eec_txq_flush_done(arg, label);

		break;
	}
	case FSE_AZ_RX_DESCQ_FLS_DONE_EV: {
		uint32_t label;
		uint32_t failed;

		label = EFX_QWORD_FIELD(*eqp, FSF_AZ_DRIVER_EV_RX_DESCQ_ID);
		failed = EFX_QWORD_FIELD(*eqp, FSF_AZ_DRIVER_EV_RX_FLUSH_FAIL);

		EFSYS_ASSERT(eecp->eec_rxq_flush_done != NULL);
		EFSYS_ASSERT(eecp->eec_rxq_flush_failed != NULL);

		if (failed) {
			EFX_EV_QSTAT_INCR(eep, EV_DRIVER_RX_DESCQ_FLS_FAILED);

			EFSYS_PROBE1(rx_descq_fls_failed, uint32_t, label);

			should_abort = eecp->eec_rxq_flush_failed(arg, label);
		} else {
			EFX_EV_QSTAT_INCR(eep, EV_DRIVER_RX_DESCQ_FLS_DONE);

			EFSYS_PROBE1(rx_descq_fls_done, uint32_t, label);

			should_abort = eecp->eec_rxq_flush_done(arg, label);
		}

		break;
	}
	case FSE_AZ_EVQ_INIT_DONE_EV:
		EFSYS_ASSERT(eecp->eec_initialized != NULL);
		should_abort = eecp->eec_initialized(arg);

		break;

	case FSE_AZ_EVQ_NOT_EN_EV:
		EFSYS_PROBE(evq_not_en);
		break;

	case FSE_AZ_SRM_UPD_DONE_EV: {
		uint32_t code;

		EFX_EV_QSTAT_INCR(eep, EV_DRIVER_SRM_UPD_DONE);

		code = EFX_QWORD_FIELD(*eqp, FSF_AZ_DRIVER_EV_SUBDATA);

		EFSYS_ASSERT(eecp->eec_sram != NULL);
		should_abort = eecp->eec_sram(arg, code);

		break;
	}
	case FSE_AZ_WAKE_UP_EV: {
		uint32_t id;

		id = EFX_QWORD_FIELD(*eqp, FSF_AZ_DRIVER_EV_SUBDATA);

		EFSYS_ASSERT(eecp->eec_wake_up != NULL);
		should_abort = eecp->eec_wake_up(arg, id);

		break;
	}
	case FSE_AZ_TX_PKT_NON_TCP_UDP:
		EFSYS_PROBE(tx_pkt_non_tcp_udp);
		break;

	case FSE_AZ_TIMER_EV: {
		uint32_t id;

		id = EFX_QWORD_FIELD(*eqp, FSF_AZ_DRIVER_EV_SUBDATA);

		EFSYS_ASSERT(eecp->eec_timer != NULL);
		should_abort = eecp->eec_timer(arg, id);

		break;
	}
	case FSE_AZ_RX_DSC_ERROR_EV:
		EFX_EV_QSTAT_INCR(eep, EV_DRIVER_RX_DSC_ERROR);

		EFSYS_PROBE(rx_dsc_error);

		EFSYS_ASSERT(eecp->eec_exception != NULL);
		should_abort = eecp->eec_exception(arg,
			EFX_EXCEPTION_RX_DSC_ERROR, 0);

		break;

	case FSE_AZ_TX_DSC_ERROR_EV:
		EFX_EV_QSTAT_INCR(eep, EV_DRIVER_TX_DSC_ERROR);

		EFSYS_PROBE(tx_dsc_error);

		EFSYS_ASSERT(eecp->eec_exception != NULL);
		should_abort = eecp->eec_exception(arg,
			EFX_EXCEPTION_TX_DSC_ERROR, 0);

		break;

	default:
		break;
	}

	return (should_abort);
}

static	__checkReturn	boolean_t
efx_ev_drv_gen(
	__in		efx_evq_t *eep,
	__in		efx_qword_t *eqp,
	__in		const efx_ev_callbacks_t *eecp,
	__in_opt	void *arg)
{
	uint32_t data;
	boolean_t should_abort;

	EFX_EV_QSTAT_INCR(eep, EV_DRV_GEN);

	data = EFX_QWORD_FIELD(*eqp, FSF_AZ_EV_DATA_DW0);
	if (data >= ((uint32_t)1 << 16)) {
		EFSYS_PROBE3(bad_event, unsigned int, eep->ee_index,
			    uint32_t, EFX_QWORD_FIELD(*eqp, EFX_DWORD_1),
			    uint32_t, EFX_QWORD_FIELD(*eqp, EFX_DWORD_0));
		return (B_TRUE);
	}

	EFSYS_ASSERT(eecp->eec_software != NULL);
	should_abort = eecp->eec_software(arg, (uint16_t)data);

	return (should_abort);
}

#if EFSYS_OPT_MCDI

static	__checkReturn	boolean_t
efx_ev_mcdi(
	__in		efx_evq_t *eep,
	__in		efx_qword_t *eqp,
	__in		const efx_ev_callbacks_t *eecp,
	__in_opt	void *arg)
{
	efx_nic_t *enp = eep->ee_enp;
	unsigned code;
	boolean_t should_abort = B_FALSE;

	EFSYS_ASSERT3U(enp->en_family, ==, EFX_FAMILY_SIENA);

	if (enp->en_family != EFX_FAMILY_SIENA)
		goto out;

	EFX_EV_QSTAT_INCR(eep, EV_MCDI_RESPONSE);

	code = EFX_QWORD_FIELD(*eqp, MCDI_EVENT_CODE);
	switch (code) {
	case MCDI_EVENT_CODE_BADSSERT:
		efx_mcdi_ev_death(enp, EINTR);
		break;

	case MCDI_EVENT_CODE_CMDDONE:
		efx_mcdi_ev_cpl(enp,
				MCDI_EV_FIELD(*eqp, CMDDONE_SEQ),
				MCDI_EV_FIELD(*eqp, CMDDONE_DATALEN),
				MCDI_EV_FIELD(*eqp, CMDDONE_ERRNO));
		break;

	case MCDI_EVENT_CODE_LINKCHANGE: {
		efx_link_mode_t link_mode;

		siena_phy_link_ev(enp, eqp, &link_mode);
		should_abort = eecp->eec_link_change(arg, link_mode);
		break;
	}
	case MCDI_EVENT_CODE_SENSOREVT: {
#if EFSYS_OPT_MON_STATS
		efx_mon_stat_t id;
		efx_mon_stat_value_t value;
		int rc;

		if ((rc = siena_mon_ev(enp, eqp, &id, &value)) == 0)
			should_abort = eecp->eec_monitor(arg, id, value);
		else if (rc == ENOTSUP) {
			should_abort = eecp->eec_exception(arg,
				EFX_EXCEPTION_UNKNOWN_SENSOREVT,
				MCDI_EV_FIELD(eqp, DATA));
		} else
			EFSYS_ASSERT(rc == ENODEV);	/* Wrong port */
#else
		should_abort = B_FALSE;
#endif
		break;
	}
	case MCDI_EVENT_CODE_SCHEDERR:
		/* Informational only */
		break;

	case MCDI_EVENT_CODE_REBOOT:
		efx_mcdi_ev_death(enp, EIO);
		break;

	case MCDI_EVENT_CODE_MAC_STATS_DMA:
#if EFSYS_OPT_MAC_STATS
		if (eecp->eec_mac_stats != NULL) {
			eecp->eec_mac_stats(arg,
			    MCDI_EV_FIELD(eqp, MAC_STATS_DMA_GENERATION));
		}
#endif
		break;

	case MCDI_EVENT_CODE_FWALERT: {
		uint32_t reason = MCDI_EV_FIELD(eqp, FWALERT_REASON);

		if (reason == MCDI_EVENT_FWALERT_REASON_SRAM_ACCESS)
			should_abort = eecp->eec_exception(arg,
				EFX_EXCEPTION_FWALERT_SRAM,
				MCDI_EV_FIELD(eqp, FWALERT_DATA));
		else
			should_abort = eecp->eec_exception(arg,
				EFX_EXCEPTION_UNKNOWN_FWALERT,
				MCDI_EV_FIELD(eqp, DATA));
		break;
	}

	default:
		EFSYS_PROBE1(mc_pcol_error, int, code);
		break;
	}

out:
	return (should_abort);
}

#endif	/* EFSYS_OPT_SIENA */

	__checkReturn	int
efx_ev_qprime(
	__in		efx_evq_t *eep,
	__in		unsigned int count)
{
	efx_nic_t *enp = eep->ee_enp;
	uint32_t rptr;
	efx_dword_t dword;
	int rc;

	EFSYS_ASSERT3U(eep->ee_magic, ==, EFX_EVQ_MAGIC);

	if (!(enp->en_mod_flags & EFX_MOD_INTR)) {
		rc = EINVAL;
		goto fail1;
	}

	rptr = count & eep->ee_mask;

	EFX_POPULATE_DWORD_1(dword, FRF_AZ_EVQ_RPTR, rptr);

	EFX_BAR_TBL_WRITED(enp, FR_AZ_EVQ_RPTR_REG, eep->ee_index,
			    &dword, B_FALSE);

	return (0);

fail1:
	EFSYS_PROBE1(fail1, int, rc);

	return (rc);
}

	__checkReturn	boolean_t
efx_ev_qpending(
	__in		efx_evq_t *eep,
	__in		unsigned int count)
{
	size_t offset;
	efx_qword_t qword;

	EFSYS_ASSERT3U(eep->ee_magic, ==, EFX_EVQ_MAGIC);

	offset = (count & eep->ee_mask) * sizeof (efx_qword_t);
	EFSYS_MEM_READQ(eep->ee_esmp, offset, &qword);

	return (EFX_QWORD_FIELD(qword, EFX_DWORD_0) != 0xffffffff &&
		EFX_QWORD_FIELD(qword, EFX_DWORD_1) != 0xffffffff);
}

#if EFSYS_OPT_EV_PREFETCH

			void
efx_ev_qprefetch(
	__in		efx_evq_t *eep,
	__in		unsigned int count)
{
	unsigned int offset;

	EFSYS_ASSERT3U(eep->ee_magic, ==, EFX_EVQ_MAGIC);

	offset = (count & eep->ee_mask) * sizeof (efx_qword_t);
	EFSYS_MEM_PREFETCH(eep->ee_esmp, offset);
}

#endif	/* EFSYS_OPT_EV_PREFETCH */

#define	EFX_EV_BATCH	8

#define	EFX_EV_PRESENT(_qword)						\
	(EFX_QWORD_FIELD((_qword), EFX_DWORD_0) != 0xffffffff &&	\
	EFX_QWORD_FIELD((_qword), EFX_DWORD_1) != 0xffffffff)

			void
efx_ev_qpoll(
	__in		efx_evq_t *eep,
	__inout		unsigned int *countp,
	__in		const efx_ev_callbacks_t *eecp,
	__in_opt	void *arg)
{
	efx_qword_t ev[EFX_EV_BATCH];
	unsigned int batch;
	unsigned int total;
	unsigned int count;
	unsigned int index;
	size_t offset;

	EFSYS_ASSERT3U(eep->ee_magic, ==, EFX_EVQ_MAGIC);
	EFSYS_ASSERT(countp != NULL);
	EFSYS_ASSERT(eecp != NULL);

	count = *countp;
	do {
		/* Read up until the end of the batch period */
		batch = EFX_EV_BATCH - (count & (EFX_EV_BATCH - 1));
		offset = (count & eep->ee_mask) * sizeof (efx_qword_t);
		for (total = 0; total < batch; ++total) {
			EFSYS_MEM_READQ(eep->ee_esmp, offset, &(ev[total]));

			if (!EFX_EV_PRESENT(ev[total]))
				break;

			EFSYS_PROBE3(event, unsigned int, eep->ee_index,
			    uint32_t, EFX_QWORD_FIELD(ev[total], EFX_DWORD_1),
			    uint32_t, EFX_QWORD_FIELD(ev[total], EFX_DWORD_0));

			offset += sizeof (efx_qword_t);
		}

#if EFSYS_OPT_EV_PREFETCH && (EFSYS_OPT_EV_PREFETCH_PERIOD > 1)
		/*
		 * Prefetch the next batch when we get within PREFETCH_PERIOD
		 * of a completed batch. If the batch is smaller, then prefetch
		 * immediately.
		 */
		if (total == batch && total < EFSYS_OPT_EV_PREFETCH_PERIOD)
			EFSYS_MEM_PREFETCH(eep->ee_esmp, offset);
#endif	/* EFSYS_OPT_EV_PREFETCH */

		/* Process the batch of events */
		for (index = 0; index < total; ++index) {
			boolean_t should_abort;
			uint32_t code;
			efx_ev_handler_t handler;

#if EFSYS_OPT_EV_PREFETCH
			/* Prefetch if we've now reached the batch period */
			if (total == batch &&
			    index + EFSYS_OPT_EV_PREFETCH_PERIOD == total) {
				offset = (count + batch) & eep->ee_mask;
				offset *= sizeof (efx_qword_t);

				EFSYS_MEM_PREFETCH(eep->ee_esmp, offset);
			}
#endif	/* EFSYS_OPT_EV_PREFETCH */

			EFX_EV_QSTAT_INCR(eep, EV_ALL);

			code = EFX_QWORD_FIELD(ev[index], FSF_AZ_EV_CODE);
			handler = eep->ee_handler[code];
			EFSYS_ASSERT(handler != NULL);
			should_abort = handler(eep, &(ev[index]), eecp, arg);
			if (should_abort) {
				/* Ignore subsequent events */
				total = index + 1;
				break;
			}
		}

		/*
		 * Now that the hardware has most likely moved onto dma'ing
		 * into the next cache line, clear the processed events. Take
		 * care to only clear out events that we've processed
		 */
		EFX_SET_QWORD(ev[0]);
		offset = (count & eep->ee_mask) * sizeof (efx_qword_t);
		for (index = 0; index < total; ++index) {
			EFSYS_MEM_WRITEQ(eep->ee_esmp, offset, &(ev[0]));
			offset += sizeof (efx_qword_t);
		}

		count += total;

	} while (total == batch);

	*countp = count;
}

		void
efx_ev_qpost(
	__in	efx_evq_t *eep,
	__in	uint16_t data)
{
	efx_nic_t *enp = eep->ee_enp;
	efx_qword_t ev;
	efx_oword_t oword;

	EFSYS_ASSERT3U(eep->ee_magic, ==, EFX_EVQ_MAGIC);

	EFX_POPULATE_QWORD_2(ev, FSF_AZ_EV_CODE, FSE_AZ_EV_CODE_DRV_GEN_EV,
	    FSF_AZ_EV_DATA_DW0, (uint32_t)data);

	EFX_POPULATE_OWORD_3(oword, FRF_AZ_DRV_EV_QID, eep->ee_index,
	    EFX_DWORD_0, EFX_QWORD_FIELD(ev, EFX_DWORD_0),
	    EFX_DWORD_1, EFX_QWORD_FIELD(ev, EFX_DWORD_1));

	EFX_BAR_WRITEO(enp, FR_AZ_DRV_EV_REG, &oword);
}

	__checkReturn	int
efx_ev_qmoderate(
	__in		efx_evq_t *eep,
	__in		unsigned int us)
{
	efx_nic_t *enp = eep->ee_enp;
	unsigned int locked;
	efx_dword_t dword;
	int rc;

	EFSYS_ASSERT3U(eep->ee_magic, ==, EFX_EVQ_MAGIC);

	if (us > enp->en_nic_cfg.enc_evq_moderation_max) {
		rc = EINVAL;
		goto fail1;
	}

	/* If the value is zero then disable the timer */
	if (us == 0) {
		if (enp->en_family == EFX_FAMILY_FALCON)
			EFX_POPULATE_DWORD_2(dword,
			    FRF_AB_TC_TIMER_MODE, FFE_AB_TIMER_MODE_DIS,
			    FRF_AB_TC_TIMER_VAL, 0);
		else
			EFX_POPULATE_DWORD_2(dword,
			    FRF_CZ_TC_TIMER_MODE, FFE_CZ_TIMER_MODE_DIS,
			    FRF_CZ_TC_TIMER_VAL, 0);
	} else {
		uint32_t timer_val;

		/* Calculate the timer value in quanta */
		us -= (us % EFX_EV_TIMER_QUANTUM);
		if (us < EFX_EV_TIMER_QUANTUM)
			us = EFX_EV_TIMER_QUANTUM;

		timer_val = us / EFX_EV_TIMER_QUANTUM;

		/* Moderation value is base 0 so we need to deduct 1 */
		if (enp->en_family == EFX_FAMILY_FALCON)
			EFX_POPULATE_DWORD_2(dword,
			    FRF_AB_TC_TIMER_MODE, FFE_AB_TIMER_MODE_INT_HLDOFF,
			    FRF_AB_TIMER_VAL, timer_val - 1);
		else
			EFX_POPULATE_DWORD_2(dword,
			    FRF_CZ_TC_TIMER_MODE, FFE_CZ_TIMER_MODE_INT_HLDOFF,
			    FRF_CZ_TC_TIMER_VAL, timer_val - 1);
	}

	locked = (eep->ee_index == 0) ? 1 : 0;

	EFX_BAR_TBL_WRITED(enp, FR_BZ_TIMER_COMMAND_REGP0,
	    eep->ee_index, &dword, locked);

	return (0);

fail1:
	EFSYS_PROBE1(fail1, int, rc);

	return (rc);
}

	__checkReturn	int
efx_ev_qcreate(
	__in		efx_nic_t *enp,
	__in		unsigned int index,
	__in		efsys_mem_t *esmp,
	__in		size_t n,
	__in		uint32_t id,
	__deref_out	efx_evq_t **eepp)
{
	efx_nic_cfg_t *encp = &(enp->en_nic_cfg);
	uint32_t size;
	efx_evq_t *eep;
	efx_oword_t oword;
	int rc;

	EFSYS_ASSERT3U(enp->en_magic, ==, EFX_NIC_MAGIC);
	EFSYS_ASSERT3U(enp->en_mod_flags, &, EFX_MOD_EV);

	EFSYS_ASSERT3U(enp->en_ev_qcount + 1, <, encp->enc_evq_limit);

	if (!ISP2(n) || !(n & EFX_EVQ_NEVS_MASK)) {
		rc = EINVAL;
		goto fail1;
	}
	if (index >= encp->enc_evq_limit) {
		rc = EINVAL;
		goto fail2;
	}
#if EFSYS_OPT_RX_SCALE
	if (enp->en_intr.ei_type == EFX_INTR_LINE &&
	    index >= EFX_MAXRSS_LEGACY) {
		rc = EINVAL;
		goto fail3;
	}
#endif
	for (size = 0; (1 << size) <= (EFX_EVQ_MAXNEVS / EFX_EVQ_MINNEVS);
	    size++)
		if ((1 << size) == (int)(n / EFX_EVQ_MINNEVS))
			break;
	if (id + (1 << size) >= encp->enc_buftbl_limit) {
		rc = EINVAL;
		goto fail4;
	}

	/* Allocate an EVQ object */
	EFSYS_KMEM_ALLOC(enp->en_esip, sizeof (efx_evq_t), eep);
	if (eep == NULL) {
		rc = ENOMEM;
		goto fail5;
	}

	eep->ee_magic = EFX_EVQ_MAGIC;
	eep->ee_enp = enp;
	eep->ee_index = index;
	eep->ee_mask = n - 1;
	eep->ee_esmp = esmp;

	/* Set up the handler table */
	eep->ee_handler[FSE_AZ_EV_CODE_RX_EV] = efx_ev_rx;
	eep->ee_handler[FSE_AZ_EV_CODE_TX_EV] = efx_ev_tx;
	eep->ee_handler[FSE_AZ_EV_CODE_DRIVER_EV] = efx_ev_driver;
	eep->ee_handler[FSE_AZ_EV_CODE_GLOBAL_EV] = efx_ev_global;
	eep->ee_handler[FSE_AZ_EV_CODE_DRV_GEN_EV] = efx_ev_drv_gen;
#if EFSYS_OPT_MCDI
	eep->ee_handler[FSE_AZ_EV_CODE_MCDI_EVRESPONSE] = efx_ev_mcdi;
#endif	/* EFSYS_OPT_SIENA */

	/* Set up the new event queue */
	if (enp->en_family != EFX_FAMILY_FALCON) {
		EFX_POPULATE_OWORD_1(oword, FRF_CZ_TIMER_Q_EN, 1);
		EFX_BAR_TBL_WRITEO(enp, FR_AZ_TIMER_TBL, index, &oword);
	}

	EFX_POPULATE_OWORD_3(oword, FRF_AZ_EVQ_EN, 1, FRF_AZ_EVQ_SIZE, size,
	    FRF_AZ_EVQ_BUF_BASE_ID, id);

	EFX_BAR_TBL_WRITEO(enp, FR_AZ_EVQ_PTR_TBL, index, &oword);

	enp->en_ev_qcount++;
	*eepp = eep;
	return (0);

fail5:
	EFSYS_PROBE(fail5);
fail4:
	EFSYS_PROBE(fail4);
#if EFSYS_OPT_RX_SCALE
fail3:
	EFSYS_PROBE(fail3);
#endif
fail2:
	EFSYS_PROBE(fail2);
fail1:
	EFSYS_PROBE1(fail1, int, rc);

	return (rc);
}

#if EFSYS_OPT_NAMES
/* START MKCONFIG GENERATED EfxEventQueueStatNamesBlock 67e9bdcd920059bd */
static const char 	__cs * __cs __efx_ev_qstat_name[] = {
	"all",
	"rx",
	"rx_ok",
	"rx_recovery",
	"rx_frm_trunc",
	"rx_tobe_disc",
	"rx_pause_frm_err",
	"rx_buf_owner_id_err",
	"rx_ipv4_hdr_chksum_err",
	"rx_tcp_udp_chksum_err",
	"rx_eth_crc_err",
	"rx_ip_frag_err",
	"rx_mcast_pkt",
	"rx_mcast_hash_match",
	"rx_tcp_ipv4",
	"rx_tcp_ipv6",
	"rx_udp_ipv4",
	"rx_udp_ipv6",
	"rx_other_ipv4",
	"rx_other_ipv6",
	"rx_non_ip",
	"rx_overrun",
	"tx",
	"tx_wq_ff_full",
	"tx_pkt_err",
	"tx_pkt_too_big",
	"tx_unexpected",
	"global",
	"global_phy",
	"global_mnt",
	"global_rx_recovery",
	"driver",
	"driver_srm_upd_done",
	"driver_tx_descq_fls_done",
	"driver_rx_descq_fls_done",
	"driver_rx_descq_fls_failed",
	"driver_rx_dsc_error",
	"driver_tx_dsc_error",
	"drv_gen",
	"mcdi_response",
};
/* END MKCONFIG GENERATED EfxEventQueueStatNamesBlock */

		const char __cs *
efx_ev_qstat_name(
	__in	efx_nic_t *enp,
	__in	unsigned int id)
{
	EFSYS_ASSERT3U(enp->en_magic, ==, EFX_NIC_MAGIC);
	EFSYS_ASSERT3U(id, <, EV_NQSTATS);

	return (__efx_ev_qstat_name[id]);
}
#endif	/* EFSYS_OPT_NAMES */

#if EFSYS_OPT_QSTATS
					void
efx_ev_qstats_update(
	__in				efx_evq_t *eep,
	__inout_ecount(EV_NQSTATS)	efsys_stat_t *stat)
{
	unsigned int id;

	EFSYS_ASSERT3U(eep->ee_magic, ==, EFX_EVQ_MAGIC);

	for (id = 0; id < EV_NQSTATS; id++) {
		efsys_stat_t *essp = &stat[id];

		EFSYS_STAT_INCR(essp, eep->ee_stat[id]);
		eep->ee_stat[id] = 0;
	}
}
#endif	/* EFSYS_OPT_QSTATS */

		void
efx_ev_qdestroy(
	__in	efx_evq_t *eep)
{
	efx_nic_t *enp = eep->ee_enp;
	efx_oword_t oword;

	EFSYS_ASSERT3U(eep->ee_magic, ==, EFX_EVQ_MAGIC);

	EFSYS_ASSERT(enp->en_ev_qcount != 0);
	--enp->en_ev_qcount;

	/* Purge event queue */
	EFX_ZERO_OWORD(oword);

	EFX_BAR_TBL_WRITEO(enp, FR_AZ_EVQ_PTR_TBL,
	    eep->ee_index, &oword);

	if (enp->en_family != EFX_FAMILY_FALCON) {
		EFX_ZERO_OWORD(oword);
		EFX_BAR_TBL_WRITEO(enp, FR_AZ_TIMER_TBL,
		    eep->ee_index, &oword);
	}

	/* Free the EVQ object */
	EFSYS_KMEM_FREE(enp->en_esip, sizeof (efx_evq_t), eep);
}

		void
efx_ev_fini(
	__in	efx_nic_t *enp)
{
	EFSYS_ASSERT3U(enp->en_magic, ==, EFX_NIC_MAGIC);
	EFSYS_ASSERT3U(enp->en_mod_flags, &, EFX_MOD_INTR);
	EFSYS_ASSERT3U(enp->en_mod_flags, &, EFX_MOD_EV);
	EFSYS_ASSERT(!(enp->en_mod_flags & EFX_MOD_RX));
	EFSYS_ASSERT(!(enp->en_mod_flags & EFX_MOD_TX));
	EFSYS_ASSERT3U(enp->en_ev_qcount, ==, 0);

	enp->en_mod_flags &= ~EFX_MOD_EV;
}
