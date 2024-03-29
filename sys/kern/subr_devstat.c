/*-
 * Copyright (c) 1997, 1998, 1999 Kenneth D. Merry.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
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
 */

#include <sys/cdefs.h>
__FBSDID("$FreeBSD: stable/9/sys/kern/subr_devstat.c 248085 2013-03-09 02:36:32Z marius $");

#include "opt_kdtrace.h"

#include <sys/param.h>
#include <sys/kernel.h>
#include <sys/systm.h>
#include <sys/bio.h>
#include <sys/devicestat.h>
#include <sys/sysctl.h>
#include <sys/malloc.h>
#include <sys/lock.h>
#include <sys/mutex.h>
#include <sys/conf.h>
#include <vm/vm.h>
#include <vm/pmap.h>

#include <machine/atomic.h>

#ifdef KDTRACE_HOOKS
#include <sys/dtrace_bsd.h>

dtrace_io_start_probe_func_t dtrace_io_start_probe;
dtrace_io_done_probe_func_t dtrace_io_done_probe;
dtrace_io_wait_start_probe_func_t dtrace_io_wait_start_probe;
dtrace_io_wait_done_probe_func_t dtrace_io_wait_done_probe;

uint32_t	dtio_start_id;
uint32_t	dtio_done_id;
uint32_t	dtio_wait_start_id;
uint32_t	dtio_wait_done_id;

#define DTRACE_DEVSTAT_START() \
	if (dtrace_io_start_probe != NULL) \
		(*dtrace_io_start_probe)(dtio_start_id, NULL, ds);

#define DTRACE_DEVSTAT_BIO_START() \
	if (dtrace_io_start_probe != NULL) \
		(*dtrace_io_start_probe)(dtio_start_id, bp, ds);

#define DTRACE_DEVSTAT_DONE() \
	if (dtrace_io_done_probe != NULL) \
		(*dtrace_io_done_probe)(dtio_done_id, NULL, ds);

#define DTRACE_DEVSTAT_BIO_DONE() \
	if (dtrace_io_done_probe != NULL) \
		(*dtrace_io_done_probe)(dtio_done_id, bp, ds);

#define DTRACE_DEVSTAT_WAIT_START() \
	if (dtrace_io_wait_start_probe != NULL) \
		(*dtrace_io_wait_start_probe)(dtio_wait_start_id, NULL, ds);

#define DTRACE_DEVSTAT_WAIT_DONE() \
	if (dtrace_io_wait_done_probe != NULL) \
		(*dtrace_io_wait_done_probe)(dtio_wait_done_id, NULL, ds);

#else /* ! KDTRACE_HOOKS */

#define DTRACE_DEVSTAT_START()

#define DTRACE_DEVSTAT_BIO_START()

#define DTRACE_DEVSTAT_DONE()

#define DTRACE_DEVSTAT_BIO_DONE()

#define DTRACE_DEVSTAT_WAIT_START()

#define DTRACE_DEVSTAT_WAIT_DONE()
#endif /* KDTRACE_HOOKS */

static int devstat_num_devs;
static long devstat_generation = 1;
static int devstat_version = DEVSTAT_VERSION;
static int devstat_current_devnumber;
static struct mtx devstat_mutex;
MTX_SYSINIT(devstat_mutex, &devstat_mutex, "devstat", MTX_DEF);

static struct devstatlist device_statq = STAILQ_HEAD_INITIALIZER(device_statq);
static struct devstat *devstat_alloc(void);
static void devstat_free(struct devstat *);
static void devstat_add_entry(struct devstat *ds, const void *dev_name, 
		       int unit_number, uint32_t block_size,
		       devstat_support_flags flags,
		       devstat_type_flags device_type,
		       devstat_priority priority);

/*
 * Allocate a devstat and initialize it
 */
