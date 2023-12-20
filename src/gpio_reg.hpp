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

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#include <libhal-util/bit.hpp>

namespace hal::stm32f4 {
/// gpio peripheral register map
struct stm32f4_gpio_t
{
  /// Offset: 0x000 pin mode (00 = Input, 01 = Output, 10 = Alternate Function mode, 11 Analog) (R/W)
  volatile std::uint32_t pin_mode;
  /// Offset: 0x004 output type(0 = output push-pull, 1 = output open-drain)
  std::array<std::uint32_t, 3> output_type;
  /// Offset: 0x008 output speed(00 = Low speed, 01 = Medium speed, 10 = Fast speed, 11 = High speed)
  volatile std::uint32_t output_speed;
  /// Offset: 0x00C port pull-up/pull-down (00 = no pull-up/pull-down, 01 = pull-up, 10 pull-down)
  volatile std::uint32_t pull_up_pull_down;
  /// Offset: 0x010 port input data (RO)
  volatile std::uint32_t input_data;
  /// Offset: 0x014 port output data 
  volatile std::uint32_t output_data;
  /// Offset: 0x018high port reset (0 = no action, 1 = reset)
  volatile std::uint16_t reset;
  /// Offset: 0x018low port set
  volatile std::uint16_t set;
  /// Offset: 0x01C config lock
  volatile std::uint32_t lock;
  /// Offset: 0x020 alternate function low (bits 0 - 7)
  volatile std::uint32_t alt_function_low;
  /// Offset: 0x024 alternate function high (bits 8 - 15)
  volatile std::uint32_t alt_function_high;
};

inline constexpr intptr_t ahb_base = 0x40020000UL;

enum class gpio_reg{
  a = reinterpret_cast<stm32f4_gpio_t*>(ahb_base + 0x00000),
  b = reinterpret_cast<stm32f4_gpio_t*>(ahb_base + 0x00400),
  c = reinterpret_cast<stm32f4_gpio_t*>(ahb_base + 0x00800),
  d = reinterpret_cast<stm32f4_gpio_t*>(ahb_base + 0x00C00),
  e = reinterpret_cast<stm32f4_gpio_t*>(ahb_base + 0x01000),
  h = reinterpret_cast<stm32f4_gpio_t*>(ahb_base + 0x01C00)
};



inline constexpr bit_mask pin_mask(std::uint8_t p_pin)
{
  return bit_mask{ .position = p_pin, .width = 1 };
}
}  // namespace hal::stm32f4
