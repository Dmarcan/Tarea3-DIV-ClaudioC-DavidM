#ifndef AVL_H
#define AVL_H

typedef struct TreeNode TreeNode;
typedef struct TreeMap TreeMap;

struct TreeNode {
    int key;
    void *value;
    struct node *left;
    struct node *right;
    struct node *parent;
    int height;
};

struct TreeMap{
    TreeNode *root;
    TreeNode *current;
};

/* FUNCIONES COMPLEMENTARIAS */

int max(int a, int b);

int height(TreeNode *node);

// Crea un nuevo nodo con una clave y un valor dados, para ser insertado en el árbol
TreeNode *createTreeNode(int key, void* value);



/*FUNCIONES ARBOL*/

// Función para crear un nuevo nodo AVL
TreeNode* newTreeNode(int key, void* value);

// Función para insertar un nuevo nodo en el árbol AVL
void AVLInsert(TreeMap* map, int key, void* value);

// Función para eliminar un nodo del árbol AVL
void AVLDelete(TreeMap* map, int key);

// Función para buscar un nodo en el árbol AVL
TreeNode* AVLFind(TreeMap* map, int key);

// Función para obtener el nodo con la menor clave en el árbol AVL
TreeNode* AVLFirst(TreeMap* map);

// Función para obtener el nodo siguiente en orden después de un nodo dado en el árbol AVL
TreeNode* AVLNext(TreeMap* map, TreeNode* node);

// Función para obtener el nodo anterior en orden antes de un nodo dado en el árbol AVL
//TreeNode* AVLPrev(TreeMap* map, TreeNode* node);

// Función para balancear un subárbol AVL después de la inserción o eliminación de un nodo
void AVLRebalance(TreeMap* map, TreeNode* node);

// Función para rotar un subárbol AVL hacia la izquierda
void AVLRotateLeft(TreeMap* map, TreeNode* node);

// Función para rotar un subárbol AVL hacia la derecha
TreeNode *AVLRotateRight(TreeMap* map, TreeNode* node);

// Función para actualizar la altura de un nodo AVL
void AVLUpdateHeight(TreeNode* node);

// Función para calcular la diferencia de altura entre los subárboles izquierdo y derecho de un nodo AVL
int AVLBalanceFactor(TreeNode* node);

#endif /* AVL_H */