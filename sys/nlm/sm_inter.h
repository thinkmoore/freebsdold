/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */
/* $FreeBSD: stable/9/sys/nlm/sm_inter.h 177633 2008-03-26 15:23:12Z dfr $ */

#ifndef _SM_INTER_H_RPCGEN
#define	_SM_INTER_H_RPCGEN

#include <rpc/rpc.h>

#ifdef __cplusplus
extern "C" {
#endif

#define	SM_MAXSTRLEN 1024

struct sm_name {
	char *mon_name;
};
typedef struct sm_name sm_name;

struct my_id {
	char *my_name;
	int my_prog;
	int my_vers;
	int my_proc;
};
typedef struct my_id my_id;

struct mon_id {
	char *mon_name;
	struct my_id my_id;
};
typedef struct mon_id mon_id;

struct mon {
	struct mon_id mon_id;
	char priv[16];
};
typedef struct mon mon;

struct stat_chge {
	char *mon_name;
	int state;
};
typedef struct stat_chge stat_chge;

struct sm_stat {
	int state;
};
typedef struct sm_stat sm_stat;

enum sm_res {
	stat_succ = 0,
	stat_fail = 1
};
typedef enum sm_res sm_res;

struct sm_stat_res {
	sm_res res_stat;
	int state;
};
typedef struct sm_stat_res sm_stat_res;

struct sm_status {
	char *mon_name;
	int state;
	char priv[16];
};
typedef struct sm_status sm_status;

#define	SM_PROG ((unsigned long)(100024))
#define	SM_VERS ((unsigned long)(1))

extern  void sm_prog_1(struct svc_req *rqstp, SVCXPRT *transp);
#define	SM_STAT ((unsigned long)(1))
extern  struct sm_stat_res * sm_stat_1(struct sm_name *, CLIENT *);
extern  struct sm_stat_res * sm_stat_1_svc(struct sm_name *, struct svc_req *);
#define	SM_MON ((unsigned long)(2))
extern  struct sm_stat_res * sm_mon_1(struct mon *, CLIENT *);
extern  struct sm_stat_res * sm_mon_1_svc(struct mon *, struct svc_req *);
#define	SM_UNMON ((unsigned long)(3))
extern  struct sm_stat * sm_unmon_1(struct mon_id *, CLIENT *);
extern  struct sm_stat * sm_unmon_1_svc(struct mon_id *, struct svc_req *);
#define	SM_UNMON_ALL ((unsigned long)(4))
extern  struct sm_stat * sm_unmon_all_1(struct my_id *, CLIENT *);
extern  struct sm_stat * sm_unmon_all_1_svc(struct my_id *, struct svc_req *);
#define	SM_SIMU_CRASH ((unsigned long)(5))
extern  void * sm_simu_crash_1(void *, CLIENT *);
extern  void * sm_simu_crash_1_svc(void *, struct svc_req *);
#define	SM_NOTIFY ((unsigned long)(6))
extern  void * sm_notify_1(struct stat_chge *, CLIENT *);
extern  void * sm_notify_1_svc(struct stat_chge *, struct svc_req *);
extern int sm_prog_1_freeresult(SVCXPRT *, xdrproc_t, caddr_t);

/* the xdr functions */
extern  bool_t xdr_sm_name(XDR *, sm_name*);
extern  bool_t xdr_my_id(XDR *, my_id*);
extern  bool_t xdr_mon_id(XDR *, mon_id*);
extern  bool_t xdr_mon(XDR *, mon*);
extern  bool_t xdr_stat_chge(XDR *, stat_chge*);
extern  bool_t xdr_sm_stat(XDR *, sm_stat*);
extern  bool_t xdr_sm_res(XDR *, sm_res*);
extern  bool_t xdr_sm_stat_res(XDR *, sm_stat_res*);
extern  bool_t xdr_sm_status(XDR *, sm_status*);

#ifdef __cplusplus
}
#endif

#endif /* !_SM_INTER_H_RPCGEN */
