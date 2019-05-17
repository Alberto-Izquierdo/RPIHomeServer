import os

from conans import ConanFile, CMake, tools


class RPI_GPIO(ConanFile):
    settings = "os", "compiler", "build_type", "arch", "cppstd"
    generators = "cmake"

    def requirements(self):
        self.requires("tgbot_cpp/1.1@jgsogo/stable")
        self.requires("fmt/5.2.1@bincrafters/stable")
        self.requires("jsonformoderncpp/3.6.1@vthiery/stable")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin")
        self.copy("*.dylib*", dst="bin", src="lib")
        self.copy('*.so*', dst='bin', src='lib')
