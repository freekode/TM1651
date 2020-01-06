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

#include "TM1651.h"

const int8_t TM1651::_LEVEL_TAB[] = {0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f};

TM1651::TM1651(uint8_t clk_pin, uint8_t data_pin) {
  _clk_pin = clk_pin;
  _data_pin = data_pin;
  pinMode(_clk_pin, OUTPUT);
  pinMode(_data_pin, OUTPUT);
}

void TM1651::init() {
  set(BRIGHT_TYPICAL);
  clearDisplay();
}

void TM1651::writeByte(int8_t wr_data) {
  uint8_t i, count1;
  // sent 8bit data
  for (i = 0; i < 8; i++) {
    digitalWrite(_clk_pin, LOW);
    if (wr_data & 0x01) {
      // LSB first
      digitalWrite(_data_pin, HIGH);
    } else {
      digitalWrite(_data_pin, LOW);
    }
    delayMicroseconds(3);
    wr_data >>= 1;
    digitalWrite(_clk_pin, HIGH);
    delayMicroseconds(3);
  }

  // wait for the ACK
  digitalWrite(_clk_pin, LOW);
  digitalWrite(_data_pin, HIGH);
  digitalWrite(_clk_pin, HIGH);
  pinMode(_data_pin, INPUT);
  while (digitalRead(_data_pin)) {
    count1 += 1;
    if (count1 == 200) {
      pinMode(_data_pin, OUTPUT);
      digitalWrite(_data_pin, LOW);
      count1 = 0;
    }
    pinMode(_data_pin, INPUT);
  }
  pinMode(_data_pin, OUTPUT);
}

/**
 * send start signal to TM1651
 */
void TM1651::start(void) {
  digitalWrite(_clk_pin, HIGH);
  digitalWrite(_data_pin, HIGH);
  delayMicroseconds(2);
  digitalWrite(_data_pin, LOW);
  digitalWrite(_clk_pin, LOW);
}

/**
 * End of transmission
 */
void TM1651::stop(void) {
  digitalWrite(_clk_pin, LOW);
  digitalWrite(_data_pin, LOW);
  digitalWrite(_clk_pin, HIGH);
  digitalWrite(_data_pin, HIGH);
}

void TM1651::displayLevel(uint8_t level) {
  if (level > 7) {
    return;
  }

  // start signal sent to TM1651 from MCU
  start();
  writeByte(ADDR_FIXED);
  stop();
  start();
  writeByte(0xc0);
  writeByte(TM1651::_LEVEL_TAB[level]);
  stop();
  start();
  writeByte(_cmd_disp_ctrl);
  stop();
}

void TM1651::frame(boolean frame_on) {
  int8_t SegData;
  if (frame_on) {
    SegData = 0x40;
  } else {
    SegData = 0x00;
  }

  // start signal sent to TM1651 from MCU
  start();
  writeByte(ADDR_AUTO);
  stop();
  start();
  writeByte(0xc1);
  for (uint8_t i = 0; i < 3; i++) {
    writeByte(SegData);
  }
  stop();
  start();
  writeByte(_cmd_disp_ctrl);
  stop();
}

void TM1651::clearDisplay(void) {
  displayLevel(0);
  frame(false);
}

/**
 * To take effect the next time it displays.
 */
void TM1651::set(uint8_t brightness) { _cmd_disp_ctrl = 0x88 + brightness; }
