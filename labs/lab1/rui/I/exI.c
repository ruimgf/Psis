#include <stdlib.h>
#include <stdio.h>

int string_len(char string[]){
	int len=0;
	int i=0;

	while(1){
		if(string[i]=='\0'){
			break;
		}
		len++;
		i++;
	}
	return slen;
}
/*
 * 
 *indice_start on dest_string 
 */
char * copy_string(char * origin_string, char * dest_string, int indice_start){
		int i,j;
		i=indice_start;
		
		for(j=0;j<string_len(origin_string);j++){
			dest_string[i]=origin_string[j];
			i++;
		}
		
		dest_string[i]='\0';
		return dest_string;
}

/* concat2strig
 * input : strig1 and string 2
 * output: poiter to a concatnated string
 */
char * concat2strig(char * string1, char * string2, int free_1 ){
	int len = string_len(string1) + string_len(string2) + 1 ;
	char * out_string;
	out_string=(char *)malloc(len*sizeof(char)); 
	
	out_string=copy_string(string1,out_string,0);
	out_string=copy_string(string2,out_string,string_len(string1));
	if(free_1==1){
		free(string1);
		
	}
	
	return out_string;
}

int main(int argc, char ** argv){
	
	char * out_string=NULL;
	int i;
	if(argc<3){
		printf("wrong usage\n");
		exit(-1);
	}
	for(i=1;i<argc-1;i++){
		if(i==1){
			out_string=concat2strig(argv[i], argv[i+1],0);
		}else{
			out_string=concat2strig(out_string, argv[i+1],1);
		}
	}
	
	printf("%s\n",out_string);
	free(out_string);
	return 1;
}
