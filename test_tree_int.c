#include <stdio.h>
#include <time.h>
#include <assert.h>
#include "tree.h"

static void __print_nodes(tree_node_t *n)
{
    if (n != NULL) {
        __print_nodes(n->left);
        printf("%d\n", *(int *)n->data);
        __print_nodes(n->right);
    }
}

static void print_nodes(tree_t *t)
{
    __print_nodes(t->root);
}

int main(void)
{
    int val;
    struct timespec ts;
    tree_t *tree = new_tree(compare_int, sizeof(int), 1UL);

    timespec_get(&ts, TIME_UTC);
    srand(ts.tv_nsec);

    for (int i = 1; i <= 10; i++) {
        val = rand() % 100 + 1;
        tree_insert(tree, &val);
    }

    assert(tree_size(tree) == 10);

    print_nodes(tree);

    if (tree_contains(tree, &val))
        printf("tree contains %d\n", val);
    else
        printf("tree doesn't contain %d\n", val);

    printf("tree has depth %lu, and min val %d\n", tree_depth(tree), *(int *)tree_min(tree));

    destroy_tree(tree);

    return 0;
}
