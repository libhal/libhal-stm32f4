#!/usr/bin/python
#
# Copyright 2024 Khalil Estell
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout
from conan.tools.files import copy
from conan.tools.build import check_min_cppstd
import os


required_conan_version = ">=2.0.6"


class libhal_stm32f4_conan(ConanFile):
    name = "libhal-stm32f4"
    version = "0.0.1"
    license = "Apache-2.0"
    url = "https://github.com/conan-io/conan-center-index"
    homepage = "https://libhal.github.io/libhal-stm32f4"
    description = ("A collection of drivers and libraries for the stm32f4 "
                   "series microcontrollers.")
    topics = ("microcontroller", "stm32f4",)
    settings = "compiler", "build_type", "os", "arch"
    exports_sources = ("include/*", "linker_scripts/*", "tests/*", "LICENSE",
                       "CMakeLists.txt", "src/*")
    generators = "CMakeToolchain", "CMakeDeps", "VirtualBuildEnv"

    options = {
        "platform": [
            "profile1",
            "profile2",
            "ANY"
        ],
    }

    default_options = {
        "platform": "ANY",
    }

    @property
    def _use_linker_script(self):
        return (self.options.platform == "profile1" or
                self.options.platform == "profile2")

    @property
    def _min_cppstd(self):
        return "20"

    @property
    def _compilers_minimum_version(self):
        return {
            "gcc": "11",
            "clang": "14",
            "apple-clang": "14.0.0"
        }

    @property
    def _bare_metal(self):
        return self.settings.os == "baremetal"

    def validate(self):
        if self.settings.get_safe("compiler.cppstd"):
            check_min_cppstd(self, self._min_cppstd)

    def build_requirements(self):
        self.tool_requires("cmake/3.27.1")
        self.tool_requires("libhal-cmake-util/2.2.0")
        self.test_requires("libhal-mock/[^2.0.1]")
        self.test_requires("boost-ext-ut/1.1.9")

    def requirements(self):
        self.requires("libhal/[^2.0.1]")
        self.requires("libhal-util/[^3.0.0]")
        # Replace with appropriate processor library
        self.requires("libhal-armcortex/[^2.0.3]")

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self,
             "LICENSE",
             dst=os.path.join(self.package_folder, "licenses"),
             src=self.source_folder)
        copy(self,
             "*.h",
             dst=os.path.join(self.package_folder, "include"),
             src=os.path.join(self.source_folder, "include"))
        copy(self,
             "*.hpp",
             dst=os.path.join(self.package_folder, "include"),
             src=os.path.join(self.source_folder, "include"))
        copy(self,
             "*.ld",
             dst=os.path.join(self.package_folder, "linker_scripts"),
             src=os.path.join(self.source_folder, "linker_scripts"))

        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.set_property("cmake_target_name", "libhal::stm32f4")
        self.cpp_info.libs = ["libhal-stm32f4"]

        if self._bare_metal and self._use_linker_script:
            linker_path = os.path.join(self.package_folder, "linker_scripts")
            link_script = "-Tlibhal-stm32f4/" + \
                str(self.options.platform) + ".ld"
            self.cpp_info.exelinkflags = ["-L" + linker_path, link_script]
