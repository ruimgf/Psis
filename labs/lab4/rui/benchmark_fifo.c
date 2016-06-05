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
#include "lab4-1.h"

void error_and_die(const char *msg) {
  perror(msg);
  exit(EXIT_FAILURE);
}

int main(){

    unsigned int nr;

    if (mkfifo("/tmp/fifo", 0666)!=0)
  	{
  	 	error_and_die("father");
  	}

    int fd;
    char buf[10];
    unsigned int i=0;
    struct timespec start,end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    int pid = fork();
    if (pid==0) {

      fd = open("/tmp/fifo", O_RDONLY);
    	if (fd==-1)
    	{
    		error_and_die("rip1");
    	}

      while(1){
        if (read(fd,buf,10)>0){
    	  	i++;
          /*
          if(i==UINT_MAX)
            break;
          */
        }
      }

    }else{

      fd = open("fifo", O_WRONLY);

    	if (fd==-1)
    	{
    		error_and_die("rip1");
    	}
      /*
        esta a demorar 158 segundos com UINT_MAX/125
        se for linear ...
      */

      for ( i = 0; i < UINT_MAX; i++) {
        sprintf(buf,"%d",i);
    	  write(fd,buf, 10);
      }

      clock_gettime(CLOCK_MONOTONIC, &end);
      int tempo = end.tv_sec - start.tv_sec;
		  printf("%d s\n",tempo);

    }
      close(fp);
      unlink("/tmp/fifo");

}
