#ifndef arrayList_h
#define arrayList_h

typedef struct Duo {
    char * nombre;
    int  priority;
} Duo;

typedef struct Priority{
    long capacity;
    long size;
    long current;
    Duo* array;
} ArrayList;


ArrayList * createList(int capacity);

void pushBack(ArrayList * arrayList, char * nombre, int priority);

void first(ArrayList * arrayList);

void next(ArrayList * arrayList);

int cmp(const void* elemento1, const void* elemento2);

#endif /* arrayList_h */