#include "psiskv.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char ** argv){

    char buf[100];
    sprintf(buf,"%s",SOCK_ADDRESS);
    unsigned int key;
    int port;
    int op;

    if(argc == 1){
      port = 9999;
    }else{
        sscanf(argv[1],"%d",&port);
    }
//verificar return
    int sock_fd = kv_connect(buf, port);
    if (sock_fd==-1) {
      printf("invalid connect\n");
      exit(-1);
    }
    int naosair = 1;

    while(naosair){

      printf("Operation: ");
      fgets(buf, 100, stdin);
      sscanf(buf,"%s",buf);

      for(int i = 0; i < strlen(buf); i++)
        buf[i] = tolower(buf[i]);
      if(strcmp(buf,"write")==0)
        op=WRITE;
      else if(strcmp(buf,"overwrite")==0)
        op=OVERWRITE;
      else if(strcmp(buf,"read")==0)
        op=READ;
      else if(strcmp(buf,"delete")==0)
        op=DELETE;
      else if(strcmp(buf,"exit")==0)
        op=EXIT;
      else op=NONE;

      if(op != EXIT){
        printf("Key:");
        fgets(buf,100, stdin);
        sscanf(buf,"%u",&key);
      }

      switch (op) {
        case WRITE:
          printf("Value: ");
          fgets(buf, 100, stdin);
          buf[strlen(buf)-1]='\0';
          kv_write(sock_fd,key, buf, strlen(buf)+1,0);
          break;
        case OVERWRITE:
          printf("Value: ");
          fgets(buf, 100, stdin);
          buf[strlen(buf)-1]='\0';
          kv_write(sock_fd,key, buf, strlen(buf)+1,1);
          break;
        case READ:
          if(kv_read(sock_fd,key,buf,100)!=-2){
            printf("Key: %u --> Value: %s\n",key,buf );
          }else{
            printf("Key does not exist!\n");
          }
          break;
        case DELETE:
          if(kv_delete(sock_fd,key)==-1)
            printf("Key does not exist!\n");
          break;
        case EXIT :
          naosair = 0;
          kv_close(sock_fd);
          break;
        default:
          printf("Invalid Operation!\n");
          kv_close(sock_fd);
        break;
      }
    }

    kv_close(sock_fd);
    printf("OK\n");
    exit(0);
}
