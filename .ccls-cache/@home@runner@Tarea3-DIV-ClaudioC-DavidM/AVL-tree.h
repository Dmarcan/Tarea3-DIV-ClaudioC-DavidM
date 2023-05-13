#ifndef AVL_H
#define AVL_H

typedef struct avlNode avlNode;
typedef struct avlTree avlTree;

typedef struct avlNode {
    char *key;
    void *value;
    int height;
    avlNode *left;
    avlNode *right;
} avlNode;

typedef struct avlTree {
    avlNode *root;
    int size;
} avlTree;


/*FUNCIONES COMPLEMENTARIAS AL ARBOL*/

int height(avlNode *node);

int max(int a, int b);

void updateHeight(avlNode *node);

int getBalance(avlNode *node);

int deleteNode(avlNode *node, const char *key);

avlNode *newNode(const char *key, void *value);

avlNode *rightRotate(avlNode *y);

avlNode *leftRotate(avlNode *x);

void avlInsertNode(avlNode **node, const char *key, void *value);


/*FUNCIONES ARBOL*/

void avlInit(avlTree *tree); // lista

//void avlClear(avlTree *tree);

void avlInsert(avlTree *tree, const char *key, void *value); //lista

void *avlGet(const avlTree *tree, const char *key); //lista

void avlDelete(avlTree *tree, const char *key);

#endif /* AVL_H */