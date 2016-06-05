#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void copy_string_UP(char * origin_string, char * dest_string){
		int j;
		
		for(j=0;j<strlen(origin_string);j++){
			if(origin_string[j]>96&&origin_string[j]<123){
				dest_string[j]=(char)(origin_string[j]-32);
			}else{
				dest_string[j]=origin_string[j];
			}
		
		}
		dest_string[j]='\0';
}

int main(int argc, char ** argv){
	char * out_string;
	int i;
	if(argc<2){
		printf("wrong use");
		exit(-1);
	}
	for(i=1;i<argc;i++){
		out_string=(char*)malloc((strlen(argv[i])+1)*sizeof(char));
		copy_string_UP(argv[i],out_string);
		printf("%s\n",out_string);
		free(out_string);
	}
	return 1 ;
}

