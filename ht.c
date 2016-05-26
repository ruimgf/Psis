#include "ht.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/** First element of list is only a pointer**/
/**
 * [creat_list Cria uma nova Lista]
 * @return [description]
 */
item_t * creat_list(){
    return NULL;
}
/**
 * [insert_end_list insere no fim da lista]
 * @param  begin     [Inicio da Lista]
 * @param  key       [chave]
 * @param  value     [valor]
 * @param  overwrite [1 para fazer overwrite 0 para não fazer overwrite ]
 * @return           [0 em caso de sucesso -1 em caso de erro]
 */
int insert_end_list(item_t * begin, unsigned int key,char * value,int overwrite)
{
  item_t * aux;
  item_t * new;
  //procura se a key ja existe

  aux = search_key_on_list(begin,key);
  //se encontrou essa key
  if(aux!=NULL)
  {
    if(overwrite==1)
    {
      //aux->value=value;
      free(aux->value);
      aux->value = (char *) malloc(sizeof(char)*(strlen(value) + 1));
      sprintf(aux->value,"%s",value);
      return 0; //fez overwrite
    }else{
      return -2;

    }
  }
  //se nao encontrou a key vai criar o novo
  else
  {
    aux=begin;

    while(aux->next!=NULL){
      aux=aux->next;
    }

    new = (item_t *) malloc(sizeof(item_t));
    new->key  = key;
    new->value = (char *) malloc(sizeof(char)*(strlen(value) + 1));
    new->next = NULL;
    sprintf(new->value,"%s",value);

    aux->next = new;


    return 0; //criou um novo e inseriu
  }
  return -1; //se nao inseriu nem fez overwrite

}
/**
 * [search_key_on_list procura por uma key na lista]
 * @param  begin [inicio da lista]
 * @param  key   [chave a procurar]
 * @return       [NULL em caso de erro ou o endereço da estrutura correspondente caso exista]
 */
item_t *  search_key_on_list(item_t * begin, unsigned int key){

     item_t * aux;
     item_t * new;

     if(begin->next==NULL){
       return NULL;
     }
     aux = begin;
     while (aux!=NULL) {
       if(aux->key == key){
         return aux;
       }
       aux = aux->next;
     }

     return aux;

}
/**
 * [delete_entry apaga uma entrada da lista]
 * @param  begin [inicio da lista]
 * @param  key   [chave]
 * @return       [-1 em caso de erro 0 em caso de sucesso]
 */
int delete_entry(item_t * begin, unsigned int key)
{
    item_t * aux1 = begin->next;

    item_t * aux2;

    if(aux1==NULL){
        return -1;//se nao tem nada nao pode fazer DELETEe de nada
    }else{
      if(aux1->key == key){
        begin->next = aux1->next;
        free(aux1->value);
        free(aux1);
        return 0;
      }


    }

    aux2 = aux1->next;

    while(aux2!=NULL)
    {
        if(aux2->key == key){
          aux1->next = aux2->next;

          free(aux2->value);
          free(aux2);
          return 0;
        }
        aux1=aux1->next;
        aux2=aux2->next;
    }

    return -1;
}

/**
 * [delete_list Apaga uma lista]
 * @param begin [inicio da lista]
 */
void delete_list(item_t * begin){

    item_t * aux1 = begin->next;
    begin->next = NULL;
    item_t * aux2;
    if(aux1 == NULL){
        return;
    }

    while(aux1!=NULL){
      aux2 = aux1->next;
      free(aux1->value);
      free(aux1);
      aux1=aux2;
    }
}
/**
 * [print_list imprime lista]
 * @param begin [inicio da lista]
 */
void print_list(item_t * begin){
    item_t * aux = begin->next;

    while(aux!=NULL){
      printf("key : %u value : %s \n", aux->key,aux->value);
      aux=aux->next;
    }
}
/**
 * [ht_create cria uma nova hashtable]
 * @param  line_nr [nr de linhas da hashtable]
 * @return         [NULL em caso de erro ou o endereço da estrutura]
 */
hashtable_t * ht_create( int line_nr ) {

	hashtable_t * hashtable = NULL;
	int i;

	if( line_nr < 1 ) return NULL;

	/* Allocate the table itself. */
	if( ( hashtable = malloc( sizeof( hashtable_t ) ) ) == NULL ) {
		return NULL;
	}

	/* Allocate pointers to the head nodes. */
	if( ( hashtable->table = malloc( sizeof( item_t * ) * line_nr ) ) == NULL ) {
		return NULL;
	}
	for( i = 0; i < line_nr; i++ ) {
		hashtable->table[i] = malloc( sizeof( item_t ) * line_nr );
    hashtable->table[i]->value = NULL;
    hashtable->table[i]->next = NULL;
  }

	hashtable->line_nr = line_nr;

	return hashtable;
}
/**
 * [ht_hash procura qual o indice da lista de uma determinada key]
 * @param  hashtable [pointer para a hashtable]
 * @param  key       [chave a pesquisar]
 * @return           [indice da chave]
 */
int ht_hash( hashtable_t * hashtable, unsigned int key ) {
	return key % hashtable->line_nr;
}
/**
 * [ht_set modifica uma entrada ou insere de novo na hashtable]
 * @param  hashtable [ponteiro para a hashtable]
 * @param  key       [chave]
 * @param  value     [valor]
 * @param  overwrite [1 para overwrite 0 para não overwrite]
 * @return           [-1 em caso de erro 0 em successo]
 */
int ht_set( hashtable_t *hashtable, unsigned int key, char *value, int overwrite ) {
	int bin = 0;
  item_t * next;
	bin = ht_hash( hashtable, key );

	next = hashtable->table[ bin ];

  return insert_end_list(next,key,value,overwrite);

}
/**
 * [ht_remove remove uma entrada da hashtable]
 * @param  hashtable [ponteiro para hashtable]
 * @param  key       [chave]
 * @return           [description]
 */
int ht_remove( hashtable_t *hashtable, unsigned int key) {
	int bin = 0;
  item_t * next;
	bin = ht_hash( hashtable, key );
  next = hashtable->table[bin];
	return delete_entry(next,key);

}
/**
 * [ht_get procura uma key na hashtable]
 * @param  hashtable [ponteiro inio da hashtable]
 * @param  key       [chave]
 * @return           [NULL em caso de erro ou o endereço do inico da chave]
 */
char * ht_get( hashtable_t *hashtable, unsigned int key ) {
	int bin = 0;
	item_t *pair;
	/* Step through the bin, looking for our value. */
  bin = ht_hash( hashtable, key );

  pair = search_key_on_list(hashtable->table[ bin ],key);
	if(pair!= NULL){
    return pair->value;
  }else{
    return NULL;
  }

}
