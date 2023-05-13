#include <stdlib.h>
#include <string.h>
#include "AVL-tree.h"

int height(avlNode *node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

avlNode *newNode(const char *key, void *value) {
    avlNode *node = (avlNode*) malloc(sizeof(avlNode));
    node->key = strdup(key);
    node->value = value;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

avlNode *rightRotate(avlNode *y) {
    avlNode *x = y->left;
    avlNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

