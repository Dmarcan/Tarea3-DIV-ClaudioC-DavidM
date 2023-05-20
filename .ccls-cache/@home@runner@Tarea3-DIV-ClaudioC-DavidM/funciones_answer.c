#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#define car *

#include "arraylist.h"
#include "stack.h"
#include "hashmap.h"
#include "funciones_answer.h"

#define MAXLEN 30

struct Tarea{
    char* nombre; // Nombre de la tarea
    char** prescedentes; // Vector con nombre de las tareas prescedentes
    int cantPresce; // Cantidad de tareas prescedentes
    int check; // Si esta completa 1 ; No esta completa 0
    int prioridad; // Prioridad que tiene la tarea
    int estado;// 1 = visitado ; 2 = explorado; 0 = ninguna
    int esPrecedente; // 1 = es precedente ; 0 = no es precedente
};

// Menu de opciones
void mostrarOpciones(){
    printf("*****************************************************************\n");
    printf("1. INGRESE 1 SI DESEA AGREGAR TAREA\n");
    printf("2. INGRESE 2 SI ESTABLECER PRECEDENCIA ENTRE TAREAS\n");
    printf("3. INGRESE 3 SI DESEA MOSTRAR TAREAS POR HACER\n");
    printf("4. INGRESE 4 SI DESEA MARCAR TAREA COMO COMPLETADA\n");
    printf("5. INGRESE 5 SI DESEA DESHACER ULTIMA ACCION\n");
    printf("6. INGRESE 6 SI DESEA CARGAR TAREAS DESDE UN ARCHIVO DE TEXTO\n");
    printf("7. INGRESE 0 SI DESEA SALIR\n");
    printf("*****************************************************************\n\n");
}

// Muestra y lee la opcion ingresada del menu, si es 0 termina la ejecucion 
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

// Crea e inicializa los miembros de una variable tipo tarea, asigna el nombre y la prioridad recibida y la retorna
void* createTarea(char* nombre, int prioridad){
    
    Tarea* tarea = (Tarea *) malloc(sizeof(Tarea));
    tarea->nombre = strdup(nombre);
    tarea->prioridad = prioridad;
    tarea->prescedentes = (char **) calloc(5, sizeof(char *));
    tarea->cantPresce = 0;
    tarea->check = 0;
    tarea->estado = 0;
    tarea->esPrecedente = 0;
    return tarea;
}

// Lee el nombre y la prioridad de la tarea agregar  
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

    Tarea* tarea = createTarea(nombre, prioridad); // Se crea variable tipo Tarea
    insertMap(hashMap,tarea->nombre,tarea); //Se inserta en el mapa con clave el nombre de la tarea
    pushBack(hashMap->arrayList,nombre,prioridad); // Se inserta en la arrayList ordenada por orden de prioridad
    push(hashMap->stackAcc,1,nombre,NULL); // Se inserta en la stack que la ultima accion es la opcion 1 junto con el nombre de la tarea
    
    return;
}

// Establece precedencia entre dos tareas
void establecerPrecedencia(HashMap * hashMap)
{
    char tarea1[MAXLEN + 1];
    do{
        printf("INGRESE NOMBRE DE LA TAREA QUE DEBE REALIZARSE PRIMERO\n");
        scanf("%s",tarea1);
        getchar();
    }while(strlen(tarea1) > MAXLEN);

    // Si no se encuentra en el mapa la tarea 1 finalia la ejecucion
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

    // Si no se encuentra en el mapa la tarea 1 finalia la ejecucion
    if (searchMap(hashMap,tarea2) == NULL) 
    {
        printf("LA TAREA %s NO SE ENCUENTRA EN LA BASE DE DATOS\n",tarea2);
        return;
    }

    // Inserta la tarea 1 como prescedente de la tarea 2, en el vector de cadenas
    Tarea* aux = (Tarea *) searchMap(hashMap,tarea2)->value;
    int indice = aux->cantPresce;
    aux->prescedentes[indice] = strdup(tarea1);
    (aux->cantPresce)++;
    printf("LA TAREA %s ES PRECEDENTE DE LA TAREA %s\n",tarea1,tarea2);

    push(hashMap->stackAcc,2,tarea1,tarea2); // Se inserta en la stack que la ultima accion es la opcion 1 junto con el nombre de la tarea1 y tarea2
}

