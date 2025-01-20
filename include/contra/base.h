/**
 * Contra's base definitions, such as control-flow helpers.
 *
 * The MIT License (MIT)
 * Copyright (c) 2016 GochoMugo <mugo@forfuture.co.ke>
 */

#ifndef _CONTRA_base_h_
#define _CONTRA_base_h_ 1

/**
 * Temporary buffers for return codes
 * and custom error codes.
 *
 * Using these variables avoid any macro arguments
 * from being substituted more than once.
 */
static int __contra_rc = 0;
static int __contra_ce = 0;

/**
 * Define booleans; 'true' and 'false'.
 */
#define bool unsigned int
#define true 1
#define false 0

/**
 * Defines error section of the function.
 */
#define _on_error                                                              \
  goto cleanup;                                                                \
  on_error

/**
 * Defines clean-up section of the function.
 */
#define _cleanup                                                               \
  goto cleanup;                                                                \
  cleanup

/**
 * Set 'ret_code' to 'result' and jump to cleanup.
 */
#define return_ok(result)                                                      \
  {                                                                            \
    __contra_rc = result;                                                      \
    ret_code = __contra_rc;                                                    \
    goto cleanup;                                                              \
  }

/**
 * If 'result' is less than zero, set the 'ret_code' to 'result' and
 * jump to error-handling.
 */
#ifdef contra_error_set_cb
#define return_err(result)                                                     \
  __contra_rc = result;                                                        \
  if (0 > __contra_rc) {                                                       \
    contra_error_set_cb(__contra_rc);                                          \
    ret_code = __contra_rc;                                                    \
    goto on_error;                                                             \
  }
#else
#define return_err(result)                                                     \
  __contra_rc = result;                                                        \
  if (0 > __contra_rc) {                                                       \
    ret_code = __contra_rc;                                                    \
    goto on_error;                                                             \
  }
#endif

/**
 * If 'result' is less than zero, set the 'ret_code' to 'custom_err' and
 * jump to error-handling.
 */
#ifdef contra_error_set_cb
#define return_err_ext(result, custom_err)                                     \
  __contra_rc = result;                                                        \
  __contra_ce = custom_err;                                                    \
  if (0 > __contra_rc) {                                                       \
    contra_error_set_cb(__contra_ce);                                          \
    ret_code = __contra_ce;                                                    \
    goto on_error;                                                             \
  }
#else
#define return_err_ext(result, custom_err)                                     \
  __contra_rc = result;                                                        \
  __contra_ce = custom_err;                                                    \
  if (0 > __contra_rc) {                                                       \
    ret_code = __contra_ce;                                                    \
    goto on_error;                                                             \
  }
#endif

/**
 * Set 'ret_code' to 'custom_err' and jump to error-handling.
 */
#ifdef contra_error_set_cb
#define return_err_now(custom_err)                                             \
  {                                                                            \
    __contra_ce = custom_err;                                                  \
    contra_error_set_cb(__contra_ce);                                          \
    ret_code = __contra_ce;                                                    \
    goto on_error;                                                             \
  }
#else
#define return_err_now(custom_err)                                             \
  {                                                                            \
    __contra_ce = custom_err;                                                  \
    ret_code = __contra_ce;                                                    \
    goto on_error;                                                             \
  }
#endif

#endif
