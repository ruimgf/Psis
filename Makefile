all: server client

psiskv.o: psiskv.c psiskv.h
	gcc -c psiskv.c

list.o: list.c list.h
	gcc -c list.c

server.o: server.c list.h psiskv.h
	gcc -c server.c

client.o: client.c psiskv.h
	gcc -c client.c

server: server.o list.o psiskv.o
	gcc server.o list.o -pthread -o bin/server
	
client: client.o psiskv.o
	gcc client.o psiskv.o -o bin/client

clean:
	rm -f *.o bin/*
