#ifndef stack_h
#define stack_h
typedef struct Stack Stack;
typedef struct Info Info;

struct Info{
    int accion; // Numero funcion
    char * actionValue1; // Nombre tarea1
    char * actionValue2; // Nombre tarea2 o null
};

/*
    OPCION 1:
    actionValue1 = nombre tarea1
    actionValue2 = NULL
    
    OPCION 2
    actionValue1 = nombre de la tarea1
    actionValue2 = nombre de la tarea2
    
    OPCION 4
    actionValue1 = nombre de la tarea que fue marcada como completada
    actionValue2 = NULL

*/

Stack * createStack(int capacity);

void initializeStack(Stack * stack);

int isStackEmpty(Stack * stack);

int isStackFull(Stack * stack);

void push(Stack* stack, int action, char* actionValue, char * actionValue2);

Info * pop(Stack * stack);

#endif /* stack_h */