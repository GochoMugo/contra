/**
 * Contra's Path mini-library.
 *
 * The MIT License (MIT)
 * Copyright (c) 2016 GochoMugo <mugo@forfuture.co.ke>
 * Copyright (c) 2016 Forfuture, LLC <we@forfuture.co.ke>
 */


#include "../../include/contra.h"
#include "index.h"


int
contra_path__substr(char **out, const char *path, int last_char, int direction) {
    int ret_code = 0;
    size_t path_len = -1;
    const char *suffix = NULL;
    size_t suffix_len = -1;
    char *last_slash = NULL;
    char *new_path = NULL;
    size_t new_path_len = -1;

    assert(path);

    path_len = strlen(path);

    suffix = rindex(path, last_char);
    if (is_null(suffix)) {
        suffix = path + path_len;
    } else {
        if (CONTRA_PATH__DIRECTION_RIGHT == direction) suffix++;
    }

    suffix_len = strlen(suffix);

    /* if the suffix is not '/', ensure the found 'last_char'
     * is after the last '/' */
    if ('/' != last_char) {
        last_slash = rindex(path, '/');
        if (!(is_null(last_slash)) && strlen(last_slash) < suffix_len) {
            suffix = path + path_len;
            suffix_len = 0;
        }
    }

    if (CONTRA_PATH__DIRECTION_LEFT == direction) new_path_len = path_len - suffix_len;
    else new_path_len = suffix_len;

    new_path = (char *) malloc(new_path_len + 1);
    if (is_null(new_path)) {
        return_err_now(ERR(MALLOC));
    }

    if (CONTRA_PATH__DIRECTION_LEFT == direction) strncpy(new_path, path, new_path_len);
    else strncpy(new_path, suffix, new_path_len);

    new_path[new_path_len] = '\0';

    *out = new_path;

_on_error
    if (NULL != new_path) free(new_path);
_cleanup
    return ret_code;
}


int
contra_path__rtrim(char **out, const char *path, int needle) {
    int ret_code = 0;
    size_t path_len = -1;
    int rindex;
    char *trimmed_path = NULL;
    int trimmed_path_len = -1;

    assert(path);

    path_len = strlen(path);
    rindex = path_len - 1;

    while (needle == path[rindex]) rindex--;

    trimmed_path_len = rindex + 1;
    trimmed_path = (char *) malloc(trimmed_path_len + 1);
    if (is_null(trimmed_path)) {
        return_err_now(ERR(MALLOC));
    }

    strncpy(trimmed_path, path, trimmed_path_len);
    trimmed_path[trimmed_path_len] = '\0';

    *out = trimmed_path;

_on_error
    if (NULL != trimmed_path) free(trimmed_path);
_cleanup
    return ret_code;
}


int
contra_path__rtrim_substr(char **out, const char *path, int last_char, int direction) {
    int ret_code = 0;
    char *trimmed_path = NULL;

    ret_code = contra_path__rtrim(&trimmed_path, path, last_char);
    return_err(ret_code);

    ret_code = contra_path__substr(out, trimmed_path, last_char, direction);
    return_err(ret_code);

_on_error
_cleanup
    if (NULL != trimmed_path) free(trimmed_path);
    return ret_code;
}


/**
 * #tests
 * "/home/gochomugo/todo.txt"   => "todo.txt"
 * "/home/gochomugo/projects"   => "projects"
 * "/home/gochomugo/"           => "gochomugo"
 * "/home/gochomugo//"          => "gochomugo"
 * "projects"                   => "projects"
 * "/"                          => ""
 * "."                          => "."
 * ".."                         => ".."
 * ""                           => ""
 * #endtests
 *
 * #pseudocode
 * 1. If 'path' does not contain '/', return 'path' as is
 * 2. Otherwise:
 * 2.1. Right-trim '/' from 'path'
 * 2.2. Return substring from the last '/' to end of string
 * #endpseudocode
 */
int
contra_path_basename(char **out, const char *path) {
    int ret_code = 0;
    char *basename = NULL;

    if (is_null(rindex(path, '/'))) {
        basename = strdup(path);
        if (is_null(basename)) return_err_now(ERR(MALLOC));
    } else {
        ret_code = contra_path__rtrim_substr(&basename, path, '/', CONTRA_PATH__DIRECTION_RIGHT);
        return_err(ret_code);
    }

    *out = basename;

_on_error
    if (NULL != basename) free(basename);
_cleanup
    return ret_code;
}


/**
 * #tests
 * "/home/gochomugo/todo.txt"   => "/home/gochomugo/todo"
 * "todo.txt"                   => "todo"
 * "/home/gocho.mugo/todo.txt"  => "/home/gocho.mugo/todo"
 * "/home/gocho.mugo/todo"      => "/home/gocho.mugo/todo"
 * "/home/gochomugo/"           => "/home/gochomugo/"
 * "/home/gochomugo//"          => "/home/gochomugo//"
 * ""                           => ""
 * #endtests
 */
