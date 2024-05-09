#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {

    TreeMap * new = (TreeMap *)malloc(sizeof(TreeMap));
    new->root = NULL;
    new->current = NULL;
    new->lower_than = lower_than;
    return new;
}
    


void insertarEnTreeMap(TreeMap *arbol, void* clave, void* valor) {
    if (arbol == NULL || arbol->raiz == NULL) return;

    NodoArbol *nuevoNodo = crearNodoArbol(clave, valor); // Crear un nuevo nodo con la clave y el valor dados

    NodoArbol *actual = arbol->raiz;
    NodoArbol *padre = NULL;

    // Recorrer el árbol para encontrar la posición adecuada para insertar el nuevo nodo
    while (actual != NULL) {
        padre = actual;
        // Comparar las claves para decidir si ir a la izquierda o a la derecha
        if (arbol->esMenorQue(clave, actual->par->clave)) {
            actual = actual->izquierda;
        } else {
            actual = actual->derecha;
        }
    }

    // Ahora, 'padre' apunta al nodo padre del nuevo nodo
    // Insertar el nuevo nodo como hijo de 'padre'
    if (arbol->esMenorQue(clave, padre->par->clave)) {
        padre->izquierda = nuevoNodo;
    } else {
        padre->derecha = nuevoNodo;
    }
}

TreeNode * minimum(TreeNode * x){

    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    if (tree == NULL || tree->root == NULL) return NULL;
    TreeNode * node = tree->root;
    while (node != NULL) {
        if (is_equal(tree,node->pair->key,key)) {
            tree->current = node;
            return node->pair;
        }
        if (tree->lower_than(node->pair->key,key)) node = node->right;
        else node = node->left;
    }
    tree->current = NULL;
    
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
