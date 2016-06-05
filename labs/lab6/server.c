#include "kv.h"

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

int sock_fd;

void intHandler(int dumbi){

  close(sock_fd);
  exit(0);
}


int main(){
  message m;
  char buf[100];
  struct sockaddr_in server_addr;
  struct sockaddr_in client_addr;
  socklen_t size_addr;


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

  while(1){

    int new_fd = accept(sock_fd,(struct sockaddr *)&client_addr, &size_addr);
		if(new_fd == -1)
			exit(-1);

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



}

//  intHandler(0);
  return 0;

}
