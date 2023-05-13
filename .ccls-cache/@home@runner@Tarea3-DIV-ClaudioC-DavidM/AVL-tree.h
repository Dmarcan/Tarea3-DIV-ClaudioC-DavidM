#ifndef AVL_H
#define AVL_H

typedef struct Node Node;
typedef struct TreeMap TreeMap;

struct Node {
    char *key;
    void *value;
    int height;
    Node *left;
    Node *right;
    Node *parent;
};

struct TreeMap {
    Node *root;
    Node *current;
    int size;
};


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

void avlInit(TreeMap *treeMap);

//void avlClear(TreeMap *tree);

void avlInsert(TreeMap *treeMap, const char *key, void *value);

void *avlGet(const TreeMap *treeMap, const char *key); 

void avlDelete(TreeMap *treeMap, const char *key);

void* avlFirst(TreeMap *treeMap);

//void *avlNext(TreeMap* treeMap);

#endif /* AVL_H */