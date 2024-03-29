#!/bin/sh
#
# $FreeBSD: stable/9/tools/tools/bus_autoconf/bus_autoconf.sh 223535 2011-06-25 15:22:44Z hselasky $
#
# Copyright (c) 2011 Hans Petter Selasky. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.
#

OS=FreeBSD
DOLLAR=$
OBJCOPY=objcopy

cat <<EOF
#
# ${DOLLAR}${OS}${DOLLAR}
#
# This file was automatically generated by "tools/bus_autoconf.sh".
# Please do not edit!
#

EOF

rm -f bus_autoconf_format.bin
rm -f bus_autoconf_args.txt
rm -f bus_autoconf.ids

for F in $*
do

G=$(basename ${F})

# Format information
${OBJCOPY} -j bus_autoconf_format -O binary ${F} bus_autoconf.ids 2> /dev/null
[ -f bus_autoconf.ids ] && cat bus_autoconf.ids >> bus_autoconf_format.bin

# USB Host mode
${OBJCOPY} -j usb_host_id -O binary ${F} "usb_host_id,${G}" 2> /dev/null
[ -f "usb_host_id,${G}" ] && (echo -n " -i usb_host_id,${G}" >> bus_autoconf_args.txt)

# USB Device mode
${OBJCOPY} -j usb_device_id -O binary ${F} "usb_device_id,${G}" 2> /dev/null
[ -f "usb_device_id,${G}" ] && (echo -n " -i usb_device_id,${G}" >> bus_autoconf_args.txt)

# USB Dual mode
${OBJCOPY} -j usb_dual_id -O binary ${F} "usb_dual_id,${G}" 2> /dev/null
[ -f "usb_dual_id,${G}" ] && (echo -n " -i usb_dual_id,${G}" >> bus_autoconf_args.txt)

done

# Dump all data
bus_autoconf -F bus_autoconf_format.bin $(cat bus_autoconf_args.txt)

# Cleanup
rm -f -- \
    $(cat bus_autoconf_args.txt) \
    bus_autoconf_args.txt \
    bus_autoconf_format.bin \
    bus_autoconf.ids
