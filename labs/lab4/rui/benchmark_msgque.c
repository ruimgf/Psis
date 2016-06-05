#include <limits.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <mqueue.h>
#include <string.h>

void error_and_die(const char *msg) {
  perror(msg);
  exit(EXIT_FAILURE);
}

int main(){
    char buf[10];
    unsigned int nr;

      int fd;
    unsigned int i=0;
    struct timespec start,end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    int pid = fork();
    if (pid==0) {

      mqd_t queue = mq_open("/myqeue", O_RDONLY);
      if (queue==-1) {
        error_and_die("sddsaa son son ");
      }
      while(1){
        //printf("1\n");
        if (mq_receive(queue, buf, sizeof(buf)+1, NULL)>0){
          //printf("receive %s\n",buf);
          i++;
  		  }
      }

    }else{
      struct mq_attr attr;
      attr.mq_flags = 0;
      attr.mq_maxmsg = 10;
      attr.mq_msgsize = 11;
      attr.mq_curmsgs = 0;
      char name[] = "/myqeue";

      mqd_t queue = mq_open(name, O_CREAT | O_RDWR, 0666, &attr);
      if (queue==-1) {
        error_and_die("hey");
      }
      /*
      *demora 19.526s em UINT_MAX/125
      *
      */
      for ( i = 0; i < UINT_MAX/128; i++) {
        sprintf(buf,"%u",i);
        //printf("%s\n",buf);
        if(mq_send(queue, buf, sizeof(buf)+1, 1)!=0){
          error_and_die("hello");

        }

      }
      int status;
      clock_gettime(CLOCK_MONOTONIC, &end);
      int tempo = end.tv_sec - start.tv_sec;
		  printf("%d\n ns",tempo);

    }


}
