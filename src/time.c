/**
 * Contra's time mini-library.
 *
 * The MIT License (MIT)
 * Copyright (c) 2016 GochoMugo <mugo@forfuture.co.ke>
 */

#include "index.h"

int contra_time_now(long long *out) {
  int ret_code = 0;
  struct timeval time;

  return_err(gettimeofday(&time, NULL));
  *out = (time.tv_sec * 1e3) + (time.tv_usec / 1e3);

on_error:
cleanup:
  return ret_code;
}
