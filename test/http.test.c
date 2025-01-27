#include "index.h"

static contra_http_response *out = NULL;

void tests_contra_http_get(void **state) {
  char *no_network = getenv("CONTRA_TEST_NO_NETWORK");
  if (NULL != no_network) {
    return;
  }

  assert_ok(contra_http_get(&out, "https://eu.httpbin.org/get?foo=bar"));
  assert_int_equal(out->status_code, 200);
  assert_contains(out->body, "\"Content-Type\": \"application/json\"");
  assert_contains(out->body, "\"foo\": \"bar\"");
  out = NULL;

  // Status code is not 200.
  assert_ok(contra_http_get(&out, "https://eu.httpbin.org/put"));
  assert_int_equal(out->status_code, 405);
  out = NULL;

  // HTTP (network) error.
  int ret_code = contra_http_get(&out, "https://unknown.gocho.live");
  assert_int_equal(ret_code, CONTRA_ERR_HTTP);
  assert_true(out->error_code > 0);
  assert_contains(out->error_message, "Could not resolve host");
  out = NULL;
}

void tests_contra_http_post(void **state) {
  char *no_network = getenv("CONTRA_TEST_NO_NETWORK");
  if (NULL != no_network) {
    return;
  }

  assert_ok(contra_http_post(&out, "https://eu.httpbin.org/post",
                             "{\"foo\":\"bar\"}"));
  assert_int_equal(out->status_code, 200);
  assert_contains(out->body, "\"Content-Type\": \"application/json\"");
  assert_contains(out->body, "\"foo\": \"bar\"");
  out = NULL;

  // Request body is NULL.
  assert_ok(contra_http_post(&out, "https://eu.httpbin.org/post", NULL));
  out = NULL;

  // Status code is not 200.
  assert_ok(contra_http_post(&out, "https://eu.httpbin.org/put", NULL));
  assert_int_equal(out->status_code, 405);
  out = NULL;

  // HTTP (network) error.
  int ret_code = contra_http_post(&out, "https://unknown.gocho.live", NULL);
  assert_int_equal(ret_code, CONTRA_ERR_HTTP);
  assert_true(out->error_code > 0);
  assert_contains(out->error_message, "Could not resolve host");
  out = NULL;
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(tests_contra_http_get),
      cmocka_unit_test(tests_contra_http_post),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
