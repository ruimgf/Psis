#include "kv.h"

#include <stdlib.h>
//#include <errno.h>
#include <stdio.h>


int main(){


    char buf[100];
    sprintf(buf,"%s",SOCK_ADDRESS);
    unsigned int key;
    int op;

//verificar return
    int sock_fd = kv_connect(buf, 9999);
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
        sscanf(buf,"%d",&key);

      }


      switch (op) {
        case WRITE:
          printf("value: ");
          fgets(buf, 100, stdin);
          kv_write(sock_fd,100, buf, sizeof(buf),0);
          break;
        case READ:
          printf("op read\n");
          kv_read(sock_fd,100,buf,4);
          printf("key : %u value %s \n",key,buf );
          break;

        case DELETE:
          kv_delete(sock_fd, 20302);
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
    //getchar();
    kv_close(sock_fd);
    printf("OK\n");
    exit(0);
}
