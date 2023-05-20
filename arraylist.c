//#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

#include "arraylist.h"

ArrayList *createList(int capacity) {
  ArrayList *arrayList = (ArrayList *)malloc(sizeof(ArrayList));

  if (arrayList == NULL)
    return NULL;

  arrayList->array = (Duo *) calloc(5, sizeof(Duo));
  arrayList->size = 0;
  arrayList->capacity = capacity;
  arrayList->current = -1;

  return arrayList;
}

void pushBack(ArrayList * arrayList, char *nombre, int priority) {
  if (arrayList->size >= 0.70 * arrayList->capacity) {
    arrayList->capacity *= 2;
    arrayList->array = (Duo *) realloc(arrayList->array, sizeof(Duo) * (arrayList->capacity));

    
    if (arrayList->array == NULL) {
      printf("ERROR AL RESERVAR MEMORIA\n");
      return;
    }
    
  }

  int size = arrayList->size;
  arrayList->array[size].nombre = (char *)malloc(sizeof(char) * (strlen(nombre) + 1));
  strcpy(arrayList->array[size].nombre, nombre);
  arrayList->array[size].priority = priority;
  arrayList->size++;

  arrayList->current = arrayList->size - 1;

  qsort(arrayList->array, arrayList->size, sizeof(Duo), cmp);
}

Duo * first(ArrayList *arrayList) {
    if (arrayList->size == 0)
        return NULL;
    else {
        arrayList->current = 0;
        return &(arrayList->array[0]);
    }
}

Duo * next(ArrayList *arrayList) {
  if (arrayList->current >= arrayList->size - 1)
    return NULL;

  arrayList->current++;
  return &(arrayList->array[arrayList->current]);
}

int cmp(const void *elemento1, const void *elemento2) {
  const Duo *duo1 = (const Duo *)elemento1;
  const Duo *duo2 = (const Duo *)elemento2;

  if (duo1->priority < duo2->priority)
    return 0;
  if (duo1->priority > duo2->priority)
    return 1;
}

void delete(ArrayList * arrayList, char * key) {
    Duo* current = first(arrayList);

    int k = 0;
        
    while(current != NULL && strcmp(current->nombre,key) != 0) {
        current = next(arrayList);
        k++;
    }

    Duo * aux;
    for(int i = k ; i < arrayList->size - 1 ; i++) {
        aux = &(arrayList->array[i]);
        arrayList->array[i] = arrayList->array[i + 1];
        arrayList->array[i + 1] = *aux;
    }

    arrayList->size--;
}

/*
void search(arrayList * arrayList, char * key) {
    Duo* current = first(arrayList);

    int k = 0;
        
    while(current != NULL && strcmp(current->nombre,nombre)) {
        current = next(arrayList);
        k++;
    }
    
}
*/