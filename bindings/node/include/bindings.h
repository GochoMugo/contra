/**
 * Main header file for Node.js bindings to Contra's Path mini-library.
 *
 * The MIT License (MIT)
 * Copyright (c) 2016 GochoMugo <mugo@forfuture.co.ke>
 * Copyright (c) 2016 Forfuture, LLC <we@forfuture.co.ke>
 */

#ifndef _CONTRA_BINDINGS_bindings_h_
#define _CONTRA_BINDINGS_bindings_h_ 1

#define contra_bindings_define_function(name, function) \
    Nan::Set(target, Nan::New(name).ToLocalChecked(), \
            Nan::GetFunction(Nan::New<FunctionTemplate>(function)).ToLocalChecked());

#endif
