#ifndef stack_h
#define stack_h
typedef struct Stack Stack;
typedef struct Info Info;

struct Info{
    int accion;
    char * valorAccion;
};

Stack * createStack(int capacity);

void initializeStack(Stack * stack);

int isStackEmpty(Stack * stack);

int isStackFull(Stack * stack);

void push(Stack* stack, int accion, char* valorAccion);

Info * pop(Stack * stack);

#endif /* stack_h */