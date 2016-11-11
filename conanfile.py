#!/usr/bin/env python
#
# Contra's Path mini-library.
#
# The MIT License (MIT)
# Copyright (c) 2016 GochoMugo <mugo@forfuture.co.ke>
# Copyright (c) 2016 Forfuture, LLC <we@forfuture.co.ke>
#


from conans import ConanFile, CMake


class ContraConan(ConanFile):
    name = "contra"
    version = "0.0.0"
    url = "https://github.com/forfuturellc/contra"
    license = "MIT"
    settings = "os", "compiler", "build_type", "arch"
    exports = [ "include/*", "src/*", "deps/*", "LICENSE.txt", "README.md",
            "CMakeLists.txt"]

    def build(self):
        cmake = CMake(self.settings)
        self.run("cmake %s %s" % (self.conanfile_directory, cmake.command_line))
        self.run("cmake --build . --config Release %s" % (cmake.build_config))

    def package(self):
        self.copy("*", dst="include", src="include")
        self.copy("*.so", dst="lib")
        self.copy("*.lib", dst="lib")

    def package_info(self):
        self.cpp_info.libs = ["contra"]
