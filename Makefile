CFLAGS += -O3
LDFLAGS += -lbz2

PNAME = delta
PLIB = lib${PNAME}.so.0
SRCS = src/
MANS = man/
PREFIX ?= /usr/local
INSTALL = install
INSTALL_MAN ?= ${INSTALL} -c -m 444
RM = rm -f

all: ${PNAME}

${PLIB}: ${SRCS}delta.c
	${CC} -shared ${CFLAGS} -Wl,-soname,$@ -o $@ $^ ${LDFLAGS}

${PNAME}: ${SRCS}cli.c ${PLIB}
	${CC} ${CFLAGS} -o $@ $^

clean:
	${RM} ${PNAME} ${PLIB}

install:
	${INSTALL} -d ${PREFIX}/bin
	${INSTALL} -m 755 ${PNAME} ${PREFIX}/bin
	${INSTALL} -d ${PREFIX}/lib
	${INSTALL} -m 644 ${PLIB} ${PREFIX}/lib
	${INSTALL} -d ${PREFIX}/man/man1
	${INSTALL} -d ${PREFIX}/man/man3
	${INSTALL} -m 644 ${MANS}${PNAME}.1 ${PREFIX}/man/man1
	${INSTALL} -m 644 ${MANS}${PLIB}.3 ${PREFIX}/man/man3
