#include "deque.h"
#include <klee/klee.h> 

static Deque *deque;
static DequeConf conf;
int stat;

void setup_tests() { stat = deque_new(&deque); }

void teardown_tests() { deque_destroy(deque); }

bool pred1(const void *e) { return *(int *)e <= 3; }

bool pred2(const void *e) { return *(int *)e > 3; }

bool pred3(const void *e) { return *(int *)e > 5; }

int main() {
    setup_tests();

    int a; klee_make_symbolic(&a, sizeof(int), "a");
    int b; klee_make_symbolic(&b, sizeof(int), "b");
    int c; klee_make_symbolic(&c, sizeof(int), "c");
    int d; klee_make_symbolic(&d, sizeof(int), "d");
    int e; klee_make_symbolic(&e, sizeof(int), "e");
    int f; klee_make_symbolic(&f, sizeof(int), "f");

    klee_assume(!pred3(&d) && !pred3(&e) && pred3(&f) && !pred3(&a) && !pred3(&b) &&
           !pred3(&c));

    deque_add_last(deque, &a);
    deque_add_last(deque, &b);
    deque_add_last(deque, &c);
    deque_add_last(deque, &d);
    deque_add_last(deque, &e);
    deque_add_last(deque, &f);
    klee_assert(6 == deque_size(deque));

    deque_filter_mut(deque, pred3);
    klee_assert(1 == deque_size(deque));

    int *removed = NULL;
    deque_remove_first(deque, (void *)&removed);
    klee_assert(f == *removed);
    teardown_tests();
    return 0;
}
