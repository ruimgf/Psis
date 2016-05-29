#include <stdint.h>
#include "psiskv.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>



/**
 * [kv_connect Realiza uma nova conexão ao servidor]
 * @param  kv_server_ip   [Endereço do Servidor]
 * @param  kv_server_port [Porta do Servidor]
 * @return                [Return]
 */
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

  if(kv_server_ip == NULL || kv_server_port <= 0){
    return(-2);
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(kv_server_port);

  inet_aton(SOCK_ADDRESS, &server_addr.sin_addr);

  err = connect(sock_fd, (const struct sockaddr *) &server_addr,sizeof(server_addr));
  printf("connect KV front_server\n");
  if (err == -1){
    return(-1);
  }
  recv(sock_fd,&m,sizeof(m), 0);
  printf("reci\n");
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

/**
 * [kv_close Termina a ligação entre cliente e servidor]
 * @param kv_descriptor [Indentificador do servidor]
 */
void kv_close(int kv_descriptor){
  message m ;
  m.info = EXIT;
  m.key = -1;
  m.value_length = -1;
  if (kv_descriptor == -1 ){
    return;
  }

  if(send(kv_descriptor, &m, sizeof(m), 0)==-1){
    return;
  }
  close(kv_descriptor);

}
/**
 * [kv_write Trata operções de escrita por parte dos clientes]
 * @param  kv_descriptor [identificador do servidor]
 * @param  key           [chave]
 * @param  value         [valor]
 * @param  value_length  [tamanho do valor]
 * @param  overwrite     [se quer ou não fazer overwrite]
 * @return               [-1 em caso de erro 0 no caso de sucesso]
 */
int kv_write(int kv_descriptor, uint32_t key, char * value, int value_length, int overwrite){

    message m;

    if (overwrite == 1) {
      m.info = OVERWRITE;
    }else{
      m.info = WRITE;
    }

    m.key = key;
    m.value_length = value_length;

    //verificar argumentos
    if (kv_descriptor == -1 || value == NULL || value_length <= 0){
      return(-2);
    }

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

/**
 * [kv_read operação leitura por parte do cliente]
 * @param  kv_descriptor [identificador do servidor]
 * @param  key           [chave]
 * @param  value         [valor]
 * @param  value_length  [tamanho para receber valor]
 * @return               [nr_bytes lidos ou -1,-2 em casos de erro]
 */
int kv_read(int kv_descriptor, uint32_t key, char * value, int value_length){

  message m_r, m_s;

  m_s.info = READ;
  m_s.key = key;
  m_s.value_length = value_length;

  //verificar argumentos
  if (kv_descriptor == -1 || value == NULL || value_length <= 0){
    return(-2);
  }

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
 * @param kv_descriptor [identificador do servidor]
 * @param key           [chave]
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

  return m.info;

}
