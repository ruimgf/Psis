#include "storyserver_2.h"

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

static volatile int keepRunning = 1;
int sock_fd;
char * story;
struct sockaddr_un local_addr;


void intHandler(int dumbi){

  keepRunning = 0;
  printf("\n%s\n",story);
  printf("OK\n");
  close(sock_fd);
  unlink(SOCK_ADDRESS);
  exit(0);

}


char * concat(char * str1, char * str2){

    char * ret =(char * ) malloc(sizeof(char)*(strlen(str1)+strlen(str2)+1));
    sprintf(ret,"%s %s",str1,str2);
    //nao liberta memória
    //free(str1);
    return ret;

}



int main(){
  char fifo_name[MESSAGE_LEN];
  message m;

  char buff[MESSAGE_LEN];

  struct sockaddr_un local_addr;
  struct sockaddr_un client_addr;
  signal(SIGINT, intHandler);
	story = strdup("");

  sock_fd = socket(AF_UNIX, SOCK_STREAM, 0);

	if (sock_fd == -1){
		printf("socket: error\n");
		exit(-1);
	}


	local_addr.sun_family = AF_UNIX;

	strcpy(local_addr.sun_path, SOCK_ADDRESS);
  int err = bind(sock_fd, (struct sockaddr *)&local_addr, sizeof(local_addr));
  if(err == -1) {
    printf("bind\n");
    exit(-1);
  }

  printf(" socket created and binded \n Ready to receive messages\n");
  listen(sock_fd, 20);
  socklen_t len_endereco,size_addr;
  while(keepRunning==1){

    int new_fd = accept(sock_fd,(struct sockaddr *)&client_addr, &size_addr);
		printf("received connection from %s\n",  client_addr.sun_path);
		if(new_fd == -1)
			exit(-1);

    recv(new_fd,(void *)&m, sizeof(m), 0);

    printf("%s",m.buffer);
    m.buffer[strlen(m.buffer)-1]='\0';
    story = concat(story,m.buffer);

    strcpy(m.buffer,story);
    send(new_fd, &m, sizeof(m), 0);

    /* process message */

  }
  intHandler(0);


}
