#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tree.h"

#ifndef SIZE
    #define SIZE  8
#endif

static int int_cmp(const void *a, const void *b)
{
    int *x = (int *)a,
        *y = (int *)b;

    return *x - *y;
}

static void __print_nodes(tree_node_t *n)
{
    if (n != NULL) {
        __print_nodes(n->left);
        int *v = (int *)n->data;
        printf("[");
        for (int i = 0; i < SIZE - 1; i++)
            printf("%d ", v[i]);
        printf("%d]\n", v[SIZE - 1]);
        __print_nodes(n->right);
    }
}

static void print_nodes(tree_t *t)
{
    __print_nodes(t->root);
}

int main(void)
{
    int v[SIZE];
    tree_t *tree = new_tree(compare_mem, sizeof(int), SIZE);
    struct timespec ts;

    timespec_get(&ts, TIME_UTC);
    srand(ts.tv_nsec);

    for (int i = 1; i <= SIZE; i++) {
        for (int i = 0; i < SIZE; i++) {
            v[i] = rand() % 0xA;
        }

        qsort((void *)v, SIZE, sizeof(int), &int_cmp);

        tree_insert(tree, &v);
    }

    print_nodes(tree);
    destroy_tree(tree);

    return 0;
}
