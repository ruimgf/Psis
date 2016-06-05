/*
 * exV1.c
 * 
 * Copyright 2016 root <root@Tyrion>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>



int main(int argc, char **argv)
{
	FILE *fp;
	char line[100];
	int pid;
	int tempo;
	struct timespec start,end;
	char * argv1[11];
	int status;
	int i;
	//int argc1;
	int len;
	
	
	fp=fopen("script.txt","r");
	for (i = 0; i < 3 ; i++)
		{
			argv1[i]=(char*)malloc(30*sizeof(char));
		}
	sprintf(argv1[0],"/bin/sh");
	sprintf(argv1[1],"-c");
	
	while(fgets(line,100,fp)!=NULL){
		//printf("%s", line);
		
		len=strlen(line);
		line[len-1]='\0';/*remove \n from fgets*/
		
		sprintf(argv1[2],"\"%s\"",line);

		/*
		for (i = 0; i < 3; i++)
		{
			
			printf(" %s ",argv1[i]);
		}*/
		clock_gettime(CLOCK_MONOTONIC, &start);	/* mark start time */
		
		pid=fork();
		if(pid==0){
			//system(line);
			execle("/bin/sh","sh","-c",line,(char *)0);
			
		}else{
			wait(&status);
			clock_gettime(CLOCK_MONOTONIC, &end);
		}
		tempo= end.tv_nsec - start.tv_nsec;
		printf("%d\n ns",tempo);
	}
	return 0;
}


