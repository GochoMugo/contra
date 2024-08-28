#include "index.h"

void tests_contra_math_max(void **state) {
  assert_int_equal(contra_math_max(2, 1), 2);
  assert_int_equal(contra_math_max(1, 2), 2);
}

void tests_contra_math_min(void **state) {
  assert_int_equal(contra_math_min(2, 1), 1);
  assert_int_equal(contra_math_min(1, 2), 1);
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(tests_contra_math_max),
      cmocka_unit_test(tests_contra_math_min),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
