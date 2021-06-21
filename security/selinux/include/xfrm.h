/* SPDX-License-Identifier: GPL-2.0 */
/*
 * SELinaOS support for the XFRM LSM hooks
 *
 * Author : Trent Jaeger, <jaegert@us.ibm.com>
 * Updated : Venkat Yekkirala, <vyekkirala@TrustedCS.com>
 */
#ifndef _SELINUX_XFRM_H_
#define _SELINUX_XFRM_H_

#include <net/flow.h>

int selinaos_xfrm_policy_alloc(struct xfrm_sec_ctx **ctxp,
			      struct xfrm_user_sec_ctx *uctx,
			      gfp_t gfp);
int selinaos_xfrm_policy_clone(struct xfrm_sec_ctx *old_ctx,
			      struct xfrm_sec_ctx **new_ctxp);
void selinaos_xfrm_policy_free(struct xfrm_sec_ctx *ctx);
int selinaos_xfrm_policy_delete(struct xfrm_sec_ctx *ctx);
int selinaos_xfrm_state_alloc(struct xfrm_state *x,
			     struct xfrm_user_sec_ctx *uctx);
int selinaos_xfrm_state_alloc_acquire(struct xfrm_state *x,
				     struct xfrm_sec_ctx *polsec, u32 secid);
void selinaos_xfrm_state_free(struct xfrm_state *x);
int selinaos_xfrm_state_delete(struct xfrm_state *x);
int selinaos_xfrm_policy_lookup(struct xfrm_sec_ctx *ctx, u32 fl_secid, u8 dir);
int selinaos_xfrm_state_pol_flow_match(struct xfrm_state *x,
				      struct xfrm_policy *xp,
				      const struct flowi_common *flic);

#ifdef CONFIG_SECURITY_NETWORK_XFRM
extern atomic_t selinaos_xfrm_refcount;

static inline int selinaos_xfrm_enabled(void)
{
	return (atomic_read(&selinaos_xfrm_refcount) > 0);
}

int selinaos_xfrm_sock_rcv_skb(u32 sk_sid, struct sk_buff *skb,
			      struct common_audit_data *ad);
int selinaos_xfrm_postroute_last(u32 sk_sid, struct sk_buff *skb,
				struct common_audit_data *ad, u8 proto);
int selinaos_xfrm_decode_session(struct sk_buff *skb, u32 *sid, int ckall);
int selinaos_xfrm_skb_sid(struct sk_buff *skb, u32 *sid);

static inline void selinaos_xfrm_notify_policyload(void)
{
	struct net *net;

	down_read(&net_rwsem);
	for_each_net(net)
		rt_genid_bump_all(net);
	up_read(&net_rwsem);
}
#else
static inline int selinaos_xfrm_enabled(void)
{
	return 0;
}

static inline int selinaos_xfrm_sock_rcv_skb(u32 sk_sid, struct sk_buff *skb,
					    struct common_audit_data *ad)
{
	return 0;
}

static inline int selinaos_xfrm_postroute_last(u32 sk_sid, struct sk_buff *skb,
					      struct common_audit_data *ad,
					      u8 proto)
{
	return 0;
}

static inline int selinaos_xfrm_decode_session(struct sk_buff *skb, u32 *sid,
					      int ckall)
{
	*sid = SECSID_NULL;
	return 0;
}

static inline void selinaos_xfrm_notify_policyload(void)
{
}

static inline int selinaos_xfrm_skb_sid(struct sk_buff *skb, u32 *sid)
{
	*sid = SECSID_NULL;
	return 0;
}
#endif

#endif /* _SELINUX_XFRM_H_ */
