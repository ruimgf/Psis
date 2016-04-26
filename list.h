
typedef struct item1{
    unsigned int key;
    char * value;
    struct item1 * next;
}item;

item * creat_list();
int insert_begin_list(item * *begin, unsigned int key,char * value,int overwrite);
item *  search_key_on_list(item * begin, unsigned int key);
void delete_list(item * begin);
void print_list(item * begin);
int delete_entry(item * *begin, unsigned int key);
