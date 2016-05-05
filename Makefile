all: data_server front_server client client_jorge client_prof1 client_prof2



psiskv.o: psiskv.c psiskv.h
	gcc -c psiskv.c -g -o obj/psiskv.o

list.o: list.c list.h
	gcc -c list.c -g -o obj/list.o

data_server.o: data_server.c list.h psiskv.h
	gcc -c data_server.c -g -o obj/data_server.o

front_server.o: front_server.c psiskv.h
	gcc -c front_server.c -g -o obj/front_server.o

client.o: client.c psiskv.h
	gcc -c client.c -o obj/client.o

client_jorge.o: cliente_jorge.c psiskv.h
	gcc -c cliente_jorge.c -o obj/client_jorge.o

client_prof1.o: cli-exe-1.c psiskv.h
	gcc -c -g cli-exe-1.c -o obj/client_prof1.o

client_prof2.o: cli-exe-par-1.c psiskv.h
	gcc -c -g cli-exe-par-1.c -o obj/client_prof2.o



front_server: front_server.o
	gcc obj/front_server.o -o bin/front_server

data_server: data_server.o list.o
	gcc obj/data_server.o obj/list.o -g -pthread -o bin/data_server

client: client.o psiskv.o
	gcc obj/client.o obj/psiskv.o -o bin/client

client_jorge: client_jorge.o
	gcc obj/client_jorge.o obj/psiskv.o -o bin/cj

client_prof1: client_prof1.o
	gcc -g obj/client_prof1.o obj/psiskv.o -o bin/cp1

client_prof2: client_prof2.o
	gcc  -g obj/client_prof2.o obj/psiskv.o -o bin/cp2


clean:
	rm -f obj/* bin/*
