#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(){
	int a;
	void (*f_1)()=NULL;
	void (*f_2)()=NULL;
	void * lib=NULL;
	printf("What version of the functions you whant to use?\n");
	printf("\t1 - Normal    (test1)\n");
	printf("\t2 - Optimized (test2)\n");
	scanf("%d", &a);
	if (a == 1){
		printf("running the normal versions from \n");
		
		/* call func_1 from test1 */
		/* call func_2 from test1 */
	   lib = dlopen("/home/rui/psis/lab1/rui/V_VI/test1.so", RTLD_LAZY);
	   if (!lib)
	   {
		  printf("%s\n", dlerror());
		  exit(1);

	   }


	}else{
		if(a== 2){
			printf("runnin the normal versions\n");
			/* call func_1 from test2 */
			/* call func_2 from test2 */
			lib = dlopen("/home/rui/psis/lab1/rui/V_VI/test2.so", RTLD_LAZY);
			if (!lib)
			{
				printf("%s\n", dlerror());
				exit(1);

			}
			
		}else{
			printf("Not running anything\n");
			exit(3);
		}
	}
	f_1 = dlsym(lib, "func_1");
	f_2 = dlsym(lib, "func_2");
	f_1();
	f_2();
	exit(0);
	
	
}