struct devstat *
devstat_new_entry(const void *dev_name,
		  int unit_number, uint32_t block_size,
		  devstat_support_flags flags,
		  devstat_type_flags device_type,
		  devstat_priority priority)
{
	struct devstat *ds;

	mtx_assert(&devstat_mutex, MA_NOTOWNED);

	ds = devstat_alloc();
	mtx_lock(&devstat_mutex);
	if (unit_number == -1) {
		ds->id = dev_name;
		binuptime(&ds->creation_time);
		devstat_generation++;
	} else {
		devstat_add_entry(ds, dev_name, unit_number, block_size,
				  flags, device_type, priority);
	}
	mtx_unlock(&devstat_mutex);
	return (ds);
}

/*
 * Take a malloced and zeroed devstat structure given to us, fill it in 
 * and add it to the queue of devices.  
 */
static void
devstat_add_entry(struct devstat *ds, const void *dev_name, 
		  int unit_number, uint32_t block_size,
		  devstat_support_flags flags,
		  devstat_type_flags device_type,
		  devstat_priority priority)
{
	struct devstatlist *devstat_head;
	struct devstat *ds_tmp;

	mtx_assert(&devstat_mutex, MA_OWNED);
	devstat_num_devs++;

	devstat_head = &device_statq;

	/*
	 * Priority sort.  Each driver passes in its priority when it adds
	 * its devstat entry.  Drivers are sorted first by priority, and
	 * then by probe order.
	 * 
	 * For the first device, we just insert it, since the priority
	 * doesn't really matter yet.  Subsequent devices are inserted into
	 * the list using the order outlined above.
	 */
	if (devstat_num_devs == 1)
		STAILQ_INSERT_TAIL(devstat_head, ds, dev_links);
	else {
		STAILQ_FOREACH(ds_tmp, devstat_head, dev_links) {
			struct devstat *ds_next;

			ds_next = STAILQ_NEXT(ds_tmp, dev_links);

			/*
			 * If we find a break between higher and lower
			 * priority items, and if this item fits in the
			 * break, insert it.  This also applies if the
			 * "lower priority item" is the end of the list.
			 */
			if ((priority <= ds_tmp->priority)
			 && ((ds_next == NULL)
			   || (priority > ds_next->priority))) {
				STAILQ_INSERT_AFTER(devstat_head, ds_tmp, ds,
						    dev_links);
				break;
			} else if (priority > ds_tmp->priority) {
				/*
				 * If this is the case, we should be able
				 * to insert ourselves at the head of the
				 * list.  If we can't, something is wrong.
				 */
				if (ds_tmp == STAILQ_FIRST(devstat_head)) {
					STAILQ_INSERT_HEAD(devstat_head,
							   ds, dev_links);
					break;
				} else {
					STAILQ_INSERT_TAIL(devstat_head,
							   ds, dev_links);
					printf("devstat_add_entry: HELP! "
					       "sorting problem detected "
					       "for name %p unit %d\n",
					       dev_name, unit_number);
					break;
				}
			}
		}
	}

	ds->device_number = devstat_current_devnumber++;
	ds->unit_number = unit_number;
	strlcpy(ds->device_name, dev_name, DEVSTAT_NAME_LEN);
	ds->block_size = block_size;
	ds->flags = flags;
	ds->device_type = device_type;
	ds->priority = priority;
	binuptime(&ds->creation_time);
	devstat_generation++;
}

/*
 * Remove a devstat structure from the list of devices.
 */
void
devstat_remove_entry(struct devstat *ds)
{
	struct devstatlist *devstat_head;

	mtx_assert(&devstat_mutex, MA_NOTOWNED);
	if (ds == NULL)
		return;

	mtx_lock(&devstat_mutex);

	devstat_head = &device_statq;

	/* Remove this entry from the devstat queue */
	atomic_add_acq_int(&ds->sequence1, 1);
	if (ds->id == NULL) {
		devstat_num_devs--;
		STAILQ_REMOVE(devstat_head, ds, devstat, dev_links);
	}
	devstat_free(ds);
	devstat_generation++;
	mtx_unlock(&devstat_mutex);
}

