#include "treetable.h"
#include "utils.h"
#include <klee/klee.h> 

static TreeTable *table;

int main() {
    treetable_new(cmp, &table);

    int pa; klee_make_symbolic(&pa, sizeof(int), "pa");
    int pb; klee_make_symbolic(&pb, sizeof(int), "pb");
    int pc; klee_make_symbolic(&pc, sizeof(int), "pc");
    int pd; klee_make_symbolic(&pd, sizeof(int), "pd");

    char a; klee_make_symbolic(&a, sizeof(char), "a");

    char str_a[] = {a, '\0'};

    char b; klee_make_symbolic(&b, sizeof(char), "b");

    char str_b[] = {b, '\0'};

    char c; klee_make_symbolic(&c, sizeof(char), "c");

    char str_c[] = {c, '\0'};

    treetable_add(table, &pa, str_a);
    treetable_add(table, &pb, str_b);
    treetable_add(table, &pc, str_c);

    treetable_remove_all(table);

    klee_assert(0 == treetable_contains_key(table, &pa));
    klee_assert(0 == treetable_contains_key(table, &pb));
    klee_assert(0 == treetable_contains_key(table, &pc));

    treetable_destroy(table);
}
