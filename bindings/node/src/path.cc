/**
 * Node.js bindings to Contra's Path mini-library.
 *
 * The MIT License (MIT)
 * Copyright (c) 2016 GochoMugo <mugo@forfuture.co.ke>
 * Copyright (c) 2016 Forfuture, LLC <we@forfuture.co.ke>
 */


#include <nan.h>
#include "../include/bindings.h"

using namespace v8;


NAN_METHOD(Basename) {
    Nan::MaybeLocal<String> pathMaybe = Nan::To<String>(info[0]);
    if (pathMaybe.IsEmpty()) {
        Nan::ThrowError("");
        return;
    }
}


NAN_MODULE_INIT(Init) {
    contra_bindings_define_function("basename", Basename);
}


NODE_MODULE(path, Init)
