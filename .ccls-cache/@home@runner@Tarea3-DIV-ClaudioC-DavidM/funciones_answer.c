#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "arraylist.h"
#include "stack.h"
#include "hashmap.h"
#include "funciones_answer.h"

#define MAXLEN 30

struct Tarea{
    char* nombre;
    char** prescedentes;
    int check; // Si esta completa 1 ; No esta completa 0
    int cantPresce;
    int prioridad;
    Stack* stackAcc; //Stack con acciones
    int esPrecedente;//1=es precedente,0 =no es precedente
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

void mostrarMenu(HashMap* hashMap)
{
    int opcion;
    do {
        printf("\n");
        mostrarOpciones();
        scanf("%d", &opcion);
        switch (opcion) {
        case 1:
            printf("OPCION 1 INGRESADA\n\n");
            agregarTarea(hashMap);
            break;
        case 2:
            printf("OPCION 2 INGRESADA\n\n");
            establecerPrecedencia(hashMap);
            break;
        case 3:
            printf("OPCION 3 INGRESADA\n\n");
            mostrarTareasPendientes(hashMap);
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


void* createTarea(char* nombre, int prioridad){
    
    Tarea* tarea = (Tarea *) malloc(sizeof(Tarea));
    tarea->nombre = strdup(nombre);
    tarea->prioridad = prioridad;
    tarea->prescedentes = (char **) calloc(30, sizeof(char *));
    tarea->cantPresce = 0;
    tarea->check = 0;
    tarea->esPrecedente = 0;
    tarea->stackAcc = createStack(3);
    return tarea;
}

void agregarTarea(HashMap* hashMap)
{
    char nombre[MAXLEN + 1];
    do{
        printf("INGRESE NOMBRE DE LA TAREA A AGREGAR\n");
        scanf("%s",nombre);
        getchar();
    }while(strlen(nombre) > MAXLEN);

    int prioridad;
    do{
        printf("INGRESE PRIORIDAD DE LA TAREA %s\n",nombre);
        scanf("%d",&prioridad);
    }while(prioridad < 0);

    Tarea* tarea = createTarea(nombre, prioridad);
    insertMap(hashMap,tarea->nombre,tarea);
    pushBack(hashMap->arrayList,nombre,prioridad);
     
    return;
}

void establecerPrecedencia(HashMap* hashMap)
{
    char tarea1[MAXLEN + 1];
    do{
        printf("INGRESE NOMBRE DE LA TAREA QUE DEBE REALIZARSE PRIMERO\n");
        scanf("%s",tarea1);
        getchar();
    }while(strlen(tarea1) > MAXLEN);

    if (searchMap(hashMap,tarea1) == NULL) 
    {
        printf("LA TAREA %s NO SE ENCUENTRA EN LA BASE DE DATOS\n",tarea1);
        return;
    }
    
    char tarea2[MAXLEN + 1];
    do{
        printf("INGRESE NOMBRE DE LA TAREA QUE DEBE REALIZARSE DESPUES \n");
        scanf("%s",tarea2);
        getchar();
    }while(strlen(tarea2) > MAXLEN || strcmp(tarea1, tarea2) == 0);

    if (searchMap(hashMap,tarea2) == NULL) 
    {
        printf("LA TAREA %s NO SE ENCUENTRA EN LA BASE DE DATOS\n",tarea2);
        return;
    }

    Tarea* aux = (Tarea *) searchMap(hashMap,tarea2)->value;
    int indice = aux->cantPresce;
    aux->prescedentes[indice] = strdup(tarea1);
    (aux->cantPresce)++;
}
  

void mostrarTareasPendientes(HashMap *hashMap) {
    printf("TAREAS POR HACER, ORDENADAS POR PRIORIDAD Y PRECEDENCIA : \n\n");
    int cantTareas = ((ArrayList *) hashMap->arrayList)->size;
    int cont = 1;

    for(int k = 0 ; k < cantTareas ; k++) {
        char *tareaActual = (char *) ( (ArrayList *)hashMap->arrayList)->array[k].nombre;
        
        Tarea* tareaActualMapa = (Tarea *) searchMap(hashMap,tareaActual)->value;
        int totalPrecedentes = tareaActualMapa->cantPresce;
        
        for(int j = 0 ; j < totalPrecedentes ; j++) {//impresion de precedentes
            Tarea* tareaPrecedente = (Tarea *) searchMap(hashMap,tareaActualMapa->prescedentes[j])->value;
            tareaPrecedente->esPrecedente = 1;
            
            printf("%i. Tarea %s (Prioridad: %i)\n", cont, tareaActualMapa->prescedentes[j],tareaPrecedente->prioridad);
            cont++;
        }
        if (tareaActualMapa->esPrecedente == 0)printf("%i. Tarea %s (Prioridad: %i)",cont,tareaActual,tareaActualMapa->prioridad);
        
        if (totalPrecedentes != 0)
        {
            printf(" - Precedente/s:");
            for(int j = 0 ; j < totalPrecedentes ; j++) {
                
                printf(" Tarea %s",tareaActualMapa->prescedentes[j]);
            }
            printf("\n");
        }
        else printf("\n");
        cont++;
    }
}


