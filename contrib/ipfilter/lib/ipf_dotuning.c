/*	$FreeBSD: stable/9/contrib/ipfilter/lib/ipf_dotuning.c 170268 2007-06-04 02:54:36Z darrenr $	*/

/*
 * Copyright (C) 2003-2005 by Darren Reed.
 * 
 * See the IPFILTER.LICENCE file for details on licencing.  
 *   
 * $Id: ipf_dotuning.c,v 1.2.4.3 2006/06/16 17:21:02 darrenr Exp $ 
 */     

#include "ipf.h"
#include "netinet/ipl.h"
#include <sys/ioctl.h>

void ipf_dotuning(fd, tuneargs, iocfn)
int fd;
char *tuneargs;
ioctlfunc_t iocfn;
{
	ipfobj_t obj;
	ipftune_t tu;
	char *s, *t;

	bzero((char *)&tu, sizeof(tu));
	obj.ipfo_rev = IPFILTER_VERSION;
	obj.ipfo_size = sizeof(tu);;
	obj.ipfo_ptr = (void *)&tu;
	obj.ipfo_type = IPFOBJ_TUNEABLE;

	for (s = strtok(tuneargs, ","); s != NULL; s = strtok(NULL, ",")) {
		if (!strcmp(s, "list")) {
			while (1) {
				if ((*iocfn)(fd, SIOCIPFGETNEXT, &obj) == -1) {
					perror("ioctl(SIOCIPFGETNEXT)");
					break;
				}
				if (tu.ipft_cookie == NULL)
					break;

				tu.ipft_name[sizeof(tu.ipft_name) - 1] = '\0';
				printtunable(&tu);
			}
		} else if ((t = strchr(s, '=')) != NULL) {
			tu.ipft_cookie = NULL;
			*t++ = '\0';
			strncpy(tu.ipft_name, s, sizeof(tu.ipft_name));
			if (sscanf(t, "%lu", &tu.ipft_vlong) == 1) {
				if ((*iocfn)(fd, SIOCIPFSET, &obj) == -1) {
					perror("ioctl(SIOCIPFSET)");
					return;
				}
			} else {
				fprintf(stderr, "invalid value '%s'\n", s);
				return;
			}
		} else {
			tu.ipft_cookie = NULL;
			strncpy(tu.ipft_name, s, sizeof(tu.ipft_name));
			if ((*iocfn)(fd, SIOCIPFGET, &obj) == -1) {
				perror("ioctl(SIOCIPFGET)");
				return;
			}
			if (tu.ipft_cookie == NULL) {
				fprintf(stderr, "Null cookie for %s\n", s);
				return;
			}

			tu.ipft_name[sizeof(tu.ipft_name) - 1] = '\0';
			printtunable(&tu);
		}
	}
}
