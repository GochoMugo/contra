
/**
 * Contra's filesystem mini-library.
 *
 * The MIT License (MIT)
 * Copyright (c) 2016 GochoMugo <mugo@forfuture.co.ke>
 *
 * \file fs.h
 */

#ifndef _CONTRA_fs_h_
#define _CONTRA_fs_h_ 1

/**
 * Reads the entire contents of a file into a buffer.
 *
 * @param  out Buffer
 * @param  filename Filename
 * @return 0 or error code
 */
int contra_fs_read_file(char **out, char *filename);

#endif
