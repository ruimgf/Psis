#include <limits.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


typedef struct _child{
	 unsigned int min;
	 unsigned int max;
	unsigned int  m_7, m_19, m_7_19;
}child;


typedef struct _childs{
	child filhos[3];
	
	
}childs;



int main(){
	unsigned int  m_7, m_19, m_7_19;
	unsigned int i;
	int j;
	int status;
	int fd;
		
	/*
	fd  = shm_open("/myregion",O_CREAT | O_TRUNC | O_RDWR, 0600);
	if (fd == -1){
		printf("error");
		exit(0);
	
	}*/	
	/*
	int r = ftruncate(fd, sizeof(childs));
	
	if (r != 0){
		exit(-1);
	}*/
	
	child * sons = mmap(0, 3*sizeof(child),PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON,-1, 0);
		
	sons[0].min=0;
	sons[0].max=UINT_MAX/3;
	sons[1].min=UINT_MAX/3 + 1;
	sons[1].max=(UINT_MAX)/3*2;
	sons[2].min=(UINT_MAX)/3*2 + 1;
	sons[2].max=UINT_MAX;
	printf("%u\n\n",sons[0].min);
	printf("%u\n\n",sons[0].max);
	printf("%u\n\n",sons[1].min);
	printf("%u\n\n",sons[1].max);
	printf("%u\n\n",sons[2].min);
	printf("%u\n\n",sons[2].max);
	for (j = 0; j < 3  ; j++)
	{
		if(fork()==0){
			break;
		}
	}
	
	if(j==3){
		for(i=0;i<3;i++){
			wait(&status);
			printf("fim fimlh\n");
			
		}
		
		
	
	
	}else{
		m_7_19=0;
		m_19=0;
		m_7=0;
		for (i = sons[j].min; i <  sons[j].max; i++){
			if(i%7 == 0){ 
				m_7 ++;
			}
			if(i%19 == 0){ 
				m_19 ++;
			}
			if((i%7 == 0)	&& (i%19 == 0)){
				m_7_19++;
			}
		}
		sons[j].m_7 = m_7 ;
		sons[j].m_19 = m_19 ;
		sons[j].m_7_19 = m_7_19 ;	
		exit(0);	
		
	}
	
	printf("m 7    %d\n", sons[0].m_7 + sons[1].m_7 + sons[2].m_7);
	printf("m   19 %d\n", sons[0].m_19 + sons[1].m_19 + sons[2].m_19);
	printf("m 7 19 %d\n", sons[0].m_7_19 + sons[1].m_7_19 + sons[2].m_7_19);
	close(fd);
	shm_unlink ("/myregion");
}
