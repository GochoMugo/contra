#include "index.h"

static contra_http_request *req = NULL;
static contra_http_response *res = NULL;

#define teardown()                                                             \
  contra_http_request_free(&req);                                              \
  req = NULL;                                                                  \
  res = NULL;

void tests_contra_http_get(void **state) {
  char *no_network = getenv("CONTRA_TEST_NO_NETWORK");
  if (NULL != no_network) {
    return;
  }

  assert_ok(
      contra_http_request_new(&req, "https://eu.httpbin.org/get?foo=bar"));
  assert_ok(contra_http_get(&res, req));
  assert_int_equal(res->status_code, 200);
  assert_contains(res->body, "\"Content-Type\": \"application/json\"");
  assert_contains(res->body, "\"foo\": \"bar\"");
  teardown();

  // Custom headers.
  assert_ok(contra_http_request_new(&req, "https://eu.httpbin.org/get"));
  assert_ok(contra_http_request_append_header(req, "X-Header-One: foo"));
  assert_ok(contra_http_request_append_header(req, "X-Header-Two: bar"));
  assert_int_equal(req->headers_count, 2);
  assert_ok(contra_http_get(&res, req));
  assert_contains(res->body, "\"X-Header-One\": \"foo\"");
  assert_contains(res->body, "\"X-Header-Two\": \"bar\"");
  teardown();

  // Status code is not 200.
  assert_ok(contra_http_request_new(&req, "https://eu.httpbin.org/put"));
  assert_ok(contra_http_get(&res, req));
  assert_int_equal(res->status_code, 405);
  teardown();

  // HTTP (network) error.
  assert_ok(contra_http_request_new(&req, "https://unknown.gocho.live"));
  int ret_code = contra_http_get(&res, req);
  assert_int_equal(ret_code, CONTRA_ERR_HTTP);
  assert_true(res->error_code > 0);
  assert_contains(res->error_message, "Could not resolve host");
  teardown();
}

void tests_contra_http_post(void **state) {
  char *no_network = getenv("CONTRA_TEST_NO_NETWORK");
  if (NULL != no_network) {
    return;
  }

  assert_ok(contra_http_request_new(&req, "https://eu.httpbin.org/post"));
  assert_ok(contra_str_copy(&(req->body), "{\"foo\":\"bar\"}"));
  assert_ok(contra_http_post(&res, req));
  assert_int_equal(res->status_code, 200);
  assert_contains(res->body, "\"Content-Type\": \"application/json\"");
  assert_contains(res->body, "\"foo\": \"bar\"");
  teardown();

  // Request body is NULL.
  assert_ok(contra_http_request_new(&req, "https://eu.httpbin.org/post"));
  assert_ok(contra_http_post(&res, req));
  teardown();

  // Custom headers.
  assert_ok(contra_http_request_new(&req, "https://eu.httpbin.org/post"));
  assert_ok(contra_http_request_append_header(req, "X-Header-One: foo"));
  assert_int_equal(req->headers_count, 1);
  assert_ok(contra_http_post(&res, req));
  assert_contains(res->body, "\"X-Header-One\": \"foo\"");
  teardown();

  // Status code is not 200.
  assert_ok(contra_http_request_new(&req, "https://eu.httpbin.org/put"));
  assert_ok(contra_http_post(&res, req));
  assert_int_equal(res->status_code, 405);
  teardown();

  // HTTP (network) error.
  assert_ok(contra_http_request_new(&req, "https://unknown.gocho.live"));
  int ret_code = contra_http_post(&res, req);
  assert_int_equal(ret_code, CONTRA_ERR_HTTP);
  assert_true(res->error_code > 0);
  assert_contains(res->error_message, "Could not resolve host");
  teardown();
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(tests_contra_http_get),
      cmocka_unit_test(tests_contra_http_post),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}

#undef teardown
