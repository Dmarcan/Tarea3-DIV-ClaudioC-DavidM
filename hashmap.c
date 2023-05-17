#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "hashmap.h"

typedef struct HashMap HashMap;
//typedef struct HashMap mapItem;
int enlarge_called=0; 


struct mapItem {
    parItems** buckets;
    long size;
    long capacity; 
    long current; 
};


/*
struct HashMap {
    Pair** buckets;
    Priority* infoPriority;
    long size;
    long capacity; 
    long current; 
};
*/

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash % capacity;
}

int is_equal(void* key1, void* key2){
    if(key1 == NULL || key2 == NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}

void insertInfo(HashMap * map, char * nombre, int priority)
{
    Priority* aux  = map->infoPriority;
    if (aux->size >= 0.70 * aux->capacity)
    {
        aux->capacity *= 2;
        aux->duo = (Duo *) realloc(aux->duo, sizeof(Duo) * aux->capacity);
    }

    aux->duo[aux->size].nombre = (char **) malloc(sizeof(char*) * 31);
    strcpy(aux->duo[aux->size].nombre, nombre);
    aux->duo[aux->current].priority = priority;
    aux->size++;
    
}


void insertMap(HashMap * map, char * key, void * value) {
    if (map->size >= 0.70 * map->capacity)
        enlarge(map);
    
    long indice = hash(key,map->capacity);
    
    while (map->buckets[indice]!=NULL && map->buckets[indice]->key!=NULL)
    {
        if (is_equal(key,map->buckets[indice]->key)==1)return;
        indice=(indice+1) % map->capacity;    
    }
    
    map->buckets[indice] = createPair(key,value);
    map->current=indice;
    map->size++;
    return;
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)
    Pair** aux = map->buckets;
    long sizeAux = map->capacity;
    map->capacity *= 2;
    map->buckets = (Pair **) calloc(map->capacity,sizeof(Pair *));
    
    if (map->buckets == NULL) exit(EXIT_FAILURE);
    map->size = 0;
    
    for (long k = 0 ; k < sizeAux ; k++)
    {
        if (aux[k] !=NULL && aux[k]->key != NULL)
            insertMap(map,aux[k]->key,aux[k]->value); 
    }
    free(aux); 
}


HashMap * createMap(long capacity) {
    HashMap *map = (HashMap *) malloc(sizeof(HashMap));
    if (map == NULL) return NULL;
    
    map->buckets = (Pair **) calloc(capacity,sizeof(Pair *));
    
    if (map->buckets == NULL) return NULL;

    
    map->infoPriority = (Priority *) malloc(sizeof(Priority));
    if (map->infoPriority == NULL) return NULL;
    map->infoPriority->duo = (Duo *) calloc(5, sizeof(Duo));
    map->infoPriority->size = 0;
    map->infoPriority->capacity = 5;
    map->infoPriority->current = -1;
    
    map->size = 0;
    map->capacity = capacity;
    map->current = -1;
    return map;
}

void eraseMap(HashMap * map,  char * key) {    
    if (searchMap(map,key) != NULL)
    {
        map->buckets[map->current]->key = NULL;
        map->size--;
        return;
    }
}

Pair * searchMap(HashMap * map,  char * key) {  
    long indice = hash(key,map->capacity);
    
    while (map->buckets[indice]!=NULL)
    {
        if (is_equal(key,map->buckets[indice]->key))
        {
            map->current=indice;
            return map->buckets[indice];
        }
        indice=(indice+1) % map->capacity;    
    }
    return NULL;
}

Pair * firstMap(HashMap * map) {
    for (size_t k = 0;k < map->capacity ; k++)
    {
        if (map->buckets[k] != NULL && map->buckets[k]->key != NULL)
        {
            map->current = k;
            return map->buckets[k];
        }
    }
    return NULL;
    
}

Pair * nextMap(HashMap * map) {
    for (size_t k=map->current+1;k<map->capacity;k++)
    {
        if (map->buckets[k] != NULL && map->buckets[k]->key != NULL)
        {
            map->current=k;
            return map->buckets[k];
        }
    }
    return NULL;

}

bool areTaskPresents(HashMap * map)
{
    if(map->size == 0) return false;
    return true;
}

long sizeMap(HashMap * map)
{
    return map->size;
}