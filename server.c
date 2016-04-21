#include "kv.h"

#include <pthread.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/un.h>
#include <signal.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_THREADS 20


int sock_fd;

void intHandler(int dumbi){

  close(sock_fd);
  exit(0);
}

int n_thread_ocupate=0;

int n_thread=0;

void * thread(void * fd){
  int socket_fd = *((int*)(fd));
  socklen_t size_addr;
  pthread_t client;
  char buf[100];
  struct sockaddr_in client_addr;
  message m;

  int new_fd = accept(sock_fd,(struct sockaddr *)&client_addr, &size_addr);
  if(new_fd == -1)
    exit(-1);

  n_thread_ocupate++;
  if (n_thread_ocupate>=MAX_THREADS) {
    n_thread++;
    pthread_create(&client,NULL,thread,(void*)fd);
  }



  recv(new_fd,(void *)&m, sizeof(m), 0);

  switch (m.operation) {
    case READ:
      printf("read : %u\n",m.key);
      sprintf(buf,"100");
      send(new_fd,buf, m.value_length,0);
      break;
    case WRITE:
      recv(new_fd,buf,m.value_length, 0);
      printf("%s",buf);
      break;
    case DELETE:
      printf("delete : %u\n",m.key);
      break;

    default:
      break;
  }
  if (n_thread>=MAX_THREADS) {
      n_thread--;
      n_thread_ocupate--;
      //pthread_exit();

  }

}


int main(){


  struct sockaddr_in server_addr;



  signal(SIGINT, intHandler);

  sock_fd = socket(AF_INET, SOCK_STREAM, 0);

	if (sock_fd == -1){
		printf("socket: error\n");
		exit(-1);
	}


	server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  int port = 9999;
  int err = -1;
  while(1){
    server_addr.sin_port = htons(port);
    err= bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if(err != -1) { //bind sucess
      printf("bind on port %d \n",port);
      break;
    }
    port++;
  }

  printf(" socket created and binded \n Ready to receive messages\n");

  listen(sock_fd, MAX_CLIENT_WAIT);
  int i;
  pthread_t clients[MAX_THREADS];

  for(i=0; i < MAX_THREADS;i++){
    pthread_create(&clients[i],NULL,thread,(void*)&sock_fd);

  }



  while(1){

  }

//  intHandler(0);
  return 0;

}
