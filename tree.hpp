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

    tree_node_t *root()
    {
        return this->t->root;
    }

    void insert(void *data)
    {
        tree_insert(this->t, data);
    }

    bool contains(void *data)
    {
        return tree_contains(this->t, data);
    }

    size_t depth()
    {
        return tree_depth(this->t);
    }

    size_t size()
    {
        return tree_size(this->t);
    }

    bool is_empty()
    {
        return tree_is_empty(this->t);
    }

    void *min()
    {
        return tree_min(this->t);
    }

    void *max()
    {
        return tree_max(this->t);
    }
};
