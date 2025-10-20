/**
 * Contra's time mini-library.
 *
 * The MIT License (MIT)
 * Copyright (c) 2016 GochoMugo <mugo@forfuture.co.ke>
 *
 * \file time.h
 */

#ifndef _CONTRA_time_h_
#define _CONTRA_time_h_ 1

/**
 * Returns the current time as milliseconds since epoch.
 *
 * @param  out Current time
 * @return 0 or error code
 */
int contra_time_now(long long *out);

#endif
