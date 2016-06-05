#include "storyserver_4.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/socket.h>
#include <sys/un.h>

#include <netinet/in.h>
#include <arpa/inet.h>


int main(){
    message m;

    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    if (sock_fd == -1){
      perror("socket: ");
      exit(-1);
    }

    printf(" socket created \n Ready to send\n");

    server_addr.sin_family = AF_INET;
    inet_aton(SOCK_ADDRESS, &server_addr.sin_addr);
    server_addr.sin_port = htons(2000);
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

  //  recv(sock_fd,(void *)&m, sizeof(m), 0);
    //printf("%s\n",m.buffer );
    printf("OK\n");
    exit(0);

}
