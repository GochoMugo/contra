/**
 * Contra's Errors
 *
 * The MIT License (MIT)
 * Copyright (c) 2016 GochoMugo <mugo@forfuture.co.ke>
 * Copyright (c) 2016 Forfuture, LLC <we@forfuture.co.ke>
 */

#ifndef _CONTRA_error_h_
#define _CONTRA_error_h_ 1


/** Errors */
#define ERR_START -101
#define ERR(x) CONTRA_ERR_##x
typedef enum {
    ERR(START) = ERR_START,

    ERR(MALLOC),
    ERR(BAD_ARGS),
} contra_error_code;

#endif
