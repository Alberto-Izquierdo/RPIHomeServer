#!/usr/bin/env python
from conans import ConanFile, CMake


class RPIHomeServer(ConanFile):
    settings = "os", "compiler", "build_type", "arch", "cppstd"
    generators = "cmake"

    default_options = {"tgbot_cpp:shared": False}

    def requirements(self):
        self.requires("tgbot_cpp/1.1@jgsogo/stable")
        self.requires("jsonformoderncpp/3.6.1@vthiery/stable")
        self.requires("Catch2/2.7.1@catchorg/stable")
        if self.settings.arch != "armv7":
            self.requires("OpenSSL/1.1.1c@conan/stable")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin")
        self.copy("*.dylib*", dst="bin", src="lib")
        self.copy('*.so*', dst='bin', src='lib')
