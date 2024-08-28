/**
 * Contra's HTTP mini-library.
 *
 * The MIT License (MIT)
 * Copyright (c) 2016 GochoMugo <mugo@forfuture.co.ke>
 */

#include "index.h"

size_t write_response(void *contents, size_t size, size_t nmemb, void *userp);

typedef struct Buffer {
  char *data;
  size_t size;
} Buffer;

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

  _on_error if (NULL != buffer) {
    if (NULL != buffer->data && (NULL == res || NULL == res->body))
      free(buffer->data);
    free(buffer);
  }
  if (NULL != res)
    contra_http_response_free(&res);
  _cleanup if (NULL != curl) curl_easy_cleanup(curl);
  if (NULL != headers)
    curl_slist_free_all(headers);
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
