/**
 * Contra's HTTP mini-library.
 *
 * The MIT License (MIT)
 * Copyright (c) 2016 GochoMugo <mugo@forfuture.co.ke>
 *
 * \file http.h
 */

#ifndef _CONTRA_http_h_
#define _CONTRA_http_h_ 1

/** HTTP request. */
typedef struct contra_http_request {
  char *body;
  char **headers;
  int headers_count;
  char *url;
} contra_http_request;

/** HTTP response. */
typedef struct contra_http_response {
  char *body;
  int error_code;
  char *error_message;
  int status_code;
} contra_http_response;

/**
 * Sends a GET request to the specified URL.
 *
 * @param out Response
 * @param url URL
 * @return 0 or error code
 */
int contra_http_get(contra_http_response **out, const contra_http_request *req);

/**
 * Sends a POST request to the specified URL.
 *
 * @param  out Response
 * @param  url URL
 * @param  body Body
 * @return 0 or error code
 */
int contra_http_post(contra_http_response **out,
                     const contra_http_request *req);

/**
 * Appends a header to the request.
 *
 * @param out Request
 * @param header Header
 */
int contra_http_request_append_header(contra_http_request *req,
                                      const char *header);

/**
 * Frees a HTTP request.
 *
 * @param  req Request
 */
void contra_http_request_free(contra_http_request **req);

/**
 * Creates a new HTTP request.
 *
 * Any memory that is assigned to any request property
 * is considered owned by the request object.
 *
 * The `url` passed is copied into the request object.
 *
 * @param out Request
 * @param url URL
 */
int contra_http_request_new(contra_http_request **out, const char *url);

/**
 * Frees a HTTP response.
 *
 * @param  res Response
 */
void contra_http_response_free(contra_http_response **res);

#endif
