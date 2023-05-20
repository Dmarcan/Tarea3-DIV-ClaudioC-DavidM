#ifndef arrayList_h
#define arrayList_h

typedef struct Duo {
    char * nombre; // Nombre de la tarea
    int  priority; // Prioridad de la tarea
} Duo;

typedef struct Priority{
    long capacity; // Capacidad del arreglo
    long size; // Tamaño ocupado del arreglo
    long current; // Ultimo elemento accedido
    Duo* array; // Arreglo de tipo Duo
} ArrayList;


ArrayList * createList(int capacity);

void pushBack(ArrayList * arrayList, char * nombre, int priority);

Duo * first(ArrayList * arrayList);

Duo * next(ArrayList * arrayList);

int cmp(const void* elemento1, const void* elemento2);

void delete(ArrayList * arrayList, char * key);

#endif /* arrayList_h */