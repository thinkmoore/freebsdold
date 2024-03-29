/*
 * hid.c
 */

/*-
 * Copyright (c) 2006 Maksim Yevmenkin <m_evmenkin@yahoo.com>
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
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $Id: hid.c,v 1.5 2006/09/07 21:06:53 max Exp $
 * $FreeBSD: stable/9/usr.sbin/bluetooth/bthidd/hid.c 221448 2011-05-04 17:58:15Z emax $
 */

#include <sys/consio.h>
#include <sys/mouse.h>
#include <sys/queue.h>
#include <assert.h>
#include <bluetooth.h>
#include <dev/usb/usb.h>
#include <dev/usb/usbhid.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <syslog.h>
#include <unistd.h>
#include <usbhid.h>
#include "bthid_config.h"
#include "bthidd.h"
#include "kbd.h"

#undef	min
#define	min(x, y)	(((x) < (y))? (x) : (y))

#undef	ASIZE
#define	ASIZE(a)	(sizeof(a)/sizeof(a[0]))

/*
 * Process data from control channel
 */

int32_t
hid_control(bthid_session_p s, uint8_t *data, int32_t len)
{
	assert(s != NULL);
	assert(data != NULL);
	assert(len > 0);

	switch (data[0] >> 4) {
        case 0: /* Handshake (response to command) */
		if (data[0] & 0xf)
			syslog(LOG_ERR, "Got handshake message with error " \
				"response 0x%x from %s",
				data[0], bt_ntoa(&s->bdaddr, NULL));
		break;

	case 1: /* HID Control */
		switch (data[0] & 0xf) {
		case 0: /* NOP */
			break;

		case 1: /* Hard reset */
		case 2: /* Soft reset */
			syslog(LOG_WARNING, "Device %s requested %s reset",
				bt_ntoa(&s->bdaddr, NULL),
				((data[0] & 0xf) == 1)? "hard" : "soft");
			break;

		case 3: /* Suspend */
			syslog(LOG_NOTICE, "Device %s requested Suspend",
				bt_ntoa(&s->bdaddr, NULL));
			break;

		case 4: /* Exit suspend */
			syslog(LOG_NOTICE, "Device %s requested Exit Suspend",
				bt_ntoa(&s->bdaddr, NULL));
			break;

		case 5: /* Virtual cable unplug */
			syslog(LOG_NOTICE, "Device %s unplugged virtual cable",
				bt_ntoa(&s->bdaddr, NULL));
			session_close(s);
			break;

		default:
			syslog(LOG_WARNING, "Device %s sent unknown " \
                                "HID_Control message 0x%x",
				bt_ntoa(&s->bdaddr, NULL), data[0]);
			break;
		}
		break;

	default:
		syslog(LOG_WARNING, "Got unexpected message 0x%x on Control " \
			"channel from %s", data[0], bt_ntoa(&s->bdaddr, NULL));
		break;
	}

	return (0);
}

/*
 * Process data from the interrupt channel
 */

