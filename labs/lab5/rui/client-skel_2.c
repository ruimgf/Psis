#include "storyserver_2.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/socket.h>
#include <sys/un.h>

int main(){
    message m;

    int sock_fd;

    sock_fd = socket(AF_UNIX, SOCK_DGRAM, 0);

    struct sockaddr_un server_addr;
    struct sockaddr_un local_addr;


    if (sock_fd == -1){
      perror("socket: ");
      exit(-1);
    }


    printf(" socket created \n Ready to send\n");
    char buff[100];


    int i=1;
    int err;
    local_addr.sun_family = AF_UNIX;
    server_addr.sun_family = AF_UNIX;
    while(1){
      sprintf(buff,"/tmp/sock_cli_%d",i);
      strcpy(local_addr.sun_path, buff);
      err = bind(sock_fd, (struct sockaddr *)&local_addr, sizeof(local_addr));
      if(err != -1) {
        break;
      }
      i++;
    }

    printf("message: ");
    fgets(m.buffer, MESSAGE_LEN, stdin);
    strcpy(server_addr.sun_path, SOCK_ADDRESS);
    strcpy(m.socket_add, local_addr.sun_path);
    sendto(sock_fd, &m, sizeof(m), 0, (const struct sockaddr *) &server_addr, sizeof(server_addr));

    /* write message */

    /* receive story */
    recv(sock_fd,(void *)&m, sizeof(m), 0);
    printf("OK %s\n", m.buffer);
    close(sock_fd);
    unlink(buff);
    exit(0);

}
