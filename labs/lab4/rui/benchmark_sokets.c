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
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>

void error_and_die(const char *msg) {
  perror(msg);
  exit(EXIT_FAILURE);
}

int main(){

    unsigned int nr;

    int fd[2];
    char buf[10];
    unsigned int i=0;
    struct timespec start,end;

    clock_gettime(CLOCK_MONOTONIC, &start);

    socketpair(PF_LOCAL, SOCK_STREAM, 0, fd);

    int pid = fork();
    if (pid==0) {

      while(1){
        if (read(fd[1],buf,10)>0){
    	  	i++;
          //printf("read %s\n", buf);
          /*
          if(i==UINT_MAX)
            break;
          */
        }
      }

    }else{

      /*
        esta a demorar 43 segundos com UINT_MAX/125
        se for linear ...
      */

      for ( i = 0; i < UINT_MAX/125; i++) {
        sprintf(buf,"%d",i);
    	  write(fd[0],buf, 10);
      }

      clock_gettime(CLOCK_MONOTONIC, &end);
      int tempo = end.tv_sec - start.tv_sec;
		  printf("%d s\n",tempo);

    }

}
