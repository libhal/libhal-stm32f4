// Copyright 2024 Khalil Estell
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
  /**
   * @brief Get the output pin object
   *
   * @param p_port - selects pin port to use
   * @param p_pin - selects which pin within the port to use
   * @param p_settings - initial pin settings
   * @return result<output_pin> - reference to the statically allocated output
   * pin
   */
  static result<output_pin> get(char p_port,
                                std::uint8_t p_pin,
                                output_pin::settings p_settings = {});

  static hal::result<output_pin> create();

private:
  output_pin(char p_port, std::uint8_t p_pin);
  hal::status driver_configure(const settings& p_settings) override;
  hal::result<set_level_t> driver_level(bool p_high) override;
  hal::result<level_t> driver_level() override;

  char m_port{};
  std::uint8_t m_pin{};
};
}  // namespace hal::stm32f4
