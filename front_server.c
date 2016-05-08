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

//#include <sys/types.h>
#include <sys/wait.h>

#define MAX_THREADS 20

#include <errno.h>

int sock_fd;
int data_server_pid;
int port = 9999;
int port_data_server;

void * data_server_alive(void * fd){
  int ret;
  message m;
  int fdd;
  struct sockaddr_in client_addr;
  socklen_t size_addr;
  int front_server_pid = getpid();
  while(1){
    sleep(3);
    waitpid(data_server_pid, &ret,0);
    if(kill(data_server_pid,0)!=0){
      data_server_pid = fork();
      if(data_server_pid == 0){
        char ** arg;
        arg = (char **)malloc(5*sizeof(char*));
        arg[0] = (char *)malloc(12*sizeof(char));
        sprintf(arg[0],"data_server");
        arg[1] = (char *)malloc(12*sizeof(char));
        sprintf(arg[1],"%d",port);
        arg[2] = (char *)malloc(1*sizeof(char));
        sprintf(arg[2],"1");
        arg[3] = (char *)malloc(4*sizeof(char));
        sprintf(arg[3],"%d",front_server_pid);
        arg[4] = NULL;

          if(execv("bin/data_server",arg)==-1){
            perror("Error execve:");
          }

      }else{
        int fifo;
        fifo = open("/tmp/fifo", O_RDONLY);
      	if (fifo==-1)
      	{
          exit(-1);
      	}

        char buf_fifo[10];

        read(fifo,buf_fifo,10);
        sscanf(buf_fifo,"%d",&port_data_server);
        close(fifo);
      }
    }
  }

}

void intHandler(int dumbi){
  //print_list(begin);
  //kill(pid,SIGINT);
  kill(data_server_pid,SIGINT);
  close(sock_fd);
  exit(0);
}

int main(int argc, char * argv[]){

  struct sockaddr_in server_addr;

  signal(SIGINT, intHandler);

  sock_fd = socket(AF_INET, SOCK_STREAM, 0);

	if (sock_fd == -1){
		printf("socket: error\n");
		exit(-1);
	}

  if (mkfifo("/tmp/fifo", 0666)!=0)
  {
    printf("fifo already exist\n");
  }


	server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;

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
  pthread_create(&client,NULL,data_server_alive,(void*)NULL);

  int pid = 1;
  int father_pid = getpid();
  int comunicar = 1;
  if(argc > 1){
    sscanf(argv[1],"%d",&data_server_pid);
    comunicar = 0;
    sscanf(argv[2],"%d",&port_data_server);

  }else{
    pid = fork();
    data_server_pid = pid;
  }
  message m;

  if(pid!=0){
    int new_fd;
    if(comunicar != 0){

      int fifo;
      fifo = open("/tmp/fifo", O_RDONLY);

      if (fifo==-1)
    	{
        exit(-1);
    	}

      char buf_fifo[10];
      read(fifo,buf_fifo,10);
      sscanf(buf_fifo,"%d",&port_data_server);
      close(fifo);


    }

    printf("go accept\n");

    while(1){
      new_fd = accept(sock_fd,(struct sockaddr *)&client_addr, &size_addr);
      printf("accept front_server\n");
      if(new_fd == -1){
        exit(-1);
      }

      m.info = port_data_server;
      if(send(new_fd, &m, sizeof(m), 0)==-1){
        return(-1);
      }
      printf("make send\n");

      // faz um send
      close(new_fd);
    }



  }else{

    //excve e passa porta por argumento
    char ** arg;
    arg = (char **)malloc(4*sizeof(char*));
    arg[0] = (char *)malloc(12*sizeof(char));
    sprintf(arg[0],"data_server");
    arg[1] = (char *)malloc(12*sizeof(char));
    sprintf(arg[1],"%d",port);
    arg[2] = (char * )malloc(sizeof(char));
    sprintf(arg[2],"%d",father_pid);
    arg[3]=NULL;

    if(execv("bin/data_server",arg)==-1){
      perror("Error execve:");
    }

  }

  return 0;

}
