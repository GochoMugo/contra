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

int contra_str_trim(char **out, char *str) {
  int ret_code = 0;
  int len = strlen(str);
  char *temp = NULL;

  int start = 0;
  int end = len - 1;
  while (isspace((str)[start]))
    start++;
  while (isspace((str)[end]))
    end--;
  int size = end - start + 1;

  temp = malloc(size + 1);
  if (NULL == temp) {
    return_err_now(CONTRA_ERR_MALLOC);
  }

  memcpy(temp, str + start, size);
  temp[size] = '\0';
  *out = temp;

on_error:
  if (NULL != temp)
    free(temp);
cleanup:
  return ret_code;
}
