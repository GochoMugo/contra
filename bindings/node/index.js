/**
 * Node.js bindings for the contra library.
 *
 * The MIT License (MIT)
 * Copyright (c) 2016 GochoMugo <mugo@forfuture.co.ke>
 * Copyright (c) 2016 Forfuture, LLC <we@forfuture.co.ke>
 */


// npm-installed modules
const bindings = require("bindings");


// module variables
const modules = [
    "path",
];


modules.forEach(function(moduleName) {
    exports[moduleName] = bindings(moduleName);
});
