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
#include <cstdint>

namespace hal::stm32f4 {
struct reset_and_clock_control_t
{
  /// Offset: 0x00 Clock Control Register
  volatile std::uint32_t cr;
  /// Offset: 0x04 PLL config register
  volatile std::uint32_t pllcfgr;
  /// Offset: 0x08 clock config register
  volatile std::uint32_t cfgr;
  /// Offset: 0x0c clock interrupt register
  volatile std::uint32_t cir;
  /// Offset: 0x10 ahb1 peripheral reset register
  volatile std::uint32_t ahb1rstr;
  /// Offset: 0x14 ahb2 peripheral reset register
  volatile std::uint32_t ahb2rstr;

  volatile std::array<std::uint32_t, 2> reserved0;

  /// Offset: 0x20 ahb1 peripheral reset register
  volatile std::uint32_t apb1rstr;
  /// Offset: 0x24 ahb2 peripheral reset register
  volatile std::uint32_t apb2rstr;

  volatile std::array<std::uint32_t, 2> reserved1;

  /// Offset: 0x30 ahb1 clock enable register
  volatile std::uint32_t ahb1enr;
  /// Offset: 0x34 ahb1 clock enable register
  volatile std::uint32_t ahb2enr;

  volatile std::array<std::uint32_t, 2> reserved2;

  /// Offset: 0x40 apb1 clock enable register
  volatile std::uint32_t apb1enr;
  /// Offset: 0x44 apb1 clock enable register
  volatile std::uint32_t apb2enr;

  volatile std::array<std::uint32_t, 2> reserved3;

  /// Offset: 0x50 ahb1 peripheral clock enable in low power mode register
  volatile std::uint32_t ahb1lpenr;
  /// Offset: 0x54 ahb2 peripheral clock enable in low power mode register
  volatile std::uint32_t ahb2lpenr;

  volatile std::array<std::uint32_t, 2> reserved4;

  /// Offset: 0x60 apb1 peripheral clock enable in low power mode register
  volatile std::uint32_t apb1lpenr;
  /// Offset: 0x64 apb2 peripheral clock enable in low power mode register
  volatile std::uint32_t apb2lpenr;

  volatile std::array<std::uint32_t, 2> reserved5;

  /// Offset: 0x70 backup domain control register
  volatile std::uint32_t bdcr;
  /// Offset: 0x74 control and status register
  volatile std::uint32_t csr;

  volatile std::array<std::uint32_t, 2> reserved6;

  /// Offset: 0x80 spread spectrum clock generation register
  volatile std::uint32_t sscgr;
  /// Offset: 0x84 plli2s config register
  volatile std::uint32_t plli2scfgr;

  volatile std::uint32_t reserved7;

  /// Offset 0x8c dedicated clocks configuration register
  volatile std::uint32_t dckcfgr;
};

/**
 * @return reset_and_clock_control_t& - return reset_and_clock_control_t
 * register.
 */
inline reset_and_clock_control_t* rcc =
  reinterpret_cast<reset_and_clock_control_t*>(0x40000000 + 0x20000 + 0x3800);
}  // namespace hal::stm32f4
