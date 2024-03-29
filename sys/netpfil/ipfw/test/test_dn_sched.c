/*
 * $FreeBSD: stable/9/sys/netpfil/ipfw/test/test_dn_sched.c 204736 2010-03-04 21:52:40Z luigi $
 *
 * library functions for userland testing of dummynet schedulers
 */

#include "dn_test.h"

void
m_freem(struct mbuf *m)
{
	printf("free %p\n", m);
}

int
dn_sched_modevent(module_t mod, int cmd, void *arg)
{
	return 0;
}

void
dn_free_pkts(struct mbuf *m)
{
	struct mbuf *x;
	while ( (x = m) ) {
		m = m->m_nextpkt;
		m_freem(x);
	}
}
		
int
dn_delete_queue(void *_q, void *do_free)
{
	struct dn_queue *q = _q;
        if (q->mq.head)
                dn_free_pkts(q->mq.head);
        free(q);
        return 0;
}

/*
 * This is a simplified function for testing purposes, which does
 * not implement statistics or random loss.
 * Enqueue a packet in q, subject to space and queue management policy
 * (whose parameters are in q->fs).
 * Update stats for the queue and the scheduler.
 * Return 0 on success, 1 on drop. The packet is consumed anyways.
 */
int
dn_enqueue(struct dn_queue *q, struct mbuf* m, int drop)
{
        if (drop)
                goto drop;
        if (q->ni.length >= 200)
                goto drop;
        mq_append(&q->mq, m);
        q->ni.length++;
        q->ni.tot_bytes += m->m_pkthdr.len;
        return 0;

drop:
        q->ni.drops++;
        return 1;
}

int
ipdn_bound_var(int *v, int dflt, int lo, int hi, const char *msg)
{
        if (*v < lo) {
                *v = dflt;
        } else if (*v > hi) {
                *v = hi;
        }
        return *v;
}

#ifndef __FreeBSD__
int
fls(int mask)
{
	int bit;

	if (mask == 0)
		return (0);
	for (bit = 1; mask != 1; bit++)
		mask = (unsigned int)mask >> 1;
	return (bit);
}
#endif
