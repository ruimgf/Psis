
#define MESSAGE_LEN 1000
#define SOCK_ADDRESS "/tmp/sock_34"
typedef struct message{
    char buffer[MESSAGE_LEN];
    char socket_add[100];
} message;
