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
int contra_path_join(char **out, const char *segment1, const char *segment2);

#endif
