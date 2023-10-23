CC=gcc
CFLAGS = -o

s-talk:
	${CC} -c chatserver2.c
	${CC} -o s-talk -pthread chatserver2.o list.o
.PHONY:s-talk
clean:
	rm s-talk *.o