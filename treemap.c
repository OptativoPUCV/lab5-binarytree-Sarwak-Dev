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
    if (tree == NULL || tree->root == NULL)
        return;

    TreeNode *node = tree->root;
    TreeNode *parent = NULL;

    // Buscamos el lugar adecuado para insertar el nuevo nodo
    while (node != NULL) {
        parent = node;
        // Si la clave ya existe en el árbol, no hacemos nada y salimos
        if (is_equal(tree, node->pair->key, key) == 1) {
            return;
        }

        // Determinamos si moverse hacia el hijo izquierdo o derecho según la comparación de claves
        if (tree->lower_than(key, node->pair->key) == 0) {
            node = node->left;
        } else {
            node = node->right;
        }
    }

    // Creamos el nuevo nodo con la clave y el valor dados
    TreeNode* newNode = createTreeNode(key, value);
    newNode->parent = parent;

    // Insertamos el nuevo nodo como hijo del nodo padre, dependiendo de la comparación de claves
    if (tree->lower_than(key, parent->pair->key) == 0) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
}

TreeNode *minimum(TreeNode *x) { return NULL; }

void removeNode(TreeMap *tree, TreeNode *node) {}

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
