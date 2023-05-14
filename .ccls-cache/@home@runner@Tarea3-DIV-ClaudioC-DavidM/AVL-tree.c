#include <stdlib.h>
#include "stdio.h"
#include <string.h>
#include "AVL-tree.h"

// Retorna el con mayor valor
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Retorna la altura de ese nodo
int height(TreeNode *node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

// Crea nodo e inicializa
TreeNode *createTreeNode(int key, void *value) {
    TreeNode *newNode = (TreeNode *) malloc(sizeof(TreeNode));
    newNode->key = key;
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    newNode->height = 1;
    return newNode;
}

TreeNode *AVLRotateRight(TreeNode *node) {
    TreeNode *new_root = node->left;
    node->left = new_root->right;
    new_root->right = node;

    // Actualizar padres
    new_root->parent = node->parent;
    node->parent = new_root;
    if (node->left != NULL) {
        node->left->parent = node;
    }

    // Actualizar alturas
    AVLUpdateHeight(node);
    AVLUpdateHeight(new_root);

    return new_root;
}

void AVLRotateLeft(TreeMap* map, TreeNode* node) {
    TreeNode* right = node->right;
    node->right = right->left;

    if (right->left != NULL) {
        right->left->parent = node;
    }

    right->parent = node->parent;

    if (node->parent == NULL) {
        map->root = right;
    } else if (node == node->parent->left) {
        node->parent->left = right;
    } else {
        node->parent->right = right;
    }

    right->left = node;
    node->parent = right;

    AVLUpdateHeight(node);
    AVLUpdateHeight(right);
}


void AVLRebalance(TreeMap* map, TreeNode* node) {
    AVLUpdateHeight(node);

    int balanceFactor = AVLBalanceFactor(node);

    if (balanceFactor > 1) {
        if (AVLBalanceFactor(node->left) < 0) {
            AVLRotateLeft(map, node->left);
        }
        AVLRotateRight(map, node);
    } else if (balanceFactor < -1) {
        if (AVLBalanceFactor(node->right) > 0) {
            AVLRotateRight(map, node->right);
        }
        AVLRotateLeft(map, node);
    }

    if (node->parent != NULL) {
        AVLRebalance(map, node->parent);
    } else {
        map->root = node;
    }
}

// Retorna factor de equilibrio del nodo
int AVLBalanceFactor(TreeNode *node) {
    if (node == NULL) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

// Inserta el nodo
TreeNode* insertNode(TreeNode *root, int key, void *value) {
    if (root == NULL) {
        return createTreeNode(key, value);
    }
    if (key < root->key) {
        root->left = insertNode(root->left, key, value);
    } else {
        root->right = insertNode(root->right, key, value);
    }
    root->height = max(height(root->left), height(root->right)) + 1;
    int balance = getBalance(root);
    if (balance > 1 && key < root->left->key) {
        return rotateRight(root);
    }
    if (balance < -1 && key > root->right->key) {
        return rotateLeft(root);
    }
    if (balance > 1 && key > root->left->key) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && key < root->right->key) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    return root;
}

void AVLInsert(TreeMap *tree, int key, void *value) {
    tree->root = insertNode(tree->root, key, value);
}

void AVLDelete(TreeMap *tree, int key) {
    tree->root = deleteNode(tree->root, key);
}

void *AVLFind(TreeMap *tree, int key) {
    TreeNode *currentNode = tree->root;
    while (currentNode != NULL) {
        if (key == currentNode->key) {
            return currentNode->value;
        } else if (key < currentNode->key) {
            currentNode = currentNode->left;
        } else {
            currentNode = currentNode->right;
        }
    }
    return NULL;
}

void * AVLFirst(TreeMap *tree) {
    if (tree->root == NULL) {
        return NULL;
    }
    TreeNode *currentNode = tree->root;
    while (currentNode->left != NULL) {
        currentNode = currentNode->left;
    }
    tree->current = currentNode;
    return currentNode->value;
}

void *AVLNext(TreeMap *tree) {
    if (tree->current == NULL) {
        return NULL;
    }
    if (tree->current->right != NULL) {
        TreeNode *currentNode = tree->current->right;
        while (currentNode->left != NULL) {
            currentNode = currentNode->left;
        }
        tree->current = currentNode;
        return currentNode->value;
    } else {
        TreeNode *currentNode = tree->current->parent;
        while (currentNode != NULL && tree->current == currentNode->right) {
            tree->current = currentNode;
            currentNode = currentNode->parent;
        }
        tree->current = currentNode;
        return currentNode != NULL ? currentNode->value : NULL;
    }
}
