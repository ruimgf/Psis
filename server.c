#include "psiskv.h"
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

item * begin ;

void intHandler(int dumbi){
  print_list(begin);
  close(sock_fd);
  exit(0);
}

int op_read(int new_fd, uint32_t key){

  item * aux;
  message m;
  char * buf;

  #ifdef DEBUG
    printf("key read : %u \n",key);
  #endif

  aux = search_key_on_list(begin, key);
  buf  = (char * )malloc(sizeof(char)*strlen(aux->value)+1);
  sprintf(buf,"%s",aux->value);
  m.value_length = strlen(buf) + 1;

  if(send(new_fd,&m, sizeof(m),0)==-1){
    return -1;
  }

  if(send(new_fd,buf, sizeof(buf),0)==-1){
    return -1;
  }
  free(buf);

}

int op_write(int new_fd, message m){
  char buf[100]; // tem de ser alterado isto é so para compilar

  #ifdef DEBUG
    printf("WRITE\n");
  #endif

  recv(new_fd,buf,m.value_length, 0);
  begin = insert_begin_list(begin, m.key,buf);

  #ifdef DEBUG
    printf("%s",buf);
  #endif

  return 0;
}

int op_delete(message m){

  delete_entry(&begin,m.key);
  //printf("delete : %u\n",m.key);
  return 0;
}

void * thread(void * fd){

  int new_fd = *((int*)(fd));
  char buf[100];

  message m;

  int naosair = 1;
  while (naosair) {

      recv(new_fd,(void *)&m, sizeof(m), 0);

      switch (m.operation) {
        case READ:
          op_read(new_fd, m.key);
          break;
        case WRITE:
          op_write(new_fd,m);
          break;
        case DELETE:
          op_delete(m);
          break;
        case EXIT :
          naosair = 0;
          #ifdef DEBUG
          printf("client exit\n");
          #endif
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

	server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  int port = 9999;
  int err = -1;

  // bind server
  while(1){
    server_addr.sin_port = htons(port);
    err = bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if(err != -1) { //bind sucess
      printf("bind on port %d \n",port);
      break;
    }
    port++;
  }

  #ifdef DEBUG
    printf(" socket created and binded \n Ready to receive messages\n");
    printf("sucess \n");
  #endif

  listen(sock_fd, MAX_CLIENT_WAIT);
  pthread_t client;
  struct sockaddr_in client_addr;
  socklen_t size_addr;

  begin = creat_list();
  int new_fd;
  while(1){
    new_fd = accept(sock_fd,(struct sockaddr *)&client_addr, &size_addr);

    if(new_fd == -1){
      exit(-1);
    }

    pthread_create(&client,NULL,thread,(void*)&new_fd);

    #ifdef DEBUG
    printf("accept\n");
    #endif

  }

//  intHandler(0);
  return 0;

}
