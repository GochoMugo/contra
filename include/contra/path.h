/**
 * Contra's Path mini-library.
 *
 * The MIT License (MIT)
 * Copyright (c) 2016 GochoMugo <mugo@forfuture.co.ke>
 */

#ifndef _CONTRA_path_h_
#define _CONTRA_path_h_ 1


/**
 * Join path segments into a complete path string.
 *
 * @param  out Path string
 * @param  segment1 First path segment
 * @param  segment2 Second path segment
 * @return 0 or error code
 */
int
contra_path_join(char **out, const char *segment1, const char *segment2);


/**
 * Return 'true' if path 'p' is falsey, i.e. NULL or empty string.
 * Otherwise, false.
 *
 * @param  p Path to check
 * @return true/false
 */
#define contra_path__falsey(p) (NULL == p || strlen(p) == 0 || '\0' == p[0])


#endif
