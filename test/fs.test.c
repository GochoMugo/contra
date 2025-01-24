#include "index.h"

static char *out = NULL;

void tests_contra_fs_read_file(void **state) {
  assert_ok(contra_fs_read_file(&out, "../test/data/sample_file.txt"));
  assert_contains(out, "information wants to be free");
  assert_int_equal(strlen(out), 29);
  out = NULL;
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(tests_contra_fs_read_file),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
