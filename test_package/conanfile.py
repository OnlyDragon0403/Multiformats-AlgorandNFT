import os

from conans import ConanFile, CMake, tools


class MultiformatsTestConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"
    requires = "gtest/1.8.1@bincrafters/stable", "multiformats/0.1@matt1795/testing"
    def configure(self):
        self.options["gtest"].build_gmock = False
        self.options["gtest"].shared = True

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder=self.source_folder)
        cmake.build()

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin")
        self.copy("*.dylib", dst="bin", src="lib")
        self.copy("*.so", dst="bin", src="lib")

    def test(self):
        if not tools.cross_building(self.settings):
            pass
            self.run("bin%sMultiformatsTests --gtest_output=\"xml:results.xml\"" % os.sep)
