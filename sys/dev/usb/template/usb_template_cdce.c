#include <sys/cdefs.h>
__FBSDID("$FreeBSD: stable/9/sys/dev/usb/template/usb_template_cdce.c 223467 2011-06-23 07:54:03Z hselasky $");

/*-
 * Copyright (c) 2007 Hans Petter Selasky <hselasky@FreeBSD.org>
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

/*
 * This file contains the USB templates for a CDC USB ethernet device.
 */

#include <sys/stdint.h>
#include <sys/stddef.h>
#include <sys/param.h>
#include <sys/queue.h>
#include <sys/types.h>
#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/bus.h>
#include <sys/module.h>
#include <sys/lock.h>
#include <sys/mutex.h>
#include <sys/condvar.h>
#include <sys/sysctl.h>
#include <sys/sx.h>
#include <sys/unistd.h>
#include <sys/callout.h>
#include <sys/malloc.h>
#include <sys/priv.h>

#include <dev/usb/usb.h>
#include <dev/usb/usbdi.h>
#include <dev/usb/usb_cdc.h>

#include <dev/usb/template/usb_template.h>

enum {
	STRING_LANG_INDEX,
	STRING_MAC_INDEX,
	STRING_ETH_CONTROL_INDEX,
	STRING_ETH_DATA_INDEX,
	STRING_ETH_CONFIG_INDEX,
	STRING_ETH_VENDOR_INDEX,
	STRING_ETH_PRODUCT_INDEX,
	STRING_ETH_SERIAL_INDEX,
	STRING_ETH_MAX,
};

#define	STRING_LANG \
  0x09, 0x04,				/* American English */

#define	STRING_MAC \
  '2', 0, 'A', 0, '2', 0, '3', 0, \
  '4', 0, '5', 0, '6', 0, '7', 0, \
  '8', 0, '9', 0, 'A', 0, 'B', 0,

#define	STRING_ETH_CONTROL \
  'U', 0, 'S', 0, 'B', 0, ' ', 0, \
  'E', 0, 't', 0, 'h', 0, 'e', 0, \
  'r', 0, 'n', 0, 'e', 0, 't', 0, \
  ' ', 0, 'C', 0, 'o', 0, 'm', 0, \
  'm', 0, ' ', 0, 'i', 0, 'n', 0, \
  't', 0, 'e', 0, 'r', 0, 'f', 0, \
  'a', 0, 'c', 0, 'e', 0,

#define	STRING_ETH_DATA \
  'U', 0, 'S', 0, 'B', 0, ' ', 0, \
  'E', 0, 't', 0, 'h', 0, 'e', 0, \
  'r', 0, 'n', 0, 'e', 0, 't', 0, \
  ' ', 0, 'D', 0, 'a', 0, 't', 0, \
  'a', 0, ' ', 0, 'i', 0, 'n', 0, \
  't', 0, 'e', 0, 'r', 0, 'f', 0, \
  'a', 0, 'c', 0, 'e', 0,

#define	STRING_ETH_CONFIG \
  'D', 0, 'e', 0, 'f', 0, 'a', 0, \
  'u', 0, 'l', 0, 't', 0, ' ', 0, \
  'c', 0, 'o', 0, 'n', 0, 'f', 0, \
  'i', 0, 'g', 0,

#define	STRING_ETH_VENDOR \
  'F', 0, 'r', 0, 'e', 0, 'e', 0, \
  'B', 0, 'S', 0, 'D', 0, ' ', 0, \
  'f', 0, 'o', 0, 'u', 0, 'n', 0, \
  'd', 0, 'a', 0, 't', 0, 'i', 0, \
  'o', 0, 'n', 0,

#define	STRING_ETH_PRODUCT \
  'U', 0, 'S', 0, 'B', 0, ' ', 0, \
  'E', 0, 't', 0, 'h', 0, 'e', 0, \
  'r', 0, 'n', 0, 'e', 0, 't', 0, \
  ' ', 0, 'A', 0, 'd', 0, 'a', 0, \
  'p', 0, 't', 0, 'e', 0, 'r', 0,

