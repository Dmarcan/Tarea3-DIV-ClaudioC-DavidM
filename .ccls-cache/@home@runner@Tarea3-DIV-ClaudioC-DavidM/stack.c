#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "stack.h"
#define MAXLEN 30

struct Stack{
    int top;
    int capac;
    Info** acciones;
};

Stack * createStack(int capacity) {
    Stack * stack = (Stack*)malloc(sizeof(Stack));
    stack->top = -1;
    stack->capac = capacity;
    stack->acciones = (Info**) malloc(stack->capac * sizeof(Info*));
    if (stack->acciones == NULL) {
        printf("NO HAY SUFICIENTE ESPACIO PARA LA PILA\n");
        exit(EXIT_FAILURE);
    }
    return stack;
}

void initializeStack(Stack * stack) {
    stack->top = -1;
}

int isStackEmpty(Stack * stack) {
    return (stack->top == -1);
}

int isStackFull(Stack * stack) {
    return (stack->top == stack->capac - 1);
}

void push(Stack* stack, int action, char* actionValue) {
    if (stack->top == stack->capac -1 ) {
        stack->capac *= 2;
        stack->acciones = (Info**) realloc(stack->acciones, sizeof(Info*) * stack->capac);
        if (stack->acciones == NULL) {
            printf("ERROR AL ASIGNAR MEMORIA AL STACK.\n");
            exit(1);
        }
    }
    Info* info = (Info*)malloc(sizeof(Info));
    if (info == NULL) {
        printf("ERROR AL ASIGNAR MEMORIA.\n");
        exit(1);
    }
    info->accion = action;
    info->valorAccion = (char *) malloc(sizeof(char)* MAXLEN + 1);
    strcpy(info->valorAccion,actionValue);
    stack->top++;
    stack->acciones[stack->top] = info;
}

Info * pop(Stack * stack) {
    if (isStackEmpty(stack)) {
        printf("Error: stack underflow\n");
        return NULL;
    }
    Info * info = stack->acciones[stack->top];
    stack->top--;
    return info;
}