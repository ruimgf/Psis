#include <limits.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


typedef struct box{
	 int nr;
	 int read;
}box;


int main(){
		
	int fd;
	int i;
	fd  = shm_open("/myregion",O_CREAT | O_TRUNC | O_RDWR, 0600);
	if (fd == -1){
		printf("error");
		exit(0);
	
	}	
	
	int r = ftruncate(fd, sizeof(box));
	
	if (r != 0){
		exit(-1);
	}
	
	box * caixa = mmap(0, sizeof(box),PROT_READ | PROT_WRITE, MAP_SHARED,fd, 0);
	
	caixa->read=1;
	
	i=0;
	while(i<100000){
		
		if(caixa->read==1){
			srandom((i+1)*getpid()*caixa->nr);
			caixa->nr=random();
			caixa->read=0;
			i++;
	    }
		while(caixa->read==0);
	}
	caixa->read=2;
	printf("Fim");
	
	
	return 0;
}
