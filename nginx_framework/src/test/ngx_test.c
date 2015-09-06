#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_event.h>

static char *ngx_test_block(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);

static ngx_command_t ngx_test_commands[] = {
	{ngx_string("test"),
	NGX_MAIN_CONF | NGX_CONF_BLOCK | NGX_CONF_NOARGS ,
	ngx_test_block,
	0,
	0,
	NULL},
	ngx_null_command	
};

static ngx_core_module_t ngx_test_module_ctx = {
	ngx_string("test"),
	NULL,
	NULL,
};

ngx_module_t ngx_test_module = {
	NGX_MODULE_V1,
	&ngx_test_module_ctx,
	ngx_test_commands,
	NGX_CORE_MODULE,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NGX_MODULE_V1_PADDING
};

static void ngx_test_init_connection(ngx_connection_t *c)
{
	ngx_pool_t *pool;
	pool = c->pool;
	/*close connection for test*/
	ngx_close_connection(c);
	ngx_destroy_pool(pool);
}

static char *ngx_test_block(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
	char *rv;
	//ngx_uint_t i, m, mi, s;
	//ngx_conf_t pcf;
	//ngx_array_t ports;
	ngx_listening_t *ls;

	rv = ngx_conf_parse(cf, NULL);
	if (rv != NGX_CONF_OK) {
		return rv;
	}
	struct sockaddr addr;
	struct sockaddr_in *p_addr = (struct sockaddr_in *)&addr;
	p_addr->sin_family = AF_INET;
	p_addr->sin_addr.s_addr = htonl(INADDR_ANY);
	p_addr->sin_port = htons(9999);

	socklen_t socklen = sizeof(struct sockaddr_in);

	ls = ngx_create_listening(cf, p_addr, socklen);
	if (ls == NULL) {
		return NGX_CONF_ERROR;
	}

	ls->addr_ntop = 1;
	ls->handler = ngx_test_init_connection;
	ls->pool_size = 512;
	
	ls->logp = &cf->cycle->new_log;
	ls->log.data = &ls->addr_text;
	ls->log.handler = ngx_accept_log_error;
	
	return NGX_CONF_OK;
}
