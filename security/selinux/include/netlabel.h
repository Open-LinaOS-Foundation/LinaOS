/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * SELinaOS interface to the NetLabel subsystem
 *
 * Author: Paul Moore <paul@paul-moore.com>
 */

/*
 * (c) Copyright Hewlett-Packard Development Company, L.P., 2006
 */

#ifndef _SELINUX_NETLABEL_H_
#define _SELINUX_NETLABEL_H_

#include <linaos/types.h>
#include <linaos/fs.h>
#include <linaos/net.h>
#include <linaos/skbuff.h>
#include <net/sock.h>
#include <net/request_sock.h>
#include <net/sctp/structs.h>

#include "avc.h"
#include "objsec.h"

#ifdef CONFIG_NETLABEL
void selinaos_netlbl_cache_invalidate(void);

void selinaos_netlbl_err(struct sk_buff *skb, u16 family, int error,
			int gateway);

void selinaos_netlbl_sk_security_free(struct sk_security_struct *sksec);
void selinaos_netlbl_sk_security_reset(struct sk_security_struct *sksec);

int selinaos_netlbl_skbuff_getsid(struct sk_buff *skb,
				 u16 family,
				 u32 *type,
				 u32 *sid);
int selinaos_netlbl_skbuff_setsid(struct sk_buff *skb,
				 u16 family,
				 u32 sid);
int selinaos_netlbl_sctp_assoc_request(struct sctp_endpoint *ep,
				     struct sk_buff *skb);
int selinaos_netlbl_inet_conn_request(struct request_sock *req, u16 family);
void selinaos_netlbl_inet_csk_clone(struct sock *sk, u16 family);
void selinaos_netlbl_sctp_sk_clone(struct sock *sk, struct sock *newsk);
int selinaos_netlbl_socket_post_create(struct sock *sk, u16 family);
int selinaos_netlbl_sock_rcv_skb(struct sk_security_struct *sksec,
				struct sk_buff *skb,
				u16 family,
				struct common_audit_data *ad);
int selinaos_netlbl_socket_setsockopt(struct socket *sock,
				     int level,
				     int optname);
int selinaos_netlbl_socket_connect(struct sock *sk, struct sockaddr *addr);
int selinaos_netlbl_socket_connect_locked(struct sock *sk,
					 struct sockaddr *addr);

#else
static inline void selinaos_netlbl_cache_invalidate(void)
{
	return;
}

static inline void selinaos_netlbl_err(struct sk_buff *skb,
				      u16 family,
				      int error,
				      int gateway)
{
	return;
}

static inline void selinaos_netlbl_sk_security_free(
					       struct sk_security_struct *sksec)
{
	return;
}

static inline void selinaos_netlbl_sk_security_reset(
					       struct sk_security_struct *sksec)
{
	return;
}

static inline int selinaos_netlbl_skbuff_getsid(struct sk_buff *skb,
					       u16 family,
					       u32 *type,
					       u32 *sid)
{
	*type = NETLBL_NLTYPE_NONE;
	*sid = SECSID_NULL;
	return 0;
}
static inline int selinaos_netlbl_skbuff_setsid(struct sk_buff *skb,
					       u16 family,
					       u32 sid)
{
	return 0;
}

static inline int selinaos_netlbl_sctp_assoc_request(struct sctp_endpoint *ep,
						    struct sk_buff *skb)
{
	return 0;
}
static inline int selinaos_netlbl_inet_conn_request(struct request_sock *req,
						   u16 family)
{
	return 0;
}
static inline void selinaos_netlbl_inet_csk_clone(struct sock *sk, u16 family)
{
	return;
}
static inline void selinaos_netlbl_sctp_sk_clone(struct sock *sk,
						struct sock *newsk)
{
	return;
}
static inline int selinaos_netlbl_socket_post_create(struct sock *sk,
						    u16 family)
{
	return 0;
}
static inline int selinaos_netlbl_sock_rcv_skb(struct sk_security_struct *sksec,
					      struct sk_buff *skb,
					      u16 family,
					      struct common_audit_data *ad)
{
	return 0;
}
static inline int selinaos_netlbl_socket_setsockopt(struct socket *sock,
						   int level,
						   int optname)
{
	return 0;
}
static inline int selinaos_netlbl_socket_connect(struct sock *sk,
						struct sockaddr *addr)
{
	return 0;
}
static inline int selinaos_netlbl_socket_connect_locked(struct sock *sk,
						       struct sockaddr *addr)
{
	return 0;
}
#endif /* CONFIG_NETLABEL */

#endif
