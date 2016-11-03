/**
 * Contra's base definitions, such as control-flow helpers.
 *
 * The MIT License (MIT)
 * Copyright (c) 2016 GochoMugo <mugo@forfuture.co.ke>
 * Copyright (c) 2016 Forfuture, LLC <we@forfuture.co.ke>
 */

#ifndef _CONTRA_base_h_
#define _CONTRA_base_h_ 1


/**
 * Define 'true' and 'false'.
 */
#define true 1
#define false 0


/**
 * Defines error section of the function.
 */
#define _on_error goto cleanup; on_error:


/**
 * Defines clean-up section of the function.
 */
#define _cleanup goto cleanup; cleanup:


/**
 * Set 'ret_code' to 0 and jump to cleanup.
 */
#define return_ok(ret_code) { ret_code = 0; goto cleanup; }


/**
 * If 'result' is less than zero, set the 'ret_code' to 'result' and
 * jump to error-handling.
 */
#define return_err(result) if (0 > result) { ret_code = result; goto on_error; }


/**
 * If 'result' is less than zero, set the 'ret_code' to 'custom_err' and
 * jump to error-handling.
 */
#define return_err_ext(result, custom_err) if (0 > result) { ret_code = custom_err; goto on_error; }


/**
 * Set 'ret_code' to 'custom_err' and jump to error-handling.
 */
#define return_err_now(custom_err) { ret_code = custom_err; goto on_error; }


#endif
