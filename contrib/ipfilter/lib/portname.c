/*	$FreeBSD: stable/9/contrib/ipfilter/lib/portname.c 170268 2007-06-04 02:54:36Z darrenr $	*/

/*
 * Copyright (C) 2000-2003 by Darren Reed.
 *
 * See the IPFILTER.LICENCE file for details on licencing.
 *
 * $Id: portname.c,v 1.7.2.1 2006/06/16 17:21:09 darrenr Exp $
 */
#include "ipf.h"


char	*portname(pr, port)
int	pr, port;
{
	static	char	buf[32];
	struct	protoent	*p = NULL;
	struct	servent	*sv = NULL, *sv1 = NULL;

	if ((opts & OPT_NORESOLVE) == 0) {
		if (pr == -1) {
			if ((sv = getservbyport(htons(port), "tcp"))) {
				strncpy(buf, sv->s_name, sizeof(buf)-1);
				buf[sizeof(buf)-1] = '\0';
				sv1 = getservbyport(htons(port), "udp");
				sv = strncasecmp(buf, sv->s_name, strlen(buf)) ?
				     NULL : sv1;
			}
			if (sv)
				return buf;
		} else if ((pr != -2) && (p = getprotobynumber(pr))) {
			if ((sv = getservbyport(htons(port), p->p_name))) {
				strncpy(buf, sv->s_name, sizeof(buf)-1);
				buf[sizeof(buf)-1] = '\0';
				return buf;
			}
		}
	}

	(void) sprintf(buf, "%d", port);
	return buf;
}
