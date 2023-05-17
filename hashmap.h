#ifndef HashMap_h
#define HashMap_h
#include "stdbool.h"
typedef struct HashMap HashMap;
typedef struct HashMap mapItem;

typedef struct Pair {
     char * key;
     void * value; 
} Pair;

typedef struct parItems{
     char * key;
     void * value; 
} parItems;

struct HashMap {
    Pair** buckets;
    long size;
    void* arrayList;
    long capacity; 
    long current; 
};

HashMap * createMap(long capacity);

void insertInfo(HashMap * map, char * nombre, int priority);

void insertMap(HashMap * table, char * key, void * value);

void eraseMap(HashMap * table, char * key);

Pair * searchMap(HashMap * table, char * key);

Pair * firstMap(HashMap * table);

Pair * nextMap(HashMap * table);

void enlarge(HashMap * map);

bool areTaskPresents(HashMap * map);

long sizeMap(HashMap * map);

//void insertArray(HashMap * map, void *)

#endif /* HashMap_h */