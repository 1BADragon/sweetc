#ifndef _SC_TEST_HARNESS_H
#define _SC_TEST_HARNESS_H

#include <stdbool.h>
#include <stdio.h>

/**
 * @macro STRINGIZE
 * Transforms the content of x into a string literal.
 */
#define STRINGIZE(x)   _STRINGIZE(x)
#define _STRINGIZE(x)  __STRINGIZE(x)
#define __STRINGIZE(x) #x

/**
 * @macro sct_assert
 * Used to assert a condition in a test case. This macro should only be used
 * in the test suite. `stmt` is evaluated into a boolean conditional if the
 * result is false the assertion fails.
 */
#define sct_assert(stmt)                                                                           \
    _sc_assert_check(__FILE__, __LINE__, STRINGIZE(stmt), (stmt) ? true : false)

#define sct_assert_eq(a, b) sct_assert((a) == (b))

struct sc_test_context;

/**
 * @brief Prototype of tests in the test harness. One argument is passed in
 * which is the context of the current test harness.
 */
typedef void (*sc_test_f)(struct sc_test_context *);

/**
 * @brief Prototype of a test initialization. This function can be called at the
 * begining of each test case, if provided, to run any construction code
 * common to all test cases. This function can return a pointer that is passed in
 * as `test_data` in the test context struct.
 */
typedef void *(*sc_test_init_f)();

/**
 * @brief Prototype of a test tear down. This function can be called at the end
 * of each test case, if provided. It is passed any data returned from the test
 * initialization functions, (`test_ctx->test_data`).
 */
typedef void (*sc_test_deinit_f)(void *);

/**
 * @brief The sc_test struct defines a unit test case and its name. To be passed as a
 * NULL terminated array in the `tests` field. The `name` filed should be NULL in
 * the last entry for the tests array.
 */
struct sc_test {
    /// The name of the test (whatever the user wants)
    const char *name;
    /// Pointer to the function for the test
    sc_test_f test_func;
};

/**
 * @brief The sc_test_harness struct defines the asspects of a test suite.
 */
struct sc_test_harness {
    /// The name of the whole test harness, required.
    const char *name;
    /// An array of struct sc_test entries, terminated by an entry with `name` being NULL.
    /// Required
    struct sc_test *tests;
    /// An initialization function that returns some user specified data, optional.
    sc_test_init_f init_func;
    /// A tear down function that is passed the returned data from init. This funciton should
    /// no be set if `init_func` is NULL, optional.
    sc_test_deinit_f dinit_func;
};

/**
 * @brief The sc_test_context struct defines the context for a given test case.
 */
struct sc_test_context {
    /// Name of the current test harness.
    const char *harness_name;
    /// Name of the current test case.
    const char *test_name;
    /// User data returned from the harness init function. This data is also passed to
    /// the tear down optionaly configured as `dinit_func`
    void *test_data;
};

/**
 * @brief Runs the provided test suit.
 * @param h The test harness context, needs to be allocated and initalized by the caller.
 * @param output An optional FILE pointer to output test results to. If NULL test results are
 * printed to stderr.
 * @return 0 if all tests pass, 1 otherwise.
 */
int run_tests(struct sc_test_harness *h, FILE *output) __attribute__((warn_unused_result));

/**
 * @brief Helper function to check and a test suite assert and fail a test if stmt resolves to
 * false. This function should not be called by the user. Instead the macro `sct_assert` should
 * be called.
 * @param file The file name in of the source file containing the assert.
 * @param line The line of the assert.
 * @param str_stmt The conent of the assert statement.
 * @param stmt The result of the statement.
 *
 * @note This function should not be called directly. Instead, use the `sct_assert*` family of
 * macros.
 */
void _sc_assert_check(const char *file, int line, const char *str_stmt, bool stmt);

#endif //_SC_TEST_HARNESS_H
