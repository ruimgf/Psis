
typedef struct item_s{
    unsigned int key;
    char * value;
    struct item_s * next;
}item_t;

typedef struct hashtable_s {

      int line_nr;
      struct item_s ** table;

}hashtable_t;

item_t * creat_list();
int insert_begin_list(item_t  * begin, unsigned int key,char * value,int overwrite);
item_t *  search_key_on_list(item_t * begin, unsigned int key);
void delete_list(item_t * begin);
void print_list(item_t * begin);
int delete_entry(item_t * begin, unsigned int key);
hashtable_t * ht_create( int line_nr );
int ht_hash( hashtable_t * hashtable, unsigned int key );
void ht_set( hashtable_t *hashtable, unsigned int key, char *value, int overwrite );
char * ht_get( hashtable_t *hashtable, unsigned int key );
void ht_remove( hashtable_t *hashtable, unsigned int key);
