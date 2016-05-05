#include "psiskv.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char ** argv){


    char buf[100];
    sprintf(buf,"%s",SOCK_ADDRESS);
    unsigned int key;
    int port;
    int op;

    if(argc ==1){

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

      printf("operation: ");
      fgets(buf, 100, stdin);
      sscanf(buf,"%d",&op);

      if(op != EXIT){
        printf("key:");
        fgets(buf,100, stdin);
        sscanf(buf,"%u",&key);
      }


      switch (op) {
        case WRITE:
          printf("value: ");
          fgets(buf, 100, stdin);
          buf[strlen(buf)-1]='\0';
          kv_write(sock_fd,key, buf, strlen(buf)+1,0);
          break;
        case OVERWRITE:
          printf("value: ");
          fgets(buf, 100, stdin);
          buf[strlen(buf)-1]='\0';
          kv_write(sock_fd,key, buf, strlen(buf)+1,1);
          break;
        case READ:
          printf("op read\n");
          if(kv_read(sock_fd,key,buf,100)!=-2){
            printf("key : %u value %s \n",key,buf );
          }else{
            printf("nao existe key\n");
          }
          break;
        case DELETE:
          kv_delete(sock_fd,key);
          break;
        case EXIT :
          naosair = 0;
          kv_close(sock_fd);
          break;
        default:
          printf("invalid operation \n");
          kv_close(sock_fd);
        break;
      }
    }
  
    kv_close(sock_fd);
    printf("OK\n");
    exit(0);
}
