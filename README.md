# Psis
Project of course 'Programação de Sistemas - IST' 2015-2016

To Compile
1) sudo apt-get install cmake

2) cmake CMakeLists.txt

3) make


This to do

1) implement critical region and mutex


to complile

1) gcc list.c -c -o list.o
2) gcc kv.c -c -o kv.o
3) gcc server.c list.o -o bin/server
4) gcc client.c kv.o -o bin/client
