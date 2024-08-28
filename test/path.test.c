#include "index.h"

static char *out = NULL;

#define assert_ok(result, expected)                                            \
  assert_int_equal(result, 0);                                                 \
  assert_string_equal(out, expected);                                          \
  out = NULL

#define assert_fail(result, expected) assert_int_equal(result, expected)

void tests_contra_path_join(void **state) {
  assert_ok(contra_path_join(&out, "/home/user", "projects"),
            "/home/user/projects");
  assert_ok(contra_path_join(&out, "/home/user", "/projects"),
            "/home/user/projects");
  assert_ok(contra_path_join(&out, "/home/gochomugo", "/"), "/home/gochomugo/");
  assert_ok(contra_path_join(&out, "/home/gochomugo/", "/"),
            "/home/gochomugo/");
  assert_ok(contra_path_join(&out, "/home/gochomugo", "."),
            "/home/gochomugo/.");
  assert_ok(contra_path_join(&out, "/home/gochomugo", ".."),
            "/home/gochomugo/..");
  assert_ok(contra_path_join(&out, "gochomugo", "projects"),
            "gochomugo/projects");
  assert_ok(contra_path_join(&out, "gochomugo", "/projects"),
            "gochomugo/projects");
  assert_ok(contra_path_join(&out, "/home/gochomugo", NULL), "/home/gochomugo");
  assert_ok(contra_path_join(&out, "/home/gochomugo", ""), "/home/gochomugo");
  assert_ok(contra_path_join(&out, NULL, "projects"), "projects");
  assert_ok(contra_path_join(&out, NULL, "/projects"), "/projects");
  assert_ok(contra_path_join(&out, "", "projects"), "projects");
  assert_ok(contra_path_join(&out, "", "/projects"), "/projects");
  assert_fail(contra_path_join(&out, "", NULL), CONTRA_ERR_BAD_ARGS);
  assert_fail(contra_path_join(&out, "", ""), CONTRA_ERR_BAD_ARGS);
  assert_fail(contra_path_join(&out, NULL, NULL), CONTRA_ERR_BAD_ARGS);
  assert_fail(contra_path_join(&out, NULL, ""), CONTRA_ERR_BAD_ARGS);
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(tests_contra_path_join),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
