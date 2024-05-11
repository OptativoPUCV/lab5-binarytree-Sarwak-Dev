#include "treemap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode TreeNode;

struct TreeNode {
  Pair *pair;
  TreeNode *left;
  TreeNode *right;
  TreeNode *parent;
};

struct TreeMap {
  TreeNode *root;
  TreeNode *current;
  int (*lower_than)(void *key1, void *key2);
};

int is_equal(TreeMap *tree, void *key1, void *key2) {
  if (tree->lower_than(key1, key2) == 0 && tree->lower_than(key2, key1) == 0)
    return 1;
  else
    return 0;
}

TreeNode *createTreeNode(void *key, void *value) {
  TreeNode *new = (TreeNode *)malloc(sizeof(TreeNode));
  if (new == NULL)
    return NULL;
  new->pair = (Pair *)malloc(sizeof(Pair));
  new->pair->key = key;
  new->pair->value = value;
  new->parent = new->left = new->right = NULL;
  return new;
}

TreeMap *createTreeMap(int (*lower_than)(void *key1, void *key2)) {

  TreeMap *new = (TreeMap *)malloc(sizeof(TreeMap));
  new->root = NULL;
  new->current = NULL;
  new->lower_than = lower_than;
  return new;
}

void insertTreeMap(TreeMap *tree, void *key, void *value) {
  if (tree == NULL) // Verificar si el árbol existe
    return;

  TreeNode *parent = NULL;
  TreeNode *node = tree->root;

  // Crear un nuevo nodo con la clave y el valor proporcionados
  TreeNode* newNode = createTreeNode(key, value);

  // Si el árbol está vacío, el nuevo nodo se convierte en la raíz
  if (node == NULL) {
    tree->root = newNode;
    return;
  }

  // Buscar la posición de inserción para el nuevo nodo
  while (node != NULL) {
    parent = node;
    if (is_equal(tree, node->pair->key, key)) {
      // La clave ya existe, no es necesario insertar
      free(newNode); // Liberar la memoria del nuevo nodo
      return;
    } else if (tree->lower_than(key, node->pair->key)) {
      node = node->left;
    } else {
      node = node->right;
    }
  }

  // Asignar el padre al nuevo nodo
  newNode->parent = parent;

  // Insertar el nuevo nodo como hijo izquierdo o derecho del padre
  if (tree->lower_than(key, parent->pair->key)) {
    parent->left = newNode;
  } else {
    parent->right = newNode;
  }
}

TreeNode *minimum(TreeNode *x) { 

  while (x->left != NULL) {
    x = x->left;
  }
  return x;
}

void removeNode(TreeMap *tree, TreeNode *node) {
    
}

void eraseTreeMap(TreeMap *tree, void *key) {
  if (tree == NULL || tree->root == NULL)
    return;

  if (searchTreeMap(tree, key) == NULL)
    return;
  TreeNode *node = tree->current;
  removeNode(tree, node);
}

Pair *searchTreeMap(TreeMap *tree, void *key) {
  if (tree == NULL || tree->root == NULL)
    return NULL;
  TreeNode *node = tree->root;
  while (node != NULL) {
    if (is_equal(tree, node->pair->key, key)) {
      tree->current = node;
      return node->pair;
    }
    if (tree->lower_than(node->pair->key, key))
      node = node->right;
    else
      node = node->left;
  }
  tree->current = NULL;

  return NULL;
}

Pair *upperBound(TreeMap *tree, void *key) { return NULL; }

Pair *firstTreeMap(TreeMap *tree) { return NULL; }

Pair *nextTreeMap(TreeMap *tree) { return NULL; }
