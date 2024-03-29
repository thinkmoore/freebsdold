/* prepend_args.h - utilility programs for manpiulating argv[]
   Copyright (C) 1999 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
   02111-1307, USA.  */

/* $FreeBSD: stable/9/gnu/usr.bin/cvs/cvs/prepend_args.h 102849 2002-09-02 06:09:03Z peter $ */

/* This code, taken from GNU Grep, originally used the "PARAM" macro, as the
   current GNU coding standards requires.  Older GNU code used the "PROTO"
   macro, before the GNU coding standards replaced it.  We use the older
   form here to keep from having to include another file in cvs/src/main.c.  */

void prepend_default_options PROTO ((char const *, int *, char ***));
