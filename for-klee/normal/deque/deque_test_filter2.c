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

    klee_assume(pred2(&d) && pred2(&e) && pred2(&f) && !pred2(&a) && !pred2(&b) &&
           !pred2(&c));

    deque_add_last(deque, &a);
    deque_add_last(deque, &b);
    deque_add_last(deque, &c);
    deque_add_last(deque, &d);
    deque_add_last(deque, &e);
    deque_add_last(deque, &f);
    klee_assert(6 == deque_size(deque));

    Deque *filter = NULL;
    deque_filter(deque, pred2, &filter);
    const void *const *buff = deque_get_buffer(filter);

    klee_assert(3 == deque_size(filter));
    klee_assert(buff[0] == &d);
    klee_assert(buff[1] == &e);
    klee_assert(buff[2] == &f);

    free(filter);

    teardown_tests();
    return 0;
}
