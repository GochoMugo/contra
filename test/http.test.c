#include "index.h"

const contra_http_request null_req = {
    .body = NULL,
    .headers = NULL,
    .headers_count = 0,
    .url = NULL,
};

static contra_http_request req = null_req;
static contra_http_response *res = NULL;

#define reset()                                                                \
  req = null_req;                                                              \
  res = NULL;

void tests_contra_http_get(void **state) {
  char *no_network = getenv("CONTRA_TEST_NO_NETWORK");
  if (NULL != no_network) {
    return;
  }

  req.url = "https://eu.httpbin.org/get?foo=bar";
  assert_ok(contra_http_get(&res, &req));
  assert_int_equal(res->status_code, 200);
  assert_contains(res->body, "\"Content-Type\": \"application/json\"");
  assert_contains(res->body, "\"foo\": \"bar\"");
  reset();

  // Custom headers.
  req.url = "https://eu.httpbin.org/get";
  req.headers = malloc(sizeof(char *) * 2);
  assert(req.headers);
  req.headers_count = 2;
  req.headers[0] = "X-Header-One: foo";
  req.headers[1] = "X-Header-Two: bar";
  assert_ok(contra_http_get(&res, &req));
  assert_contains(res->body, "\"X-Header-One\": \"foo\"");
  assert_contains(res->body, "\"X-Header-Two\": \"bar\"");
  free(req.headers);
  reset();

  // Status code is not 200.
  req.url = "https://eu.httpbin.org/put";
  assert_ok(contra_http_get(&res, &req));
  assert_int_equal(res->status_code, 405);
  reset();

  // HTTP (network) error.
  req.url = "https://unknown.gocho.live";
  int ret_code = contra_http_get(&res, &req);
  assert_int_equal(ret_code, CONTRA_ERR_HTTP);
  assert_true(res->error_code > 0);
  assert_contains(res->error_message, "Could not resolve host");
  reset();
}

void tests_contra_http_post(void **state) {
  char *no_network = getenv("CONTRA_TEST_NO_NETWORK");
  if (NULL != no_network) {
    return;
  }

  req.url = "https://eu.httpbin.org/post";
  req.body = "{\"foo\":\"bar\"}";
  assert_ok(contra_http_post(&res, &req));
  assert_int_equal(res->status_code, 200);
  assert_contains(res->body, "\"Content-Type\": \"application/json\"");
  assert_contains(res->body, "\"foo\": \"bar\"");
  reset();

  // Custom headers.
  req.url = "https://eu.httpbin.org/post";
  req.body = "{\"foo\":\"bar\"}";
  req.headers = malloc(sizeof(char *));
  assert(req.headers);
  req.headers_count = 1;
  req.headers[0] = "X-Header-One: foo";
  assert_ok(contra_http_post(&res, &req));
  assert_contains(res->body, "\"X-Header-One\": \"foo\"");
  free(req.headers);
  reset();

  // Request body is NULL.
  req.url = "https://eu.httpbin.org/post";
  assert_ok(contra_http_post(&res, &req));
  reset();

  // Status code is not 200.
  req.url = "https://eu.httpbin.org/put";
  assert_ok(contra_http_post(&res, &req));
  assert_int_equal(res->status_code, 405);
  reset();

  // HTTP (network) error.
  req.url = "https://unknown.gocho.live";
  int ret_code = contra_http_post(&res, &req);
  assert_int_equal(ret_code, CONTRA_ERR_HTTP);
  assert_true(res->error_code > 0);
  assert_contains(res->error_message, "Could not resolve host");
  reset();
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(tests_contra_http_get),
      cmocka_unit_test(tests_contra_http_post),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}

#undef reset
