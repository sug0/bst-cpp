#include "tree.h"

class Tree
{
    tree_t *t;

public:
    Tree(cmp_ptr_t cmp, size_t nmemb, size_t size)
    {
        this->t = new_tree(cmp, nmemb, size);
    }

    ~Tree()
    {
        destroy_tree(this->t);
    }

    cmp_ptr_t get_cmp()
    {
        return this->t->cmp;
    }

    size_t get_size()
    {
        return this->t->size;
    }

    size_t get_nmemb()
    {
        return this->t->nmemb;
    }

    void insert(void *data)
    {
        tree_insert(this->t, data);
    }

    tree_node_t *root()
    {
        return this->t->root;
    }
};
