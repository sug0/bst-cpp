#include <cmath>
#include <ctime>
#include <assert.h>
#include "tree.hpp"

struct Point
{
    double x, y;

    Point(double x, double y)
    {
        this->x = x;
        this->y = y;
    }

    double get_norm()
    {
        return sqrt(x*x + y*y);
    }
};

static void __print_nodes(tree_node_t *n)
{
    if (n != NULL) {
        __print_nodes(n->left);
        Point *p = (Point *)n->data;
        printf("norm of (%lf, %lf) is %lf\n", p->x, p->y, p->get_norm());
        __print_nodes(n->right);
    }
}

static void print_nodes(Tree *t)
{
    __print_nodes(t->root());
}

static double rand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

static int compare_point(void *x, void *y, size_t nmemb, size_t size)
{
    Point *p = (Point *)x,
          *q = (Point *)y;

    return (int)(p->x - q->x);
}

int main()
{
    Point *p;
    Tree *t = new Tree(compare_point, sizeof(Point), 1UL);
    struct timespec ts;

    timespec_get(&ts, TIME_UTC);
    srand(ts.tv_nsec);

    for (int i = 1; i <= 10; i++) {
        p = new Point(rand(1.0, 100.0), rand(1.0, 100.0));
        t->insert(p);
        delete p;
    }

    assert(t->size() == 10);

    print_nodes(t);

    printf("\ndepth of tree: %lu\n", t->depth());

    p = (Point *)t->min();
    printf("min point: (%lf, %lf)\n", p->x, p->y);

    p = (Point *)t->max();
    printf("min point: (%lf, %lf)\n", p->x, p->y);

    delete t;

    return 0;
}
