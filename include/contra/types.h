/**
 * Contra's types.
 *
 * The MIT License (MIT)
 * Copyright (c) 2016 GochoMugo <mugo@forfuture.co.ke>
 * Copyright (c) 2016 Forfuture, LLC <we@forfuture.co.ke>
 */

#ifndef _CONTRA_types_h_
#define _CONTRA_types_h_ 1


/**
 * Path structure.
 */
typedef struct {
    /** Path to the root directory */
    char *root;
    /** Path to the directory for this path */
    char *dir;
    /** Full filename */
    char *base;
    /** Name of the file, without the extension */
    char *name;
    /** Extension of the file */
    char *ext;
} contra_path_struct;


#endif
