#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

#include <sc/testing/test_harness.h>

#define ERR_BUFFER_SIZE (512)

static char err_str[ERR_BUFFER_SIZE];
static jmp_buf err_buf;

int run_tests(struct sc_test_harness *h, FILE *output)
{
    struct sc_test *curr_test;
    size_t total_tests = 0;
    size_t successes = 0;

    fprintf(stderr, "Running test suite: %s\n\n", h->name);

    curr_test = h->tests;

    if (NULL == output) {
        output = stderr;
    }

    while (curr_test->name) {
        struct sc_test_context ctx = { 0 };

        fprintf(output, "%s::%s running... ", h->name, curr_test->name);
        fflush(output);

        total_tests++;

        if (!setjmp(err_buf)) {
            ctx.harness_name = h->name;
            ctx.test_name = curr_test->name;
            if (h->init_func) {
                ctx.test_data = h->init_func();
            }

            curr_test->test_func(&ctx);

            if (h->dinit_func) {
                h->dinit_func(ctx.test_data);
            }

            fprintf(output, "[OK]\n");
            successes++;
        } else {
            fprintf(output, "[Fail]\n");
            fprintf(output, "\t--- %s\n", err_str);
        }
        curr_test++;
    }

    fprintf(output, "\nTests complete: %zu / %zu tests passed.\n\n", successes, total_tests);
    return (successes == total_tests) ? 0 : 1;
}

void _sc_assert_check(const char *file, int line, const char *str_stmt, bool stmt)
{
    if (!stmt) {
        snprintf(err_str, ERR_BUFFER_SIZE, "%s:%d ASSERT FAILURE: \"%s\"", file, line, str_stmt);
        longjmp(err_buf, 1);
    }
}
