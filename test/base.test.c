#include "index.h"

void tests_array_size(void **state) {
  int array1[5];
  int array2[] = {4, 5, 6};

  assert_int_equal(array_size(array1), 5);
  assert_int_equal(array_size(array2), 3);
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(tests_array_size),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
