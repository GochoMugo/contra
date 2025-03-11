#include "index.h"

static char *out = NULL;

void tests_contra_str_copy(void **state) {
  assert_out(contra_str_copy(&out, "hello"), "hello");
  assert_out(contra_str_copy(&out, ""), "");
  assert_out(contra_str_copy(&out, " "), " ");

  assert_int_equal(contra_str_copy(&out, "abc"), 0);
  // correct length
  assert_int_equal(strlen(out), 3);
  // null-terminated
  assert_null(out[3]);

  // Does not break on null.
  assert_ok(contra_str_copy(&out, NULL));
  assert_null(out);
}

void tests_contra_str_trim(void **state) {
  assert_out(contra_str_trim(&out, "foo"), "foo");
  assert_out(contra_str_trim(&out, " foo"), "foo");
  assert_out(contra_str_trim(&out, "foo "), "foo");
  assert_out(contra_str_trim(&out, " foo "), "foo");
  assert_out(contra_str_trim(&out, "   foo   "), "foo");
  assert_out(contra_str_trim(&out, "\nfoo\n"), "foo");
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(tests_contra_str_copy),
      cmocka_unit_test(tests_contra_str_trim),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
