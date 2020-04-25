#include "slist.h"
#include <klee/klee.h> 

static SList *list;
static SList *list2;
static int stat;

int va, vb, vc, vd, ve, vf, vg, vh;

void setup_test() {
    slist_new(&list), slist_new(&list2);

    klee_make_symbolic(&va, sizeof(int), "va");
    klee_make_symbolic(&vb, sizeof(int), "vb");
    klee_make_symbolic(&vc, sizeof(int), "vc");
    klee_make_symbolic(&vd, sizeof(int), "vd");
    klee_make_symbolic(&ve, sizeof(int), "ve");
    klee_make_symbolic(&vf, sizeof(int), "vf");
    klee_make_symbolic(&vg, sizeof(int), "vg");
    klee_make_symbolic(&vh, sizeof(int), "vh");

    int *a = (int *)malloc(sizeof(int));
    int *b = (int *)malloc(sizeof(int));
    int *c = (int *)malloc(sizeof(int));
    int *d = (int *)malloc(sizeof(int));

    *a = va;
    *b = vb;
    *c = vc;
    *d = vd;

    slist_add(list, a);
    slist_add(list, b);
    slist_add(list, c);
    slist_add(list, d);

    a = (int *)malloc(sizeof(int));
    b = (int *)malloc(sizeof(int));
    c = (int *)malloc(sizeof(int));
    d = (int *)malloc(sizeof(int));

    *a = ve;
    *b = vf;
    *c = vg;
    *d = vh;

    slist_add(list2, a);
    slist_add(list2, b);
    slist_add(list2, c);
    slist_add(list2, d);
};

void teardown_test() {
    slist_destroy(list);
    slist_destroy(list2);
};

int main() {
    setup_test();

    int *ins = (int *)malloc(sizeof(int));
    klee_make_symbolic(ins, sizeof(int), "ins");

    slist_add_at(list, ins, 2);
    klee_assert(5 == slist_size(list));

    int *new;
    slist_get_at(list, 2, (void *)&new);
    klee_assert(*ins == *new);
    klee_assert(CC_OK == slist_add_at(list, ins, 4));
    klee_assert(CC_OK == slist_add_at(list, ins, 0));

    void *el;
    slist_get_first(list, &el);
    klee_assert(*ins == *((int *)el));

    slist_get_first(list, &el);
    klee_assert(*ins == *((int *)el));

    teardown_test();
    return 0;
}