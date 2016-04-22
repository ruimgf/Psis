#include "kv.h"
#include "list.h"

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



int n_thread_ocupate=0;

int n_thread=0;

item * begin , *aux;

void intHandler(int dumbi){
  print_list(begin);
  close(sock_fd);
  exit(0);
}

void * thread(void * fd){
  int new_fd = *((int*)(fd));

  pthread_t client;
  char buf[100];

  message m;

  int naosair = 1;
  while (naosair) {

      recv(new_fd,(void *)&m, sizeof(m), 0);

      switch (m.operation) {
        case READ:
          printf("key read : %u\n",m.key);
          aux = search_key_on_list(begin, m.key);
          sprintf(buf,"%s",aux->value);
          m.value_length = strlen(buf) + 1;
          send(new_fd,&m, sizeof(m),0);
          send(new_fd,buf, sizeof(buf),0);
          break;
        case WRITE:
          printf("WRITE\n");
          recv(new_fd,buf,m.value_length, 0);
          begin = insert_begin_list(begin, m.key,buf);
          printf("%s",buf);
          break;
        case DELETE:
          printf("delete : %u\n",m.key);
          break;
        case EXIT :
          naosair = 0;
          printf("client exit\n");
          break;
        default:
          break;
      }
  }
  close(new_fd);
  int ret=0;
  pthread_exit(&ret);
}


int main(){

  struct sockaddr_in server_addr;

  signal(SIGINT, intHandler);

  sock_fd = socket(AF_INET, SOCK_STREAM, 0);

	if (sock_fd == -1){
		printf("socket: error\n");
		exit(-1);
	}

  begin = creat_list();


	server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  int port = 9999;
  int err = -1;
  while(1){
    server_addr.sin_port = htons(port);
    err = bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if(err != -1) { //bind sucess
      printf("bind on port %d \n",port);
      break;
    }
    port++;
  }

  printf(" socket created and binded \n Ready to receive messages\n");

  listen(sock_fd, MAX_CLIENT_WAIT);
  printf("sucess \n");
  int i;
  pthread_t clients[MAX_THREADS];

  pthread_t client;
  struct sockaddr_in client_addr;
  socklen_t size_addr;
  int new_fd;
  while(1){
    new_fd = accept(sock_fd,(struct sockaddr *)&client_addr, &size_addr);
    if(new_fd == -1)
      exit(-1);
    pthread_create(&client,NULL,thread,(void*)&new_fd);

    printf("accept\n");

  }

//  intHandler(0);
  return 0;

}
