/*-
 * Copyright 2007-2009 Solarflare Communications Inc.  All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS AND
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
 *
 * $FreeBSD: stable/9/sys/dev/sfxge/common/siena_flash.h 228100 2011-11-28 20:28:23Z philip $
 */

#ifndef	_SYS_SIENA_FLASH_H
#define	_SYS_SIENA_FLASH_H

#pragma pack(1)

/* Fixed locations near the start of flash (which may be in the internal PHY
 * firmware header) point to the boot header.
 *
 * - parsed by MC boot ROM and firmware
 * - reserved (but not parsed) by PHY firmware
 * - opaque to driver
 */

#define	SIENA_MC_BOOT_PHY_FW_HDR_LEN (0x20)

#define	SIENA_MC_BOOT_PTR_LOCATION (0x18)      /* First thing we try to boot */
#define	SIENA_MC_BOOT_ALT_PTR_LOCATION (0x1c)  /* Alternative if that fails */

#define	SIENA_MC_BOOT_HDR_LEN (0x200)

#define	SIENA_MC_BOOT_MAGIC (0x51E4A001)
#define	SIENA_MC_BOOT_VERSION (1)

typedef struct siena_mc_boot_hdr_s {		/* GENERATED BY scripts/genfwdef */
	efx_dword_t	magic;			/* = SIENA_MC_BOOT_MAGIC */
	efx_word_t	hdr_version;		/* this structure definition is version 1 */
	efx_byte_t	board_type;
	efx_byte_t	firmware_version_a;
	efx_byte_t	firmware_version_b;
	efx_byte_t	firmware_version_c;
	efx_word_t	checksum;		/* of whole header area + firmware image */
	efx_word_t	firmware_version_d;
	efx_word_t	reserved_a[1];		/* (set to 0) */
	efx_dword_t	firmware_text_offset;	/* offset to firmware .text */
	efx_dword_t	firmware_text_size;	/* length of firmware .text, in bytes */
	efx_dword_t	firmware_data_offset;	/* offset to firmware .data */
	efx_dword_t	firmware_data_size;	/* length of firmware .data, in bytes */
	efx_dword_t	reserved_b[8];		/* (set to 0) */
} siena_mc_boot_hdr_t;

#define	SIENA_MC_STATIC_CONFIG_MAGIC (0xBDCF5555)
#define	SIENA_MC_STATIC_CONFIG_VERSION (0)

typedef struct siena_mc_static_config_hdr_s {	/* GENERATED BY scripts/genfwdef */
	efx_dword_t	magic;			/* = SIENA_MC_STATIC_CONFIG_MAGIC */
	efx_word_t	length;			/* of header area (i.e. not including VPD) */
	efx_byte_t	version;
	efx_byte_t	csum;			/* over header area (i.e. not including VPD) */
	efx_dword_t	static_vpd_offset;
	efx_dword_t	static_vpd_length;
	efx_dword_t	capabilities;
	efx_byte_t	mac_addr_base[6];
	efx_byte_t	green_mode_cal;		/* Green mode calibration result */
	efx_byte_t	green_mode_valid;	/* Whether cal holds a valid value */
	efx_word_t	mac_addr_count;
	efx_word_t	mac_addr_stride;
	efx_dword_t	reserved2[2];		/* (write as zero) */
	efx_dword_t	num_dbi_items;
	struct {
		efx_word_t	addr;
		efx_word_t	byte_enables;
		efx_dword_t	value;
	} dbi[];
} siena_mc_static_config_hdr_t;

#define	SIENA_MC_DYNAMIC_CONFIG_MAGIC (0xBDCFDDDD)
#define	SIENA_MC_DYNAMIC_CONFIG_VERSION (0)

typedef struct siena_mc_fw_version_s {		/* GENERATED BY scripts/genfwdef */
	efx_dword_t	fw_subtype;
	efx_word_t	version_w;
	efx_word_t	version_x;
	efx_word_t	version_y;
	efx_word_t	version_z;
} siena_mc_fw_version_t;

typedef struct siena_mc_dynamic_config_hdr_s {	/* GENERATED BY scripts/genfwdef */
	efx_dword_t	magic;			/* = SIENA_MC_DYNAMIC_CONFIG_MAGIC */
	efx_word_t	length;			/* of header area (i.e. not including VPD) */
	efx_byte_t	version;
	efx_byte_t	csum;			/* over header area (i.e. not including VPD) */
	efx_dword_t	dynamic_vpd_offset;
	efx_dword_t	dynamic_vpd_length;
	efx_dword_t	num_fw_version_items;
	siena_mc_fw_version_t	fw_version[];
} siena_mc_dynamic_config_hdr_t;

#define	SIENA_MC_EXPROM_SINGLE_MAGIC (0xAA55)  /* little-endian uint16_t */

#define	SIENA_MC_EXPROM_COMBO_MAGIC (0xB0070102)  /* little-endian uint32_t */

typedef struct siena_mc_combo_rom_hdr_s {	/* GENERATED BY scripts/genfwdef */
	efx_dword_t	magic;			/* = SIENA_MC_EXPROM_COMBO_MAGIC */
	efx_dword_t	len1;			/* length of first image */
	efx_dword_t	len2;			/* length of second image */
	efx_dword_t	off1;			/* offset of first byte to edit to combine images */
	efx_dword_t	off2;			/* offset of second byte to edit to combine images */
	efx_word_t	infoblk0_off;		/* infoblk offset */
	efx_word_t	infoblk1_off;		/* infoblk offset */
	efx_byte_t	infoblk_len;		/* length of space reserved for infoblk structures */
	efx_byte_t	reserved[7];		/* (set to 0) */
} siena_mc_combo_rom_hdr_t;

#pragma pack()

#endif	/* _SYS_SIENA_FLASH_H */
