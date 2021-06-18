#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <sc/containers/raw/tree.h>
#include <sc/testing/test_harness.h>

struct node {
    RB_ENTRY(node) entry;
    int val;
};

static int cmp_nodes(struct node *a, struct node *b);

RB_HEAD(node_tree, node) head = RB_INITIALIZER(_head);

RB_PROTOTYPE(node_tree, node, entry, cmp_nodes)
RB_GENERATE(node_tree, node, entry, cmp_nodes)

static void basic_tree_test(struct sc_test_context *ctx)
{
    struct node *n;
    struct node *var;
    srand(time(NULL));

    RB_INIT(&head);

    for (size_t i = 0; i < 100; i++) {
        struct node *n = malloc(sizeof(struct node));

        do {
            n->val = random() % 10000;
        } while (RB_FIND(node_tree, &head, n));

        RB_INSERT(node_tree, &head, n);
    }

    int last = -1;

    RB_FOREACH_SAFE (n, node_tree, &head, var) {
        RB_REMOVE(node_tree, &head, n);
        sct_assert(last <= n->val);
        last = n->val;

        free(n);
        n = NULL;
    }

    sct_assert(RB_EMPTY(&head));
}

static struct sc_test tests[] = {
    { "basic_tree_test", basic_tree_test },
    { NULL },
};

static struct sc_test_harness th = {
    "raw_tree",
    tests,
    NULL,
    NULL,
};

int main()
{
    return run_tests(&th, NULL);
}

static int cmp_nodes(struct node *a, struct node *b)
{
    return a->val - b->val;
}
