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
    
  while (node != NULL) {
    if (is_equal(tree, node->pair->key, key)) {
        return;
    }
    parent = node;
    if (tree->lower_than(key, node->pair->key) == 1) {
      node = node->left;
    } 
    else {
      node = node->right;
    }
    TreeNode* aux = createTreeNode(key, value);
      aux->parent = parent;
      if (tree->lower_than(key, parent->pair->key) == 1) {
        parent->left = aux->parent;
      } 
      else {
          parent->right = aux->parent;
      }
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
