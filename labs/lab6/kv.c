#include <stdint.h>
#include "kv.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>

int kv_connect(char * kv_server_ip, int kv_server_port){


  struct sockaddr_in server_addr;
  socklen_t len_endereco;
  int err;

  int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fd == -1){
    return(-1);
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(kv_server_port);

  inet_aton(SOCK_ADDRESS, &server_addr.sin_addr);

  err = connect(sock_fd, (const struct sockaddr *) &server_addr,sizeof(server_addr));
  if (err == -1){
    return(-1);
  }

  return(sock_fd);
}

void kv_close(int kv_descriptor){

  close(kv_descriptor);

}

int kv_write(int kv_descriptor, uint32_t key, char * value, int value_length){

    message m;

    m.operation = WRITE;
    m.key=key;
    m.value_length=value_length;

    if(send(kv_descriptor, &m, sizeof(m), 0)==-1){
      return(-1);
    }

    if(send(kv_descriptor,value,value_length, 0)==-1){
      return(-1);
    }

    return 0;

}


int kv_read(int kv_descriptor, uint32_t key, char * value, int value_length){

  message m;

  m.operation = READ;
  m.key=key;
  m.value_length=value_length;

  if(send(kv_descriptor, &m, sizeof(m), 0)==-1){
    return(-1);
  }

  if(recv(kv_descriptor,value,value_length, 0)==-1){
    return(-1);
  }

  // printf("%s\n",value);

  return 0;
}


/**
 * [kv_delete Send to server an order to delete a entry identify by key]
 * @param kv_descriptor [fd indentifier of server]
 * @param key           [key of entry to delete]
 * @return [-1 case of error 0 on sucess]
 */
int kv_delete(int kv_descriptor, uint32_t key){

  message m;
  m.operation = DELETE;
  m.key=key;

  if(send(kv_descriptor, &m, sizeof(m), 0)==-1){
    return(-1);
  }

  return(0);

}
