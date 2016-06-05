/*
 * exV.c
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
// used example in http://www.gnu.org/software/libc/manual/html_node/Sigaction-Function-Example.html
int cont=1;
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
void termination_handler (int signum)
{
  int nr_random;
  srandom(cont);
  nr_random=random()%10;
  cont=0;
  alarm(nr_random);
}

int main(int argc, char **argv)
{
	struct sigaction new_action;
	
	alarm(random()%10);
	new_action.sa_handler = termination_handler;
	sigaction(SIGALRM,&new_action, NULL);
	
	while (1){
		sleep(1);
		printf("%d\n",cont++);
	}
	
	return 0;
}

