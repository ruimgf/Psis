

typedef struct item_s{
    unsigned int key;
    char * value;
    struct item_s * next;
}item_t;

typedef struct hashtable_s {

      int line_nr;
      struct item_s ** table;

}hashtable_t;
/** First element of list is only a pointer**/
/**
 * [creat_list Cria uma nova Lista]
 * @return [description]
 */
item_t * creat_list();
/**
 * [insert_end_list insere no fim da lista]
 * @param  begin     [Inicio da Lista]
 * @param  key       [chave]
 * @param  value     [valor]
 * @param  overwrite [1 para fazer overwrite 0 para não fazer overwrite ]
 * @return           [0 em caso de sucesso -1 em caso de erro]
 */
int insert_end_list(item_t  * begin, unsigned int key,char * value,int overwrite);
item_t *  search_key_on_list(item_t * begin, unsigned int key);
/**
 * [delete_list Apaga uma lista]
 * @param begin [inicio da lista]
 */
void delete_list(item_t * begin);
/**
 * [print_list imprime lista]
 * @param begin [inicio da lista]
 */
void print_list(item_t * begin);
/**
 * [delete_entry apaga uma entrada da lista]
 * @param  begin [inicio da lista]
 * @param  key   [chave]
 * @return       [-1 em caso de erro 0 em caso de sucesso]
 */
int delete_entry(item_t * begin, unsigned int key);
/**
 * [ht_create cria uma nova hashtable]
 * @param  line_nr [nr de linhas da hashtable]
 * @return         [NULL em caso de erro ou o endereço da estrutura]
 */
hashtable_t * ht_create( int line_nr );
/**
 * [ht_hash procura qual o indice da lista de uma determinada key]
 * @param  hashtable [pointer para a hashtable]
 * @param  key       [chave a pesquisar]
 * @return           [indice da chave]
 */
int ht_hash( hashtable_t * hashtable, unsigned int key );
/**
 * [ht_set modifica uma entrada ou insere de novo na hashtable]
 * @param  hashtable [ponteiro para a hashtable]
 * @param  key       [chave]
 * @param  value     [valor]
 * @param  overwrite [1 para overwrite 0 para não overwrite]
 * @return           [-1 em caso de erro 0 em successo]
 */
int ht_set( hashtable_t *hashtable, unsigned int key, char *value, int overwrite );
/**
 * [ht_get procura uma key na hashtable]
 * @param  hashtable [ponteiro inio da hashtable]
 * @param  key       [chave]
 * @return           [NULL em caso de erro ou o endereço do inico da chave]
 */
char * ht_get( hashtable_t *hashtable, unsigned int key );
/**
 * [ht_remove remove uma entrada da hashtable]
 * @param  hashtable [ponteiro para hashtable]
 * @param  key       [chave]
 * @return           [description]
 */
int ht_remove( hashtable_t *hashtable, unsigned int key);
