/**
 * Contra's base definitions, such as control-flow helpers.
 *
 * The MIT License (MIT)
 * Copyright (c) 2016 GochoMugo <mugo@forfuture.co.ke>
 */

#ifndef _CONTRA_base_h_
#define _CONTRA_base_h_ 1

/**
 * Define booleans; 'true' and 'false'.
 */
#define bool unsigned int
#define true 1
#define false 0

/**
 * Defines error section of the function.
 */
#define on_error                                                               \
  goto __contra_cleanup;                                                       \
  __contra_on_error

/**
 * Defines clean-up section of the function.
 */
#define cleanup                                                                \
  goto __contra_cleanup;                                                       \
  __contra_cleanup

/**
 * Set 'ret_code' to 'result' and jump to cleanup.
 */
#define return_ok(result)                                                      \
  {                                                                            \
    ret_code = result;                                                         \
    goto __contra_cleanup;                                                     \
  }

/**
 * If 'result' is less than zero, set the 'ret_code' to 'result' and
 * jump to error-handling.
 */
#ifdef contra_error_set_cb
#define return_err(result)                                                     \
  ret_code = result;                                                           \
  if (0 > ret_code) {                                                          \
    contra_error_set_cb(ret_code);                                             \
    goto __contra_on_error;                                                    \
  }
#else
#define return_err(result)                                                     \
  ret_code = result;                                                           \
  if (0 > ret_code) {                                                          \
    goto __contra_on_error;                                                    \
  }
#endif

/**
 * If 'result' is less than zero, set the 'ret_code' to 'custom_err' and
 * jump to error-handling.
 */
#ifdef contra_error_set_cb
#define return_err_ext(result, custom_err)                                     \
  ret_code = result;                                                           \
  if (0 > ret_code) {                                                          \
    ret_code = custom_err;                                                     \
    contra_error_set_cb(ret_code);                                             \
    goto __contra_on_error;                                                    \
  }
#else
#define return_err_ext(result, custom_err)                                     \
  ret_code = result;                                                           \
  if (0 > ret_code) {                                                          \
    ret_code = custom_err;                                                     \
    goto __contra_on_error;                                                    \
  }
#endif

/**
 * Set 'ret_code' to 'custom_err' and jump to error-handling.
 */
#ifdef contra_error_set_cb
#define return_err_now(custom_err)                                             \
  {                                                                            \
    ret_code = custom_err;                                                     \
    contra_error_set_cb(ret_code);                                             \
    goto __contra_on_error;                                                    \
  }
#else
#define return_err_now(custom_err)                                             \
  {                                                                            \
    ret_code = custom_err;                                                     \
    goto __contra_on_error;                                                    \
  }
#endif

#endif
