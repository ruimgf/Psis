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

//////////////////

//backup jorge

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

int fp;

//////////////////




int sock_fd;



int n_thread_ocupate=0;

int n_thread=0;

hashtable_t * ht;


void intHandler(int dumbi){
  //print_list(begin);
  close(sock_fd);
  exit(0);
}

int op_read(int new_fd, message m){

  item_t * aux;
  message m1;
  char * buf,*buf_send;

  buf = ht_get( ht , m.key );

  if(buf==NULL){
    m1.info = -2 ;
    if(send(new_fd,&m1, sizeof(m1),0)==-1){
      return -1;
    }
    return 0;
  }else{
    m1.info = strlen(buf) +1;
    if(send(new_fd,&m1, sizeof(m1),0)==-1){
      return -1;
    }
  }

  if(buf!=NULL){
    buf_send = (char *)malloc(sizeof(char)*m.value_length);
    buf_send = strncpy(buf_send,buf, m.value_length-1);
    buf_send[m.value_length-1]='\0';
    if(send(new_fd,buf_send, m.value_length,0)==-1){
      return -1;
    }
  }



}



int op_write(int new_fd, message m){
  char * buf; // tem de ser alterado isto é so para compilar
  message m1;

  buf = (char *)malloc(sizeof(char) * (m.value_length) );

  recv(new_fd,buf,m.value_length, 0);

  //printf("key %u value %s \n", m.key, buf);

  if (m.info == OVERWRITE) {
    m1.info = ht_set(ht,m.key,buf,1);

  }else{
    m1.info = ht_set(ht,m.key,buf,0);
  }

  m.value_length--;
  if (m1.info==0) {
    write(fp,&m,sizeof(m));////backup jorge
    write(fp,buf,strlen(buf));
  }
  if(send(new_fd, &m1, sizeof(m1), 0)==-1){
    return(-1);
  }

  free(buf);
  return 0;
}

int op_delete(int new_fd ,message m){
  message m1;


  m1.info = DELETE_OK;
  m1.info = ht_remove(ht,m.key);
  if(send(new_fd, &m1, sizeof(m1), 0)==-1){
    return(-1);
  }
  return 0;
}

void * thread(void * fd){

  int new_fd = *((int*)(fd));
  char buf[100];

  message m;

  int naosair = 1;
  while (naosair) {

      recv(new_fd,(void *)&m, sizeof(m), 0);

      switch (m.info) {
        case READ:
          printf("read %d\n",m.info);
          op_read(new_fd, m);
          break;
        case WRITE:
          printf("WRITE %d\n",m.info);
          op_write(new_fd,m);
          break;
        case OVERWRITE:
          printf("OVERWRITE %d\n",m.info);
          op_write(new_fd,m);
          break;
        case DELETE:
          printf("delete %d\n",m.info);
          op_delete(new_fd,m);
          break;
        case EXIT :
          naosair = 0;
          close(fp);//teste
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




int main(int argc, char *argv[]){

/////////////

message m_buf;
char * buf;


fp = open("backup.txt",O_RDONLY);//read
ht = ht_create(10);
if(fp!=-1){

  while(read(fp,&m_buf,sizeof(m_buf))!=0)
  {
    if(m_buf.info==WRITE || m_buf.info==OVERWRITE){
      buf = (char*)malloc((m_buf.value_length+1)*sizeof(char));
      read(fp,buf,m_buf.value_length);
      buf[m_buf.value_length]='\0';
      ht_set(ht,m_buf.key,buf,1);
      printf("%u %s\n",m_buf.key,buf);
    }

  }



}else{
    fp=open("backup.txt",O_CREAT | O_WRONLY,0600);//write

}

if (fp==-1)
{
  printf("Failed to create and open file!\n");
  exit(-1);
}

/////////////

  struct sockaddr_in server_addr;

  signal(SIGINT, intHandler);

  sock_fd = socket(AF_INET, SOCK_STREAM, 0);

	if (sock_fd == -1){
		printf("socket: error\n");
		exit(-1);
	}

	server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  int port = 10500;
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

  struct sockaddr_in front_server_addr;
  socklen_t len_endereco_1;
  int err1;

  int sock_fd1 = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fd1 == -1){
    return(-1);
  }

  front_server_addr.sin_family = AF_INET;
  int front_server_port;
  sscanf(argv[1],"%d",&front_server_port);
  front_server_addr.sin_port = htons(front_server_port);

  inet_aton(SOCK_ADDRESS, &server_addr.sin_addr);

  err = connect(sock_fd1, (const struct sockaddr *) &front_server_addr,sizeof(front_server_addr));
  if (err == -1){
    return(-1);
  }
  message m;
  m.info = port;
  if(send(sock_fd1,&m, sizeof(m),0)==-1){
    return -1;
  }
  close(sock_fd1);
  listen(sock_fd, MAX_CLIENT_WAIT);
  pthread_t client;
  struct sockaddr_in client_addr;
  socklen_t size_addr;


  int new_fd;
  while(1){
    new_fd = accept(sock_fd,(struct sockaddr *)&client_addr, &size_addr);

    if(new_fd == -1){
      exit(-1);
    }
    #ifdef DEBUG
    printf("accept\n");
    #endif
    pthread_create(&client,NULL,thread,(void*)&new_fd);



  }

//  intHandler(0);
  return 0;

}
