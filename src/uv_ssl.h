#ifndef _UV_SSL_H
#define _UV_SSL_H
#include <openssl/ssl.h>
#include "uv_tcp.h"

#define SSL_METHOD_SSLV2 0
#define SSL_METHOD_SSLV3 1
#define SSL_METHOD_SSLV23 2
#define SSL_METHOD_TLSV1 3
#define SSL_METHOD_TLSV1_1 4
#define SSL_METHOD_TLSV1_2 5

ZEND_BEGIN_ARG_INFO(ARGINFO(UVSSL, __construct), 0)
    ZEND_ARG_INFO(0, loop)
    ZEND_ARG_INFO(0, sslMethod)
    ZEND_ARG_INFO(0, nContexts)
ZEND_END_ARG_INFO()

static zend_object_value createUVSSLResource(zend_class_entry *class_type TSRMLS_DC);

void freeUVSSLResource(void *object TSRMLS_DC);

typedef struct uv_ssl_ext_s{
    uv_tcp_ext_t uv_tcp_ext;
    const SSL_METHOD *ssl_method;
    SSL_CTX** ctx;
    int nctx;
    SSL* ssl;
    BIO* read_bio;
    BIO* write_bio;
} uv_ssl_ext_t;

PHP_METHOD(UVSSL, __construct);

DECLARE_FUNCTION_ENTRY(UVSSL) = {
    PHP_ME(UVSSL, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
    PHP_FE_END
};
#endif
