#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "AVL-tree.h"
#include "stack.h"
#include "funciones_answer.h"

int main(void) {

    TreeMap* treeMap = (TreeMap *) malloc(sizeof(TreeMap));
    avlInit(treeMap);
    //TreeMap* treeMap;
    
    mostrarMenu(treeMap);
    return 0;
}