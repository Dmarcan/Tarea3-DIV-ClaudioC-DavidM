#include <stdio.h>

#include "hashmap.h"
#include "funciones_answer.h"

int main(void) {
    HashMap* newMap = (HashMap *) createMap(3);
    
    mostrarMenu(newMap);
    return 0;
}