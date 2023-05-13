#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "stack.h"
#include "AVL-tree.h"
#include "funciones_answer.h"

#define MAXLEN 30

struct Tarea{
    char* nombre;
    int check; //SI ESTA COMPLETADA 1 ; NO ESTA COMPLETADA 0
    Stack* stackAcc; //STACK CON ACCIONES
    TreeMap* prescendentes;
};

void mostrarOpciones(){
    printf("*********************************************************\n");
    printf("1. INGRESE 1 SI DESEA AGREGAR TAREA\n");
    printf("2. INGRESE 2 SI ESTABLECER PRECEDENCIA ENTRE TAREAS\n");
    printf("3. INGRESE 3 SI DESEA MOSTRAR TAREAS POR HACER\n");
    printf("4. INGRESE 4 SI DESEA MARCAR TAREA COMO COMPLETADA\n");
    printf("5. INGRESE 5 SI DESEA DESHACER ULTIMA ACCION\n");
    printf("6. INGRESE 6 SI DESEA CARGAR TAREAS DESDE UN ARCHIVO DE TEXTO\n");
    printf("7. INGRESE 0 SI DESEA SALIR\n");
    printf("*********************************************************\n\n");
}

void mostrarMenu(TreeMap* treeMap)
{
    int opcion;
    do {
        printf("\n");
        mostrarOpciones();
        scanf("%d", &opcion);
        switch (opcion) {
        case 1:
            printf("OPCION 1 INGRESADA\n\n");
            agregarTarea(treeMap);
            break;
        case 2:
            printf("OPCION 2 INGRESADA\n\n");
            establecerPrecedencia(treeMap);
            break;
        case 3:
            printf("OPCION 3 INGRESADA\n\n");
            break;
        case 4:
            printf("OPCION 4 INGRESADA\n\n");
            break;
        case 5:
            printf("OPCION 5 INGRESADA\n\n");
            break;
        case 6:
            printf("OPCION 6 INGRESADA\n\n");
            char nombre_archivoE[MAXLEN+1];
            printf("INGRESE NOMBRE DEL ARCHIVO\n");
            scanf("%s", nombre_archivoE);
            break;
        case 0:
            printf("CERRANDO EL PROGRAMA...\n");
        }
    } while (opcion != 0);
}


void* createTarea(char* nombre){
    
    Tarea* tarea = (Tarea *) malloc(sizeof(Tarea));
    tarea->nombre = nombre;
    tarea->prescendentes = (TreeMap *) malloc(sizeof(TreeMap));
    tarea->check = 0;
    tarea->stackAcc = createStack(3);
    return tarea;
}

void agregarTarea(TreeMap* treeMap)
{
    char nombre[MAXLEN + 1];
    do{
        printf("INGRESE NOMBRE DE LA TAREA A AGREGAR\n");
        scanf("%s",nombre);
        getchar();
    }while(strlen(nombre) > MAXLEN);

    char prioridad[6];
    do{
        printf("INGRESE PRIORIDAD DE LA TAREA %s\n",nombre);
        scanf("%s",prioridad);
    }while(strlen(prioridad) > 5);

    avlInsert(treeMap,prioridad,createTarea(nombre));
     
    return;
}

void establecerPrecedencia(TreeMap* treeMap)
{
    char tarea1[MAXLEN + 1];
    do{
        printf("INGRESE NOMBRE DE LA TAREA QUE DEBE REALIZARSE PRIMERO\n");
        scanf("%s",tarea1);
        getchar();
    }while(strlen(tarea1) > MAXLEN);
    
    if (avlGet(treeMap,tarea1)==NULL)
    {
        printf("LA TAREA %s NO SE ENCUENTRA EN LA BASE DE DATOS\n",tarea1);
        return;
    }
    
    char tarea2[MAXLEN + 1];
    do{
        printf("INGRESE NOMBRE DE LA TAREA QUE DEBE REALIZARSE DESPUES DE LA TAREA %s\n",tarea1);
        scanf("%s",tarea2);
        getchar();
    }while(strlen(tarea2) > MAXLEN);

    if (avlGet(treeMap,tarea2)==NULL)
    {
        printf("LA TAREA %s NO SE ENCUENTRA EN LA BASE DE DATOS\n",tarea1);
        return;
    }
    
}

