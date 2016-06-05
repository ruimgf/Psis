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

void funtion(int argf){

	printf("%d\n", argf);

}

int main(){
	
	
	int fd;
	int count=0;
	fd  = shm_open("/myregion",O_RDWR, 0666);
	
	if (fd == -1){
		printf("error");
		exit(0);
	
	}	
	
	int r = ftruncate(fd, sizeof(box));

	if (r != 0){
		exit(-1);
	}
	
	box * caixa = mmap(0, sizeof(box),PROT_READ | PROT_WRITE, MAP_SHARED,fd, 0);
	
	while(1){
			
		if(caixa->read == 0 && caixa->nr%2 != 0 ){
			
			count++;		
			caixa->read = 1;
		}
		if(caixa->read == 2){
			break;
		}
	}
	printf("%d", count++);	



}
