/**
 * Contra's string handling.
 *
 * The MIT License (MIT)
 * Copyright (c) 2016 GochoMugo <mugo@forfuture.co.ke>
 */

#ifndef _CONTRA_string_h_
#define _CONTRA_string_h_ 1

/**
 * Copies the string into `out`.
 *
 * @param  out Copied string
 * @param  str String to be copied
 * @return 0 or error code
 */
int contra_str_copy(char **out, const char *str);

#endif
