// Copyright 2023 Google LLC
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

#include <cstdint>

#include <libhal-stm32f4/pin.hpp>

#include <libhal-util/bit.hpp>
#include <libhal/units.hpp>

#include "gpio_reg.hpp"

namespace hal::stm32f4 {

const pin& pin::function(hal::stm32f4::pin_function p_function) const
{
  auto port_reg = get_reg(m_port);
  auto pin_mode_mask = port_reg->pin_mode.from<2 * m_pin, 2 * m_pin + 1>();
  uint8_t alt_func = 0;
  if (p_function == pin_function::input) {
    pin_mode_mask.modify(0b00);
  } else if (p_function == pin_function::output) {
    pin_mode_mask.modify(0b01);
  } else if (p_function == pin_function::analog) {
    pin_mode_mask.modify(0b01);
  } else {
    pin_mode_mask.modify(0b10);
    alt_func = p_function - 3;
    if (m_pin < 8) {
      port_reg->alt_function_low.from<2 * m_pin, 2 * m_pin + 3>().modify(
        static_cast<int>(pin_function) - 3);
    } else if (m_pin > 8) {
      port_reg->alt_function_high.from<2 * (m_pin - 8), 2 * (m_pin - 8) + 3>().modify(
        static_cast<int>(pin_function) - 3);
    }
  }
  return *this;
}

const pin& pin::resistor(hal::pin_resistor p_resistor) const
{
  // modify the pull_up_pull_down reg to the enumclass of p_registor
  hal::bit_modify(pin_map->matrix[m_port][m_pin])
    .insert<pin_input_invert>(p_enable);
  return *this;
}

const pin& pin::open_drain(bool p_enable) const
{
  // modify output_type to p_enable
  hal::bit_modify(pin_map->matrix[m_port][m_pin])
    .insert<pin_open_drain>(p_enable);
  return *this;
}

}  // namespace hal::stm32f4
