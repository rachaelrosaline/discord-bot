#include <stdio.h>
#include <string.h>

#include "config.h"

char *post(char *t) {
    char p[4096];
    snprintf(
        p, 4096,
        "%s%s%s%s%s%s\r\n%s%s%s%s%lu\r\n\r\n%s%s\r\n\r\n",
        "POST /api/v10/channels/", CHANNEL, "/messages HTTP/1.1\r\n",
        "Host: discord.com\r\n",
        "Authorization: Bot ", KEY,
        "User-Agent: DiscordBot (",
        "https://github.com/rosalinesystems/idkbot, 0.0)\r\n",
        "Content-Type: application/x-www-form-urlencoded\r\n",
        "Content-Length: ", strnlen(t, 2000) + 8,
        "content=", t
    );
    char *ptr = p;
    return ptr;
}
