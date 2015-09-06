
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#ifndef _NGX_TEST_H_INCLUDED_
#define _NGX_TEST_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_event.h>
#include <ngx_event_connect.h>

typedef struct {
	void **main_conf;
	void **srv_conf;
} ngx_test_conf_ctx_t;

typedef struct {
	u_char sockaddr[NGX_SOCKADDRLEN];
	socklen_t socklen;
	
	ngx_test_conf_ctx_t *ctx;
	
	unsigned bind:1;
	unsigned wildcard:1;
	unsigned so_keepalive:2;
} ngx_test_listen_t;

#endif /* _NGX_MAIL_H_INCLUDED_ */
