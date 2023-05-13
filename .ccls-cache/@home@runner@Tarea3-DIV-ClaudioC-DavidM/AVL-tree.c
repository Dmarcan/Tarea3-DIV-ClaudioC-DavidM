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
    node->key = strdup(key);
    node->value = value;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node *rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

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
void avlInit(Tree *tree) {
    tree->root = NULL;
    tree->size = 0;
}

//INSERTA NODO AL ARBOL CON LA FUNCION "avlInserNode"
void avlInsert(Tree *tree, const char *key, void *value) {
    insertNode(&tree->root, key, value);
    tree->size++;
}

// BUSCA Y RETORNA UN ELEMENTO DEL ARBOL ABL, SI NO SE ENCUENTRA RETORNA NULL
void *avlGet(const Tree *tree, const char *key) {
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

void avlDelete(Tree *tree, const char *key) {
    if (tree == NULL || tree->root == NULL || key == NULL) {
        return;
    }

    tree->root = deleteNode(tree->root, key);
    tree->size--;
}
