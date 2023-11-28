#include <err.h>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>

#include <netinet/in.h>

#include <sys/socket.h>

#include "bot.c"

void ssl(BIO *o, SSL_CTX *c, char *t) {
    SSL *s = SSL_new(c);

    struct hostent *h = gethostbyname("discord.com");

    int f = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in n;
    n.sin_family = AF_INET;
    n.sin_port = htons(443);
    n.sin_addr.s_addr = *(long*)(h->h_addr);

    memset(&(n.sin_zero), '\0', 8);

    if(connect(
        f, (struct sockaddr *) &n, sizeof(struct sockaddr)
    ) == -1) {
        err(errno, "connect");
        SSL_free(s);
        return;
    }

    SSL_set_fd(s, f);

    bot(o, s, t);

    SSL_free(s);
    close(f);
}
