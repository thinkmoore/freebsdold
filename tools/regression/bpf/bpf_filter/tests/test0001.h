/*-
 * Test 0001:	Catch illegal instruction.
 *
 * $FreeBSD: stable/9/tools/regression/bpf/bpf_filter/tests/test0001.h 182415 2008-08-28 22:19:57Z jkim $
 */

/* BPF program */
struct bpf_insn pc[] = {
	BPF_STMT(0x55, 0),
	BPF_STMT(BPF_RET+BPF_A, 0),
};

/* Packet */
u_char	pkt[] = {
	0x00,
};

/* Packet length seen on wire */
u_int	wirelen =	sizeof(pkt);

/* Packet length passed on buffer */
u_int	buflen =	sizeof(pkt);

/* Invalid instruction */
int	invalid =	1;

/* Expected return value */
u_int	expect =	0;

/* Expected signal */
int	expect_signal =	SIGABRT;
