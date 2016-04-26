#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/** First element of list is only a pointer**/

item * creat_list(){
    //item * begin;
    //begin = (item *) malloc(sizeof(item));
    //begin->next = NULL
    return NULL;
}

int insert_begin_list(item * *begin, unsigned int key,char * value,int overwrite)
{
  item * aux = begin;
  item * new;
  //procura se a key ja existe
  while(aux->key!=key)
    aux=aux->seg;
  //se encontrou essa key
  if(aux->key==key)
  {
    if(overwrite==1)
    {
      aux->value=value;
      return 2; //fez overwrite
    }
  }
  //se nao encontrou a key vai criar o novo
  else
  {
    aux=begin;
    new = (item *) malloc(sizeof(item));
    new->key  = key;
    new->value = (char *) malloc(sizeof(value));
    strcpy(new->value, value);
    new->next = aux;
    *begin=new;
    return 1; //criou um novo e inseriu
  }
  return 0; //se nao inseriu nem fez overwrite
}

item *  search_key_on_list(item * begin, unsigned int key){

     item * aux;
     item * new;

     if(begin==NULL){
       return NULL;
     }
     aux = begin;
     while (aux!=NULL) {
       if(aux->key == key){
         return aux;
       }
       aux = aux->next;
     }

     return begin;

}

int delete_entry(item * *begin, int id)
{
    item * aux1 = begin;
    item * aux2 = aux->seg;
    if(aux1=NULL)
        return 0;//se nao tem nada nao pode fazer DELETEe de nada
    if(aux1->value==id)
    {
      *begin=aux2;
      free(aux1->value);
      free(aux1);
      return 1; //fez delete
    }
    while(aux2->value!=id)
    {
        aux1=aux1->seg;
        aux2=aux2->seg;
    }
    aux1->seg=aux2->seg;
    free(aux2->value);
    free(aux2);
    return 1; // fez delete
}


void delete_list(item * begin){

    item * aux1 = begin;
    item * aux2;
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

void print_list(item * begin){
    item * aux = begin;

    while(aux!=NULL){
      printf("key : %d value : %s \n", aux->key,aux->value);
      aux=aux->next;
    }
}
