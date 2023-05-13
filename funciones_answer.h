#ifndef Funciones_answer_h
#define Funciones_answer_h

#include "stack.h"
#include "AVL-tree.h"

typedef struct Tarea Tarea;

void mostrarOpciones();

void mostrarMenu(TreeMap* treeMap);

void *createTarea(char* nombre);

void agregarTarea(TreeMap* treeMap);

void establecerPrecedencia(TreeMap* treeMap);

#endif /* Funciones_answer_h */