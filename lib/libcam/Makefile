# $FreeBSD: stable/9/lib/libcam/Makefile 225227 2011-08-28 09:26:48Z kib $

LIB=		cam
SHLIBDIR?=	/lib
SRCS=		camlib.c scsi_cmdparse.c scsi_all.c scsi_da.c scsi_sa.c cam.c \
		ata_all.c smp_all.c
INCS=		camlib.h

DPADD=		${LIBSBUF}
LDADD=		-lsbuf

MAN=		cam.3 cam_cdbparse.3

WARNS?=		2

MLINKS+=	cam.3 cam_open_device.3 \
		cam.3 cam_open_spec_device.3 \
		cam.3 cam_open_btl.3 \
		cam.3 cam_open_pass.3 \
		cam.3 cam_close_device.3 \
		cam.3 cam_close_spec_device.3 \
		cam.3 cam_getccb.3 \
		cam.3 cam_send_ccb.3 \
		cam.3 cam_freeccb.3 \
		cam.3 cam_path_string.3 \
		cam.3 cam_device_dup.3 \
		cam.3 cam_device_copy.3 \
		cam.3 cam_get_device.3 \
		cam_cdbparse.3 csio_build.3 \
		cam_cdbparse.3 csio_build_visit.3 \
		cam_cdbparse.3 csio_decode.3 \
		cam_cdbparse.3 csio_decode_visit.3 \
		cam_cdbparse.3 buff_decode.3 \
		cam_cdbparse.3 buff_decode_visit.3 \
		cam_cdbparse.3 csio_encode.3 \
		cam_cdbparse.3 csio_encode_visit.3 \
		cam_cdbparse.3 buff_encode_visit.3

.PATH:		${.CURDIR}/../../sys/cam/scsi ${.CURDIR}/../../sys/cam/ata \
		${.CURDIR}/../../sys/cam

SDIR=		${.CURDIR}/../../sys
CFLAGS+=	-I${.CURDIR} -I${SDIR}

SHLIB_MAJOR=	6

.include <bsd.lib.mk>
