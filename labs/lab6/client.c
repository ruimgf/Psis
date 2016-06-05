#include "kv.h"

#include <stdlib.h>
//#include <errno.h>
#include <stdio.h>


int main(){


    char buf[100];
    sprintf(buf,"%s",SOCK_ADDRESS);
    printf("message: ");


//verificar return
    int sock_fd = kv_connect(buf, 9999);
    if (sock_fd==-1) {
      /* code */
    }

    //fgets(buf, MESSAGE_LEN, stdin);


    //kv_write(sock_fd,1000, buf, sizeof(buf));

    //kv_read(sock_fd,100,buf,4);

    kv_delete(sock_fd, 20302);

    kv_close(sock_fd);
    printf("OK\n");
    exit(0);
}
