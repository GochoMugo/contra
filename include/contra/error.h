/**
 * Contra's Errors
 *
 * The MIT License (MIT)
 * Copyright (c) 2016 GochoMugo <mugo@forfuture.co.ke>
 */

#ifndef _CONTRA_error_h_
#define _CONTRA_error_h_ 1

/** Errors */
typedef enum {
  /* General errors */
  CONTRA_ERR = -1000,
  /** Could not allocate memory. */
  CONTRA_ERR_MALLOC,
  /** Bad arguments were provided. */
  CONTRA_ERR_BAD_ARGS,
} contra_error_code;

#endif
