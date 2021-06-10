#include <string.h>

#include <sc/hooks.h>
#include <sc/macros.h>
#include <sc/testing/test_harness.h>
#include <sc/traits/cmp.h>
#include <sc/traits/object.h>
#include <sc/traits/partial_cmp.h>
#include <sc/types/string.h>

static void basic_alloc(struct sc_test_context *ctx)
{
    sc_string_t *str = sc_string_build_empty();
    sct_assert(str);

    sct_assert_eq(sc_string_len(str), 0);

    sc_object_free(str);
}

static void str_alloc(struct sc_test_context *ctx)
{
    sc_string_t *str = sc_string_build_str("Test String");

    sct_assert(str);

    sct_assert(sc_string_strncmp(str, "Test String", 11) == 0);

    sc_object_free(str);
}

static void str_cmp(struct sc_test_context *ctx)
{
    sc_string_t *a = sc_string_build_str("Test String");
    sc_string_t *b = sc_string_build_str("Test String");

    sct_assert(a);
    sct_assert(b);

    sct_assert(sc_object_cmp(a, b) == 0);

    sct_assert(sc_object_partial_cmp(a, b));

    sc_object_free(a);
    sc_object_free(b);
}

static void str_raw(struct sc_test_context *ctx)
{
    sc_string_t *a = sc_string_build_raw((uint8_t *)"\x01\x02\x03", 3);

    sct_assert(a);

    sct_assert(sc_string_append_raw(a, (uint8_t *)"\x04", 1) == 0);

    sct_assert(sc_string_len(a) == 4);

    sct_assert(memcmp(sc_string_ptr(a), "\x01\x02\x03\x04", 4) == 0);

    sc_object_free(a);
}

static void str_take(struct sc_test_context *ctx)
{
    char *str = sc_zalloc(5);

    memcpy(str, "hello", 5);

    sc_string_t *a = sc_string_take_raw((uint8_t *)str, 5);

    sct_assert(a);

    sct_assert(sc_string_len(a) == 5);

    sc_object_free(a);
}

static void str_long(struct sc_test_context *ctx)
{
    sc_string_t *a = sc_string_build_str("this is a really long string");

    sc_string_t *b = sc_string_build_str(" and it gets even longer");

    size_t test_size = sc_string_len(a) + sc_string_len(b);

    sct_assert(sc_string_append_scstr(a, b) == 0);

    sct_assert(sc_string_len(a) == test_size);

    sct_assert(strlen(sc_string_ptr(a)) == test_size);

    const char *test_str = "this is a really long string and it gets even longer";

    sct_assert(strcmp(sc_string_ptr(a), test_str) == 0);

    sct_assert(sc_string_raw_cmp(a, (const uint8_t *)test_str, strlen(test_str)) == 0);

    sc_object_free(a);
    sc_object_free(b);
}

struct sc_test string_tests[] = {
    { "basic_alloc", basic_alloc },
    { "str_alloc", str_alloc },
    { "str_cmp", str_cmp },
    { "str_raw", str_raw },
    { "str_take", str_take },
    { "str_long", str_long },
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
