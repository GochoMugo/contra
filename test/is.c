#include <test-headers/main.h>

int tests_contra_is_setup_each(void **state) { return 0; }
int tests_contra_is_teardown_each(void **state) { return 0; }


void tests_contra_is_int_equal(void **state) {
    assert_ok(contra_is_int_equal(0, 0));
    assert_ok(contra_is_int_equal(1, 1));
    assert_ok(contra_is_int_equal(-1, -1));
}


void tests_contra_is_int_less_than(void **state) {
    assert_ok(contra_is_int_less_than(-2, -1));
    assert_ok(contra_is_int_less_than(-1, 0));
    assert_ok(contra_is_int_less_than(0, 1));
}


void tests_contra_is_int_less_than_or_equal(void **state) {
    assert_ok(contra_is_int_less_than_or_equal(-2, -1));
    assert_ok(contra_is_int_less_than_or_equal(-1, -1));
    assert_ok(contra_is_int_less_than_or_equal(-1, 0));
    assert_ok(contra_is_int_less_than_or_equal(0, 0));
    assert_ok(contra_is_int_less_than_or_equal(0, 1));
}


void tests_contra_is_int_greater_than(void **state) {
    assert_ok(contra_is_int_greater_than(-1, -2));
    assert_ok(contra_is_int_greater_than(0, -1));
    assert_ok(contra_is_int_greater_than(1, 0));
}


void tests_contra_is_int_greater_than_or_equal(void **state) {
    assert_ok(contra_is_int_greater_than_or_equal(-1, -2));
    assert_ok(contra_is_int_greater_than_or_equal(-1, -1));
    assert_ok(contra_is_int_greater_than_or_equal(0, -1));
    assert_ok(contra_is_int_greater_than_or_equal(0, 0));
    assert_ok(contra_is_int_greater_than_or_equal(1, 0));
}


void tests_contra_is_str_equal(void **state) {
    assert_ok(contra_is_str_equal("", ""));
    assert_ok(contra_is_str_equal("abc\tdef", "abc\tdef"));
}


void tests_contra_is_str_empty(void **state) {
    assert_ok(contra_is_str_empty(""));
}


void tests_contra_is_null(void **state) {
    assert_ok(contra_is_null(NULL));
}
