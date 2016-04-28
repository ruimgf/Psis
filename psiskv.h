#include <stdint.h>

#define DEBUG 0
#define SOCK_ADDRESS "127.0.0.1"
#define WRITE 1
#define OVERWRITE 2
#define READ 3
#define DELETE 4
#define WRITE_OK 5
#define READ_OK 6
#define DELETE_OK 7
#define EXIT 8


#define  MAX_CLIENT_WAIT 20

typedef struct message{
    int operation;
    unsigned int key;
    int value_length;
    int info;
}message;

int kv_connect(char * kv_server_ip, int kv_server_port);
int kv_write(int kv_descriptor, uint32_t key, char * value, int value_length, int overwrite);
int kv_read(int kv_descriptor, uint32_t key, char * value, int value_length);
int kv_delete(int kv_descriptor, uint32_t key);
void kv_close(int kv_descriptor);
