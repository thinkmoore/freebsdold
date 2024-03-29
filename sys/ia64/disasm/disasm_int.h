/*-
 * Copyright (c) 2000-2006 Marcel Moolenaar
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $FreeBSD: stable/9/sys/ia64/disasm/disasm_int.h 159916 2006-06-24 19:21:11Z marcel $
 */

#ifndef _DISASM_INT_H_
#define	_DISASM_INT_H_

#ifdef _DISASM_H_
#error	Include disasm_int.h before disasm.h
#endif

/*
 * Instruction bundle specifics.
 */
#define	TMPL_BITS	5
#define	SLOT_BITS	41
#define	SLOT_COUNT	3

#define	BUNDLE_SIZE	(SLOT_COUNT * SLOT_BITS + TMPL_BITS)
#define	BUNDLE_BYTES	((BUNDLE_SIZE+7) >> 3)
#define	TMPL_MASK	((1 << TMPL_BITS) - 1)
#define	SLOT_MASK	((1ULL << SLOT_BITS) - 1ULL)
#define	TMPL(p)		(*(const uint8_t*)(p) & TMPL_MASK)
#define	_U32(p,i)	((uint64_t)(((const uint32_t*)(p))[i]))
#define	_SLOT(p,i)	(_U32(p,i) | (_U32(p,(i)+1)<<32))
#define	SLOT(p,i)	((_SLOT(p,i) >> (TMPL_BITS+((i)<<3)+(i))) & SLOT_MASK)

/*
 * Instruction specifics
 */
#define	_FLD64(i,o,l)	((i >> o) & ((1LL << l) - 1LL))
#define	FIELD(i,o,l)	((uint32_t)_FLD64(i,o,l))
#define	OPCODE(i)	FIELD(i, 37, 4)
#define	QP_BITS		6
#define	QP(i)		FIELD(i, 0, QP_BITS)
#define	REG_BITS	7
#define	REG(i,r)	FIELD(i, ((r) - 1) * REG_BITS + QP_BITS, REG_BITS)

/*
 * Opcodes used internally as sentinels to denote either a lack of more
 * specific information or to preserve the additional state/information
 * we already have and need to pass around for later use.
 */
