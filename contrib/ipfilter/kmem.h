/*	$FreeBSD: stable/9/contrib/ipfilter/kmem.h 153881 2005-12-30 11:52:26Z guido $	*/

/*
 * Copyright (C) 1993-2001 by Darren Reed.
 *
 * See the IPFILTER.LICENCE file for details on licencing.
 * $Id: kmem.h,v 2.5 2002/08/21 22:57:36 darrenr Exp $
 */

#ifndef	__KMEM_H__
#define	__KMEM_H__

#ifndef	__P
# ifdef	__STDC__
#  define	__P(x)	x
# else
#  define	__P(x)	()
# endif
#endif
extern	int	openkmem __P((char *, char *));
extern	int	kmemcpy __P((char *, long, int));
extern	int	kstrncpy __P((char *, long, int));

#if defined(__NetBSD__) || defined(__OpenBSD)
# include <paths.h>
#endif

#ifdef _PATH_KMEM
# define	KMEM	_PATH_KMEM
#else
# define	KMEM	"/dev/kmem"
#endif

#endif /* __KMEM_H__ */
