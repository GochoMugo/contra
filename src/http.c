/**
 * Contra's HTTP mini-library.
 *
 * The MIT License (MIT)
 * Copyright (c) 2016 GochoMugo <mugo@forfuture.co.ke>
 */

#include "index.h"

typedef struct Buffer {
  char *data;
  size_t size;
} Buffer;

void contra_http_buffer_free(Buffer **buffer);
int contra_http_buffer_new(Buffer **out);
struct curl_slist *contra_http_default_headers();
void contra_http_response_free(contra_http_response **res);
int contra_http_response_new(contra_http_response **out);
size_t write_response(void *contents, size_t size, size_t nmemb, void *userp);

static struct curl_slist *default_headers = NULL;

void contra_http_buffer_free(Buffer **buffer) {
  Buffer *b = *buffer;
  if (NULL == b)
    return;
  if (NULL != b->data)
    free(b->data);
  free(b);
  *buffer = NULL;
}

int contra_http_buffer_new(Buffer **out) {
  int ret_code = 0;
  Buffer *buffer = NULL;

  buffer = malloc(sizeof(Buffer));
  if (NULL == buffer) {
    return_err_now(CONTRA_ERR_MALLOC);
  }
  buffer->data = NULL;
  buffer->size = 0;

  *out = buffer;

_on_error:
_cleanup:
  return ret_code;
}

struct curl_slist *contra_http_default_headers() {
  if (NULL == default_headers) {
    default_headers =
        curl_slist_append(default_headers, "Content-Type: application/json");
  }
  return default_headers;
}

int contra_http_get(contra_http_response **out, const char *url) {
  int ret_code = 0;
  Buffer *buffer = NULL;
  CURL *curl = NULL;
  contra_http_response *res = NULL;
  CURLcode res_ret;

  return_err(contra_http_response_new(&res));
  return_err(contra_http_buffer_new(&buffer));

  curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
  curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, res->error_message);
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, contra_http_default_headers());
  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_USERAGENT, "contra");
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)buffer);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_response);

  res_ret = curl_easy_perform(curl);
  if (CURLE_OK != res_ret) {
    res->error_code = res_ret;
    *out = res;
    return_err_now(CONTRA_ERR_HTTP);
  }

  res->body = buffer->data;
  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &(res->status_code));

  *out = res;

_on_error:
  if (ret_code != CONTRA_ERR_HTTP) {
    contra_http_response_free(&res);
    contra_http_buffer_free(&buffer);
  }
_cleanup:
  if (NULL != curl)
    curl_easy_cleanup(curl);
  return ret_code;
}

int contra_http_post(contra_http_response **out, const char *url,
                     const char *body) {
  int ret_code = 0;
  Buffer *buffer = NULL;
  CURL *curl = NULL;
  struct curl_slist *headers = NULL;
  contra_http_response *res = NULL;
  CURLcode res_ret;

  res = malloc(sizeof(contra_http_response));
  if (NULL == res) {
    return_err_now(CONTRA_ERR_MALLOC);
  }
  res->body = NULL;
  res->error_code = 0;
  res->error_message = malloc(CURL_ERROR_SIZE);
  if (NULL == res->error_message) {
    return_err_now(CONTRA_ERR_MALLOC);
  }
  res->status_code = 0;
  *out = res;

  buffer = malloc(sizeof(Buffer));
  if (NULL == buffer) {
    return_err_now(CONTRA_ERR_MALLOC);
  }
  buffer->data = NULL;
  buffer->size = 0;

  headers = curl_slist_append(headers, "Content-Type: application/json");

  curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
  curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, res->error_message);
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
  if (NULL != body) {
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE_LARGE,
                     (curl_off_t)strlen(body));
  }
  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_USERAGENT, "contra");
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)buffer);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_response);

  res_ret = curl_easy_perform(curl);
  if (CURLE_OK != res_ret) {
    res->error_code = res_ret;
    return_err_now(CONTRA_ERR_HTTP);
  }

  res->body = buffer->data;
  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &(res->status_code));

_on_error:
  if (NULL != buffer) {
    if (NULL != buffer->data && (NULL == res || NULL == res->body))
      free(buffer->data);
    free(buffer);
  }
  if (NULL != res && ret_code != CONTRA_ERR_HTTP)
    contra_http_response_free(&res);
_cleanup:
  if (NULL != curl)
    curl_easy_cleanup(curl);
  if (NULL != headers)
    curl_slist_free_all(headers);
  return ret_code;
}

void contra_http_response_free(contra_http_response **res) {
  contra_http_response *r = *res;
  if (NULL == r)
    return;
  if (NULL != r->body)
    free(r->body);
  if (NULL != r->error_message)
    free(r->error_message);
  free(r);
  *res = NULL;
}

int contra_http_response_new(contra_http_response **out) {
  int ret_code = 0;
  contra_http_response *res = malloc(sizeof(contra_http_response));
  if (NULL == res) {
    return_err_now(CONTRA_ERR_MALLOC);
  }
  res->body = NULL;
  res->error_code = 0;
  res->error_message = malloc(CURL_ERROR_SIZE);
  if (NULL == res->error_message) {
    return_err_now(CONTRA_ERR_MALLOC);
  }
  res->status_code = 0;

  *out = res;

_on_error:
  contra_http_response_free(&res);
_cleanup:
  return ret_code;
}

size_t write_response(void *contents, size_t size, size_t nmemb, void *userp) {
  size_t realsize = size * nmemb;
  Buffer *buffer = (Buffer *)userp;

  buffer->data = realloc(buffer->data, buffer->size + realsize + 1);
  if (buffer->data == NULL) {
    return 0;
  }

  memcpy(&(buffer->data[buffer->size]), contents, realsize);
  buffer->size += realsize;
  buffer->data[buffer->size] = 0;
  return realsize;
}
