.include "config.mk"

SRC = config.h bot.c main.c post.c ssl.c

all: bot

bot: ${SRC}
	${CC} ${CFLAGS} main.c -o $@

clean:
	rm bot
