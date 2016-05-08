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

#include <sys/types.h>
#include <sys/wait.h>

#define MAX_THREADS 20
#define NR_LINES_HT 10
//////////////////

//backup jorge

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

int fp;//ficheiro txt
int log_file;//ficheiro log

//////////////////
// variaveis globais
pthread_mutex_t mux[10];
pthread_mutex_t muxfile;
int sock_fd;
hashtable_t * ht;
int front_server_pid;
int data_server_pid;
int port = 10500;
/////////

void * front_server_alive(void * fd){

  int ret;
  int data_server_pid = getpid();
  while(1){
    sleep(3);
    waitpid(front_server_pid, &ret,0);
    if(kill(front_server_pid,0)!=0){
      printf("go lauch\n");

      front_server_pid = fork();
      if(front_server_pid == 0){
        printf("fork\n");
        char ** arg;
        arg = (char **)malloc(4*sizeof(char*));
        arg[0] = (char *)malloc(12*sizeof(char));
        sprintf(arg[0],"front_server");
        //arg[1] = (char *)malloc(12*sizeof(char));
        //sprintf(arg[1],"%d",port);
        //arg[2] = (char *)malloc(sizeof(int));
        //sprintf(arg[2],"0");
        arg[1] = (char*)malloc(10*sizeof(char));
        sprintf(arg[1],"%d",data_server_pid);
        arg[2] = (char*)malloc(10*sizeof(char));
        sprintf(arg[2],"%d",port);
        arg[3] = NULL;
        printf("go execv\n");
          if(execv("bin/front_server",arg)==-1){
            perror("Error execve:");
          }

      }
    }
  }
}




int backup_ht(){
    int i;
    item_t * aux;
    message m;
    for( i = 0 ; i < ht-> line_nr ; i++  ){
      aux = ht->table[i]->next;
      while (aux!=NULL) {
        m.info = WRITE;
        m.key = aux->key;
        m.value_length = strlen(aux->value) + 1;
        write(fp,&m,sizeof(m));////backup jorge
        write(fp,aux->value,strlen(aux->value) + 1);
        aux=aux->next;
      }

    }

    return 0;
}

void * log_cycle(void * name)
{

  int i;

  while(1)
  {
    for (i = 0; i < NR_LINES_HT; i++) {
      pthread_mutex_lock(&mux[i]);
    }
    pthread_mutex_lock(&muxfile);
    printf("lock\n");

    close(log_file);

    remove("backup.txt");
    fp = open("backup.txt",O_CREAT|O_WRONLY,0600);
    if (fp==-1)
    {
      printf("Backup.txt was not created succesfully!\n");
      exit(-1);
    }
    backup_ht();
    close(fp);

    remove("backup.log");
    log_file = open("backup.log",O_CREAT|O_WRONLY,0600);
    if (log_file==-1)
    {
      printf("Backup.log was not created succesfully!\n");
      exit(-1);
    }

    for (i = 0; i < NR_LINES_HT; i++) {
      pthread_mutex_unlock(&mux[i]);
    }
      pthread_mutex_unlock(&muxfile);
    printf("unlock\n");
    sleep(60);
  }

}


void intHandler(int dumbi){
  close(log_file);
  remove("backup.log");
  remove("backup.txt");
  fp = open("backup.txt",O_CREAT|O_WRONLY,0600);
  if (fp==-1)
  {
    printf("Backup.txt was not created succesfully!\n");
    exit(-1);
  }
  backup_ht();
  close(fp);
  close(sock_fd);
  exit(0);
}

int op_read(int new_fd, message m){

  item_t * aux;
  message m1;
  char * buf,* buf_send;

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
  return 0;
}



int op_write(int new_fd, message m){
  char * buf;
  message m1;
  buf = (char *)malloc(sizeof(char) * (m.value_length) );
  recv(new_fd,buf,m.value_length, 0);

  if (m.info == OVERWRITE) {
    m1.info = ht_set(ht,m.key,buf,1);
  }else{
    m1.info = ht_set(ht,m.key,buf,0);
  }

  if (m1.info==0) {
    pthread_mutex_lock(&muxfile);
    write(log_file,&m,sizeof(m));////backup jorge
    write(log_file,buf,m.value_length);
    pthread_mutex_unlock(&muxfile);
  }
  if(send(new_fd, &m1, sizeof(m1), 0)==-1){
    return(-1);
  }
  free(buf);
  return 0;
}

int op_delete(int new_fd ,message m){
  message m1;

  m1.info = ht_remove(ht,m.key);

  if (m1.info==0) {
    pthread_mutex_lock(&muxfile);
    write(log_file,&m,sizeof(m));////backup jorges
    pthread_mutex_unlock(&muxfile);
  }
  if(send(new_fd, &m1, sizeof(m1), 0)==-1){
    return(-1);
  }
  return 0;
}

