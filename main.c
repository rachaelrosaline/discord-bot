#include <stdio.h>

#include "ssl.c"

int main(int argc, char *argv[]) {
    BIO *o = BIO_new_fp(stdout, BIO_NOCLOSE);
    SSL_CTX *c;
    if((c = SSL_CTX_new(TLS_client_method())) == NULL) {
        BIO_printf(o, "SSL_CTX_new error\n");
        return 1;
    }

    ssl(o, c, argv[1]);

    SSL_CTX_free(c);
}
