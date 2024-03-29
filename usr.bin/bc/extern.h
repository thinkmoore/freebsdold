/*	$FreeBSD: stable/9/usr.bin/bc/extern.h 203498 2010-02-04 18:43:05Z delphij $						*/
/*      $OpenBSD: extern.h,v 1.6 2006/03/18 20:44:43 otto Exp $	*/

/*
 * Copyright (c) 2003, Otto Moerbeek <otto@drijf.net>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <stdio.h>

struct lvalue {
	ssize_t	 load;
	ssize_t	 store;
};

int			 yylex(void);
void			 yyerror(const char *);
void			 fatal(const char *);
void			 abort_line(int);

extern int		 lineno;
extern int		 fileindex;
extern int		 sargc;
extern const char	**sargv;
extern const char	*filename;
extern char		*cmdexpr;
extern bool		 interactive;
extern EditLine		*el;
extern History		*hist;
extern HistEvent	 he;

