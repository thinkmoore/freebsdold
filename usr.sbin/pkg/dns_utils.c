/*-
 * Copyright (c) 2012 Baptiste Daroussin <bapt@FreeBSD.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer,
 *    without modification, immediately at the beginning of the file.
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
 */

#include <sys/cdefs.h>
__FBSDID("$FreeBSD: stable/9/usr.sbin/pkg/dns_utils.c 252216 2013-06-25 21:49:06Z bapt $");

#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <resolv.h>

#include "dns_utils.h"

typedef union {
	HEADER hdr;
	unsigned char buf[1024];
} dns_query;

struct dns_srvinfo *
dns_getsrvinfo(const char *zone)
{
	struct dns_srvinfo **res, *first;
	unsigned char *end, *p;
	char host[MAXHOSTNAMELEN];
	dns_query q;
	int len, qdcount, ancount, n, i;
	unsigned int type, class, ttl, priority, weight, port;

	if ((len = res_query(zone, C_IN, T_SRV, q.buf, sizeof(q.buf))) == -1 ||
	    len < (int)sizeof(HEADER))
		return (NULL);

	qdcount = ntohs(q.hdr.qdcount);
	ancount = ntohs(q.hdr.ancount);

	end = q.buf + len;
	p = q.buf + sizeof(HEADER);

	while(qdcount > 0 && p < end) {
		qdcount--;
		if((len = dn_expand(q.buf, end, p, host, MAXHOSTNAMELEN)) < 0)
			return (NULL);
		p += len + NS_QFIXEDSZ;
	}

	res = calloc(ancount, sizeof(struct dns_srvinfo *));
	if (res == NULL)
		return (NULL);

	n = 0;
	while (ancount > 0 && p < end) {
		ancount--;
		len = dn_expand(q.buf, end, p, host, MAXHOSTNAMELEN);
		if (len < 0) {
			for (i = 0; i < n; i++)
				free(res[i]);
			free(res);
			return NULL;
		}

		p += len;

		NS_GET16(type, p);
		NS_GET16(class, p);
		NS_GET32(ttl, p);
		NS_GET16(len, p);

		if (type != T_SRV) {
			p += len;
			continue;
		}

		NS_GET16(priority, p);
		NS_GET16(weight, p);
		NS_GET16(port, p);

		len = dn_expand(q.buf, end, p, host, MAXHOSTNAMELEN);
		if (len < 0) {
			for (i = 0; i < n; i++)
				free(res[i]);
			free(res);
			return (NULL);
		}

		res[n] = malloc(sizeof(struct dns_srvinfo));
		if (res[n] == NULL) {
			for (i = 0; i < n; i++)
				free(res[i]);
			free(res);
			return (NULL);
		}
		res[n]->type = type;
		res[n]->class = class;
		res[n]->ttl = ttl;
		res[n]->priority = priority;
		res[n]->weight = weight;
		res[n]->port = port;
		res[n]->next = NULL;
		strlcpy(res[n]->host, host, MAXHOSTNAMELEN);

		p += len;
		n++;
	}

	for (i = 0; i < n - 1; i++)
		res[i]->next = res[i + 1];

	first = res[0];
	free(res);

	return (first);
}
