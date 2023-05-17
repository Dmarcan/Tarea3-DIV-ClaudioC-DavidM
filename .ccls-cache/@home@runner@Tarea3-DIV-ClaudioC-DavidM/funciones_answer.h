#ifndef Funciones_answer_h
#define Funciones_answer_h

#include "hashmap.h"

typedef struct Tarea Tarea;

void mostrarOpciones();

void mostrarMenu(HashMap * hashMap);

void *createTarea(char* nombre, int prioridad);

void agregarTarea(HashMap * hashMap);

void establecerPrecedencia(HashMap * hashMap);

void mostrarTareasPendientes(HashMap * hashMap);

#endif /* Funciones_answer_h */