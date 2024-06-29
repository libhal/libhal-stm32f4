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

#include <libhal-armcortex/dwt_counter.hpp>
#include <libhal-stm32f4/output_pin.hpp>
#include <libhal-util/serial.hpp>
#include <libhal-util/steady_clock.hpp>

// TODO(#15): Replace with `hal::cortex_m::dwt_counter`

void delay_by_cycles(int p_cycles)
{
  int volatile i = 0;
  while (i < p_cycles) {
    i = i + 1;
  }
}

void application()
{
  hal::stm32f4::output_pin led(hal::stm32f4::peripheral::gpio_b, 15);

  while (true) {
    led.level(false);
    delay_by_cycles(1000000);
    led.level(true);
    delay_by_cycles(1000000);
  }
}
