#ifndef HashMap_h
#define HashMap_h

typedef struct HashMap mapTareasPrece;

typedef struct parMap {
     char * key;
     void * value; 
} parMap;



HashMap * createMap(long capacity);

void insertMap(HashMap * table, char * key, void * value);

void eraseMap(HashMap * table, char * key);

Pair * searchMap(HashMap * table, char * key);

Pair * firstMap(HashMap * table);

Pair * nextMap(HashMap * table);

void enlarge(HashMap * map);

bool existenJugadores(HashMap * map);

long sizeMap(HashMap * map);

#endif /* HashMap_h */