void * thread(void * fd){

  int new_fd = *((int*)(fd));
  free(fd);
  message m;

  int naosair = 1;
  while (naosair) {
      recv(new_fd,(void *)&m, sizeof(m), 0);
      switch (m.info) {
        case READ:
          pthread_mutex_lock(&mux[m.key%10]);
          op_read(new_fd, m);
          pthread_mutex_unlock(&mux[m.key%10]);
          break;
        case WRITE:
          pthread_mutex_lock(&mux[m.key%10]);
          op_write(new_fd,m);
          pthread_mutex_unlock(&mux[m.key%10]);
          break;
        case OVERWRITE:
          pthread_mutex_lock(&mux[m.key%10]);
          op_write(new_fd,m);
          pthread_mutex_unlock(&mux[m.key%10]);
          break;
        case DELETE:
          pthread_mutex_lock(&mux[m.key%10]);
          op_delete(new_fd,m);
          pthread_mutex_unlock(&mux[m.key%10]);
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




int main(int argc, char *argv[]){

/////////////

message m_buf;
char * buf;

  signal(SIGINT, intHandler);
  int i;

  for(i = 0;i< 10;i++){
    if(0 != pthread_mutex_init(&mux[i], NULL)){
  		printf("mutex creation error\n");
  		exit(-1);
  	}

  }
  if(0 != pthread_mutex_init(&muxfile, NULL)){
		printf("mutex creation error\n");
		exit(-1);
	}
  //falta o destroy

  ht = ht_create(NR_LINES_HT);

  fp = open("backup.txt",O_RDONLY);//read
  if(fp!=-1)
  {
    printf("\nbackup.txt is going to be loaded!\n\n");
    while(read(fp,&m_buf,sizeof(m_buf))!=0)
    {
      if(m_buf.info==WRITE || m_buf.info==OVERWRITE){
        buf = (char*)malloc((m_buf.value_length)*sizeof(char));
        read(fp,buf,m_buf.value_length);
        buf[m_buf.value_length]='\0';
        ht_set(ht,m_buf.key,buf,1);
        printf("Backup.txt | key:%10u | value:%10s | WRITE\n",m_buf.key,buf);
      }
    }
    printf("\nbackup.txt was loaded correctly!\n");
    close(fp);
  }

  log_file = open("backup.log",O_RDONLY);//read
  if(log_file!=-1)
  {
    printf("\nbackup.log is going to be loaded!\n\n");
    while(read(log_file,&m_buf,sizeof(m_buf))!=0)
    {
      if(m_buf.info==WRITE || m_buf.info==OVERWRITE){
        buf = (char*)malloc((m_buf.value_length)*sizeof(char));
        read(fp,buf,m_buf.value_length);
        buf[m_buf.value_length]='\0';
        ht_set(ht,m_buf.key,buf,1);
        printf("Backup.log | key:%10u | value:%10s | WRITE\n",m_buf.key,buf);
      }else{
        ht_remove(ht,m_buf.key);
        printf("Backup.log | key:%10u | value:%10s | REMOVE\n",m_buf.key,buf);
      }
    }
    printf("\nbackup.log was loaded correctly!\n");
    close(log_file);
  }
  remove("backup.log");
  log_file = open("backup.log",O_CREAT|O_WRONLY);

  struct sockaddr_in server_addr;

  sock_fd = socket(AF_INET, SOCK_STREAM, 0);

	if (sock_fd == -1){
		printf("socket: error\n");
		exit(-1);
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
  int comunicar = 1;
  if(argc > 2){
    sscanf(argv[1],"%d",&front_server_port);
    sscanf(argv[2],"%d",&comunicar);
    if(argc > 3){
      sscanf(argv[3],"%d",&front_server_pid);
      printf("%d\n",front_server_pid);
    }
  }else{
    printf("need to specify front_server_port\n");
    exit(-1);
  }
  comunicar = 1;
  front_server_addr.sin_port = htons(front_server_port);

  inet_aton(SOCK_ADDRESS, &server_addr.sin_addr);
  char buf_fifo[10];
  int fifo;
  if(comunicar==1){
    sprintf(buf_fifo,"%d",port);
    fifo = open("/tmp/fifo", O_WRONLY);
    write(fifo,buf_fifo, 10);
    close(fifo);

    /*
    err = connect(sock_fd1, (const struct sockaddr *) &front_server_addr,sizeof(front_server_addr));
    if (err == -1){
      return(-1);
    }
    message m;
    m.info = SEND_DATA_SERVER_PORT;
    m.value_length = port;
    if(send(sock_fd1,&m, sizeof(m),0)==-1){
      return -1;
    }

    close(sock_fd1);
    */
  }

  listen(sock_fd, MAX_CLIENT_WAIT);
  pthread_t client;
  struct sockaddr_in client_addr;
  socklen_t size_addr;

  pthread_create(&client,NULL,log_cycle,(void*)NULL);
  pthread_create(&client,NULL,front_server_alive,(void*)NULL);
  //int new_fd;
  while(1){
    int * new_fd = (int *)malloc(sizeof(int));
    *new_fd = accept(sock_fd,(struct sockaddr *)&client_addr, &size_addr);

    if(*new_fd == -1){
      exit(-1);
    }
    #ifdef DEBUG
    printf("accept\n");
    #endif
    pthread_create(&client,NULL,thread,(void*)new_fd);

  }

//  intHandler(0);
  return 0;

}
