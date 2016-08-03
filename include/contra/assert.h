/**
 * Contra's assert mini-library.
 *
 * The MIT License (MIT)
 * Copyright (c) 2016 GochoMugo <mugo@forfuture.co.ke>
 * Copyright (c) 2016 Forfuture, LLC <we@forfuture.co.ke>
 */

#ifndef _CONTRA_assert_h_
#define _CONTRA_assert_h_ 1


#ifndef NDEBUG
#define contra_assert__make(expression, message, args...) \
    if (!expression) { \
        fprintf(stderr, "Assertion failed at %s:%d\n", __FILE__, __LINE__); \
        fprintf(stderr, message, ##args); \
        abort(); \
    }
#else
#define contra_assert__make(expression, message, args...)
#endif


/**
 * Assert that the expression is 'ok'. This is analogous to the
 * traditional `assert`.
 *
 * @param  expression scalar
 */
#define contra_assert_ok(expression) \
        contra_assert__make((expression), \
                "Expected the expression to be truthy\n")


/**
 * Assert that the integer 'a' is equal to integer 'b'.
 *
 * @param  a int
 * @param  b int
 */
#define contra_assert_int_equal(a, b) \
        contra_assert__make(contra_is_int_equal(a, b), \
                "Expected: %d == %d\n", a, b)
#define contra_assert_int_eq(a, b) assert_int_equal(a, b)


/**
 * Assert that the integer 'a' is not equal to integer 'b'.
 *
 * @param  a int
 * @param  b int
 */
#define contra_assert_int_not_equal(a, b) \
        contra_assert__make(!contra_is_int_equal(a, b), \
                "Expected: %d != %d\n", a, b)
#define contra_assert_int_ne(a, b) contra_assert_int_not_equal(a, b)


/**
 * Assert that the integer 'a' is less than integer 'b'.
 *
 * @param  a int
 * @param  b int
 */
#define contra_assert_int_less_than(a, b) \
        contra_assert__make(contra_is_int_less_than(a, b), \
                "Expected: %d < %d\n", a, b)
#define contra_assert_int_lt(a, b) contra_assert_int_less_than(a, b)


/**
 * Assert that the integer 'a' is less than or equal to integer 'b'.
 *
 * @param  a int
 * @param  b int
 */
#define contra_assert_int_less_than_or_equal(a, b) \
        contra_assert__make(contra_is_int_less_than_or_equal(a, b), \
                "Expected: %d <= %d\n", a, b)
#define contra_assert_int_lte(a, b) contra_assert_int_less_than_or_equal(a, b)


/**
 * Assert that the integer 'a' is greater than integer 'b'.
 *
 * @param  a int
 * @param  b int
 */
#define contra_assert_int_greater_than(a, b) \
        contra_assert__make(contra_is_int_greater_than(a, b), \
                "Expected: %d > %d\n", a, b)
#define contra_assert_int_gt(a, b) contra_assert_int_greater_than(a, b)


/**
 * Assert that integer 'a' is greater than or equal to integer 'b'.
 *
 * @param  a int
 * @param  b int
 */
#define contra_assert_int_greater_than_or_equal(a, b) \
        contra_assert__make(contra_is_int_greater_than_or_equal(a, b), \
                "Expected: %d >= %d\n", a, b)
#define contra_assert_int_gte(a, b) contra_assert_int_greater_than_or_equal(a, b)


/**
 * Assert that string 'a' equals string 'b'.
 *
 * @param  a string
 * @param  b string
 */
#define contra_assert_str_equal(a, b) \
        contra_assert__make(contra_is_str_equal(a, b), \
                "Expected: %s == %s\n", a, b)
#define contra_assert_str_eq(a, b) contra_assert_str_equal(a, b)


/**
 * Assert that string 'a' does not equal string 'b'.
 *
 * @param  a string
 * @param  b string
 */
#define contra_assert_str_not_equal(a, b) \
        contra_assert__make(!contra_is_str_equal(a, b), \
                "Expected: %s != %s\n", a, b)
#define contra_assert_str_ne(a, b) contra_assert_str_not_equal(a, b)


/**
 * Assert that string 'str' is empty.
 *
 * @param  str string
 */
#define contra_assert_str_empty(str) \
        contra_assert__make(contra_is_str_empty(str), \
                "Expected: %s == \"\"\n", str)


/**
 * Assert that string 'str' is not empty.
 *
 * @param  str string
 */
#define contra_assert_str_not_empty(str) \
        contra_assert__make(!contra_is_str_empty(str), \
                "Expected: %s != \"\"\n", str)


/**
 * Assert that pointer 'ptr' is NULL.
 *
 * @param  ptr pointer
 */
#define contra_assert_null(ptr) \
        contra_assert__make(contra_is_null(ptr), \
                "Expected: %p == NULL\n", ptr)


/**
 * Assert that pointer 'ptr' is not NULL.
 *
 * @param  ptr pointer
 */
#define contra_assert_not_null(ptr) \
        contra_assert__make(!contra_is_null(ptr), \
                "Expected: %p != NULL\n", ptr)

#endif
