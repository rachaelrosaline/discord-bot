#include <limits.h>
#include <stdio.h>

#include <openssl/err.h>
#include <openssl/rand.h>

#include "ssl.c"

int main() {
    char s[4096];
    long long i = 0;
    FILE *f = fopen(FILENAME, "r");
    while(fgets(s, 4096, f))
        i ++;

    fclose(f);

    long long randmax = LLONG_MAX - (LLONG_MAX - i + 1) % i;
    long long n = 0;
    int bytes = sizeof(long long);
    unsigned char buf[bytes];
    while(n == 0 || n > randmax) {
        RAND_bytes(buf, bytes);
        unsigned long e = ERR_get_error();
        if(e) {
            fprintf(
                stderr, "RAND_bytes: %s\n", ERR_reason_error_string(e)
            );
            return((int) e);
        }
        n = buf[0];
        for(int byte = 1; byte < bytes; byte ++) {
            int factor = 256;
            for(int p = 2; p <= byte; p ++)
                factor *= factor;

            n += factor * buf[byte];
        }
    }
    f = fopen("crimes.txt", "r");
    for(int line = 0; line < n % i + 1; line ++)
        fgets(s, 4096, f);

    fclose(f);

    BIO *o = BIO_new_fp(stdout, BIO_NOCLOSE);
    SSL_CTX *c;
    if((c = SSL_CTX_new(TLS_client_method())) == NULL) {
        BIO_printf(o, "SSL_CTX_new error\n");
        return 1;
    }

    ssl(o, c, s);

    SSL_CTX_free(c);
}
