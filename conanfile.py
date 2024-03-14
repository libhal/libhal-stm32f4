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
import os

required_conan_version = ">=2.0.14"


class libhal_stm32f4_conan(ConanFile):
    name = "libhal-stm32f4"
    license = "Apache-2.0"
    homepage = "https://libhal.github.io/libhal-stm32f4"
    description = ("A collection of drivers and libraries for the stm32f4 "
                   "series microcontrollers.")
    topics = ("arm", "microcontroller", "stm32f4")
    settings = "compiler", "build_type", "os", "arch"

    python_requires = "libhal-bootstrap/[^1.0.0]"
    python_requires_extend = "libhal-bootstrap.library"

    options = {
        "platform": ["ANY"],
    }
    default_options = {
        "platform": "ANY",
    }

    def package_id(self):
        if self.info.options.get_safe("platform"):
            del self.info.options.platform

    @property
    def _use_linker_script(self):
        return (self.options.platform == "stm32f411re")

    def requirements(self):
        self.requires("libhal-armcortex/[^3.0.2]", transitive_headers=True)

    def package_info(self):
        self.cpp_info.libs = ["libhal-stm32f4"]
        self.cpp_info.set_property("cmake_target_name", "libhal::stm32f4")

        if self.settings.os == "baremetal" and self._use_linker_script:
            linker_path = os.path.join(self.package_folder, "linker_scripts")
            link_script = "-Tlibhal-stm32f4/" + \
                str(self.options.platform) + ".ld"
            self.cpp_info.exelinkflags = ["-L" + linker_path, link_script]
