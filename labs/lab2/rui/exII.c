/*
 * exII.c
 * 
 * Copyright 2016 Rui <Ruimgf95@gmail.com>
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



int main(int argc, char **argv)
{
	int i=0,pid;
	int nr_random;
	int status;
	int total_time=0;
	for(i=0;i<10;i++){
		pid=fork();
		if(pid==0){
			srandom(i*getpid());
			nr_random=random()%10;
			sleep(nr_random);
			//printf("time slepp : %d | pid : %d \n",nr_random,getpid());
			exit(nr_random);
		}else{

			
		}
	}
	for(i=0;i<10;i++){
		printf("pid : %d\n",waitpid(-1, &status, 0));
		printf("sleep : %d\n",WEXITSTATUS(status));
		total_time=total_time+WEXITSTATUS(status);
	}
	printf("total time %d\n", total_time);
	
	return 0;
}

