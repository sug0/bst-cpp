#include <stdio.h>
#include "tree.h"

int compare_uchar(void *x, void *y, size_t nmemb, size_t size)
{
    unsigned char *a = (unsigned char *)x,
                  *b = (unsigned char *)y;

    if (*a == *b)
        return 0;

    if (*a > *b)
        return 1;
    else
        return -1;
}

static void __print_nodes(tree_node_t *n)
{
    if (n != NULL) {
        __print_nodes(n->left);
        printf("%u\n", *(unsigned int *)n->data);
        __print_nodes(n->right);
    }
}

static void print_nodes(tree_t *t)
{
    __print_nodes(t->root);
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "%s: too little arguments\n", argv[0]);
        return 1;
    }

    FILE *fp;

    if ((fp = (FILE *)fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "%s: invalid file: %s\n", argv[0], argv[1]);
        return 1;
    }

    int c;
    tree_t *tree = new_tree(compare_uchar, sizeof(unsigned char), 1UL);

    while ((c = fgetc(fp)) != EOF)
        tree_insert(tree, &c);

    print_nodes(tree);
    destroy_tree(tree);
    fclose(fp);

    return 0;
}
