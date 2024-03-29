/*
 * Copyright (c) 2010-2011 Qlogic Corporation
 * All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 * $FreeBSD: stable/9/sys/dev/qlxgb/qla_ioctl.h 227064 2011-11-03 21:20:22Z bz $
 */
/*
 * File: qla_ioctl.h
 * Author : David C Somayajulu, Qlogic Corporation, Aliso Viejo, CA 92656.
 */

#ifndef _QLA_IOCTL_H_
#define _QLA_IOCTL_H_

#include <sys/ioccom.h>

struct qla_reg_val {
        uint16_t rd;
        uint16_t direct;
        uint32_t reg;
        uint32_t val;
};
typedef struct qla_reg_val qla_reg_val_t;

struct qla_rd_flash {
        uint32_t off;
        uint32_t data;
};
typedef struct qla_rd_flash qla_rd_flash_t;


/*
 * Read/Write Register
 */
#define QLA_RDWR_REG                    _IOWR('q', 1, qla_reg_val_t)

/*
 * Read Flash
 */
#define QLA_RD_FLASH                    _IOWR('q', 2, qla_rd_flash_t)

#endif /* #ifndef _QLA_IOCTL_H_ */
