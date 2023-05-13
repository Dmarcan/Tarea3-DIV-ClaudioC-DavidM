#ifndef AVL_H
#define AVL_H

typedef struct Node Node;
typedef struct Tree Tree;

typedef struct Node {
    char *key;
    void *value;
    int height;
    Node *left;
    Node *right;
} Node;

typedef struct Tree {
    Node *root;
    int size;
} Tree;


/*FUNCIONES COMPLEMENTARIAS AL ARBOL*/

int height(Node *node);

int max(int a, int b);

void updateHeight(Node *node);

int getBalance(Node *node);

int deleteNode(Node *node, const char *key);

Node *newNode(const char *key, void *value);

Node *rightRotate(Node *y);

Node *leftRotate(Node *x);

void insertNode(Node **node, const char *key, void *value);


/*FUNCIONES ARBOL*/

void avlInit(Tree *tree);

//void avlClear(Tree *tree);

void avlInsert(Tree *tree, const char *key, void *value);

void *avlGet(const Tree *tree, const char *key); 

void avlDelete(Tree *tree, const char *key);

#endif /* AVL_H */