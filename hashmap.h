#ifndef HashMap_h
#define HashMap_h

typedef struct HashMap HashMap;
typedef struct HashMap mapItem;

typedef struct Pair {
     char * key;
     void * value; 
} Pair;

typedef struct Duo {
    char * nombre;
    int * priority;
} Duo;

typedef struct Priority{
    long capacity;
    long size;
    long current;
    Duo* duo;
} Priority;

typedef struct parItems{
     char * key;
     void * value; 
} parItems;



struct HashMap {
    Pair** buckets;
    Priority* infoPriority;
    long size;
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

#endif /* HashMap_h */