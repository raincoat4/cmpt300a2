CC=gcc
CFLAGS = -o

s-talk:
	${CC} -c chatserver2.c list.c
	${CC} -o run -pthread chatserver2.o list.o
.PHONY:s-talk
clean:
	rm s-talk *.o run