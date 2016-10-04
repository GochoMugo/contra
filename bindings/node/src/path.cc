/**
 * Node.js bindings to Contra's Path mini-library.
 *
 * The MIT License (MIT)
 * Copyright (c) 2016 GochoMugo <mugo@forfuture.co.ke>
 * Copyright (c) 2016 Forfuture, LLC <we@forfuture.co.ke>
 */

#include "../include/bindings.h"


NAN_METHOD(Basename) {
    Nan::MaybeLocal<v8::String> pathMaybe = Nan::To<v8::String>(info[0]);
    if (pathMaybe.IsEmpty()) {
        Nan::ThrowError("empty path");
        return;
    }

    std::string path = std::string(pathMaybe.ToLocalChecked());
    char *basename = NULL;
    int ret_code = contra_path_basename(&basename, path);
    info.GetReturnValue().Set(basename);
}


NAN_MODULE_INIT(Init) {
    contra_bindings_define_function("basename", Basename);
}


NODE_MODULE(path, Init)
