#include <assert.h>
#include <stdlib.h>

#include <sc/containers/list.h>
#include <sc/testing/test_harness.h>

struct node {
    struct list_head list;
    int val;
};

static void basic_add_tail(struct sc_test_context *ctx)
{
    struct list_head head;
    struct node *at;
    struct node *safe;

    INIT_LIST_HEAD(&head);

    for (int i = 0; i < 100; i++) {
        struct node *new = malloc(sizeof(struct node));

        new->val = i;
        list_add_tail(&new->list, &head);
    }

    int i = 0;
    list_for_each_entry_safe(at, safe, &head, list)
    {
        sct_assert_eq(i++, at->val);

        list_del(&at->list);
        free(at);
    }
}

static void basic_add_front(struct sc_test_context *ctx)
{
    struct list_head head;
    struct node *at;
    struct node *safe;

    INIT_LIST_HEAD(&head);

    for (int i = 0; i < 100; i++) {
        struct node *node = malloc(sizeof(struct node));

        node->val = i;
        list_add(&node->list, &head);
    }

    int i = 99;
    list_for_each_entry_safe(at, safe, &head, list)
    {
        sct_assert_eq(i--, at->val);

        list_del(&at->list);
        free(at);
    }

    sct_assert(list_empty(&head));
}

static struct sc_test tests[] = {
    { "basic_add_tail", basic_add_tail },
    { "basic_add_front", basic_add_front },
    { NULL },
};

static struct sc_test_harness th = {
    "list",
    tests,
    NULL,
    NULL,
};

int main()
{
    return run_tests(&th, NULL);
}
