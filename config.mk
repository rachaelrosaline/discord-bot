LIBS = -lssl -lcrypto

CPPFLAGS =
LDFLAGS = -O2 ${LIBS}

CFLAGS = ${CPPFLAGS} ${LDFLAGS}

CC = cc
