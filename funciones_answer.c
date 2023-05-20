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
    int esPrecedente; // 1 = es precedente, 0 = no es precedente
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
            marcarTarea(hashMap);
            break;
        case 5:
            printf("OPCION 5 INGRESADA\n\n");
            deshacerUltimaAccion(hashMap);
            break;
        case 6:
            printf("OPCION 6 INGRESADA\n\n");
            char nombre_archivoE[MAXLEN+1];
            printf("INGRESE NOMBRE DEL ARCHIVO\n");
            scanf("%s", nombre_archivoE);
            importarArchivoCSV(nombre_archivoE,hashMap);
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
    return tarea;
}

void agregarTarea(HashMap * hashMap)
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
    push(hashMap->stackAcc,1,nombre,NULL);
    
    return;
}

void establecerPrecedencia(HashMap * hashMap)
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

    push(hashMap->stackAcc,2,tarea1,tarea2);
}
  
void mostrarTareasPendientes(HashMap *hashMap) {
    printf("TAREAS POR HACER, ORDENADAS POR PRIORIDAD Y PRECEDENCIA : \n\n");
    
    int cantTareas = ((ArrayList *) hashMap->arrayList)->size;
    int cont = 1;
    int contCompletados=0;

    for(int k = 0 ; k < cantTareas ; k++) {
        char *tareaActual = (char *) ( (ArrayList *)hashMap->arrayList)->array[k].nombre;
        
        Tarea* tareaActualMapa = (Tarea *) searchMap(hashMap,tareaActual)->value;
        if (tareaActualMapa->check==1)continue;
        int totalPrecedentes = tareaActualMapa->cantPresce;
        
        for(int j = 0 ; j < totalPrecedentes ; j++) { //impresion de precedentes
            Tarea* tareaPrecedente = (Tarea *) searchMap(hashMap,tareaActualMapa->prescedentes[j])->value;
            tareaPrecedente->esPrecedente = 1;
            if (tareaPrecedente->check==0)
            {
                printf("%i. Tarea %s (Prioridad: %i)\n", cont, tareaActualMapa->prescedentes[j],tareaPrecedente->prioridad);
                cont++;
                
            }
            else contCompletados++;
        }
        if (tareaActualMapa->esPrecedente == 0)
        {
            printf("%i. Tarea %s (Prioridad: %i)",cont,tareaActual,tareaActualMapa->prioridad);
            cont++;
        }
        //si el total de presedentes de esta tarea es igual a el contcompletados quiere decir que todos sus presedentes estan marcados como completados
        //entonces no los muestra
        if (contCompletados!=tareaActualMapa->cantPresce)
        {
            if (totalPrecedentes != 0) {
            printf(" - Precedente/s:");
            for(int j = 0 ; j < totalPrecedentes ; j++) {
                
                printf(" Tarea %s",tareaActualMapa->prescedentes[j]);
            }
            printf("\n");
            }
            else printf("\n");
        }
        else printf("\n");
    }
    if (cont==1)printf("NO EXISTEN TAREAS ");
}

void marcarTarea(HashMap * hashMap) {
    char tarea1[MAXLEN + 1];
    do{
        printf("INGRESE NOMBRE DE LA TAREA QUE ESTA COMPLETADA\n");
        scanf("%s",tarea1);
        getchar();
    }while(strlen(tarea1) > MAXLEN);
    Pair* current=searchMap(hashMap,tarea1);
    if (current==NULL)
    {
        printf("LA TAREA %s AUN NO SE HA INGRESADO",tarea1);
        return;
    }
    Tarea* aux =current->value;
    
    if (aux->esPrecedente == 1 || aux->cantPresce>0)//codigo que pregunta confirmacion del usuario
    {
        printf("¿ESTAS SEGURO QUE DESEA ELIMINAR LA TAREA %s?(S/N)\n",tarea1);
        char respuesta[MAXLEN + 1];
        do{
            scanf("%s",respuesta);
            getchar();
            if (strcmp(respuesta,"S")==0)
            {
                aux->check = 1;
                push(hashMap->stackAcc,4,tarea1,NULL);
                printf("LA TAREA %s HA SIDO ELIINADA\n",tarea1);
                return;
            }
            else if (strcmp(respuesta,"N")==0)return;
        } while (strlen(respuesta) > MAXLEN || (strcmp(respuesta, "N") != 0 && strcmp(respuesta, "S") != 0));
    }
    
    aux->check = 1;
    push(hashMap->stackAcc,4,tarea1,NULL);
    printf("LA TAREA %s HA SIDO ELIINADA\n",tarea1);
}