#define	STRING_ETH_SERIAL \
  'D', 0, 'e', 0, 'c', 0, 'e', 0, \
  'm', 0, 'b', 0, 'e', 0, 'r', 0, \
  ' ', 0, '2', 0, '0', 0, '0', 0, \
  '7', 0,

/* make the real string descriptors */

USB_MAKE_STRING_DESC(STRING_LANG, string_lang);
USB_MAKE_STRING_DESC(STRING_MAC, string_mac);
USB_MAKE_STRING_DESC(STRING_ETH_CONTROL, string_eth_control);
USB_MAKE_STRING_DESC(STRING_ETH_DATA, string_eth_data);
USB_MAKE_STRING_DESC(STRING_ETH_CONFIG, string_eth_config);
USB_MAKE_STRING_DESC(STRING_ETH_VENDOR, string_eth_vendor);
USB_MAKE_STRING_DESC(STRING_ETH_PRODUCT, string_eth_product);
USB_MAKE_STRING_DESC(STRING_ETH_SERIAL, string_eth_serial);

/* prototypes */

static usb_temp_get_string_desc_t eth_get_string_desc;

static const struct usb_cdc_union_descriptor eth_union_desc = {
	.bLength = sizeof(eth_union_desc),
	.bDescriptorType = UDESC_CS_INTERFACE,
	.bDescriptorSubtype = UDESCSUB_CDC_UNION,
	.bMasterInterface = 0,		/* this is automatically updated */
	.bSlaveInterface[0] = 1,	/* this is automatically updated */
};

static const struct usb_cdc_header_descriptor eth_header_desc = {
	.bLength = sizeof(eth_header_desc),
	.bDescriptorType = UDESC_CS_INTERFACE,
	.bDescriptorSubtype = UDESCSUB_CDC_HEADER,
	.bcdCDC[0] = 0x10,
	.bcdCDC[1] = 0x01,
};

static const struct usb_cdc_ethernet_descriptor eth_enf_desc = {
	.bLength = sizeof(eth_enf_desc),
	.bDescriptorType = UDESC_CS_INTERFACE,
	.bDescriptorSubtype = UDESCSUB_CDC_ENF,
	.iMacAddress = STRING_MAC_INDEX,
	.bmEthernetStatistics = {0, 0, 0, 0},
	.wMaxSegmentSize = {0xEA, 0x05},/* 1514 bytes */
	.wNumberMCFilters = {0, 0},
	.bNumberPowerFilters = 0,
};

static const void *eth_control_if_desc[] = {
	&eth_union_desc,
	&eth_header_desc,
	&eth_enf_desc,
	NULL,
};

static const struct usb_temp_packet_size bulk_mps = {
	.mps[USB_SPEED_FULL] = 64,
	.mps[USB_SPEED_HIGH] = 512,
};

static const struct usb_temp_packet_size intr_mps = {
	.mps[USB_SPEED_FULL] = 8,
	.mps[USB_SPEED_HIGH] = 8,
};

static const struct usb_temp_endpoint_desc bulk_in_ep = {
	.pPacketSize = &bulk_mps,
#ifdef USB_HIP_IN_EP_0
	.bEndpointAddress = USB_HIP_IN_EP_0,
#else
	.bEndpointAddress = UE_DIR_IN,
#endif
	.bmAttributes = UE_BULK,
};

static const struct usb_temp_endpoint_desc bulk_out_ep = {
	.pPacketSize = &bulk_mps,
#ifdef USB_HIP_OUT_EP_0
	.bEndpointAddress = USB_HIP_OUT_EP_0,
#else
	.bEndpointAddress = UE_DIR_OUT,
#endif
	.bmAttributes = UE_BULK,
};

static const struct usb_temp_endpoint_desc intr_in_ep = {
	.pPacketSize = &intr_mps,
	.bEndpointAddress = UE_DIR_IN,
	.bmAttributes = UE_INTERRUPT,
};

