#ifndef stack_h
#define stack_h
typedef struct Stack Stack;
typedef struct Info Info;

struct Info{
    int accion; // Numero funcion
    char * valorAccion; // Nombre tarea1
    char * cambio; // Nombre tarea2 o null
};

/*
    OPCION 1:
    valorAccion = nombre tarea1
    cambio = NULL
    
    OPCION 2
    valorAccion = nombre de la tarea1
    cambio = nombre de la tarea2
    
    OPCION 4
    valorAccion = nombre de la tarea que fue marcada como completada
    cambio = NULL

*/

Stack * createStack(int capacity);

void initializeStack(Stack * stack);

int isStackEmpty(Stack * stack);

int isStackFull(Stack * stack);

void push(Stack* stack, int action, char* actionValue, char * actionValue2);

Info * pop(Stack * stack);

#endif /* stack_h */