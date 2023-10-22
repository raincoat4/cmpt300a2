CC=gcc
CFLAGS = -w -o

make: chatserver.c
	${CC} $(CFLAGS) s-talk chatserver.c
	
s-talk: 
	./s-talk 

.PHONY: s-talk
clean:
	rm s-talk