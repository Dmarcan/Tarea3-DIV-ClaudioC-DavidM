#include <stdlib.h>
#include <string.h>
#include "AVL-tree.h"

//RETORNA LA ALTURA DE ESE NODO
int height(Node *node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

//RETORNA EL CON MAYOR VALOR
int max(int a, int b) {
    return (a > b) ? a : b;
}

//ACTUALIZA ALTURA
void updateHeight(Node *node) {
    node->height = 1 + max(height(node->left), height(node->right));
}

//RETORNA EL FACTOR DE EQUILIBRIO
int getBalance(Node *node) {
    if (node == NULL) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

int deleteNode(Node *node, const char *key) {
    if (node == NULL) {
        return NULL;
    }

    int cmp = strcmp(key, node->key);

    if (cmp < 0) {
        node->left = deleteNode(node->left, key);
    } else if (cmp > 0) {
        node->right = deleteNode(node->right, key);
    } else {
        if (node->left == NULL && node->right == NULL) {
            free(node->key);
            free(node);
            return NULL;
        } else if (node->left == NULL) {
            Node *right = node->right;
            free(node->key);
            free(node);
            return right;
        } else if (node->right == NULL) {
            Node *left = node->left;
            free(node->key);
            free(node);
            return left;
        } else {
            Node *minRight = node->right;
            while (minRight->left != NULL) {
                minRight = minRight->left;
            }

            char *minKey = strdup(minRight->key);
            void *minValue = avlGet(node->right, minKey);

            node->key = minKey;
            node->value = minValue;
            node->right = deleteNode(node->right, minKey);
        }
    }

    updateHeight(node);
    return getBalance(node);
}

Node *newNode(const char *key, void *value) {
    Node *node = (Node*) malloc(sizeof(Node));

    if (node == NULL) {
        printf("NO SE PUDO RESERVAR MEMORIA\n");
        return NULL;
    }
    
    node->key = strdup(key);
    node->value = value;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    return node;
}

Node *rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;
    // HACE LA ROTACION
    x->right = y;
    y->left = T2;
    // ACTUALIZA EL PARENT DE Y
    if (T2 != NULL) {
        T2->parent = y;
    }
    x->parent = y->parent;
    y->parent = x;
    // ACTUALIZA LA ALTURA DE LOS NODOS CAMBIADOS
    updateHeight(y);
    updateHeight(x);
    return x;
}

Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    // HACE LA ROTACION
    y->left = x;
    x->right = T2;

    // ACTUALIZA ALTURA DE NODOS MODIFICADOS
    updateHeight(x);
    updateHeight(y);

    // ACTUALIZA PUNTEROS DEL PADRE
    y->parent = x->parent;
    x->parent = y;
    if (T2 != NULL) {
        T2->parent = x;
    }

    //RETORNA EL DATO QUE QUEDO EN LA POSICION
    return y;
}


// INSERTA NODO AL ARBOL AVL
void insertNode(Node **node, const char *key, void *value) {
    //SI ESTA VACIO SOLO SE CREA EL NODO Y SE INSERTA EN LA RAIZ (NO NECESIDAD DE ROTACIONES)
    if (*node == NULL) {
        *node = newNode(key, value);
        return;
    }

    //LLAMADA RECURSIVA PARA LLEGAR AL NODO DONDE INSERTAR
    //STRCMP COMPARA LA CLAVE CON LOS NODOS DEL ARBOL Y DEPENDIENDO SI SU CLAVE ES MAYOR O MENOR SE DIRIGE A UNA RAMA
    int cmp = strcmp(key, (*node)->key);
    if (cmp < 0) {
        insertNode(&(*node)->left, key, value);
    } else if (cmp > 0) {
        insertNode(&(*node)->right, key, value);
    } else {
        (*node)->value = value;
        return;
    }
    
    (*node)->height = 1 + max(height((*node)->left), height((*node)->right));
    
    int balance = getBalance(*node);
    if (balance > 1 && strcmp(key, (*node)->left->key) < 0) {
        rightRotate(node);
    } else if (balance < -1 && strcmp(key, (*node)->right->key) > 0) {
        leftRotate(node);
    } else if (balance > 1 && strcmp(key, (*node)->left->key) > 0) {
        leftRotate(&(*node)->left);
        rightRotate(node);
    } else if (balance < -1 && strcmp(key, (*node)->right->key) < 0) {
        rightRotate(&(*node)->right);
        leftRotate(node);
    }
}

/*FUNCIONES ARBOL*/

//INICIALIZA ARBOL VACIO
void avlInit(TreeMap *tree) {
    tree->root = NULL;
    tree->current = NULL;
    tree->size = 0;
}

//INSERTA NODO AL ARBOL CON LA FUNCION "avlInserNode"
void avlInsert(TreeMap *tree, const char *key, void *value) {
    insertNode(&tree->root, key, value);
    tree->size++;
}

// BUSCA Y RETORNA UN ELEMENTO DEL ARBOL ABL, SI NO SE ENCUENTRA RETORNA NULL
void *avlGet(const TreeMap *tree, const char *key) {
    Node *current = tree->root;
    while (current != NULL) {
        int cmp = strcmp(key, current->key);
        if (cmp == 0) {
            return current->value;
        } else if (cmp < 0) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return NULL;
}

void avlDelete(TreeMap *tree, const char *key) {
    if (tree == NULL || tree->root == NULL || key == NULL) {
        return;
    }

    tree->root = deleteNode(tree->root, key);
    tree->size--;
}

void *avlFirst(TreeMap *treeMap){
    Node *node = treeMap->root;
    if(node == NULL)
        return NULL;
    
    while(node->left != NULL)
        node = node->left;

    treeMap->current = node;
    return node->value;
}

/*
void *avlNext(TreeMap* treeMap){
    Node* node = treeMap->current;
    if(node == NULL)
        return NULL;
    
    if(node->right != NULL){
        node = node->right;
        while(node->left != NULL)
            node = node->left;

        treeMap->current = node;
        return node->value;
    }
    
    Node* parent = node->parent;
    while(parent != NULL && node == parent->right){
        node = parent;
        parent = node->parent;
    }

    treeMap->current = parent;
    return parent != NULL ? parent->value : NULL;
}
*/