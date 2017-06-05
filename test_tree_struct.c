#include <stdio.h>
#include "tree.h"

#define VSIZE(V)  sizeof(V) / sizeof(V[0])

typedef struct __tuple_s {
    int x;
    int y;
} tuple_t;

static void __print_nodes(tree_node_t *n)
{
    if (n != NULL) {
        __print_nodes(n->left);
        tuple_t *v = (tuple_t *)n->data;
        printf("(%d, %d)\n", v->x, v->y);
        __print_nodes(n->right);
    }
}

static void print_nodes(tree_t *t)
{
    __print_nodes(t->root);
}

int main(void)
{
    tree_t *tree   = new_tree(compare_mem, sizeof(tuple_t), 1UL);
    tuple_t vals[] = {{3, 1}, {5, 8}, {1, 4}};

    for (int i = 0; i < VSIZE(vals); i++) {
        tree_insert(tree, &vals[i]);
    }

    print_nodes(tree);
    destroy_tree(tree);

    return 0;
}
