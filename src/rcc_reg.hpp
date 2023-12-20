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

#include <cstdint>

namespace hal::stm32f4 {
struct reset_and_clock_control_t
{
  volatile std::uint32_t cr;
  volatile std::uint32_t pllcfgr;
  volatile std::uint32_t cfgr;
  volatile std::uint32_t cir;
  volatile std::uint32_t apb2rstr;
  volatile std::uint32_t apb1rstr;
  volatile std::uint32_t ahbenr;
  volatile std::uint32_t apb2enr;
  volatile std::uint32_t apb1enr;
  volatile std::uint32_t bdcr;
  volatile std::uint32_t csr;
  volatile std::uint32_t ahbrstr;
  volatile std::uint32_t cfgr2;
};

/**
 * @return reset_and_clock_control_t& - return reset_and_clock_control_t
 * register.
 */
inline reset_and_clock_control_t* rcc =
  reinterpret_cast<reset_and_clock_control_t*>(0x40000000 + 0x20000 + 0x1000);

/// Bit masks for the CR register
struct clock_control
{
  /// Indicates if the PLL i2s is enabled and ready
  static constexpr auto plli2s_ready = bit_mask::from<27>();

  /// Used to enable the PLL i2s
  static constexpr auto plli2s_enable = bit_mask::from<26>();
  
  /// Indicates if the PLL is enabled and ready
  static constexpr auto pll_ready = bit_mask::from<25>();
  
  /// Used to enable the PLL
  static constexpr auto pll_enable = bit_mask::from<24>();

  /// Used to enable the Clock Secuity
  static constexpr auto css_enable = bit_mask::from<19>();

  /// HSE ocillator bypass 
  static constexpr auto hse_bypass = bit_mask::from<18>();

  /// HSE clock enable
  static constexpr auto hse_enable = bit_mask::from<16>();

  /// HSI calibration
  static constexpr auto hsi_calibration = bit_mask::from<8, 15>();

  /// HSI trim
  static constexpr auto hsi_trim = bit_mask::from<3, 7>();

  /// HSI ready
  static constexpr auto hsi_ready = bit_mask::from<1>();

  /// HSI enable
  static constexpr auto hsi_ready = bit_mask::from<0>();

  static auto reg()
  {
    return hal::bit_modify(rcc->cr);
  }
};

/// Bit masks for the CFGR register
struct clock_configuration
{
  /// Controls which clock signal is sent to the Microcontroller Clock 2 pin
  static constexpr auto mco2 = bit_mask::from<30, 31>();

  ///MCO2 prescaler
  static constexpr auto mco2pre = bit_mask::from<29, 27>();

  ///MCO1 prescaler
  static constexpr auto mco1pre = bit_mask::from<26, 24>();

  /// Sets the USB clock divider
  static constexpr auto i2ssrc = bit_mask::from<23>();

  /// Controls which clock signal is sent to the MC1 pin
  static constexpr auto mco1 = bit_mask::from<21, 22>();

  /// HSE division factor for RTC clock
  static constexpr auto rtcpre = bit_mask::from<16, 20>();

  /// APB2 high-speed prescaler
  static constexpr auto ppre2 = bit_mask::from<13, 15>();

  /// APB1 low-speed prescaler
  static constexpr auto ppre1 = bit_mask::from<10, 12>();

  /// AHB prescalar
  static constexpr auto hpre = bit_mask::from<4, 7>();

  /// System clock switch status
  static constexpr auto sws = bit_mask::from<2, 3>();

  /// System clock switch 
  static constexpr auto sw = bit_mask::from<0, 1>();

  static auto reg()
  {
    return hal::bit_modify(rcc->cfgr);
  }
};

/// Bit masks for interupt registers
struct rcc_interupt
{
  /// clears the clock security interupt
  static constexpr auto css_clear = bit_mask::from<23>();

  /// clears the pll i2s ready interupt
  static constexpr auto plli2srdy_clear = bit_mask::from<21>();

  /// clears the pll ready interupt
  static constexpr auto pllrdy_clear = bit_mask::from<20>();

  /// clears the hse ready interupt
  static constexpr auto hserdy_clear = bit_mask::from<19>();

  /// clears the hsi ready interupt
  static constexpr auto hsirdy_clear = bit_mask::from<18>();

  /// clears the lse ready interupt
  static constexpr auto lserdy_clear = bit_mask::from<17>();

  /// clears the lsi ready interupt
  static constexpr auto lsirdy_clear = bit_mask::from<16>();

  /// enables the pll i2s ready interupt
  static constexpr auto plli2srdy_enable = bit_mask::from<13>();

  /// enables the pll ready interupt
  static constexpr auto pllrdy_enable = bit_mask::from<12>();

  /// enables the hse ready interupt
  static constexpr auto hserdy_enable = bit_mask::from<11>();

  /// enables the hsi ready interupt
  static constexpr auto hsirdy_enable = bit_mask::from<10>();

  /// enables the lse ready interupt
  static constexpr auto lserdy_enable = bit_mask::from<9>();

  /// enables the lsi ready interupt
  static constexpr auto lsirdy_enable = bit_mask::from<8>();

  /// clock security interupt flag
  static constexpr auto css_flag = bit_mask::from<7>();

  /// pll i2s ready interupt flag
  static constexpr auto plli2srdy_flag = bit_mask::from<5>();

  /// pll ready interupt flag
  static constexpr auto pllrdy_flag = bit_mask::from<4>();

  /// hse ready interupt flag
  static constexpr auto hserdy_flag = bit_mask::from<3>();

  /// hsi ready interupt flag
  static constexpr auto hsirdy_flag = bit_mask::from<2>();

  /// lse ready interupt flag
  static constexpr auto lserdy_flag = bit_mask::from<1>();

  /// lsi ready interupt flag
  static constexpr auto lsirdy_flag = bit_mask::from<0>();

  static auto reg()
  {
    return hal::bit_modify(rcc->cir);
  }
};

/// Bitmasks for the BDCR register
struct rtc_register
{
  /// Will reset all clock states for the RTC
  static constexpr auto backup_domain_reset = bit_mask::from<16>();
  /// Enables the RTC clock
  static constexpr auto rtc_enable = bit_mask::from<15>();
  /// Selects the clock source for the RTC
  static constexpr auto rtc_source_select = bit_mask::from<8, 9>();
  /// Indicates if the LSE is ready for use
  static constexpr auto low_speed_osc_ready = bit_mask::from<1>();
  /// Used to enable the LSE
  static constexpr auto low_speed_osc_enable = bit_mask::from<0>();

  static auto reg()
  {
    return hal::bit_modify(rcc->bdcr);
  }
};
}  // namespace hal::stm32f1
