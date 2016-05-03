#include <stdint.h>
#include "psiskv.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int kv_connect(char * kv_server_ip, int kv_server_port){


  struct sockaddr_in server_addr;
  socklen_t len_endereco;
  int err;
  message m;
  int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  int sock_fd1 = socket(AF_INET, SOCK_STREAM, 0);
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
  recv(sock_fd,&m,sizeof(m), 0);
  printf("recv %d\n",m.info);
  close(sock_fd);

  // connect data server
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(m.info);

  inet_aton(SOCK_ADDRESS, &server_addr.sin_addr);

  err = connect(sock_fd1, (const struct sockaddr *) &server_addr,sizeof(server_addr));
  if (err == -1){
    return(-1);
  }

  return(sock_fd1);
}

void kv_close(int kv_descriptor){
  message m ;
  m.info = EXIT;
  m.key = -1;
  m.value_length = -1;

  if(send(kv_descriptor, &m, sizeof(m), 0)==-1){
    return;
  }
  close(kv_descriptor);

}

int kv_write(int kv_descriptor, uint32_t key, char * value, int value_length, int overwrite){

    message m;

    if (overwrite == 1) {
      m.info = OVERWRITE;
    }else{
      m.info = WRITE;
    }

    m.key = key;
    m.value_length = value_length;

    if(send(kv_descriptor, &m, sizeof(m), 0)==-1){
      return(-1);
    }

    if(send(kv_descriptor,value,value_length, 0)==-1){
      return(-1);
    }

    recv(kv_descriptor,&m,sizeof(m), 0);
    /** fazer um rcv para confirmar se foi ou não escrito.*/

    return m.info;

}


int kv_read(int kv_descriptor, uint32_t key, char * value, int value_length){

  message m_r, m_s;

  m_s.info = READ;
  m_s.key = key;
  m_s.value_length = value_length;

  if(send(kv_descriptor, &m_s, sizeof(m_s), 0)==-1){
    return(-1);
  }

    /** pode haver aquui um erro se m_s.value_length > sizeof(value) **/
  if(recv(kv_descriptor,&m_r,sizeof(m_r), 0)==-1){
    return(-1);
  }

  if(m_r.info == -2){
    return -2;
  }

  if(recv(kv_descriptor,value,value_length, 0)==-1){
    return(-1);
  }
  return m_r.info;
}


/**
 * [kv_delete Send to server an order to delete a entry identify by key]
 * @param kv_descriptor [fd indentifier of server]
 * @param key           [key of entry to delete]
 * @return [-1 case of error 0 on sucess]
 */
int kv_delete(int kv_descriptor, uint32_t key){

  message m;
  m.info = DELETE;
  m.key = key;

  if(send(kv_descriptor, &m, sizeof(m), 0)==-1){
    return(-1);
  }

  if(recv(kv_descriptor,&m,sizeof(m), 0)==-1){
    return(-1);
  }

  /* adicionar leitura para confirmar delete com sucesso */


  return m.info;

}
