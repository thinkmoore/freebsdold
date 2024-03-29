/*-
 * Copyright (c) 2006 Joseph Koshy
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
__FBSDID("$FreeBSD: stable/9/lib/libelf/gelf_symshndx.c 164190 2006-11-11 17:16:35Z jkoshy $");

#include <sys/limits.h>

#include <assert.h>
#include <gelf.h>

#include "_libelf.h"

GElf_Sym *
gelf_getsymshndx(Elf_Data *d, Elf_Data *id, int ndx, GElf_Sym *dst,
    Elf32_Word *shindex)
{
	int ec;
	Elf *e;
	Elf_Scn *scn;
	size_t msz;
	uint32_t sh_type;

	if (gelf_getsym(d, ndx, dst) == 0)
		return (NULL);

	if (id == NULL || (scn = id->d_scn) == NULL ||
	    (e = scn->s_elf) == NULL || (e != d->d_scn->s_elf) ||
	    shindex == NULL) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (NULL);
	}

	ec = e->e_class;
	assert(ec == ELFCLASS32 || ec == ELFCLASS64);

	if (ec == ELFCLASS32)
		sh_type = scn->s_shdr.s_shdr32.sh_type;
	else
		sh_type = scn->s_shdr.s_shdr64.sh_type;

	if (_libelf_xlate_shtype(sh_type) != ELF_T_WORD ||
	   id->d_type != ELF_T_WORD) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (NULL);
	}

	msz = _libelf_msize(ELF_T_WORD, ec, e->e_version);

	assert(msz > 0);

	if (msz * ndx >= id->d_size) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (NULL);
	}

	*shindex = ((Elf32_Word *) id->d_buf)[ndx];

	return (dst);
}

int
gelf_update_symshndx(Elf_Data *d, Elf_Data *id, int ndx, GElf_Sym *gs,
    Elf32_Word xindex)
{
	int ec;
	Elf *e;
	Elf_Scn *scn;
	size_t msz;
	uint32_t sh_type;

	if (gelf_update_sym(d, ndx, gs) == 0)
		return (0);

	if (id == NULL || (scn = id->d_scn) == NULL ||
	    (e = scn->s_elf) == NULL || (e != d->d_scn->s_elf)) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (0);
	}

	ec = e->e_class;
	assert(ec == ELFCLASS32 || ec == ELFCLASS64);

	if (ec == ELFCLASS32)
		sh_type = scn->s_shdr.s_shdr32.sh_type;
	else
		sh_type = scn->s_shdr.s_shdr64.sh_type;

	if (_libelf_xlate_shtype(sh_type) != ELF_T_WORD ||
	    d->d_type != ELF_T_WORD) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (0);
	}

	msz = _libelf_msize(ELF_T_WORD, ec, e->e_version);
	assert(msz > 0);

	if (msz * ndx >= id->d_size) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (0);
	}

	*(((Elf32_Word *) id->d_buf) + ndx) = xindex;

	return (1);
}
