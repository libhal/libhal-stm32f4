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

#include <array>

#include <cmath>
#include <libhal-stm32f4/constants.hpp>
#include <libhal-stm32f4/output_pin.hpp>
#include <libhal-stm32f4/spi.hpp>
#include <libhal-util/spi.hpp>
#include <libhal-util/steady_clock.hpp>
void delay_by_cycles(int p_cycles)
{
  volatile int i = 0;
  while (i < p_cycles) {
    i = i + 1;
  }
}

void application()
{
  using namespace hal::literals;

  hal::stm32f4::spi spi2(2, { .clock_idles_high = true });
  hal::stm32f4::output_pin chip_select(hal::stm32f4::peripheral::gpio_b, 13);
  chip_select.level(true);

  while (true) {
    using namespace std::literals;
    std::array<hal::byte, 4> payload{ 0xDE, 0xAD, 0xBE, 0xEF };
    std::array<hal::byte, 8> buffer{};

    chip_select.level(false);
    hal::write(spi2, payload);
    hal::read(spi2, buffer);
    chip_select.level(true);
    delay_by_cycles(100000);

    chip_select.level(false);
    spi2.transfer(payload, buffer);
    chip_select.level(true);
    delay_by_cycles(1000000);

    chip_select.level(false);
    hal::write_then_read(spi2, payload, buffer);
    chip_select.level(true);
    delay_by_cycles(1000000);
  }
}
