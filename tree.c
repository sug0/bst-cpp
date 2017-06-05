#include "tree.h"

int compare_int(void *x, void *y, size_t nmemb, size_t size)
{
    int *a = (int *)x,
        *b = (int *)y;

    if (*a == *b)
        return 0;

    if (*a > *b)
        return 1;
    else
        return -1;
}

int compare_char(void *x, void *y, size_t nmemb, size_t size)
{
    char *a = (char *)x,
         *b = (char *)y;

    if (*a == *b)
        return 0;

    if (*a > *b)
        return 1;
    else
        return -1;
}

int compare_mem(void *x, void *y, size_t nmemb, size_t size)
{
    return memcmp(x, y, nmemb * size);
}

tree_node_t *new_tree_node(void *data, size_t nmemb, size_t size, tree_node_t *left, tree_node_t *right)
{
    tree_node_t *n = (tree_node_t *)malloc(sizeof(tree_node_t));

    if (n == NULL) {
        fprintf(stderr, "malloc err\n");
        exit(1);
    }

    n->left  = left;
    n->right = right;
    n->data  = (void *)calloc(nmemb, size);

    memcpy(n->data, data, nmemb * size);

    return n;
}

tree_t *new_tree(cmp_ptr_t cmp, size_t nmemb, size_t size)
{
    tree_t *t = (tree_t *)malloc(sizeof(tree_t));

    if (t == NULL) {
        fprintf(stderr, "malloc err\n");
        exit(1);
    }

    t->root  = NULL;
    t->cmp   = cmp;
    t->nmemb = nmemb;
    t->size  = size;

    return t;
}

static void tree_insert_sub_tree(tree_node_t **n, cmp_ptr_t cmp, size_t nmemb, size_t size, void *data)
{
    if (*n == NULL) {
        *n = new_tree_node(data, nmemb, size, NULL, NULL);
        return;
    }

    if (cmp(data, (*n)->data, nmemb, size) <= 0)
        tree_insert_sub_tree(&(*n)->left, cmp, nmemb, size, data);
    else
        tree_insert_sub_tree(&(*n)->right, cmp, nmemb, size, data);
}

void tree_insert(tree_t *t, void *data)
{
    tree_insert_sub_tree(&t->root, t->cmp, t->nmemb, t->size, data);
}

static void destroy_sub_tree(tree_node_t *n)
{
    if (n == NULL)
        return;

    tree_node_t *left  = n->left,
                *right = n->right;

    free(n->data);
    free(n);

    destroy_sub_tree(left);
    destroy_sub_tree(right);
}

void destroy_tree(tree_t *t)
{
    destroy_sub_tree(t->root);
    free(t);
}
