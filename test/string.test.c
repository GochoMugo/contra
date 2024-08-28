#include "index.h"

static char *out = NULL;

#define assert_ok(result, expected)                                            \
  assert_int_equal(result, 0);                                                 \
  assert_string_equal(out, expected);                                          \
  out = NULL

#define assert_fail(result, expected) assert_int_equal(result, expected)

void tests_contra_str_copy(void **state) {
  assert_ok(contra_str_copy(&out, "hello"), "hello");
  assert_ok(contra_str_copy(&out, ""), "");
  assert_ok(contra_str_copy(&out, " "), " ");

  assert_int_equal(contra_str_copy(&out, "abc"), 0);
  // correct length
  assert_int_equal(strlen(out), 3);
  // null-terminated
  assert_null(out[3]);
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(tests_contra_str_copy),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
