/**
 * Contra's string handling.
 *
 * The MIT License (MIT)
 * Copyright (c) 2016 GochoMugo <mugo@forfuture.co.ke>
 */

#include "index.h"

int contra_str_copy(char **out, const char *str) {
  int size = strlen(str);
  char *ptr = malloc(size + 1);
  if (NULL == ptr) {
    return CONTRA_ERR_MALLOC;
  }
  strncpy(ptr, str, size);
  ptr[size] = '\0';
  *out = ptr;
  return 0;
}
