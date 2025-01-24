/**
 * Testing Contra
 *
 * The MIT License (MIT)
 * Copyright (c) 2016 GochoMugo <mugo@forfuture.co.ke>
 * Copyright (c) 2016 Forfuture, LLC <we@forfuture.co.ke>
 */

#ifndef _CONTRA_tests_h_
#define _CONTRA_tests_h_ 1

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>

#include "../src/index.h"

#define assert_ok(result) assert_int_equal(result, 0)

#define assert_contains(haystack, needle) assert_true(strstr(haystack, needle))

#endif
