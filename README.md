# Psis
Project of course 'Programação de Sistemas - IST' 2015-2016

To Compile
1) sudo apt-get install cmake

2) cmake CMakeLists.txt

3) make


This to do

Change Write protocol
Change Read protocol
implement delete function lists
change write function list to key existen
implement critical region and mutex


to complile

gcc list.c -c -o list.o
gcc kv.c -c -kv.o
gcc server.c list.o -o bin/server
gcc client.c kv.o -o bin/client
