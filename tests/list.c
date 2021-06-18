#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <sc/containers/list.h>
#include <sc/macros.h>
#include <sc/testing/test_harness.h>
#include <sc/types/string.h>

void basic_test(struct sc_test_context *ctx)
{
    sct_assert(ctx->test_data);
}

void test_free_on_delete(struct sc_test_context *ctx)
{
    sc_list_t *lst = ctx->test_data;

    sc_list_push_front(lst, (struct sc_object *)sc_string_build_str("test string"));
}

void test_push_pop(struct sc_test_context *ctx)
{
    char buf[32];
    sc_string_t *tmp;
    sc_list_t *lst = ctx->test_data;

    sct_assert(sc_list_len(lst) == 0);

    for (int i = 1; i <= 100; i++) {
        sprintf(buf, "%d", i);
        sct_assert(sc_list_push_front(lst, (struct sc_object *)sc_string_build_str(buf)) == 0);
    }

    sct_assert(sc_list_len(lst) == 100);

    tmp = (sc_string_t *)sc_list_front(lst);
    sct_assert(sc_string_strncmp(tmp, "100", 3) == 0);

    for (int i = 1; i <= 100; i++) {
        sprintf(buf, "%d", i);
        tmp = (sc_string_t *)sc_list_pop_back(lst);
        sct_assert(tmp);
        sct_assert(sc_string_strncmp(tmp, buf, strlen(buf)) == 0);
        sc_object_free(tmp);
    }

    sct_assert(sc_list_len(lst) == 0);

    for (int i = 1; i <= 100; i++) {
        sprintf(buf, "%d", i);
        sct_assert(sc_list_push_back(lst, (struct sc_object *)sc_string_build_str(buf)) == 0);
    }

    sct_assert(sc_list_len(lst) == 100);

    tmp = (sc_string_t *)sc_list_back(lst);
    sct_assert(sc_string_strncmp(tmp, "100", 3) == 0);

    for (int i = 100; i >= 1; i--) {
        sprintf(buf, "%d", i);
        tmp = (sc_string_t *)sc_list_pop_back(lst);
        sct_assert(tmp);
        sct_assert(sc_string_len(tmp) == strlen(buf));
        sct_assert(sc_string_strncmp(tmp, buf, strlen(buf)) == 0);
        sc_object_free(tmp);
    }

    sct_assert(sc_list_len(lst) == 0);
}

void test_sorted(struct sc_test_context *ctx)
{
    char buf[32];
    sc_list_t *lst = ctx->test_data;
    sc_string_t *prev;
    sc_string_t *curr;

    srand(time(NULL));

    for (int i = 0; i < 1000; ++i) {
        int val = rand();
        sprintf(buf, "%d", val);
        sc_list_push_sorted(lst, (struct sc_object *)sc_string_build_str(buf));
    }

    prev = (sc_string_t *)sc_list_pop_front(lst);

    while ((curr = (sc_string_t *)sc_list_pop_front(lst)) != NULL) {
        sct_assert(sc_object_cmp(curr, prev) >= 0);
        sc_object_free(prev);
        prev = curr;
    }

    sc_object_free(prev);
}

void *test_init()
{
    sc_list_t *list = sc_list_init();

    return list;
}

void test_deinit(sc_list_t *lst)
{
    sc_object_free(lst);
}

static struct sc_test tests[] = {
    { "basic_test", &basic_test },
    { "test_free_on_delete", &test_free_on_delete },
    { "test_push_pop", &test_push_pop },
    { "test_sorted", &test_sorted },
    { NULL },
};

static struct sc_test_harness th = {
    "list",
    tests,
    (sc_test_init_f)test_init,
    (sc_test_deinit_f)test_deinit,
};

int main()
{
    return run_tests(&th, NULL);
}
