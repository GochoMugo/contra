#include "index.h"

void tests_contra_is_int_equal(void **state) {
  assert_true(contra_is_int_eq(0, 0));
  assert_true(contra_is_int_equal(0, 0));
  assert_true(contra_is_int_equal(1, 1));
  assert_true(contra_is_int_equal(-1, -1));
}

void tests_contra_is_int_less_than(void **state) {
  assert_true(contra_is_int_lt(-2, -1));
  assert_true(contra_is_int_less_than(-2, -1));
  assert_true(contra_is_int_less_than(-1, 0));
  assert_true(contra_is_int_less_than(0, 1));
}

void tests_contra_is_int_less_than_or_equal(void **state) {
  assert_true(contra_is_int_lte(-2, -1));
  assert_true(contra_is_int_less_than_or_equal(-2, -1));
  assert_true(contra_is_int_less_than_or_equal(-1, -1));
  assert_true(contra_is_int_less_than_or_equal(-1, 0));
  assert_true(contra_is_int_less_than_or_equal(0, 0));
  assert_true(contra_is_int_less_than_or_equal(0, 1));
}

void tests_contra_is_int_greater_than(void **state) {
  assert_true(contra_is_int_gt(-1, -2));
  assert_true(contra_is_int_greater_than(-1, -2));
  assert_true(contra_is_int_greater_than(0, -1));
  assert_true(contra_is_int_greater_than(1, 0));
}

void tests_contra_is_int_greater_than_or_equal(void **state) {
  assert_true(contra_is_int_gte(-1, -2));
  assert_true(contra_is_int_greater_than_or_equal(-1, -2));
  assert_true(contra_is_int_greater_than_or_equal(-1, -1));
  assert_true(contra_is_int_greater_than_or_equal(0, -1));
  assert_true(contra_is_int_greater_than_or_equal(0, 0));
  assert_true(contra_is_int_greater_than_or_equal(1, 0));
}

void tests_contra_is_str_equal(void **state) {
  assert_true(contra_is_str_eq("", ""));
  assert_true(contra_is_str_equal("", ""));
  assert_true(contra_is_str_equal("abc\ndef", "abc\ndef"));
  assert_false(contra_is_str_equal("", NULL));
  assert_false(contra_is_str_equal(NULL, ""));
  assert_false(contra_is_str_equal(NULL, NULL));
}

void tests_contra_is_str_empty(void **state) {
  assert_true(contra_is_str_empty(""));
  assert_true(contra_is_str_empty(NULL));
  assert_false(contra_is_str_empty(" "));
}

void tests_contra_is_null(void **state) {
  assert_true(contra_is_null(NULL));
  assert_false(contra_is_null(1));
  assert_false(contra_is_null(""));
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(tests_contra_is_int_equal),
      cmocka_unit_test(tests_contra_is_int_less_than),
      cmocka_unit_test(tests_contra_is_int_less_than_or_equal),
      cmocka_unit_test(tests_contra_is_int_greater_than),
      cmocka_unit_test(tests_contra_is_int_greater_than_or_equal),
      cmocka_unit_test(tests_contra_is_str_equal),
      cmocka_unit_test(tests_contra_is_str_empty),
      cmocka_unit_test(tests_contra_is_null),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
