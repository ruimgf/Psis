#include <limits.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


void error_and_die(const char *msg) {
  perror(msg);
  exit(EXIT_FAILURE);
}

int main(){
	
  	int i;
	int fd1,fd2;

	char str[]="ola\n";

	if (mkfifo("par", 0666)!=0)
	{
	 	error_and_die("par");
	} 
	
	if (mkfifo("impar", 0666)!=0)
	{
	 	error_and_die("impar");
	}
	
	fd1 = open("par", O_WRONLY);
	if (fd1==-1)
	{
		error_and_die("rip1");
	}

	fd2 = open("impar", O_WRONLY);
	if (fd2==-1)
	{
		error_and_die("rip2");
	}

	char buf[10];
	int nr;
	for(i=0; i < 10000; i++){
	  nr = random();
	  sprintf(str,"%d",nr);
	  write(fd1,str, 10);
	  write(fd2,str, 10);	
    }
    /*podia enviar-se uma mensagem para programas terminaram no fim do ciclo*/
    close(fp1);
    close(fp2);
    unlink("par");
    unlink("impar");
}
