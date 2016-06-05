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
	int fd1,fd2;

	shm_unlink(memname);
	char str[]="ola\n";
	int fd = shm_open(memname, O_CREAT | O_RDWR, 0666);
	if (fd == -1)
		error_and_die("shm_open");

	int r = ftruncate(fd, sizeof(shm_region));
	if (r != 0)
		error_and_die("ftruncate");
		
	shm_region * ptr = mmap(0, sizeof(shm_region), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (ptr == MAP_FAILED)
		error_and_die("mmap");
	close(fd);

	if (mkfifo("father", 0666)!=0)
	{
	 	error_and_die("father");
	} 
	
	if (mkfifo("son", 0666)!=0)
	{
	 	error_and_die("son");
	}
	
	int token;
	printf("1\n");
	fd1 = open("father", O_WRONLY);
	if (fd1==-1)
	{
		error_and_die("rip1");
	}
	fd2 = open("son", O_RDONLY);
	if (fd2==-1)
	{
		error_and_die("rip2");
	}
	char buf[10];
	/*
	*
		token
		0 not read
		1 read generate a new number	

	*/
	for(i=0; i < 10000; i++){
	  token=0;
	  ptr->value = random();
	  sprintf(str,"%d",token);
	  // printf("3\n");
	  write(fd1,str, 10);
	  while(1){
	  	// printf("%d\n",i);
	  	if (read(fd2,buf, 10)>0)
	  	{
	  		// printf("%s\n",buf);
	  		sscanf(buf,"%d",&token);
	  		// printf("%d",token);
	  		if(token==1){
	  			break;
	  		}else{
	  			write(fd1,str, 10);
	  		}
	  	}
	  }	
    }

    unlink("father");
    unlink("son");
	shm_unlink(memname);

}
