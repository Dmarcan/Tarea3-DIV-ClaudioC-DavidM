#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "hashmap.h"
#include "stack.h"
#include "funciones_answer.h"

int main(void) {
    HashMap* newMap = (HashMap *) createMap(3);
    
    mostrarMenu(newMap);
    return 0;
}