int
contra_path_noext(char **out, const char *path) {
    return contra_path__substr(out, path, '.', CONTRA_PATH__DIRECTION_LEFT);
}


/**
 * #tests
 * "/home/gochomugo/todo.txt"   => "/home/gochomugo"
 * "/home/gochomugo/"           => "/home"
 * "/"                          => "/"
 * "."                          => "."
 * ".."                         => "."
 * ""                           => "."
 * #endtests
 *
 * #pseudocode
 * 1. If 'path' equals "/", return "/"
 * 2. If 'path' does not contain '/', return "."
 * 3. Otherwise, right-trim '/' and substring to the last '/'
 * #endpseudocode
 */
int
contra_path_dirname(char **out, const char *path) {
    int ret_code = 0;
    char *dirname = NULL;

    if (1 == strlen(path) && '/' == path[0]) {
        dirname = strdup("/");
        if (is_null(dirname)) return_err_now(ERR(MALLOC));
    } else if (is_null(rindex(path, '/'))) {
        dirname = strdup(".");
        if (is_null(dirname)) return_err_now(ERR(MALLOC));
    } else {
        ret_code = contra_path__rtrim_substr(&dirname, path, '/', CONTRA_PATH__DIRECTION_LEFT);
        return_err(ret_code);
    }

    *out = dirname;

_on_error
    if (NULL != dirname) free(dirname);
_cleanup
    return ret_code;
}


/**
 * #tests
 * "/home/gochomugo/todo.txt"   => "txt"
 * "/home/gochomugo/todo"       => ""
 * "/home/gochomugo/"           => ""
 * "/"                          => ""
 * "."                          => ""
 * ".."                         => ""
 * ""                           => ""
 * #endtests
 */
int
contra_path_extname(char **out, const char *path) {
    return contra_path__substr(out, path, '.', CONTRA_PATH__DIRECTION_RIGHT);
}


/**
 * #tests
 * "/root"                      => true
 * "/"                          => true
 * "projects"                   => false
 * "projects/"                  => false
 * "."                          => false
 * ".."                         => false
 * ""                           => false
 * #endtests
 */
int
contra_path_is_abs(int *out, const char *path) {
    int ret_code = 0;

    assert(path);

    *out = ('\0' != path[0]) && ('/' == path[0]);

_on_error
_cleanup
    return ret_code;
}


/**
 * #tests
 * "/home/gochomugo", "projects"  => "/home/gochomugo/projects"
 * "/home/gochomugo", "/projects" => "/home/gochomugo/projects"
 * "/home/gochomugo", "/"         => "/home/gochomugo/"
 * "/home/gochomugo/", "/"        => "/home/gochomugo/"
 * "/home/gochomugo", "."         => "/home/gochomugo/."
 * "/home/gochomugo", ".."        => "/home/gochomugo/.."
 * "gochomugo", "projects"        => "gochomugo/projects"
 * "gochomugo", "/projects"       => "gochomugo/projects"
 * "/home/gochomugo", NULL        => "/home/gochomugo"
 * "/home/gochomugo", ""          => "/home/gochomugo"
 * NULL, "projects"               => "projects"
 * NULL, "/projects"              => "/projects"
 * "", "projects"                 => "projects"
 * "", "/projects"                => "/projects"
 * "", NULL                       #> (CONTRA_ERR_BAD_ARGS)
 * "", ""                         #> (CONTRA_ERR_BAD_ARGS)
 * NULL, NULL                     #> (CONTRA_ERR_BAD_ARGS)
 * NULL, ""                       #> (CONTRA_ERR_BAD_ARGS)
 * #endtests
 *
 * #pseudocode
 * 1. If 'segment1' is falsey, but not 'segment2', return 'segment2'
 * 2. If 'segment2' is falsey, but not 'segment1', return 'segment1'
 * 3. If 'segment1' and 'segment2' are falsey, return error CONTRA_ERR_BAD_ARGS
 * 4. Otherwise,
 * 4.1 Set 'out' to 'segment1'
 * 4.1. If 'segment2' does not start with a '/', append '/' to 'out'
 * 4.2. Append 'segment2' to 'out' and return 'out'
 * #endpseudocode
 */
int
contra_path_join(char **out, const char *segment1, const char *segment2) {
    int ret_code = 0;
    int segment1_falsey, segment2_falsey;
    char *path = NULL;
    int segment2_slashed = false;
    char *segment1_trimmed = NULL;

    segment1_falsey = contra_path__falsey(segment1);
    segment2_falsey = contra_path__falsey(segment2);

    if (segment1_falsey || segment2_falsey) {
        if (!segment1_falsey) path = strdup(segment1);
        else if (!segment2_falsey) path = strdup(segment2);
        else return_err_now(ERR(BAD_ARGS));
        if (is_null(path)) return_err_now(ERR(MALLOC));
        *out = path;
        return_ok(ret_code);
    }

    assert(segment1);
    assert(segment2);

    segment2_slashed = '/' == segment2[0];

    ret_code = contra_path__rtrim(&segment1_trimmed, segment1, '/');
    return_err(ret_code);

    ret_code = asprintf(&path, "%s%s%s", segment1_trimmed, (segment2_slashed ? "": "/"), segment2);
    return_err_ext(ret_code, ERR(MALLOC));

    *out = path;
    ret_code = 0;

_on_error
    if (NULL != path) free(path);
_cleanup
    if (NULL != segment1_trimmed) free(segment1_trimmed);
    return ret_code;
}


