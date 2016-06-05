#include <stdint.h>

#define DEBUG 1
#define SOCK_ADDRESS "127.0.0.1"
#define WRITE 1
#define READ 2
#define DELETE 3
#define  MAX_CLIENT_WAIT 20

typedef struct message{
    int operation;
    unsigned int key;
    int value_length;
}message;

int kv_connect(char * kv_server_ip, int kv_server_port);
int kv_write(int kv_descriptor, uint32_t key, char * value, int value_length);
int kv_read(int kv_descriptor, uint32_t key, char * value, int value_length);
int kv_delete(int kv_descriptor, uint32_t key);
