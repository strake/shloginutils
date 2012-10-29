CC ?= cc
LDFLAGS += -static

.SUFFIXES: .c .o
.PHONY: all clean

all:	login su

clean:
	rm -f login su *.o

login:	login.o util.o go.o auth.shadow.o
	${CC} ${LDFLAGS} -o $@ $^ -lcrypt

su:	su.o util.o go.o auth.shadow.o
	${CC} ${LDFLAGS} -o $@ $^ -lcrypt

%.o:	%.c
	${CC} ${CFLAGS} -o $@ -c $^