/**
 * #tests
 * "/home//gochomugo"           => "/home/gochomugo"
 * "/home/gochomugo//"          => "/home/gochomugo"
 * "/home/gochomugo/.."         => "/home"
 * "/home/gochomugo/."          => "/home/gochomugo"
 * "/home/../root"              => "/root"
 * "projects//../dir"           => "dir"
 * "projects/../dir/"           => "dir"
 * "//home//gochomugo//"        => "/home/gochomugo"
 * "/home/..//../projects/"     => "/projects"
 * "."                          => "."
 * "./."                        => "."
 * ".."                         => ".."
 * "../.."                      => "../.."
 * "./.."                       => ".."
 * "./../."                     => ".."
 * ""                           #> CONTRA_ERR_BAD_ARGS
 * #endtests
 *
 * #pseudocode
 * 1. If 'path' is falsey, return CONTRA_ERR_BAD_ARGS
 * 2. Split 'path' into segments using '/'
 * 3. For each of this segment:
 * 3.1. If segment is empty ("" due to consecutive '/'s), ignore segment
 * 3.2. If segment is '..':
 * 3.2.1. If no segment is picked or previous segment is '..':
 * 3.2.1.1. If 'path' is absolute, ignore segment
 * 3.2.1.2. Else, pick segment
 * 3.2.2. If previous segment is '.', replace it
 * 3.2.3. Else unpick previous segment
 * 3.3. Else if segment is '.':
 * 3.3.1. If no segment is picked, pick segment
 * 3.3.2. Else ignore this segment
 * 3.4. Else pick segment
 * #endpseudocode
 */
int
contra_path_normalize(char **out, const char *path) {
    int ret_code = 0;
    size_t path_len = -1;
    sds *segments = NULL;
    int segments_num = -1;
    int *picked = NULL;
    int picked_len = 0;
    int i;
    int is_abs = false;
    sds token_pre = NULL;
    sds normalized_path_sds = NULL;
    char *normalized_path = NULL;

    assert(path);
    if (contra_path__falsey(path)) return_err_now(ERR(BAD_ARGS));

    path_len = strlen(path);
    is_abs = ('/' == path[0]);

    segments = sdssplitlen(path, path_len, "/", 1, &segments_num);
    if (is_null(segments)) return_err_now(ERR(MALLOC));

    picked = malloc(sizeof(int) * segments_num);
    if (is_null(picked)) return_err_now(ERR(MALLOC));

    for (i = 0; i < segments_num; i++) {
        /* ignore empty strings from sequential path separators e.g. "//" */
        if ('\0' == segments[i][0]) continue;

        /* removing preceding segments on finding ".." */
        if (0 == strcmp(segments[i], "..")) {
            if (0 < picked_len) token_pre = segments[picked[picked_len - 1]];

            /* if we can not remove any more segments, use this segment */
            if (NULL == token_pre || 0 == strcmp(token_pre, "..")) {
                if (!is_abs) picked[picked_len++] = i;
            /* if there's a ".", replace it with ".." */
            } else if (0 == strcmp(token_pre, ".")) {
                picked[picked_len - 1] = i;
            /* otherwise, do not pick the element */
            } else {
                picked_len--;
            }
        /* handling "." */
        } else if (0 == strcmp(segments[i], ".")) {
            /* if it is the first element to be found, save it */
            if (0 == picked_len && !is_abs) {
                picked[picked_len++] = i;
            }
        /* otherwise, save this 'normal' segment */
        } else {
            picked[picked_len++] = i;
        }
        token_pre = NULL;
    }

    if (0 == picked_len) return_err_now(ERR(BAD_ARGS));

    normalized_path_sds = sdscatprintf(sdsempty(), "%s%s", is_abs ? "/" : "", segments[picked[0]]);
    if (is_null(normalized_path_sds)) return_err_now(ERR(MALLOC));

    for (i = 1; i < picked_len; i++) {
        normalized_path_sds = sdscatprintf(normalized_path_sds, "/%s", segments[picked[i]]);
        if (is_null(normalized_path_sds)) return_err_now(ERR(MALLOC));
    }

    normalized_path = strdup(normalized_path_sds);
    if (is_null(normalized_path)) return_err_now(ERR(MALLOC));

    *out = normalized_path;

_on_error
    if (NULL != normalized_path) free(normalized_path);
_cleanup
    if (NULL != segments) sdsfreesplitres(segments, segments_num);
    if (NULL != normalized_path_sds) sdsfree(normalized_path_sds);
    if (NULL != picked) free(picked);
    return ret_code;
}
