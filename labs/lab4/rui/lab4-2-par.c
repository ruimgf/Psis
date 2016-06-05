#include <limits.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "lab4-1.h"

void error_and_die(const char *msg) {
  perror(msg);
  exit(EXIT_FAILURE);
}

int main(){

	int i=1;

	int fd1;

	/*só para testar isto*/
	fd1 = open("par", O_RDONLY);
	if (fd1==-1)
	{
		error_and_die("rip1");
	}

	char buf[10];
	int nr;
	while(1){
  	  if (read(fd1,buf, 10)>0){
  	  	sscanf(buf,"%d",&nr);
  	  	if(nr%2 == 0){
		    printf("%d %d\n", i++, nr);
		}
  	  }
	}

}
