#include <openssl/bio.h>
#include <openssl/ssl.h>

#include "config.h"

#include "post.c"

void bot(BIO *o, SSL *s, char *t) {
    if(SSL_connect(s) != 1) {
        BIO_printf(o, "SSL_connect failed\n");
        return;
    }
    char *p = post(t);
    SSL_write(s, p, strnlen(p, 4096));
    char r[8192];
    SSL_read(s, r, 8192);
    BIO_printf(o, "%s\n", r);
}
