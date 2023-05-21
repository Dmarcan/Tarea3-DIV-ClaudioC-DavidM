#ifndef arrayList_h
#define arrayList_h

typedef struct ArrayList ArrayList;

typedef struct Duo {
    char * nombre; // Nombre de la tarea
    int  priority; // Prioridad de la tarea
} Duo;

ArrayList * createList(int capacity);

void pushBack(ArrayList * arrayList, char * nombre, int priority);

Duo * first(ArrayList * arrayList);

Duo * next(ArrayList * arrayList);

int cmp(const void* elemento1, const void* elemento2);

void deleteArray(ArrayList * arrayList, char * key);

#endif /* arrayList_h */