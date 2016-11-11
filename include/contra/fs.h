/**
 * Contra's FS mini-library.
 *
 * The MIT License (MIT)
 * Copyright (c) 2016 GochoMugo <mugo@forfuture.co.ke>
 * Copyright (c) 2016 Forfuture, LLC <we@forfuture.co.ke>
 */

#ifndef _CONTRA_fs_h_
#define _CONTRA_fs_h_


#ifdef _WIN32
#define CONTRA_FS_OPEN_READ "rb"
#define CONTRA_FS_OPEN_WRITE "wb"
#define CONTRA_FS_OPEN_READWRITE "rwb"
#else
#define CONTRA_FS_OPEN_READ "r"
#define CONTRA_FS_OPEN_WRITE "w"
#define CONTRA_FS_OPEN_READWRITE "rw"
#endif


#endif
