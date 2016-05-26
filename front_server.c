#include "psiskv.h"

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


#include <sys/wait.h>

#define MAX_THREADS 20

#include <errno.h>

int sock_fd;
int data_server_pid;
int port = 9999;
int port_data_server;
/**
 * [data_server_alive thread que verifica se o data_server está a correr]
 * @param  fd [NULL]
 * @return    [NULL]
 */
void * data_server_alive(void * fd){
  int ret;
  message m;
  int fdd;
  struct sockaddr_in client_addr;
  socklen_t size_addr;
  int front_server_pid = getpid();
  while(1){

    sleep(3);
    // se o data_server for filho espera ate receber notificaçao da morte
    waitpid(data_server_pid, &ret,0);
    // caso contrario tenta enviar um sinal NULL que quanto morrer não conseguira ser entregue e o kill return algo diferente de 0
    if(kill(data_server_pid,0)!=0){
      data_server_pid = fork();

      if(data_server_pid == 0){
        //trata de lançar o novo data server
        char ** arg;
        arg = (char **)malloc(4*sizeof(char*));
        arg[0] = (char *)malloc(12*sizeof(char));
        sprintf(arg[0],"data_server");
        arg[1] = (char *)malloc(12*sizeof(char));
        /// passa porta do front_server por argumento
        sprintf(arg[1],"%d",port);
        arg[2] = (char *)malloc(4*sizeof(char));
        // passa pid do front_server por argumento
        sprintf(arg[2],"%d",front_server_pid);
        arg[3] = NULL;

        if(execv("bin/data_server",arg)==-1){
          perror("Error execve:");
        }

      }else{
        int fifo;
        // abre fifo para receber comunicação da porta onde o data_server deu bind
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
/**
 * [intHandler funçao que trata do sinal enviado pelo CTRL C]
 * @param dumbi [description]
 */
void intHandler(int dumbi){
  kill(data_server_pid,SIGINT);
  unlink("/tmp/fifo");
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


  int pid = 1;
  int father_pid = getpid();
  int comunicar;
  /** ve se foi lançado pelo sheel ou pelo data_server */
  if(argc > 1){
    sscanf(argv[1],"%d",&data_server_pid);
    sscanf(argv[2],"%d",&port_data_server);
    printf("%d\n",port_data_server);
    comunicar = 0;
  }else{
    pid = fork();
    data_server_pid = pid;
    comunicar = 1;
  }

  message m;
  pthread_create(&client,NULL,data_server_alive,(void*)NULL);
  if(pid!=0){
    // quando é lançado pelo front server não tem de comunicar com ele para saber a sua porta
    if(comunicar == 1){
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
    int new_fd;
    while(1){
      new_fd = accept(sock_fd,(struct sockaddr *)&client_addr, &size_addr);
      if(new_fd == -1){
        exit(-1);
      }

      m.info = port_data_server;
      if(send(new_fd, &m, sizeof(m), 0)==-1){
        return(-1);
      }
      close(new_fd);
    }



  }else{
    //quando o front lança o data.
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
