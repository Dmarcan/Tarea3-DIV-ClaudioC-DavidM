#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "hashmap.h"
#include "arraylist.h"
#include "stack.h"

typedef struct HashMap HashMap;
int enlarge_called=0; 

struct HashMap {
    Pair** buckets;
    long size; // Tamaño ocupado de la tabla
    void* arrayList; // Tda
    long capacity; // Capacidad total de la tabla
    long current; // Ultimo accedido de la tabla
    Stack* stackAcc; //Stack con acciones
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

// funcion hash para obtener el indice
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
    enlarge_called = 1; // no borrar (testing purposes)
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
    
    map->arrayList = createList(3);
    map->stackAcc = createStack(3);
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

// Busca en el mapa segun la clave
Pair * searchMap(HashMap * map,  char * key) {  
    long indice = hash(key,map->capacity); 
    
    while (map->buckets[indice] != NULL) // Mapea por la clave
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

// Retorna el primer elemento del mapa
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

// Si hay tareas en el mapa retorna true, sino false
bool areTaskPresents(HashMap * map)
{
    if(map->size == 0) return false;
    return true;
}

// Retorna el tamaño del mapa
long sizeMap(HashMap * map)
{
    return map->size;
}

// Retorna la stack de ultimas acciones
Stack* returnStack(HashMap * map)
{
    return map->stackAcc;
}

// Retorna el arreglo que esta ordenado mediante prioridad
ArrayList* returnArray(HashMap * map)
{
    return map->arrayList;
}