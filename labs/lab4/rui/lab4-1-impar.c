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
	
	char *memname = "odd_even";
	int i;
		
	int fd = shm_open(memname,  O_RDWR, 0666);
	if (fd == -1)
		error_and_die("shm_open");

		
	shm_region * ptr = mmap(0, sizeof(shm_region), PROT_READ , MAP_SHARED, fd, 0);
	if (ptr == MAP_FAILED)
		error_and_die("mmap");
	close(fd);
	int fd1,fd2;

	/*só para testar isto*/
	fd1 = open("father", O_RDONLY);
	if (fd1==-1)
	{
		error_and_die("rip1");
	}
	fd2 = open("son", O_WRONLY);
	if (fd2==-1)
	{
		error_and_die("rip2");
	}
	char buf[10];

	int token;
	i = 0;
	char str[10];
	int fd_token;
	while(1){
  	  if (read(fd1,buf, 10)>0){
  	  	if(ptr->value%2 != 0){
		    printf("%d %d\n", i++, ptr->value);
		 	sprintf(str,"%d",1);
		 	write(fd2,str, 10); 
		}else{
			sprintf(str,"%d",0);
		 	write(fd2,str, 10);
		}
  	  }
	  	  
	}

}
