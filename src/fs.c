/**
 * Contra's filesystem mini-library.
 *
 * The MIT License (MIT)
 * Copyright (c) 2016 GochoMugo <mugo@forfuture.co.ke>
 */

#include "index.h"

// See
// https://github.com/kgabis/parson/blob/ba29f4eda9ea7703a9f6a9cf2b0532a2605723c3/parson.c#L206C1-L237C2
int contra_fs_read_file(char **out, char *filename) {
  int ret_code = 0;
  FILE *stream = fopen(filename, "r");
  if (NULL == stream) {
    return_err_now(CONTRA_ERR_FS_OPEN);
  }

  return_err(fseek(stream, 0L, SEEK_END));
  return_err(ftell(stream));
  size_t file_size = ret_code;
  return_err(fseek(stream, 0L, SEEK_SET));

  char *buffer = malloc(sizeof(char) * (file_size + 1));
  if (NULL == buffer) {
    return_err_now(CONTRA_ERR_MALLOC);
  }

  return_err(fread(buffer, 1, file_size, stream));
  if (ret_code != file_size) {
    return_err_now(CONTRA_ERR_FS_READ);
  }

  buffer[file_size] = '\0';

  *out = buffer;
  ret_code = 0;

on_error:
  if (NULL != buffer)
    free(buffer);
cleanup:
  if (NULL != stream)
    fclose(stream);
  return ret_code;
}