static const struct usb_temp_endpoint_desc *eth_intr_endpoints[] = {
	&intr_in_ep,
	NULL,
};

static const struct usb_temp_interface_desc eth_control_interface = {
	.ppEndpoints = eth_intr_endpoints,
	.ppRawDesc = eth_control_if_desc,
	.bInterfaceClass = UICLASS_CDC,
	.bInterfaceSubClass = UISUBCLASS_ETHERNET_NETWORKING_CONTROL_MODEL,
	.bInterfaceProtocol = 0,
	.iInterface = STRING_ETH_CONTROL_INDEX,
};

static const struct usb_temp_endpoint_desc *eth_data_endpoints[] = {
	&bulk_in_ep,
	&bulk_out_ep,
	NULL,
};

static const struct usb_temp_interface_desc eth_data_null_interface = {
	.ppEndpoints = NULL,		/* no endpoints */
	.bInterfaceClass = UICLASS_CDC_DATA,
	.bInterfaceSubClass = 0,
	.bInterfaceProtocol = 0,
	.iInterface = STRING_ETH_DATA_INDEX,
};

static const struct usb_temp_interface_desc eth_data_interface = {
	.ppEndpoints = eth_data_endpoints,
	.bInterfaceClass = UICLASS_CDC_DATA,
	.bInterfaceSubClass = UISUBCLASS_DATA,
	.bInterfaceProtocol = 0,
	.iInterface = STRING_ETH_DATA_INDEX,
	.isAltInterface = 1,		/* this is an alternate setting */
};

static const struct usb_temp_interface_desc *eth_interfaces[] = {
	&eth_control_interface,
	&eth_data_null_interface,
	&eth_data_interface,
	NULL,
};

static const struct usb_temp_config_desc eth_config_desc = {
	.ppIfaceDesc = eth_interfaces,
	.bmAttributes = UC_BUS_POWERED,
	.bMaxPower = 25,		/* 50 mA */
	.iConfiguration = STRING_ETH_CONFIG_INDEX,
};

static const struct usb_temp_config_desc *eth_configs[] = {
	&eth_config_desc,
	NULL,
};

const struct usb_temp_device_desc usb_template_cdce = {
	.getStringDesc = &eth_get_string_desc,
	.ppConfigDesc = eth_configs,
	.idVendor = USB_TEMPLATE_VENDOR,
	.idProduct = 0x0001,
	.bcdDevice = 0x0100,
	.bDeviceClass = UDCLASS_COMM,
	.bDeviceSubClass = 0,
	.bDeviceProtocol = 0,
	.iManufacturer = STRING_ETH_VENDOR_INDEX,
	.iProduct = STRING_ETH_PRODUCT_INDEX,
	.iSerialNumber = STRING_ETH_SERIAL_INDEX,
};

/*------------------------------------------------------------------------*
 *	eth_get_string_desc
 *
 * Return values:
 * NULL: Failure. No such string.
 * Else: Success. Pointer to string descriptor is returned.
 *------------------------------------------------------------------------*/
static const void *
eth_get_string_desc(uint16_t lang_id, uint8_t string_index)
{
	static const void *ptr[STRING_ETH_MAX] = {
		[STRING_LANG_INDEX] = &string_lang,
		[STRING_MAC_INDEX] = &string_mac,
		[STRING_ETH_CONTROL_INDEX] = &string_eth_control,
		[STRING_ETH_DATA_INDEX] = &string_eth_data,
		[STRING_ETH_CONFIG_INDEX] = &string_eth_config,
		[STRING_ETH_VENDOR_INDEX] = &string_eth_vendor,
		[STRING_ETH_PRODUCT_INDEX] = &string_eth_product,
		[STRING_ETH_SERIAL_INDEX] = &string_eth_serial,
	};

	if (string_index == 0) {
		return (&string_lang);
	}
	if (lang_id != 0x0409) {
		return (NULL);
	}
	if (string_index < STRING_ETH_MAX) {
		return (ptr[string_index]);
	}
	return (NULL);
}
