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

void avlInit(avlTree *tree);

void avlClear(avlTree *tree);

void avlInsert(avlTree *tree, const char *key, void *value);

void *avlGet(const avlTree *tree, const char *key);

void avlDelete(avlTree *tree, const char *key);

#endif /* AVL_H */