void deshacerUltimaAccion(HashMap * hashMap) {
    if(!areTaskPresents(hashMap))
    {
        printf("NO EXISTEN TAREAS GUARDADAS\n");
        return;
    }
    Info* elemen = pop(hashMap->stackAcc);
    int opcion = elemen->accion;
    
    char* valorAccion = elemen->valorAccion; 
    
    if (opcion == -1){
        printf("NO HAY ULTIMA ACCION REGISTRADA\n");
        return;
    }
    
    Tarea* tarea = (Tarea *) searchMap(hashMap,valorAccion)->value;//tarea1
    
    switch(opcion)
    {   
        case 1:
            quitarTarea(hashMap,valorAccion,tarea->prioridad);
            break;
        case 2:
            quitarPrecedencia(hashMap,tarea,valorAccion,elemen->cambio);
            /*
            printf("");
            char* cambio = elemen->cambio;
            Tarea* anteriorPrece = (Tarea *) searchMap(hashMap,cambio)->value; // tarea2
            anteriorPrece->cantPresce--;
            tarea->esPrecedente = 0;
            
            printf("LA TAREA %s  YA NO ES PRECEDENTE DE LA TAREA %s\n",tarea->nombre,anteriorPrece->nombre);
            */ 
            break;
        case 4:
            quitarMarcarTarea(tarea);
            break;
        default:
            printf("LA OPCION INGRESADA NO SE PUEDE DESHACER\n");
    }
}

void quitarTarea(HashMap * hashMap, char * valorAccion, int prioridad) {
    eraseMap(hashMap,valorAccion);
    delete(hashMap->arrayList,valorAccion);

    printf("LA TAREA %s CON PRIORIDAD %i SE HA ELIMINADO\n",valorAccion,prioridad);
}


void quitarPrecedencia(HashMap * hashMap, Tarea * tarea, char * tarea1, char * precedente) {
    Tarea* tareaPrescedente = (Tarea *) searchMap(hashMap,precedente)->value; // tarea2
    tarea->cantPresce--;
    tareaPrescedente->esPrecedente = 0;

    printf("LA TAREA %s  YA NO ES PRECEDENTE DE LA TAREA %s\n",precedente,tarea1);
}


void quitarMarcarTarea(Tarea * tarea) {
    tarea->check = 0;

    printf("LA TAREA %s CON PRIORIDAD %i SE HA MARCADO COMO NO COMPLETADA\n",tarea->nombre,tarea->prioridad);

}


void importarArchivoCSV(char* nombre_archivo, HashMap* map) {
    

    FILE* archivo = fopen(nombre_archivo, "r");
    
    if (archivo == NULL) {
        printf("NO SE PUDO ABRIR EL ARCHIVO %s\n", nombre_archivo);
        return;
    }
    
    

    char* linea=NULL;
    size_t longitud = 0;
    ssize_t leido;
    int cont = 0;
    
    int preceTotal=0;
    char** preceTotall;
    preceTotall=(char **) calloc(30, sizeof(char *));
    while ((leido = getline(&linea, &longitud, archivo)) != -1)
    {
        if (cont==0)
        {
            cont++;
            continue;
        }
        char* nomTarea = strtok(linea, ",");
        int prioridad = atoi(strtok(NULL, ","));
        
        Tarea* tarea = createTarea(nomTarea, prioridad);
        
        char* prece = strtok(NULL, " ");
        int cantPrece=0;
        while (prece!=NULL)
        {
            if (!isspace((unsigned char)*prece))
            {
                tarea->prescedentes[cantPrece]=strdup(prece);
                preceTotall[preceTotal]=strdup(prece);
                cantPrece++;
                preceTotal++;
                //printf("%i\n",cantPrece);
                
            }
            prece = strtok(NULL, " ");
        }
        if (cantPrece>0)
        {
            char* utliPrece=tarea->prescedentes[cantPrece-1];
            utliPrece[strlen(utliPrece)-2]='\0';
            tarea->prescedentes[cantPrece-1]=utliPrece;
            preceTotall[preceTotal-1]=utliPrece;
            
        }
        
        tarea->cantPresce=cantPrece;
        printf("\n \n la cantidad de prece de la tarea %s es %i",tarea->nombre,tarea->cantPresce);
        
        for (size_t k=0;k<tarea->cantPresce;k++)
        {
            printf(" %s ",tarea->prescedentes[k]);
        }
        printf("\n");


        
        if (cont != 0) { //para no leer primera linea del csv
            insertMap(map,tarea->nombre,tarea);
            pushBack(map->arrayList,nomTarea,prioridad);
         }
        cont++;
        
    }
    //marcar como precedentes las tareaas en el mapa
    for (size_t k=0;k<preceTotal;k++)
    {
        printf("%s",preceTotall[k]);
        Pair* current =searchMap(map,preceTotall[k]);
        Tarea* tare=current->value;
        tare->esPrecedente=1;
    }

    free(linea);
    fclose(archivo);
    printf("LOS DATOS DE LOS JUGADORES SE HAN CARGADO DESDE %s\n", nombre_archivo);
}