/*
 * Record a transaction start.
 *
 * See comments for devstat_end_transaction().  Ordering is very important
 * here.
 */
void
devstat_start_transaction(struct devstat *ds, struct bintime *now)
{

	mtx_assert(&devstat_mutex, MA_NOTOWNED);

	/* sanity check */
	if (ds == NULL)
		return;

	atomic_add_acq_int(&ds->sequence1, 1);
	/*
	 * We only want to set the start time when we are going from idle
	 * to busy.  The start time is really the start of the latest busy
	 * period.
	 */
	if (ds->start_count == ds->end_count) {
		if (now != NULL)
			ds->busy_from = *now;
		else
			binuptime(&ds->busy_from);
	}
	ds->start_count++;
	atomic_add_rel_int(&ds->sequence0, 1);
	DTRACE_DEVSTAT_START();
}

void
devstat_start_transaction_bio(struct devstat *ds, struct bio *bp)
{

	mtx_assert(&devstat_mutex, MA_NOTOWNED);

	/* sanity check */
	if (ds == NULL)
		return;

	binuptime(&bp->bio_t0);
	devstat_start_transaction(ds, &bp->bio_t0);
	DTRACE_DEVSTAT_BIO_START();
}

/*
 * Record the ending of a transaction, and incrment the various counters.
 *
 * Ordering in this function, and in devstat_start_transaction() is VERY
 * important.  The idea here is to run without locks, so we are very
 * careful to only modify some fields on the way "down" (i.e. at
 * transaction start) and some fields on the way "up" (i.e. at transaction
 * completion).  One exception is busy_from, which we only modify in
 * devstat_start_transaction() when there are no outstanding transactions,
 * and thus it can't be modified in devstat_end_transaction()
 * simultaneously.
 *
 * The sequence0 and sequence1 fields are provided to enable an application
 * spying on the structures with mmap(2) to tell when a structure is in a
 * consistent state or not.
 *
 * For this to work 100% reliably, it is important that the two fields
 * are at opposite ends of the structure and that they are incremented
 * in the opposite order of how a memcpy(3) in userland would copy them.
 * We assume that the copying happens front to back, but there is actually
 * no way short of writing your own memcpy(3) replacement to guarantee
 * this will be the case.
 *
 * In addition to this, being a kind of locks, they must be updated with
 * atomic instructions using appropriate memory barriers.
 */
void
devstat_end_transaction(struct devstat *ds, uint32_t bytes, 
			devstat_tag_type tag_type, devstat_trans_flags flags,
			struct bintime *now, struct bintime *then)
{
	struct bintime dt, lnow;

	/* sanity check */
	if (ds == NULL)
		return;

	if (now == NULL) {
		now = &lnow;
		binuptime(now);
	}

	atomic_add_acq_int(&ds->sequence1, 1);
	/* Update byte and operations counts */
	ds->bytes[flags] += bytes;
	ds->operations[flags]++;

	/*
	 * Keep a count of the various tag types sent.
	 */
	if ((ds->flags & DEVSTAT_NO_ORDERED_TAGS) == 0 &&
	    tag_type != DEVSTAT_TAG_NONE)
		ds->tag_types[tag_type]++;

	if (then != NULL) {
		/* Update duration of operations */
		dt = *now;
		bintime_sub(&dt, then);
		bintime_add(&ds->duration[flags], &dt);
	}

	/* Accumulate busy time */
	dt = *now;
	bintime_sub(&dt, &ds->busy_from);
	bintime_add(&ds->busy_time, &dt);
	ds->busy_from = *now;

	ds->end_count++;
	atomic_add_rel_int(&ds->sequence0, 1);
	DTRACE_DEVSTAT_DONE();
}

