// Copyright 2023 Khalil Estell
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <libhal/output_pin.hpp>

namespace hal::stm32f4 {
class output_pin : public hal::output_pin
{
public:
  /// TODO: Update factory function
  static hal::result<output_pin> create();

private:
  // Add constructor
  hal::status driver_configure(const settings& p_settings) override;
  hal::result<set_level_t> driver_level(bool p_high) override;
  hal::result<level_t> driver_level() override;
};
}  // namespace hal::stm32f4
