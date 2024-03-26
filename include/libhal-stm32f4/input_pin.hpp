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

#include <libhal/input_pin.hpp>

#include "pin.hpp"

namespace hal::stm32f4 {
/**
 * @brief Input pin implementation for the stm32f4
 *
 */
class input_pin : public hal::input_pin
{
public:
  /**
   * @brief Construct a new input pin object
   *
   * @param p_port - selects pin port to use
   * @param p_pin - selects pin within the port to use
   * @param p_settings - initial pin settings
   */
  input_pin(hal::stm32f4::peripheral p_port,
            std::uint8_t p_pin,
            const input_pin::settings& p_settings = {});

  input_pin(input_pin& p_other) = delete;
  input_pin& operator=(input_pin& p_other) = delete;
  input_pin(input_pin&& p_other) noexcept = delete;
  input_pin& operator=(input_pin&& p_other) noexcept = delete;
  ~input_pin() = default;

private:
  void driver_configure(const settings& p_settings) override;
  bool driver_level() override;

  hal::stm32f4::peripheral m_port{};
  uint8_t m_pin{};
};
}  // namespace hal::stm32f4
