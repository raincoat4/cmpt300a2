CC=gcc

s-talk: 
	${CC} -o s-talk chatserver.c
	
clean:
	rm *.o