void
devstat_end_transaction_bio(struct devstat *ds, struct bio *bp)
{
	devstat_trans_flags flg;

	/* sanity check */
	if (ds == NULL)
		return;

	if (bp->bio_cmd == BIO_DELETE)
		flg = DEVSTAT_FREE;
	else if (bp->bio_cmd == BIO_READ)
		flg = DEVSTAT_READ;
	else if (bp->bio_cmd == BIO_WRITE)
		flg = DEVSTAT_WRITE;
	else 
		flg = DEVSTAT_NO_DATA;

	devstat_end_transaction(ds, bp->bio_bcount - bp->bio_resid,
				DEVSTAT_TAG_SIMPLE, flg, NULL, &bp->bio_t0);
	DTRACE_DEVSTAT_BIO_DONE();
}

/*
 * This is the sysctl handler for the devstat package.  The data pushed out
 * on the kern.devstat.all sysctl variable consists of the current devstat
 * generation number, and then an array of devstat structures, one for each
 * device in the system.
 *
 * This is more cryptic that obvious, but basically we neither can nor
 * want to hold the devstat_mutex for any amount of time, so we grab it
 * only when we need to and keep an eye on devstat_generation all the time.
 */
static int
sysctl_devstat(SYSCTL_HANDLER_ARGS)
{
	int error;
	long mygen;
	struct devstat *nds;

	mtx_assert(&devstat_mutex, MA_NOTOWNED);

	/*
	 * XXX devstat_generation should really be "volatile" but that
	 * XXX freaks out the sysctl macro below.  The places where we
	 * XXX change it and inspect it are bracketed in the mutex which
	 * XXX guarantees us proper write barriers.  I don't belive the
	 * XXX compiler is allowed to optimize mygen away across calls
	 * XXX to other functions, so the following is belived to be safe.
	 */
	mygen = devstat_generation;

	error = SYSCTL_OUT(req, &mygen, sizeof(mygen));

	if (devstat_num_devs == 0)
		return(0);

	if (error != 0)
		return (error);

	mtx_lock(&devstat_mutex);
	nds = STAILQ_FIRST(&device_statq); 
	if (mygen != devstat_generation)
		error = EBUSY;
	mtx_unlock(&devstat_mutex);

	if (error != 0)
		return (error);

	for (;nds != NULL;) {
		error = SYSCTL_OUT(req, nds, sizeof(struct devstat));
		if (error != 0)
			return (error);
		mtx_lock(&devstat_mutex);
		if (mygen != devstat_generation)
			error = EBUSY;
		else
			nds = STAILQ_NEXT(nds, dev_links);
		mtx_unlock(&devstat_mutex);
		if (error != 0)
			return (error);
	}
	return(error);
}

/*
 * Sysctl entries for devstat.  The first one is a node that all the rest
 * hang off of. 
 */
static SYSCTL_NODE(_kern, OID_AUTO, devstat, CTLFLAG_RD, NULL,
    "Device Statistics");

SYSCTL_PROC(_kern_devstat, OID_AUTO, all, CTLFLAG_RD|CTLTYPE_OPAQUE,
    NULL, 0, sysctl_devstat, "S,devstat", "All devices in the devstat list");
/*
 * Export the number of devices in the system so that userland utilities
 * can determine how much memory to allocate to hold all the devices.
 */
SYSCTL_INT(_kern_devstat, OID_AUTO, numdevs, CTLFLAG_RD, 
    &devstat_num_devs, 0, "Number of devices in the devstat list");
SYSCTL_LONG(_kern_devstat, OID_AUTO, generation, CTLFLAG_RD,
    &devstat_generation, 0, "Devstat list generation");
SYSCTL_INT(_kern_devstat, OID_AUTO, version, CTLFLAG_RD, 
    &devstat_version, 0, "Devstat list version number");

/*
 * Allocator for struct devstat structures.  We sub-allocate these from pages
 * which we get from malloc.  These pages are exported for mmap(2)'ing through
 * a miniature device driver
 */

