/**
 * Contra's process handling.
 *
 * The MIT License (MIT)
 * Copyright (c) 2016 GochoMugo <mugo@forfuture.co.ke>
 */

#ifndef _CONTRA_proc_h_
#define _CONTRA_proc_h_ 1

#ifndef CONTRA_PROC_EXEC_BUFFER_SIZE
#define CONTRA_PROC_EXEC_BUFFER_SIZE 1024 // 1 kb (in bytes)
#endif

/**
 * Executes the command in a new process and
 * returns its entire stdout in `out`.
 *
 * @param  out Process output (stdout)
 * @param  command Command passed to `sh -c`
 * @return 0 or error code
 */
int contra_proc_exec(char **out, const char *command);

#endif