int32_t
hid_interrupt(bthid_session_p s, uint8_t *data, int32_t len)
{
	hid_device_p	hid_device;
	hid_data_t	d;
	hid_item_t	h;
	int32_t		report_id, usage, page, val,
			mouse_x, mouse_y, mouse_z, mouse_butt,
			mevents, kevents, i;

	assert(s != NULL);
	assert(s->srv != NULL);
	assert(data != NULL);

	if (len < 3) {
		syslog(LOG_ERR, "Got short message (%d bytes) on Interrupt " \
			"channel from %s", len, bt_ntoa(&s->bdaddr, NULL));
		return (-1);
	}

	if (data[0] != 0xa1) {
		syslog(LOG_ERR, "Got unexpected message 0x%x on " \
			"Interrupt channel from %s",
			data[0], bt_ntoa(&s->bdaddr, NULL));
		return (-1);
	}

	report_id = data[1];
	data ++;
	len --;

	hid_device = get_hid_device(&s->bdaddr);
	assert(hid_device != NULL);

	mouse_x = mouse_y = mouse_z = mouse_butt = mevents = kevents = 0;

	for (d = hid_start_parse(hid_device->desc, 1 << hid_input, -1);
	     hid_get_item(d, &h) > 0; ) {
		if ((h.flags & HIO_CONST) || (h.report_ID != report_id) ||
		    (h.kind != hid_input))
			continue;

		page = HID_PAGE(h.usage);
		usage = HID_USAGE(h.usage);
		val = hid_get_data(data, &h);

		switch (page) {
		case HUP_GENERIC_DESKTOP:
			switch (usage) {
			case HUG_X:
				mouse_x = val;
				mevents ++;
				break;

			case HUG_Y:
				mouse_y = val;
				mevents ++;
				break;

			case HUG_WHEEL:
				mouse_z = -val;
				mevents ++;
				break;

			case HUG_SYSTEM_SLEEP:
				if (val)
					syslog(LOG_NOTICE, "Sleep button pressed");
				break;
			}
			break;

		case HUP_KEYBOARD:
			kevents ++;

			if (h.flags & HIO_VARIABLE) {
				if (val && usage < kbd_maxkey())
					bit_set(s->keys1, usage);
			} else {
				if (val && val < kbd_maxkey())
					bit_set(s->keys1, val);

				for (i = 1; i < h.report_count; i++) {
					h.pos += h.report_size;
					val = hid_get_data(data, &h);
					if (val && val < kbd_maxkey())
						bit_set(s->keys1, val);
				}
			}
			break;

		case HUP_BUTTON:
			if (usage != 0) {
				if (usage == 2)
					usage = 3;
				else if (usage == 3)
					usage = 2;
				
				mouse_butt |= (val << (usage - 1));
				mevents ++;
			}
			break;

		case HUP_CONSUMER:
			if (!val)
				break;

			switch (usage) {
			case HUC_AC_PAN:
				/* Horizontal scroll */
				if (val < 0)
					mouse_butt |= (1 << 5);
				else
					mouse_butt |= (1 << 6);

				mevents ++;
				val = 0;
				break;

			case 0xb5: /* Scan Next Track */
				val = 0x19;
				break;

			case 0xb6: /* Scan Previous Track */
				val = 0x10;
				break;

			case 0xb7: /* Stop */
				val = 0x24;
				break;

			case 0xcd: /* Play/Pause */
				val = 0x22;
				break;

			case 0xe2: /* Mute */
				val = 0x20;
				break;

			case 0xe9: /* Volume Up */
				val = 0x30;
				break;

			case 0xea: /* Volume Down */
				val = 0x2E;
				break;

			case 0x183: /* Media Select */
				val = 0x6D;
				break;

			case 0x018a: /* Mail */
				val = 0x6C;
				break;

			case 0x192: /* Calculator */
				val = 0x21;
				break;

			case 0x194: /* My Computer */
				val = 0x6B;
				break;

			case 0x221: /* WWW Search */
				val = 0x65;
				break;

			case 0x223: /* WWW Home */
				val = 0x32;
				break;

			case 0x224: /* WWW Back */
				val = 0x6A;
				break;

			case 0x225: /* WWW Forward */
				val = 0x69;
				break;

			case 0x226: /* WWW Stop */
				val = 0x68;
				break;

			case 0x227: /* WWW Refresh */
				val = 0x67;
				break;

			case 0x22a: /* WWW Favorites */
				val = 0x66;
				break;

			default:
				val = 0;
				break;
			}

			/* XXX FIXME - UGLY HACK */
			if (val != 0) {
				if (hid_device->keyboard) {
					int32_t	buf[4] = { 0xe0, val,
							   0xe0, val|0x80 };

					assert(s->vkbd != -1);
					write(s->vkbd, buf, sizeof(buf));
				} else
					syslog(LOG_ERR, "Keyboard events " \
						"received from non-keyboard " \
						"device %s. Please report",
						bt_ntoa(&s->bdaddr, NULL));
			}
			break;

		case HUP_MICROSOFT:
			switch (usage) {
			case 0xfe01:
				if (!hid_device->battery_power)
					break;

				switch (val) {
				case 1:
					syslog(LOG_INFO, "Battery is OK on %s",
						bt_ntoa(&s->bdaddr, NULL));
					break;

				case 2:
					syslog(LOG_NOTICE, "Low battery on %s",
						bt_ntoa(&s->bdaddr, NULL));
					break;

				case 3:
					syslog(LOG_WARNING, "Very low battery "\
                                                "on %s",
						bt_ntoa(&s->bdaddr, NULL));
					break;
                                }
				break;
			}
			break;
		}
	}
	hid_end_parse(d);

	/*
	 * XXX FIXME Feed keyboard events into kernel.
	 * The code below works, bit host also needs to track
	 * and handle repeat.
	 *
	 * Key repeat currently works in X, but not in console.
	 */

	if (kevents > 0) {
		if (hid_device->keyboard) {
			assert(s->vkbd != -1);
			kbd_process_keys(s);
		} else
			syslog(LOG_ERR, "Keyboard events received from " \
				"non-keyboard device %s. Please report",
				bt_ntoa(&s->bdaddr, NULL));
	}

	/* 
	 * XXX FIXME Feed mouse events into kernel.
	 * The code block below works, but it is not good enough.
	 * Need to track double-clicks etc.
	 *
	 * Double click currently works in X, but not in console.
	 */

	if (mevents > 0) {
		struct mouse_info	mi;

		mi.operation = MOUSE_ACTION;
		mi.u.data.x = mouse_x;
		mi.u.data.y = mouse_y;
		mi.u.data.z = mouse_z;
		mi.u.data.buttons = mouse_butt;

		if (ioctl(s->srv->cons, CONS_MOUSECTL, &mi) < 0)
			syslog(LOG_ERR, "Could not process mouse events from " \
				"%s. %s (%d)", bt_ntoa(&s->bdaddr, NULL),
				strerror(errno), errno);
	}

	return (0);
}
