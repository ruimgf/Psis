#include <stdint.h>

#define DEBUG 0
#define SOCK_ADDRESS "127.0.0.1"
#define WRITE 1
#define OVERWRITE 2
#define READ 3
#define DELETE 4
#define EXIT 8

#define  MAX_CLIENT_WAIT 20

/**
 * definição da estrutura de comunicação
 * key - chave a ler/escrever apagar
 * value_length tamanho do valor a escrever/ ler
 * info - flag com operaçao ou erro
 */

typedef struct message{
    unsigned int key;
    int value_length;
    int info;
}message;
/**
 * [kv_connect Realiza uma nova conexão ao servidor]
 * @param  kv_server_ip   [Endereço do Servidor]
 * @param  kv_server_port [Porta do Servidor]
 * @return                [Return]
 */
int kv_connect(char * kv_server_ip, int kv_server_port);
/**
 * [kv_write Trata operções de escrita por parte dos clientes]
 * @param  kv_descriptor [identificador do servidor]
 * @param  key           [chave]
 * @param  value         [valor]
 * @param  value_length  [tamanho do valor]
 * @param  overwrite     [se quer ou não fazer overwrite]
 * @return               [-1 em caso de erro 0 no caso de sucesso]
 */
int kv_write(int kv_descriptor, uint32_t key, char * value, int value_length, int overwrite);
/**
 * [kv_read operação leitura por parte do cliente]
 * @param  kv_descriptor [identificador do servidor]
 * @param  key           [chave]
 * @param  value         [valor]
 * @param  value_length  [tamanho para receber valor]
 * @return               [nr_bytes lidos ou -1,-2 em casos de erro]
 */
int kv_read(int kv_descriptor, uint32_t key, char * value, int value_length);
/**
 * [kv_delete Send to server an order to delete a entry identify by key]
 * @param kv_descriptor [identificador do servidor]
 * @param key           [chave]
 * @return [-1 case of error 0 on sucess]
 */
int kv_delete(int kv_descriptor, uint32_t key);
/**
 * [kv_close Termina a ligação entre cliente e servidor]
 * @param kv_descriptor [Indentificador do servidor]
 */
void kv_close(int kv_descriptor);
