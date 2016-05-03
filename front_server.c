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

void intHandler(int dumbi){
  //print_list(begin);
  close(sock_fd);
  exit(0);
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

  listen(sock_fd, MAX_CLIENT_WAIT);
  pthread_t client;
  struct sockaddr_in client_addr;
  socklen_t size_addr;
  int new_fd;
  int pid = fork();
  message m;
  int port_data_server;
  if(pid!=0){
    new_fd = accept(sock_fd,(struct sockaddr *)&client_addr, &size_addr);
      recv(new_fd,(void *)&m, sizeof(m), 0);
    close(new_fd);
    port_data_server = m.info;
    while(1){
      new_fd = accept(sock_fd,(struct sockaddr *)&client_addr, &size_addr);

      if(new_fd == -1){
        exit(-1);
      }
      m.info = port_data_server;
      if(send(new_fd, &m, sizeof(m), 0)==-1){
        return(-1);
      }

      // faz um send
      close(new_fd);
    }



  }else{


    //excve e passa porta por argumento
    char ** arg;
    arg = (char **)malloc(2*sizeof(char*));
    arg[0] = (char *)malloc(12*sizeof(char));
    sprintf(arg[0],"data_server");
    arg[1] = (char *)malloc(12*sizeof(char));
    sprintf(arg[1],"%d",port);

    if(execv("/home/rui/code/psis_project/bin/data_server",arg)==-1){
      printf("erro\n");
    }

  }



//  intHandler(0);
  return 0;

}
