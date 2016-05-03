all: data_server front_server client

psiskv.o: psiskv.c psiskv.h
	gcc -c psiskv.c

list.o: list.c list.h
	gcc -c list.c

data_server.o: data_server.c list.h psiskv.h
	gcc -c data_server.c

client.o: client.c psiskv.h
	gcc -c client.c

front_server.o: front_server.c psiskv.h
	gcc -c front_server.c

front_server: front_server.o
	gcc front_server.o -o bin/front_server

data_server: data_server.o list.o
	gcc data_server.o list.o -pthread -o bin/data_server

client: client.o psiskv.o
	gcc client.o psiskv.o -o bin/client

clean:
	rm -f *.o bin/*