#define	ASM_ADDITIONAL_OPCODES						\
	ASM_OP_INTERNAL_OPCODES,					\
	ASM_OP_BR_CALL, ASM_OP_BR_CEXIT, ASM_OP_BR_CLOOP,		\
	ASM_OP_BR_COND, ASM_OP_BR_CTOP, ASM_OP_BR_IA, ASM_OP_BR_RET,	\
	ASM_OP_BR_WEXIT, ASM_OP_BR_WTOP,				\
	ASM_OP_BREAK_B, ASM_OP_BREAK_F, ASM_OP_BREAK_I, ASM_OP_BREAK_M,	\
	ASM_OP_BREAK_X,							\
	ASM_OP_BRL_COND, ASM_OP_BRL_CALL,				\
	ASM_OP_BRP_, ASM_OP_BRP_RET,					\
	ASM_OP_BSW_0, ASM_OP_BSW_1,					\
	ASM_OP_CHK_A_CLR, ASM_OP_CHK_A_NC, ASM_OP_CHK_S,		\
	ASM_OP_CHK_S_I, ASM_OP_CHK_S_M,					\
	ASM_OP_CLRRRB_, ASM_OP_CLRRRB_PR,				\
	ASM_OP_CMP_EQ, ASM_OP_CMP_EQ_AND, ASM_OP_CMP_EQ_OR,		\
	ASM_OP_CMP_EQ_OR_ANDCM, ASM_OP_CMP_EQ_UNC, ASM_OP_CMP_GE_AND,	\
	ASM_OP_CMP_GE_OR, ASM_OP_CMP_GE_OR_ANDCM, ASM_OP_CMP_GT_AND,	\
	ASM_OP_CMP_GT_OR, ASM_OP_CMP_GT_OR_ANDCM, ASM_OP_CMP_LE_AND,	\
	ASM_OP_CMP_LE_OR, ASM_OP_CMP_LE_OR_ANDCM, ASM_OP_CMP_LT,	\
	ASM_OP_CMP_LT_AND, ASM_OP_CMP_LT_OR, ASM_OP_CMP_LT_OR_ANDCM,	\
	ASM_OP_CMP_LT_UNC, ASM_OP_CMP_LTU, ASM_OP_CMP_LTU_UNC,		\
	ASM_OP_CMP_NE_AND, ASM_OP_CMP_NE_OR, ASM_OP_CMP_NE_OR_ANDCM,	\
	ASM_OP_CMP4_EQ, ASM_OP_CMP4_EQ_AND, ASM_OP_CMP4_EQ_OR,		\
	ASM_OP_CMP4_EQ_OR_ANDCM, ASM_OP_CMP4_EQ_UNC, ASM_OP_CMP4_GE_AND,\
	ASM_OP_CMP4_GE_OR, ASM_OP_CMP4_GE_OR_ANDCM, ASM_OP_CMP4_GT_AND,	\
	ASM_OP_CMP4_GT_OR, ASM_OP_CMP4_GT_OR_ANDCM, ASM_OP_CMP4_LE_AND,	\
	ASM_OP_CMP4_LE_OR, ASM_OP_CMP4_LE_OR_ANDCM, ASM_OP_CMP4_LT,	\
	ASM_OP_CMP4_LT_AND, ASM_OP_CMP4_LT_OR, ASM_OP_CMP4_LT_OR_ANDCM,	\
	ASM_OP_CMP4_LT_UNC, ASM_OP_CMP4_LTU, ASM_OP_CMP4_LTU_UNC,	\
	ASM_OP_CMP4_NE_AND, ASM_OP_CMP4_NE_OR, ASM_OP_CMP4_NE_OR_ANDCM,	\
	ASM_OP_CMP8XCHG16_ACQ, ASM_OP_CMP8XCHG16_REL,			\
	ASM_OP_CMPXCHG1_ACQ, ASM_OP_CMPXCHG1_REL,			\
	ASM_OP_CMPXCHG2_ACQ, ASM_OP_CMPXCHG2_REL,			\
	ASM_OP_CMPXCHG4_ACQ, ASM_OP_CMPXCHG4_REL,			\
	ASM_OP_CMPXCHG8_ACQ, ASM_OP_CMPXCHG8_REL,			\
	ASM_OP_CZX1_L, ASM_OP_CZX1_R,					\
	ASM_OP_CZX2_L, ASM_OP_CZX2_R,					\
	ASM_OP_DEP_, ASM_OP_DEP_Z,					\
	ASM_OP_FC_, ASM_OP_FC_I,					\
	ASM_OP_FCLASS_M,						\
	ASM_OP_FCVT_FX, ASM_OP_FCVT_FX_TRUNC, ASM_OP_FCVT_FXU,		\
	ASM_OP_FCVT_FXU_TRUNC, ASM_OP_FCVT_XF,				\
	ASM_OP_FETCHADD4_ACQ, ASM_OP_FETCHADD4_REL,			\
	ASM_OP_FETCHADD8_ACQ, ASM_OP_FETCHADD8_REL,			\
	ASM_OP_FMA_, ASM_OP_FMA_D, ASM_OP_FMA_S,			\
	ASM_OP_FMERGE_NS, ASM_OP_FMERGE_S, ASM_OP_FMERGE_SE,		\
	ASM_OP_FMIX_L, ASM_OP_FMIX_LR, ASM_OP_FMIX_R,			\
	ASM_OP_FMS_, ASM_OP_FMS_D, ASM_OP_FMS_S,			\
	ASM_OP_FNMA_, ASM_OP_FNMA_D, ASM_OP_FNMA_S,			\
	ASM_OP_FPCMP_EQ, ASM_OP_FPCMP_LE, ASM_OP_FPCMP_LT,		\
	ASM_OP_FPCMP_NEQ, ASM_OP_FPCMP_NLE, ASM_OP_FPCMP_NLT,		\
	ASM_OP_FPCMP_ORD, ASM_OP_FPCMP_UNORD,				\
	ASM_OP_FPCVT_FX, ASM_OP_FPCVT_FX_TRUNC, ASM_OP_FPCVT_FXU,	\
	ASM_OP_FPCVT_FXU_TRUNC,						\
	ASM_OP_FPMERGE_NS, ASM_OP_FPMERGE_S, ASM_OP_FPMERGE_SE,		\
	ASM_OP_FSWAP_, ASM_OP_FSWAP_NL, ASM_OP_FSWAP_NR,		\
	ASM_OP_FSXT_L, ASM_OP_FSXT_R,					\
	ASM_OP_GETF_D, ASM_OP_GETF_EXP, ASM_OP_GETF_S, ASM_OP_GETF_SIG,	\
	ASM_OP_HINT_B, ASM_OP_HINT_F, ASM_OP_HINT_I, ASM_OP_HINT_M,	\
	ASM_OP_HINT_X,							\
	ASM_OP_INVALA_, ASM_OP_INVALA_E,				\
	ASM_OP_ITC_D, ASM_OP_ITC_I,					\
	ASM_OP_ITR_D, ASM_OP_ITR_I,					\
	ASM_OP_LD1_, ASM_OP_LD1_A, ASM_OP_LD1_ACQ, ASM_OP_LD1_BIAS,	\
	ASM_OP_LD1_C_CLR, ASM_OP_LD1_C_CLR_ACQ, ASM_OP_LD1_C_NC,	\
	ASM_OP_LD1_S, ASM_OP_LD1_SA,					\
	ASM_OP_LD16_, ASM_OP_LD16_ACQ,					\
	ASM_OP_LD2_, ASM_OP_LD2_A, ASM_OP_LD2_ACQ, ASM_OP_LD2_BIAS,	\
	ASM_OP_LD2_C_CLR, ASM_OP_LD2_C_CLR_ACQ, ASM_OP_LD2_C_NC,	\
	ASM_OP_LD2_S, ASM_OP_LD2_SA,					\
	ASM_OP_LD4_, ASM_OP_LD4_A, ASM_OP_LD4_ACQ, ASM_OP_LD4_BIAS,	\
	ASM_OP_LD4_C_CLR, ASM_OP_LD4_C_CLR_ACQ, ASM_OP_LD4_C_NC,	\
	ASM_OP_LD4_S, ASM_OP_LD4_SA,					\
	ASM_OP_LD8_, ASM_OP_LD8_A, ASM_OP_LD8_ACQ, ASM_OP_LD8_BIAS,	\
	ASM_OP_LD8_C_CLR, ASM_OP_LD8_C_CLR_ACQ, ASM_OP_LD8_C_NC,	\
	ASM_OP_LD8_FILL, ASM_OP_LD8_S, ASM_OP_LD8_SA,			\
	ASM_OP_LDF_FILL,						\
	ASM_OP_LDF8_, ASM_OP_LDF8_A, ASM_OP_LDF8_C_CLR,			\
	ASM_OP_LDF8_C_NC, ASM_OP_LDF8_S, ASM_OP_LDF8_SA,		\
	ASM_OP_LDFD_, ASM_OP_LDFD_A, ASM_OP_LDFD_C_CLR,			\
	ASM_OP_LDFD_C_NC, ASM_OP_LDFD_S, ASM_OP_LDFD_SA,		\
	ASM_OP_LDFE_, ASM_OP_LDFE_A, ASM_OP_LDFE_C_CLR,			\
	ASM_OP_LDFE_C_NC, ASM_OP_LDFE_S, ASM_OP_LDFE_SA,		\
	ASM_OP_LDFP8_, ASM_OP_LDFP8_A, ASM_OP_LDFP8_C_CLR,		\
	ASM_OP_LDFP8_C_NC, ASM_OP_LDFP8_S, ASM_OP_LDFP8_SA,		\
	ASM_OP_LDFPD_, ASM_OP_LDFPD_A, ASM_OP_LDFPD_C_CLR,		\
	ASM_OP_LDFPD_C_NC, ASM_OP_LDFPD_S, ASM_OP_LDFPD_SA,		\
	ASM_OP_LDFPS_, ASM_OP_LDFPS_A, ASM_OP_LDFPS_C_CLR,		\
	ASM_OP_LDFPS_C_NC, ASM_OP_LDFPS_S, ASM_OP_LDFPS_SA,		\
	ASM_OP_LDFS_, ASM_OP_LDFS_A, ASM_OP_LDFS_C_CLR,			\
	ASM_OP_LDFS_C_NC, ASM_OP_LDFS_S, ASM_OP_LDFS_SA,		\
	ASM_OP_LFETCH_, ASM_OP_LFETCH_EXCL, ASM_OP_LFETCH_FAULT,	\
	ASM_OP_LFETCH_FAULT_EXCL,					\
	ASM_OP_MF_, ASM_OP_MF_A,					\
	ASM_OP_MIX1_L, ASM_OP_MIX1_R,					\
	ASM_OP_MIX2_L, ASM_OP_MIX2_R,					\
	ASM_OP_MIX4_L, ASM_OP_MIX4_R,					\
	ASM_OP_MOV_, ASM_OP_MOV_CPUID, ASM_OP_MOV_DBR, ASM_OP_MOV_I,	\
	ASM_OP_MOV_IBR, ASM_OP_MOV_IP, ASM_OP_MOV_M, ASM_OP_MOV_MSR,	\
	ASM_OP_MOV_PKR, ASM_OP_MOV_PMC, ASM_OP_MOV_PMD, ASM_OP_MOV_PR,	\
	ASM_OP_MOV_PSR, ASM_OP_MOV_PSR_L, ASM_OP_MOV_PSR_UM,		\
	ASM_OP_MOV_RET, ASM_OP_MOV_RR,					\
	ASM_OP_NOP_B, ASM_OP_NOP_F, ASM_OP_NOP_I, ASM_OP_NOP_M,		\
	ASM_OP_NOP_X,							\
	ASM_OP_PACK2_SSS, ASM_OP_PACK2_USS,				\
	ASM_OP_PACK4_SSS,						\
	ASM_OP_PADD1_, ASM_OP_PADD1_SSS, ASM_OP_PADD1_UUS,		\
	ASM_OP_PADD1_UUU,						\
	ASM_OP_PADD2_, ASM_OP_PADD2_SSS, ASM_OP_PADD2_UUS,		\
	ASM_OP_PADD2_UUU,						\
	ASM_OP_PAVG1_, ASM_OP_PAVG1_RAZ,				\
	ASM_OP_PAVG2_, ASM_OP_PAVG2_RAZ,				\
	ASM_OP_PCMP1_EQ, ASM_OP_PCMP1_GT,				\
	ASM_OP_PCMP2_EQ, ASM_OP_PCMP2_GT,				\
	ASM_OP_PCMP4_EQ, ASM_OP_PCMP4_GT,				\
	ASM_OP_PMAX1_U,							\
	ASM_OP_PMIN1_U,							\
	ASM_OP_PMPY2_L, ASM_OP_PMPY2_R,					\
	ASM_OP_PMPYSHR2_, ASM_OP_PMPYSHR2_U,				\
	ASM_OP_PROBE_R, ASM_OP_PROBE_R_FAULT, ASM_OP_PROBE_RW_FAULT,	\
	ASM_OP_PROBE_W, ASM_OP_PROBE_W_FAULT,				\
	ASM_OP_PSHR2_, ASM_OP_PSHR2_U,					\
	ASM_OP_PSHR4_, ASM_OP_PSHR4_U,					\
	ASM_OP_PSUB1_, ASM_OP_PSUB1_SSS, ASM_OP_PSUB1_UUS,		\
	ASM_OP_PSUB1_UUU,						\
	ASM_OP_PSUB2_, ASM_OP_PSUB2_SSS, ASM_OP_PSUB2_UUS,		\
	ASM_OP_PSUB2_UUU,						\
	ASM_OP_PTC_E, ASM_OP_PTC_G, ASM_OP_PTC_GA, ASM_OP_PTC_L,	\
	ASM_OP_PTR_D, ASM_OP_PTR_I,					\
	ASM_OP_SETF_EXP, ASM_OP_SETF_D, ASM_OP_SETF_S, ASM_OP_SETF_SIG,	\
	ASM_OP_SHR_, ASM_OP_SHR_U,					\
	ASM_OP_SRLZ_D, ASM_OP_SRLZ_I,					\
	ASM_OP_ST1_, ASM_OP_ST1_REL,					\
	ASM_OP_ST16_, ASM_OP_ST16_REL,					\
	ASM_OP_ST2_, ASM_OP_ST2_REL,					\
	ASM_OP_ST4_, ASM_OP_ST4_REL,					\
	ASM_OP_ST8_, ASM_OP_ST8_REL, ASM_OP_ST8_SPILL,			\
	ASM_OP_STF_SPILL,						\
	ASM_OP_SYNC_I,							\
	ASM_OP_TBIT_NZ_AND, ASM_OP_TBIT_NZ_OR, ASM_OP_TBIT_NZ_OR_ANDCM,	\
	ASM_OP_TBIT_Z, ASM_OP_TBIT_Z_AND, ASM_OP_TBIT_Z_OR,		\
	ASM_OP_TBIT_Z_OR_ANDCM, ASM_OP_TBIT_Z_UNC,			\
	ASM_OP_TF_NZ_AND, ASM_OP_TF_NZ_OR, ASM_OP_TF_NZ_OR_ANDCM,	\
	ASM_OP_TF_Z, ASM_OP_TF_Z_AND, ASM_OP_TF_Z_OR,			\
	ASM_OP_TF_Z_OR_ANDCM, ASM_OP_TF_Z_UNC,				\
	ASM_OP_TNAT_NZ_AND, ASM_OP_TNAT_NZ_OR, ASM_OP_TNAT_NZ_OR_ANDCM,	\
	ASM_OP_TNAT_Z, ASM_OP_TNAT_Z_AND, ASM_OP_TNAT_Z_OR,		\
	ASM_OP_TNAT_Z_OR_ANDCM, ASM_OP_TNAT_Z_UNC,			\
	ASM_OP_UNPACK1_H, ASM_OP_UNPACK1_L,				\
	ASM_OP_UNPACK2_H, ASM_OP_UNPACK2_L,				\
	ASM_OP_UNPACK4_H, ASM_OP_UNPACK4_L,				\
	ASM_OP_VMSW_0, ASM_OP_VMSW_1,					\
	ASM_OP_XMA_H, ASM_OP_XMA_HU, ASM_OP_XMA_L,			\
	ASM_OP_NUMBER_OF_OPCODES

#endif /* _DISASM_INT_H_ */
