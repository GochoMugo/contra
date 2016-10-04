#!/usr/bin/env node
/**
 * Script to update the 'binding.gyp' file for 'node-gyp'.
 *
 * The MIT License (MIT)
 * Copyright (c) 2016 GochoMugo <mugo@forfuture.co.ke>
 * Copyright (c) 2016 Forfuture, LLC <we@forfuture.co.ke>
 */


// built-in modules
const fs = require("fs");
const path = require("path");


// module variables
const contraIncludePath = path.resolve(__dirname, "../../../include");
const modulesPath = path.resolve(__dirname, "../src");
const bindingsPath = path.resolve(__dirname, "../binding.gyp");
const bindingsData = { targets: [] };
let moduleFilenames;


try {
    moduleFilenames = fs.readdirSync(modulesPath);
} catch (ex) {
    console.error("Errored while trying to readdir containing modules");
    console.error(ex);
    process.exit(1);
}


moduleFilenames.forEach(function(moduleFilename) {
    const moduleName = moduleFilename.substring(0, moduleFilename.indexOf(".cc"));
    bindingsData.targets.push({
        "target_name": moduleName,
        "sources": [ "src/" + moduleFilename ],
        "include_dirs": [
            contraIncludePath,
            "<!(node -e \"require('nan')\")",
        ],
    });
});


try {
    const bindingsDataStr = JSON.stringify(bindingsData, null, "    ");
    fs.writeFileSync(bindingsPath, bindingsDataStr);
} catch (ex) {
    console.error("Errored while writing to bindings.gyp");
    console.error(ex);
    process.exit(1);
}
