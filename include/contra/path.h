/**
 * Contra's Path mini-library.
 *
 * The MIT License (MIT)
 * Copyright (c) 2016 GochoMugo <mugo@forfuture.co.ke>
 * Copyright (c) 2016 Forfuture, LLC <we@forfuture.co.ke>
 */

#ifndef _CONTRA_path_h_
#define _CONTRA_path_h_ 1


/**
 * Return the last portion of the 'path', similar to the UNIX
 * `basename` command.
 *
 * @param  out Basename
 * @param  path Path being inspected
 * @return 0 or error code
 */
int
contra_path_basename(char **out, const char *path);


/**
 * Remove the extension from the 'path'. This will usually be
 * used together with `contra_path_basename`.
 *
 * @param  out Extension-less path
 * @param  path Path being inspected
 * @return 0 or error code
 */
int
contra_path_noext(char **out, const char *path);


/**
 * Return the directory name of a path, similar to UNIX `dirname`
 * command.
 *
 * @param  out Dirname
 * @param  path Path being inspected
 * @return 0 or error code
 */
int
contra_path_dirname(char **out, const char *path);


/**
 * Return the extension of the 'path'.
 *
 * @param  out Extension of path
 * @param  path Path being inspected
 * @return 0 or error code
 */
int
contra_path_extname(char **out, const char *path);


/**
 * Return a path string from a broken-down path structure.
 *
 * @param  out Path string
 * @param  path_struct Path struct
 * @return 0 or error code
 */
int
contra_path_format(char **out, const contra_path_struct *path_struct);


/**
 * Return true if 'path' is absolute.
 *
 * @param  out Boolean return value
 * @param  path Path being inspected
 * @return 0 or error code
 */
int
contra_path_is_abs(int *out, const char *path);


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
 * Normalize path.
 *
 * @param  out Normalized path
 * @param  path Path being inspected
 * @return 0 or error code
 */
int
contra_path_normalize(char **out, const char *path);


/**
 * Parse a path string into a path structure.
 *
 * @param  out Path structure
 * @param  path Path being inspected
 * @return 0 or error code
 */
int
contra_path_parse(contra_path_struct **out, const char *path);


/**
 * Resolve a path into an absolute path.
 *
 * @param  out Absolute path
 * @param  path Path being resolved
 * @return 0 or error code
 */
int
contra_path_resolve(char **out, const char *path);


/**
 * Return a relative path from 'from' to 'to'.
 * If 'from' is `NULL`, we assume the current working directory as 'from'.
 *
 * @param  out Relative path
 * @param  from From
 * @param  to To
 * @return 0 or CONTRA_ERR_BAD_ARGS if 'to' is NULL
 */
int
contra_path_relative(char **out, const char *from, const char *to);


/**
 * Similar to `contra_path_resolve` but allows variadic arguments.
 *
 * @param  out Absolute path
 * @param  ... Path segments
 * @return 0 or error code
 */
int
contra_path_resolve_v(char **out, ...);


#endif
