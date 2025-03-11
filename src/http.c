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
struct curl_slist *contra_http_set_headers(struct curl_slist *headers,
                                           const contra_http_request *req);
int contra_http_response_new(contra_http_response **out);
size_t write_response(void *contents, size_t size, size_t nmemb, void *userp);

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

on_error:
cleanup:
  return ret_code;
}

struct curl_slist *contra_http_set_headers(struct curl_slist *headers,
                                           const contra_http_request *req) {
  headers = curl_slist_append(headers, "Content-Type: application/json");
  for (int i = 0; i < req->headers_count; i++) {
    headers = curl_slist_append(headers, req->headers[i]);
  }
  return headers;
}

int contra_http_get(contra_http_response **out,
                    const contra_http_request *req) {
  int ret_code = 0;
  Buffer *buffer = NULL;
  CURL *curl = NULL;
  struct curl_slist *headers = NULL;
  contra_http_response *res = NULL;
  CURLcode res_ret;

  return_err(contra_http_response_new(&res));
  return_err(contra_http_buffer_new(&buffer));

  curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
  curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, res->error_message);
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER,
                   contra_http_set_headers(headers, req));
  curl_easy_setopt(curl, CURLOPT_URL, req->url);
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

on_error:
  if (ret_code != CONTRA_ERR_HTTP) {
    contra_http_response_free(&res);
    contra_http_buffer_free(&buffer);
  }
cleanup:
  if (NULL != headers)
    curl_slist_free_all(headers);
  if (NULL != curl)
    curl_easy_cleanup(curl);
  return ret_code;
}

int contra_http_post(contra_http_response **out,
                     const contra_http_request *req) {
  int ret_code = 0;
  Buffer *buffer = NULL;
  CURL *curl = NULL;
  struct curl_slist *headers = NULL;
  contra_http_response *res = NULL;
  CURLcode res_ret;

  return_err(contra_http_response_new(&res));
  return_err(contra_http_buffer_new(&buffer));

  curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
  curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, res->error_message);
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER,
                   contra_http_set_headers(headers, req));
  if (NULL != req->body) {
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, req->body);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE_LARGE,
                     (curl_off_t)strlen(req->body));
  }
  curl_easy_setopt(curl, CURLOPT_URL, req->url);
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

on_error:
  if (ret_code != CONTRA_ERR_HTTP) {
    contra_http_response_free(&res);
    contra_http_buffer_free(&buffer);
  }
cleanup:
  if (NULL != headers)
    curl_slist_free_all(headers);
  if (NULL != curl)
    curl_easy_cleanup(curl);
  return ret_code;
}

int contra_http_request_append_header(contra_http_request *req,
                                      const char *header) {
  int ret_code = 0;
  char **headers = req->headers;

  if (req->headers_count) {
    headers = realloc(headers, sizeof(char *) * (req->headers_count + 1));
  } else {
    headers = malloc(sizeof(char *));
  }
  if (NULL == headers) {
    return_err_now(CONTRA_ERR_MALLOC);
  }
  return_err(contra_str_copy(&(headers[req->headers_count]), header));

  req->headers = headers;
  req->headers_count += 1;

on_error:
cleanup:
  return ret_code;
}

void contra_http_request_free(contra_http_request **req) {
  contra_http_request *r = *req;
  if (NULL == r)
    return;
  if (NULL != r->headers) {
    for (int i = 0; i < r->headers_count; i++) {
      free(r->headers[i]);
    }
    free(r->headers);
  }
  if (NULL != r->body)
    free(r->body);
  if (NULL != r->url)
    free(r->url);
  free(r);
  *req = NULL;
}

int contra_http_request_new(contra_http_request **out, const char *url) {
  int ret_code = 0;
  contra_http_request *req = malloc(sizeof(contra_http_request));
  if (NULL == req) {
    return_err_now(CONTRA_ERR_MALLOC);
  }

  req->body = NULL;
  req->headers = NULL;
  req->headers_count = 0;
  req->url = NULL;

  return_err(contra_str_copy(&(req->url), url));

  *out = req;

on_error:
  if (NULL != req)
    contra_http_request_free(&req);
cleanup:
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

on_error:
  contra_http_response_free(&res);
cleanup:
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