#define statsperpage (PAGE_SIZE / sizeof(struct devstat))

static d_mmap_t devstat_mmap;

static struct cdevsw devstat_cdevsw = {
	.d_version =	D_VERSION,
	.d_flags =	D_NEEDGIANT,
	.d_mmap =	devstat_mmap,
	.d_name =	"devstat",
};

struct statspage {
	TAILQ_ENTRY(statspage)	list;
	struct devstat		*stat;
	u_int			nfree;
};

static TAILQ_HEAD(, statspage)	pagelist = TAILQ_HEAD_INITIALIZER(pagelist);
static MALLOC_DEFINE(M_DEVSTAT, "devstat", "Device statistics");

static int
devstat_mmap(struct cdev *dev, vm_ooffset_t offset, vm_paddr_t *paddr,
    int nprot, vm_memattr_t *memattr)
{
	struct statspage *spp;

	if (nprot != VM_PROT_READ)
		return (-1);
	TAILQ_FOREACH(spp, &pagelist, list) {
		if (offset == 0) {
			*paddr = vtophys(spp->stat);
			return (0);
		}
		offset -= PAGE_SIZE;
	}
	return (-1);
}

static struct devstat *
devstat_alloc(void)
{
	struct devstat *dsp;
	struct statspage *spp, *spp2;
	u_int u;
	static int once;

	mtx_assert(&devstat_mutex, MA_NOTOWNED);
	if (!once) {
		make_dev_credf(MAKEDEV_ETERNAL | MAKEDEV_CHECKNAME,
		    &devstat_cdevsw, 0, NULL, UID_ROOT, GID_WHEEL, 0400,
		    DEVSTAT_DEVICE_NAME);
		once = 1;
	}
	spp2 = NULL;
	mtx_lock(&devstat_mutex);
	for (;;) {
		TAILQ_FOREACH(spp, &pagelist, list) {
			if (spp->nfree > 0)
				break;
		}
		if (spp != NULL)
			break;
		mtx_unlock(&devstat_mutex);
		spp2 = malloc(sizeof *spp, M_DEVSTAT, M_ZERO | M_WAITOK);
		spp2->stat = malloc(PAGE_SIZE, M_DEVSTAT, M_ZERO | M_WAITOK);
		spp2->nfree = statsperpage;

		/*
		 * If free statspages were added while the lock was released
		 * just reuse them.
		 */
		mtx_lock(&devstat_mutex);
		TAILQ_FOREACH(spp, &pagelist, list)
			if (spp->nfree > 0)
				break;
		if (spp == NULL) {
			spp = spp2;

			/*
			 * It would make more sense to add the new page at the
			 * head but the order on the list determine the
			 * sequence of the mapping so we can't do that.
			 */
			TAILQ_INSERT_TAIL(&pagelist, spp, list);
		} else
			break;
	}
	dsp = spp->stat;
	for (u = 0; u < statsperpage; u++) {
		if (dsp->allocated == 0)
			break;
		dsp++;
	}
	spp->nfree--;
	dsp->allocated = 1;
	mtx_unlock(&devstat_mutex);
	if (spp2 != NULL && spp2 != spp) {
		free(spp2->stat, M_DEVSTAT);
		free(spp2, M_DEVSTAT);
	}
	return (dsp);
}

static void
devstat_free(struct devstat *dsp)
{
	struct statspage *spp;

	mtx_assert(&devstat_mutex, MA_OWNED);
	bzero(dsp, sizeof *dsp);
	TAILQ_FOREACH(spp, &pagelist, list) {
		if (dsp >= spp->stat && dsp < (spp->stat + statsperpage)) {
			spp->nfree++;
			return;
		}
	}
}

SYSCTL_INT(_debug_sizeof, OID_AUTO, devstat, CTLFLAG_RD,
    NULL, sizeof(struct devstat), "sizeof(struct devstat)");
