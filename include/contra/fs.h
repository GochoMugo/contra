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

#define CONTRA_FS_OPEN_R
#define CONTRA_FS_OPEN_R+
#define CONTRA_FS_OPEN_W
#define CONTRA_FS_OPEN_W+
#define CONTRA_FS_OPEN_WX
#define CONTRA_FS_OPEN_WX+
#define CONTRA_FS_OPEN_A
#define CONTRA_FS_OPEN_AX
#define CONTRA_FS_OPEN_AX+
#endif


/**
 * Change mode of file pointed to by 'path'.
 * See chmod(2).
 *
 * @param  path Path to the file
 * @param  mode The new mode
 * @return 0 or error code
 */
int
contra_fs_chmod_sync(const char *path, mode_t mode);


/**
 * Change mode of file associated with 'fd'.
 * See fchmod(2).
 *
 * @param  fd File descriptor
 * @param  mode The new mode
 * @return 0 or error code
 */
int
contra_fs_fchmod_sync(int fd, mode_t mode);


/**
 * Change ownership of file, pointed to by 'path'.
 * See chown(2).
 *
 * @param  path Path to file
 * @param  uid User ID
 * @param  gid Group ID
 * @return 0 or error code
 */
int
contra_fs_chown_sync(const char *path, uid_t uid, gid_t gid);


/**
 * Change ownership of file, associated with 'fd'.
 * See fchown(2).
 *
 * @param  fd File descriptor
 * @param  uid User ID
 * @param  gid Group ID
 * @return 0 or error code
 */
int
contra_fs_fchown_sync(int fd, uid_t uid, gid_t gid);


/**
 * Change ownership of symbolic link, pointed to by 'path'.
 * See lchown(2).
 *
 * @param  path Path to symbolic link
 * @param  uid User ID
 * @param  gid Group ID
 * @return 0 or error code
 */
int
contra_fs_lchown_sync(const char *path, uid_t uid, gid_t gid);


#endif
