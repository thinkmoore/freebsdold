/*	$FreeBSD: stable/9/contrib/ipfilter/lib/optprint.c 170268 2007-06-04 02:54:36Z darrenr $	*/

/*
 * Copyright (C) 2000-2005 by Darren Reed.
 *
 * See the IPFILTER.LICENCE file for details on licencing.
 *
 * $Id: optprint.c,v 1.6.4.2 2006/06/16 17:21:08 darrenr Exp $
 */
#include "ipf.h"


void optprint(sec, optmsk, optbits)
u_short *sec;
u_long optmsk, optbits;
{
	u_short secmsk = sec[0], secbits = sec[1];
	struct ipopt_names *io, *so;
	char *s;

	s = " opt ";
	for (io = ionames; io->on_name; io++)
		if ((io->on_bit & optmsk) &&
		    ((io->on_bit & optmsk) == (io->on_bit & optbits))) {
			if ((io->on_value != IPOPT_SECURITY) ||
			    (!secmsk && !secbits)) {
				printf("%s%s", s, io->on_name);
				/*
				 * Because the ionames table has this entry
				 * twice.
				 */
				if (io->on_value == IPOPT_SECURITY)
					io++;
				s = ",";
			}
		}


	if (secmsk & secbits) {
		printf("%ssec-class", s);
		s = " ";
		for (so = secclass; so->on_name; so++)
			if ((secmsk & so->on_bit) &&
			    ((so->on_bit & secmsk) == (so->on_bit & secbits))) {
				printf("%s%s", s, so->on_name);
				s = ",";
			}
	}

	if ((optmsk && (optmsk != optbits)) ||
	    (secmsk && (secmsk != secbits))) {
		s = " ";
		printf(" not opt");
		if (optmsk != optbits) {
			for (io = ionames; io->on_name; io++)
				if ((io->on_bit & optmsk) &&
				    ((io->on_bit & optmsk) !=
				     (io->on_bit & optbits))) {
					if ((io->on_value != IPOPT_SECURITY) ||
					    (!secmsk && !secbits)) {
						printf("%s%s", s, io->on_name);
						s = ",";
						if (io->on_value ==
						    IPOPT_SECURITY)
							io++;
					} else
						io++;
				}
		}

		if (secmsk != secbits) {
			printf("%ssec-class", s);
			s = " ";
			for (so = secclass; so->on_name; so++)
				if ((so->on_bit & secmsk) &&
				    ((so->on_bit & secmsk) !=
				     (so->on_bit & secbits))) {
					printf("%s%s", s, so->on_name);
					s = ",";
				}
		}
	}
}
