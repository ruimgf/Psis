#include "storyserver_1.h"

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

    int sock_fd= socket(AF_UNIX, SOCK_DGRAM, 0);
    struct sockaddr_un server_addr;
    if (sock_fd == -1){
      perror("socket: ");
      exit(-1);
    }

    printf(" socket created \n Ready to send\n");

    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, SOCK_ADDRESS);


    printf("message: ");
    fgets(m.buffer, MESSAGE_LEN, stdin);

    sendto(sock_fd, &m, sizeof(m), 0, (const struct sockaddr *) &server_addr, sizeof(server_addr));

    /* write message */


    /* receive story */

    printf("OK\n");
    exit(0);

}
