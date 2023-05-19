#ifndef stack_h
#define stack_h
typedef struct Stack Stack;
typedef struct Info Info;

/*
    OPCION 1:
    valorAccion = nombre de la tarea agregada
    cambio = nombre de la tarea agregada
    
    OPCION 2
    valorAccion = nombre de la tarea1
    cambio = nombre de la tarea2
    OPCION 4
    valorAccion = nombre de la tarea agregada
    cambio = nombre de la tarea agregada

*/


struct Info{
    int accion; //numero funcion
    char * valorAccion; //nombre de la tarea
    char * cambio; // que cambio hago
};

Stack * createStack(int capacity);

void initializeStack(Stack * stack);

int isStackEmpty(Stack * stack);

int isStackFull(Stack * stack);

void push(Stack* stack, int action, char* actionValue, char * actionValue2);

Info * pop(Stack * stack);

#endif /* stack_h */