void mostrarTareasPendientes(HashMap *hashMap) {
    printf("TAREAS POR HACER, ORDENADAS POR PRIORIDAD Y PRECEDENCIA : \n\n");
    int cont = 1; // Para mostrar el numero de tarea que se esta mostrando, no es la prioridad
    int contCompletados = 0; // Para saber la cantidad de tareas prescedentes completadas que tiene una tarea

    for(Duo* currentArray = first(hashMap->arrayList) ; currentArray!=NULL ; currentArray = next(hashMap->arrayList)) { // Recorre el array ordenado por prioridad
     
        char *tareaActual = currentArray->nombre;// Nombre de la tarea, esta se ocupara como clave en el hashmap
        Tarea* tareaActualMapa = (Tarea *) searchMap(hashMap,tareaActual)->value;
        if (tareaActualMapa->check == 1) continue;// Si la tarea actual esta completada se avanza a la siguiente tarea
        
        int totalPrecedentes = tareaActualMapa->cantPresce;
        for(int j = 0 ; j < totalPrecedentes ; j++) { //impresion de precedentes
            // Se busca la posicion en el hasmap de la tarea precedente para marcarla como precedente y obtener la prioridad
            Tarea* tareaPrecedente = (Tarea *) searchMap(hashMap,tareaActualMapa->prescedentes[j])->value;
            tareaPrecedente->esPrecedente = 1;
            
            if (tareaPrecedente->check == 0)
            {
                if (tareaPrecedente->estado != 1)
                {
                    tareaPrecedente->estado = 1;
                    printf("%i. Tarea %s (Prioridad: %i)\n", cont, tareaActualMapa->prescedentes[j],tareaPrecedente->prioridad);
                    cont++; 
                }
            }
            else contCompletados++;
        }

        if (tareaActualMapa->esPrecedente == 0) // Si la tarea no es precedente se imprime
        {
            tareaActualMapa->estado = 1;
            printf("%i. Tarea %s (Prioridad: %i)",cont,tareaActual,tareaActualMapa->prioridad);
            cont++;

            if (contCompletados != tareaActualMapa->cantPresce)
            {
                if (totalPrecedentes != 0) {
                    printf(" - Precedente/s:");
                    for(int j = 0 ; j < totalPrecedentes ; j++) { // Impresion de precedentes
                        Tarea* tareaPrecedente = (Tarea *) searchMap(hashMap,tareaActualMapa->prescedentes[j])->value;
                        if (tareaPrecedente->check == 0 )
                            printf(" Tarea %s",tareaPrecedente->nombre);
                    }
                printf("\n");
                }
                else printf("\n");
            }
            else printf("\n");
        }
        else
        {
             if (tareaActualMapa->estado !=1 )// Si es precedente pero aun no se ha impreso, se imprime junto con sus precedentes
             {
                 tareaActualMapa->estado = 1;
                 printf("%i. Tarea %s (Prioridad: %i)",cont,tareaActual,tareaActualMapa->prioridad);
                cont++;
    
    
                if (contCompletados != tareaActualMapa->cantPresce)
                {
                    if (totalPrecedentes != 0) {
                    printf(" - Precedente/s:");
                    for(int j = 0 ; j < totalPrecedentes ; j++) { // Impresion de precedentes
                        Tarea* tareaPrecedente = (Tarea *) searchMap(hashMap,tareaActualMapa->prescedentes[j])->value;
                        if (tareaPrecedente->check==0)
                        {
                            printf(" Tarea %s",tareaPrecedente->nombre);
                        }
                    }
                    printf("\n");
                    }
                    else printf("\n");
                }
                else printf("\n");
                 }
        }
        contCompletados=0;
    }
    marcarEstado(hashMap); // Se vuelve a incializar el estado como no impresos para la siguiente vez que se ocupe la funcion mostrar los imprima correctamente
    if (cont == 1) printf("NO EXISTEN TAREAS");
}

void marcarEstado(HashMap *hashMap)
{
    for (Pair* current = firstMap(hashMap); current != NULL ; current=nextMap(hashMap)) // Recorre todos los espacios donde hay tareas almacenadas e inicializa su estado en 0, es decir que no se ha mostrado
    {
        Tarea* tarea = current->value;
        tarea->estado = 0;
    }
}

void marcarTarea(HashMap * hashMap) {
    char tarea1[MAXLEN + 1];
    do{
        printf("INGRESE NOMBRE DE LA TAREA QUE ESTA COMPLETADA\n");
        scanf("%s",tarea1);
        getchar();
    }while(strlen(tarea1) > MAXLEN);
    
    Pair* current = searchMap(hashMap,tarea1); // Busca la tarea en el mapa
    if (current==NULL) // Si no se encuentra en el mapa retorna
    {
        printf("LA TAREA %s AUN NO SE HA INGRESADO",tarea1);
        return;
    }
    Tarea* aux =current->value;
    
    if (aux->esPrecedente == 1 || aux->cantPresce>0) // Verifica si tiene precedentes o si es precedente
    { // Codigo que pregunta confirmacion del usuario
        printf("¿ESTAS SEGURO QUE DESEA ELIMINAR LA TAREA %s?(S/N)\n",tarea1);
        char respuesta[MAXLEN + 1];
        do{
            scanf("%s",respuesta);
            getchar();
            if (strcmp(respuesta,"S") == 0)
            {
                aux->check = 1;
                push(hashMap->stackAcc,4,tarea1,NULL);
                printf("LA TAREA %s HA SIDO ELIINADA\n",tarea1);
                return;
            }
            else if (strcmp(respuesta,"N") == 0) return;
        } while (strlen(respuesta) > MAXLEN || (strcmp(respuesta, "N") != 0 && strcmp(respuesta, "S") != 0));
    }
    
    aux->check = 1;
    push(hashMap->stackAcc,4,tarea1,NULL);
    printf("LA TAREA %s HA SIDO ELIINADA\n",tarea1);
}

