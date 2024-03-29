/*-
 * Copyright (c) 2006 Marcel Moolenaar
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
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
__FBSDID("$FreeBSD: stable/9/sys/boot/efi/libefi/errno.c 164010 2006-11-05 22:03:04Z marcel $");

#include <efi.h>
#include <efilib.h>

int
efi_status_to_errno(EFI_STATUS status)
{
	int errno;

	switch (status) {
	case EFI_ACCESS_DENIED:
		errno = EPERM;
		break;

	case EFI_BUFFER_TOO_SMALL:
		errno = EOVERFLOW;
		break;

	case EFI_DEVICE_ERROR:
	case EFI_VOLUME_CORRUPTED:
		errno = EIO;
		break;

	case EFI_INVALID_PARAMETER:
		errno = EINVAL;
		break;

	case EFI_MEDIA_CHANGED:
		errno = ESTALE;
		break;

	case EFI_NO_MEDIA:
		errno = ENXIO;
		break;

	case EFI_NOT_FOUND:
		errno = ENOENT;
		break;

	case EFI_OUT_OF_RESOURCES:
		errno = ENOMEM;
		break;

	case EFI_UNSUPPORTED:
		errno = ENODEV;
		break;

	case EFI_VOLUME_FULL:
		errno = ENOSPC;
		break;

	case EFI_WRITE_PROTECTED:
		errno = EACCES;
		break;

	case 0:
		errno = 0;
		break;

	default:
		errno = EDOOFUS;
		break;
	}

	return (errno);
}
