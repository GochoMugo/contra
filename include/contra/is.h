/**
 * Contra's is mini-library.
 *
 * The MIT License (MIT)
 * Copyright (c) 2016 GochoMugo <mugo@forfuture.co.ke>
 */

#ifndef _CONTRA_is_h_
#define _CONTRA_is_h_ 1

/**
 * Return true if integer 'a' is equal to integer 'b'.
 * Otherwise, return false.
 *
 * @param  a int
 * @param  b int
 * @return true/false
 */
#define contra_is_int_equal(a, b) (a == b)
#define contra_is_int_eq contra_is_int_equal

/**
 * Return true if integer 'a' is less than integer 'b'.
 * Otherwise, return false.
 *
 * @param  a int
 * @param  b int
 * @return true/false
 */
#define contra_is_int_less_than(a, b) (a < b)
#define contra_is_int_lt contra_is_int_less_than

/**
 * Return true if integer 'a' is less than or equal to integer 'b'.
 * Otherwise, return false.
 *
 * @param  a int
 * @param  b int
 * @return true/false
 */
#define contra_is_int_less_than_or_equal(a, b) (a <= b)
#define contra_is_int_lte contra_is_int_less_than_or_equal

/**
 * Return true if integer 'a' is greater than integer 'b'.
 * Otherwise, return false.
 *
 * @param  a int
 * @param  b int
 * @return true/false
 */
#define contra_is_int_greater_than(a, b) (a > b)
#define contra_is_int_gt contra_is_int_greater_than

/**
 * Return true if integer 'a' is greater than or equal to integer 'b'.
 * Otherwise, return false.
 *
 * @param  a int
 * @param  b int
 * @return true/false
 */
#define contra_is_int_greater_than_or_equal(a, b) (a >= b)
#define contra_is_int_gte contra_is_int_greater_than_or_equal

/**
 * Return true if string 'a' is equal to string 'b'.
 * Otherwise, return false.
 *
 * @param  a string
 * @param  b string
 * @return true/false
 */
#define contra_is_str_equal(a, b) (a != NULL && b != NULL && 0 == strcmp(a, b))
#define contra_is_str_eq contra_is_str_equal

/**
 * Return true if string 'str' is empty or null.
 * Otherwise, return false.
 *
 * @param  str string
 * @return true/false
 */
#define contra_is_str_empty(str) (NULL == str || 0 == strlen(str))

/**
 * Return true if 'ptr' is NULL.
 * Otherwise, return false.
 *
 * @param  ptr
 * @return true/false
 */
#define contra_is_null(ptr) (NULL == ptr)

#endif
