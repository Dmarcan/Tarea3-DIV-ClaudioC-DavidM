#ifndef Funciones_answer_h
#define Funciones_answer_h

//#include "stack.h"
#include "hashmap.h"

typedef struct Tarea Tarea;

void mostrarOpciones();

void mostrarMenu(HashMap * hashMap);

void *createTarea(char* nombre);

void agregarTarea(HashMap * hashMap);

void establecerPrecedencia(HashMap * hashMap);

void mostrarTareasPendientes(HashMap * hashMap);

#endif /* Funciones_answer_h */