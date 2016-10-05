/**
 * Contra's FS mini-library.
 *
 * The MIT License (MIT)
 * Copyright (c) 2016 GochoMugo <mugo@forfuture.co.ke>
 * Copyright (c) 2016 Forfuture, LLC <we@forfuture.co.ke>
 */


#include "../../include/contra.h"
#include "index.h"


int
contra_fs_chmod_sync(const char *path, mode_t mode) {
    int ret_code = 0;

    ret_code = chmod(path, mode);
    return_err_ext(ret_code, ERR(SYS));

_on_error
_cleanup
    return ret_code;
}


int
contra_fs_fchmod_sync(int fd, mode_t mode) {
    int ret_code = 0;

    ret_code = fchmod(fd, mode);
    return_err_ext(ret_code, ERR(SYS));

_on_error
_cleanup
    return ret_code;
}


int
contra_fs_chown_sync(const char *path, uid_t uid, gid_t gid) {
    int ret_code = 0;

    ret_code = chown(path, uid, gid);
    return_err_ext(ret_code, ERR(SYS));

_on_error
_cleanup
    return ret_code;
}


int
contra_fs_fchown_sync(int fd, uid_t uid, gid_t gid) {
    int ret_code = 0;

    ret_code = fchown(fd, uid, gid);
    return_err_ext(ret_code, ERR(SYS));

_on_error
_cleanup
    return ret_code;
}


int
contra_fs_lchown_sync(const char *path, uid_t uid, gid_t gid) {
    int ret_code = 0;

    ret_code = lchown(path, uid, gid);
    return_err_ext(ret_code, ERR(SYS));

_on_error
_cleanup
    return ret_code;
}
