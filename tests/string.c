#include <sc/testing/test_harness.h>
#include <sc/traits/object.h>
#include <sc/types/string.h>

static void basic_alloc(struct sc_test_context *ctx)
{
    sc_string_t *str = sc_string_build_empty();
    sct_assert(str);

    sct_assert_eq(sc_string_len(str), 0);

    sc_object_free(str);
}

struct sc_test string_tests[] = {
    { "basic_alloc", basic_alloc },
    { NULL },
};

struct sc_test_harness th = {
    "string_tests",
    string_tests,
};

int main()
{
    return run_tests(&th, NULL);
}
