all: data_server front_server client client_prof1 client_prof2



psiskv.o: psiskv.c psiskv.h
	gcc -c psiskv.c -g -o obj/psiskv.o

ht.o: ht.c ht.h
	gcc -c ht.c -g -o obj/ht.o

data_server.o: data_server.c ht.h psiskv.h
	gcc -c data_server.c -g -o obj/data_server.o

front_server.o: front_server.c psiskv.h
	gcc -c front_server.c -g -o obj/front_server.o

client.o: client.c psiskv.h
	gcc -c client.c -o obj/client.o


client_prof1.o: cli-exe-1.c psiskv.h
	gcc -c -g cli-exe-1.c -o obj/client_prof1.o

client_prof2.o: cli-exe-par-1.c psiskv.h
	gcc -c -g cli-exe-par-1.c -o obj/client_prof2.o



front_server: front_server.o
	gcc obj/front_server.o -pthread -o bin/front_server

data_server: data_server.o ht.o
	gcc obj/data_server.o obj/ht.o -g -pthread -o bin/data_server

client: client.o psiskv.o
	gcc obj/client.o obj/psiskv.o -o bin/client

client_prof1: client_prof1.o
	gcc -g obj/client_prof1.o obj/psiskv.o -o bin/cp1

client_prof2: client_prof2.o
	gcc  -g obj/client_prof2.o obj/psiskv.o -o bin/cp2


clean:
	rm -f obj/* bin/* backup.txt backup.log
