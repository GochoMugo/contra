/**
 * Contra's Path mini-library.
 *
 * The MIT License (MIT)
 * Copyright (c) 2016 GochoMugo <mugo@forfuture.co.ke>
 */

#include "index.h"

/**
 * Return 'true' if path 'p' is falsey, i.e. NULL or empty string.
 * Otherwise, false.
 *
 * @param  p Path to check
 * @return true/false
 */
#define contra_path__falsey(p) (NULL == p || strlen(p) == 0 || '\0' == p[0])

int contra_path__rtrim(char **out, const char *path, int needle) {
  int ret_code = 0;
  size_t path_len = -1;
  int rindex;
  char *trimmed_path = NULL;
  int trimmed_path_len = -1;

  assert(path);

  path_len = strlen(path);
  rindex = path_len - 1;

  while (needle == path[rindex])
    rindex--;

  trimmed_path_len = rindex + 1;
  trimmed_path = (char *)malloc(trimmed_path_len + 1);
  if (contra_is_null(trimmed_path)) {
    return_err_now(CONTRA_ERR_MALLOC);
  }

  strncpy(trimmed_path, path, trimmed_path_len);
  trimmed_path[trimmed_path_len] = '\0';

  *out = trimmed_path;

_on_error:
  if (NULL != trimmed_path)
    free(trimmed_path);
_cleanup:
  return ret_code;
}

/**
 * #pseudocode
 * 1. If 'segment1' is falsey, but not 'segment2', return 'segment2'
 * 2. If 'segment2' is falsey, but not 'segment1', return 'segment1'
 * 3. If 'segment1' and 'segment2' are falsey, return error CONTRA_ERR_BAD_ARGS
 * 4. Otherwise,
 * 4.1 Set 'out' to 'segment1'
 * 4.1. If 'segment2' does not start with a '/', append '/' to 'out'
 * 4.2. Append 'segment2' to 'out' and return 'out'
 * #endpseudocode
 */
int contra_path_join(char **out, const char *segment1, const char *segment2) {
  int ret_code = 0;
  int segment1_falsey, segment2_falsey;
  char *path = NULL;
  int segment2_slashed = false;
  char *segment1_trimmed = NULL;

  segment1_falsey = contra_path__falsey(segment1);
  segment2_falsey = contra_path__falsey(segment2);

  if (segment1_falsey || segment2_falsey) {
    if (!segment1_falsey) {
      return_err(contra_str_copy(&path, segment1));
    } else if (!segment2_falsey) {
      return_err(contra_str_copy(&path, segment2));
    } else {
      return_err_now(CONTRA_ERR_BAD_ARGS);
    }
    *out = path;
    return_ok(ret_code);
  }

  assert(segment1);
  assert(segment2);

  segment2_slashed = '/' == segment2[0];

  ret_code = contra_path__rtrim(&segment1_trimmed, segment1, '/');
  return_err(ret_code);

  ret_code = asprintf(&path, "%s%s%s", segment1_trimmed,
                      (segment2_slashed ? "" : "/"), segment2);
  return_err_ext(ret_code, CONTRA_ERR_MALLOC);

  *out = path;
  ret_code = 0;

_on_error:
  if (NULL != path)
    free(path);
_cleanup:
  if (NULL != segment1_trimmed)
    free(segment1_trimmed);
  return ret_code;
}
