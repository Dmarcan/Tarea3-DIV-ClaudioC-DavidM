#ifndef HashMap_h
#define HashMap_h

#include <stdbool.h>

#include "stack.h"
#include "arraylist.h"

typedef struct HashMap HashMap;

typedef struct Pair {
     char * key; // Almacena la clave de la tarea
     void * value; 
} Pair;

HashMap * createMap(long capacity);

void insertMap(HashMap * table, char * key, void * value);

void eraseMap(HashMap * table, char * key);

Pair * searchMap(HashMap * table, char * key);

Pair * firstMap(HashMap * table);

Pair * nextMap(HashMap * table);

void enlarge(HashMap * map);

bool areTaskPresents(HashMap * map);

long sizeMap(HashMap * map);

Stack* returnStack(HashMap * map);

ArrayList* returnArray(HashMap * map);

#endif /* HashMap_h */