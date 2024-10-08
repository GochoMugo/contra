#!/usr/bin/env crun
/* -Wall -O3 -L../../build -I../../include */

#include "../../src/index.h"

#define is(i) contra_is_str_eq(argv[1], i)

int main(int argc, char **argv) {
    contra_assert_int_gt(argc, 1);

    if (is("ok(null)")) contra_assert_ok(NULL);
    if (is("ok(0)")) contra_assert_ok(0);
    if (is("int_eq(0,1)")) contra_assert_int_equal(0, 1);
    if (is("int_ne(0,0)")) contra_assert_int_ne(0, 0);
    if (is("int_lt(1,0)")) contra_assert_int_lt(1, 0);
    if (is("int_lte(1,0)")) contra_assert_int_lte(1, 0);
    if (is("int_gt(0,1)")) contra_assert_int_gt(0, 1);
    if (is("int_gte(0,1)")) contra_assert_int_gte(0, 1);
    if (is("str_eq(abc,123)")) contra_assert_str_eq("abc", "123");
    if (is("str_ne(abc,abc)")) contra_assert_str_ne("abc", "abc");
    if (is("str_empty(abc)")) contra_assert_str_empty("abc");
    if (is("str_not_empty('')")) contra_assert_str_not_empty("");
    if (is("null('')")) contra_assert_null("");
    if (is("not_null(NULL)")) contra_assert_not_null(NULL);

    return 0;
}
