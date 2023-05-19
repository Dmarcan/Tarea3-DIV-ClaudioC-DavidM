#ifndef Funciones_answer_h
#define Funciones_answer_h

#include "hashmap.h"
#include "stack.h"

typedef struct Tarea Tarea;

void mostrarOpciones();

void mostrarMenu(HashMap* hashMap);

void *createTarea(char* nombre, int prioridad);

void agregarTarea(HashMap * hashMap);

void establecerPrecedencia(HashMap * hashMap);

void mostrarTareasPendientes(HashMap * hashMap);

void marcarTarea(HashMap * hashMap);

void deshacerUltimaAccion(HashMap * hashMap);

void importarArchivoCSV(char* nombre_archivo, HashMap* map);

void quitarTarea(HashMap * hashMap, char * valorAccion, int prioridad);

void quitarPrecedencia(HashMap * hashMap, Tarea * tarea, char * tarea1, char * precedente);

void quitarMarcarTarea(Tarea * tarea);



#endif /* Funciones_answer_h */