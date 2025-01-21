/**
 * Contra's HTTP mini-library.
 *
 * The MIT License (MIT)
 * Copyright (c) 2016 GochoMugo <mugo@forfuture.co.ke>
 */

#ifndef _CONTRA_http_h_
#define _CONTRA_http_h_ 1

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
int contra_http_get(contra_http_response **out, const char * url);

/**
 * Sends a POST request to the specified URL.
 *
 * @param  out Response
 * @param  url URL
 * @param  body Body
 * @return 0 or error code
 */
int contra_http_post(contra_http_response **out, const char *url,
                     const char *body);

/**
 * Frees a HTTP response.
 *
 * @param  res Response
 */
void contra_http_response_free(contra_http_response **res);

#endif
