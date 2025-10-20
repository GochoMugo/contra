/**
 * Contra's Errors
 *
 * The MIT License (MIT)
 * Copyright (c) 2016 GochoMugo <mugo@forfuture.co.ke>
 *
 * \file error.h
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
  /** Failed to open a file. */
  CONTRA_ERR_FS_OPEN,
  /** Failed to read a file. */
  CONTRA_ERR_FS_READ,
  /** An HTTP error occurred. */
  CONTRA_ERR_HTTP,
  /** Failed to execute a command. */
  CONTRA_ERR_PROC_EXEC,
} contra_error_code;

#endif
