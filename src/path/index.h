/**
 * Contra's Path mini-library.
 *
 * The MIT License (MIT)
 * Copyright (c) 2016 GochoMugo <mugo@forfuture.co.ke>
 * Copyright (c) 2016 Forfuture, LLC <we@forfuture.co.ke>
 */

#ifndef _CONTRA_src_path_h_
#define _CONTRA_src_path_h_ 1


#define CONTRA_PATH__BUFFER_LEN      32
#define CONTRA_PATH__DIRECTION_LEFT  1
#define CONTRA_PATH__DIRECTION_RIGHT 2


/**
 * Return a substring from the 'path'.
 * If 'direction' equals 'CONTRA_PATH__DIRECTION_LEFT': starting from the
 * start to the character just before the last character equal to 'last_char'.
 * If 'direction' equals 'CONTRA_PATH__DIRECTION_RIGHT': starting from the
 * character just after the last character equal to 'last_char' to the end of
 * the string.
 * If 'last_char' is not found, the end of the string is assumed, hence,
 * if direction is "left", the whole of 'path' is returned, and
 * if direction is "right", an empty string is returned.
 *
 * @param  out Substring of path
 * @param  path Path being inspected
 * @param  last_char Character being searched for, from the right
 * @param  direction Direction to use. Can be CONTRA_PATH__DIRECTION_LEFT or
 *  CONTRA_PATH__DIRECTION_RIGHT
 * @return 0 or error code
 */
int
contra_path__substr(char **out, const char *path, int last_char,
        int direction);


/**
 * Trim the character 'needle' from the 'path', on the right end.
 * A newly-allocated string is placed in 'out', thus the original
 * 'path' is not modified.
 *
 * @param  out Trimmed path
 * @param  path Path to trim
 * @param  needle Character to search for
 * @return 0 or error code
 */
int
contra_path__rtrim(char **out, const char *path, int needle);


/**
 * Right-trim the path and retrieve a substring from the trimmed version.
 * This handles freeing the intermediate, trimmed version of the path.
 *
 * @param  out Substring of the trimmed path
 * @param  path Path to trim and substring
 * @param  last_char Character to search for
 * @param  direction Direction to be passed to substring
 * @return 0 or error code
 */
int
contra_path__rtrim_substr(char **out, const char *path, int last_char, int direction);


/**
 * Return 'true' if path 'p' is falsey, i.e. NULL or empty string.
 * Otherwise, false.
 *
 * @param  p Path to check
 * @return true/false
 */
#define contra_path__falsey(p) (NULL == p || '\0' == p[0])


#endif
