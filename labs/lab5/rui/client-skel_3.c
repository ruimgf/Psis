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

    int sock_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    struct sockaddr_un server_addr;
    if (sock_fd == -1){
      perror("socket: ");
      exit(-1);
    }

    printf(" socket created \n Ready to send\n");

    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, SOCK_ADDRESS);
    int err;
    socklen_t len_endereco;
		err = connect(sock_fd, (const struct sockaddr *) &server_addr,sizeof(server_addr));
		if (err == -1){
			perror("connect: ");
			exit(-1);
		}

    printf("message: ");
    fgets(m.buffer, MESSAGE_LEN, stdin);

    send(sock_fd, &m, sizeof(m), 0);

    recv(sock_fd,(void *)&m, sizeof(m), 0);
    printf("%s\n",m.buffer );
    printf("OK\n");
    exit(0);

}
