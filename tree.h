#ifndef _TREE_H_
#define _TREE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// prototype for the compare function used to insert objects into a tree
typedef int (*cmp_ptr_t)(void *x, void *y, size_t nmemb, size_t size);
typedef struct _tree_node tree_node_t;
typedef struct _tree tree_t;

struct _tree_node {
    tree_node_t *left;
    tree_node_t *right;
    void *data;
};

struct _tree {
    tree_node_t *root;
    cmp_ptr_t cmp;
    size_t nmemb;
    size_t size;
};

extern tree_node_t *new_tree_node(void *data, size_t nmemb, size_t size, tree_node_t *left, tree_node_t *right);
extern tree_t *new_tree(cmp_ptr_t cmp, size_t nmemb, size_t size);
extern int compare_int(void *x, void *y, size_t nmemb, size_t size);
extern int compare_char(void *x, void *y, size_t nmemb, size_t size);
extern int compare_mem(void *x, void *y, size_t nmemb, size_t size);
extern void tree_insert(tree_t *t, void *data);
extern int tree_contains(tree_t *tree, void *data);
extern size_t tree_depth(tree_t *t);
extern size_t tree_size(tree_t *t);
extern int tree_is_empty(tree_t *t);
extern void *tree_min(tree_t *t);
extern void *tree_max(tree_t *t);
extern void destroy_tree(tree_t *t);

#ifdef __cplusplus
}
#endif

#endif
