/*-
 * Copyright (c) 2003-2007 Tim Kientzle
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
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR(S) ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR(S) BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "test.h"
__FBSDID("$FreeBSD: stable/9/contrib/libarchive/libarchive/test/test_write_compress_program.c 229592 2012-01-05 12:06:54Z mm $");

char buff[1000000];
char buff2[64];

DEFINE_TEST(test_write_compress_program)
{
#if ARCHIVE_VERSION_NUMBER < 1009000
	skipping("archive_write_set_compress_program()");
#else
	struct archive_entry *ae;
	struct archive *a;
	size_t used;
	int blocksize = 1024;
	int r;

	if (!canGzip()) {
		skipping("Cannot run 'gzip'");
		return;
	}

	/* Create a new archive in memory. */
	/* Write it through an external "gzip" program. */
	assert((a = archive_write_new()) != NULL);
	assertA(0 == archive_write_set_format_ustar(a));
	r = archive_write_set_compression_program(a, "gzip");
	if (r == ARCHIVE_FATAL) {
		skipping("Write compression via external "
		    "program unsupported on this platform");
		archive_write_finish(a);
		return;
	}
	assertA(0 == archive_write_set_bytes_per_block(a, blocksize));
	assertA(0 == archive_write_set_bytes_in_last_block(a, blocksize));
	assertA(blocksize == archive_write_get_bytes_in_last_block(a));
	assertA(0 == archive_write_open_memory(a, buff, sizeof(buff), &used));
	assertA(blocksize == archive_write_get_bytes_in_last_block(a));

	/*
	 * Write a file to it.
	 */
	assert((ae = archive_entry_new()) != NULL);
	archive_entry_set_mtime(ae, 1, 10);
	archive_entry_copy_pathname(ae, "file");
	archive_entry_set_mode(ae, S_IFREG | 0755);
	archive_entry_set_size(ae, 8);

	assertA(0 == archive_write_header(a, ae));
	archive_entry_free(ae);
	assertA(8 == archive_write_data(a, "12345678", 9));

	/* Close out the archive. */
	assertA(0 == archive_write_close(a));
	assertA(0 == archive_write_finish(a));

	/*
	 * Now, read the data back through the built-in gzip support.
	 */
	assert((a = archive_read_new()) != NULL);
	assertEqualIntA(a, ARCHIVE_OK, archive_read_support_format_all(a));
	assertEqualIntA(a, ARCHIVE_OK, archive_read_support_compression_all(a));
	r = archive_read_support_compression_gzip(a);
	/* The compression_gzip() handler will fall back to gunzip
	 * automatically, but if we know gunzip isn't available, then
	 * skip the rest. */
	if (r != ARCHIVE_OK && !canGunzip()) {
		skipping("No libz and no gunzip program, "
		    "unable to verify gzip compression");
		assertEqualInt(ARCHIVE_OK, archive_read_finish(a));
		return;
	}
	assertEqualIntA(a, ARCHIVE_OK, archive_read_open_memory(a, buff, used));

	if (!assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae))) {
		archive_read_finish(a);
		return;
	}

	assertEqualInt(1, archive_entry_mtime(ae));
	assertEqualInt(0, archive_entry_atime(ae));
	assertEqualInt(0, archive_entry_ctime(ae));
	assertEqualString("file", archive_entry_pathname(ae));
	assertEqualInt((S_IFREG | 0755), archive_entry_mode(ae));
	assertEqualInt(8, archive_entry_size(ae));
	assertEqualIntA(a, 8, archive_read_data(a, buff2, 10));
	assertEqualMem(buff2, "12345678", 8);

	/* Verify the end of the archive. */
	assertEqualIntA(a, ARCHIVE_EOF, archive_read_next_header(a, &ae));
	assertEqualIntA(a, ARCHIVE_OK, archive_read_close(a));
	assertEqualInt(ARCHIVE_OK, archive_read_finish(a));
#endif
}
