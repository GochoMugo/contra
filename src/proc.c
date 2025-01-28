/**
 * Contra's process handling.
 *
 * The MIT License (MIT)
 * Copyright (c) 2016 GochoMugo <mugo@forfuture.co.ke>
 */

#include "index.h"

int contra_proc_exec(char **out, const char *command) {
  int ret_code = 0;
  int exit_code = -1;
  char *output = NULL;
  int output_size = 0;
  FILE *proc = NULL;
  int proc_status = -1;
  int read_bytes = 0;
  int reads = 0;

  proc = popen(command, "r");
  if (NULL == proc) {
    return_err_now(CONTRA_ERR_PROC_EXEC);
  }

  do {
    size_t chunk_size = sizeof(char) * CONTRA_PROC_EXEC_BUFFER_SIZE;
    size_t offset = chunk_size * reads;
    size_t buffer_size = chunk_size * (reads + 1);

    output = realloc(output, buffer_size);
    if (NULL == output) {
      return_err_now(CONTRA_ERR_MALLOC);
    }

    read_bytes = read(fileno(proc), output + offset, chunk_size);
    return_err(read_bytes);

    output_size += read_bytes;
    reads++;
  } while (0 < read_bytes);

  proc_status = pclose(proc);
  proc = NULL;
  if (!WIFEXITED(proc_status)) {
    return_err_now(CONTRA_ERR_PROC_EXEC);
  }

  exit_code = WEXITSTATUS(proc_status);
  if (0 != exit_code) {
    return_err_now(CONTRA_ERR_PROC_EXEC);
  }

  output = realloc(output, output_size + 1);
  if (NULL == output) {
    return_err_now(CONTRA_ERR_MALLOC);
  }
  output[output_size] = '\0';

  *out = output;
  return_ok(0);

on_error:
  if (NULL != output)
    free(output);
  if (NULL != proc)
    pclose(proc);
cleanup:
  return ret_code;
}
