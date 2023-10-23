CC=gcc
CLFAGS = -o

s-talk: 
	${CC} ${CFLAGS} s-talk chatserver.c

clean:
	rm s-talk