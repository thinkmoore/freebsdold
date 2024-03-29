/*-
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <beat@chruetertee.ch> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.          Beat G�tzi
 * ----------------------------------------------------------------------------
 *
 * $FreeBSD: stable/9/usr.sbin/pkg_install/updating/pathnames.h 173514 2007-11-10 10:21:29Z krion $
 *
 */

/* Where the updating file lives by default */
#define DEF_UPDATING "/usr/ports/UPDATING"
/* macro to define location of the UPDATING file */
#define UPDATING (getenv(PORTSDIR) ? strcat(getenv(PORTSDIR), \
        "/UPDATING") : DEF_UPDATING)