void deshacerUltimaAccion(HashMap * hashMap) {
    if(!areTaskPresents(hashMap)) // Si no hay tareas en el mapa retorna
    {
        printf("NO EXISTEN TAREAS GUARDADAS\n");
        return;
    }
    Info* elemen = pop(hashMap->stackAcc);
    if (elemen == NULL) // Si la stack esta vacia retorna
    {
        printf("NO HAY ULTIMA ACCION REGISTRADA\n");
        return;
    }
    int opcion = elemen->accion;
    
    char* tarea1String = elemen->valorAccion; 
    
    Tarea* tarea1 = (Tarea *) searchMap(hashMap,tarea1String)->value;
    
    switch(opcion)
    {   
        case 1:
            eraseMap(hashMap,tarea1String); // Elimina la tarea agregada del mapa
            delete(hashMap->arrayList,tarea1String);

            printf("LA TAREA %s CON PRIORIDAD %i SE HA ELIMINADO\n",tarea1String,tarea1->prioridad);
            break;
        case 2:
            quitarPrecedencia(hashMap,tarea1,elemen->cambio);
            break;
        case 4:
            tarea1->check = 0; // Descmarca la tarea como completada
            printf("LA TAREA %s CON PRIORIDAD %i SE HA MARCADO COMO NO COMPLETADA\n",tarea1->nombre,tarea1->prioridad);
            break;
        default:
            printf("LA OPCION INGRESADA NO SE PUEDE DESHACER\n");
    }
}

void quitarPrecedencia(HashMap * hashMap, Tarea * tarea1, char * precedente) {
    Tarea* anteriorPrece = (Tarea *) searchMap(hashMap,precedente)->value; // tarea2
    anteriorPrece->cantPresce--;
    tarea1->esPrecedente = 0;      
    printf("LA TAREA %s YA NO ES PRECEDENTE DE LA TAREA %s\n",tarea1->nombre,anteriorPrece->nombre);
}

void importarArchivoCSV(char* nombre_archivo, HashMap* map) {
    FILE* archivo = fopen(nombre_archivo, "r");
    
    if (archivo == NULL) {
        printf("NO SE PUDO ABRIR EL ARCHIVO %s\n", nombre_archivo);
        return;
    }
    
    char* linea = NULL;
    size_t longitud = 0;
    ssize_t leido;
    int cont = 0;// Se utiliza para ignorar la primera linea del archivo
    
    int preceTotal=0;// Total de precedentes en el archivo
    char** preceTotall; // Almacena todos los precedentes del archivo para al terminar de leerlo en base a el nombre de la tarea precedente buscar su posicion en el mapa y la variable esPrecedente marcarla como 1
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
        while (prece != NULL)
        {
            if (!isspace((unsigned char)*prece))
            {
                tarea->prescedentes[cantPrece]=strdup(prece);
                preceTotall[preceTotal] = strdup(prece);
                cantPrece++;
                preceTotal++;
                
            }
            prece = strtok(NULL, " ");
        }
        if (cantPrece > 0) // Eliminar salto de linea en la ultima tarea precedente
        {
            char* utliPrece = tarea->prescedentes[cantPrece-1];
            utliPrece[strlen(utliPrece)-2] = '\0';
            tarea->prescedentes[cantPrece-1] = utliPrece;
            preceTotall[preceTotal-1] = utliPrece;
            
        }
        tarea->cantPresce=cantPrece;
        insertMap(map,tarea->nombre,tarea); // Se inserta al mapa
        pushBack(map->arrayList,tarea->nombre,prioridad);//se inserta al arreglo para ordenarlo por prioridad
        cont++;
    }
    // Marcar como que son precedentes las tareas en el mapa
    for (size_t k = 0 ; k < preceTotal ; k++)
    {
        Pair* current =searchMap(map,preceTotall[k]);
        Tarea* tare=current->value;
        tare->esPrecedente = 1;
    }

    free(linea);
    fclose(archivo);
    printf("LOS DATOS DE LOS JUGADORES SE HAN CARGADO DESDE %s\n", nombre_archivo);
}