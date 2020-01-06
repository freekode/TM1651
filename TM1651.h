/**
 * Author:Fred.Chu
 * Date:14 August, 2014
 *
 * Applicable Module: Battery Display v1.0
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Modified record:
 * Autor:   Detlef Giessmann Germany
 * Mail:    mydiyp@web.de
 * Demo for the new 7 LED Battery-Display 2017
 * IDE:     Arduino-1.6.5
 * Typ.:    OPEN-SMART CX10*4RY68  4Color
 * Date:    01.05.2017
 */

#ifndef TM1651_H
#define TM1651_H

#include <Arduino.h>
#include <inttypes.h>

// definitions for brightness
#define BRIGHT_DARKEST 0
#define BRIGHT_TYPICAL 2
#define BRIGHTEST 7

#define ADDR_AUTO 0x40
#define ADDR_FIXED 0x44

class TM1651 {
public:
  TM1651(uint8_t, uint8_t);

  void init();

  void displayLevel(uint8_t);

  void frame(boolean);

  void clearDisplay(void);

  void set(uint8_t = BRIGHT_TYPICAL);

private:
  static const int8_t _LEVEL_TAB[];

  uint8_t _clk_pin;
  uint8_t _data_pin;

  uint8_t _cmd_disp_ctrl;

  void start(void);
  void stop(void);

  void writeByte(int8_t wr_data);
};

#endif
