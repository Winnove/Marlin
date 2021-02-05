/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2019 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * Application custom pour Robobend, fonction d'animation des leds
 *
 */

//#include "../../../HAL/shared/Delay.h"
#include "../../../inc/MarlinConfig.h"
#include "../../gcode.h"

#include "../../../feature/leds/leds.h"
#include "../../../feature/leds/FxLed.hpp"

/**
 *
 * M5001 : Fonction d'animation des LEDS
 *
 */

void GcodeSuite::M5001() {

#if ENABLED(NEOPIXEL_LED)

  const int progID = parser.intval('P');

  //**************************************

  if (progID == 1) {
    leds.set_color(255, 0, 0, 255);
  }

  else if (progID == 2) {
    leds.set_color(0, 0, 255, 255);
    dwell(1000);
    leds.set_color(255, 0, 0, 255);
  }

  else if (progID == 3) {
    uint16_t i = 0;
    while (i < 255) {
      leds.set_color(0, 255, 0, 0, i);
      dwell(100);
      i += 10;
    }
  }

  else if (progID == 4) {
    LedFx ledfx;
    ledfx.begin(LedFx::Pattern::Blink, 500, LEDColor(0, 40, 255));
    auto ms = millis();
    while (millis() - ms < 10000) {
      dwell(1);
      ledfx.update();
    }
    ledfx.stop();
  }

  else if (progID == 5) {
    LedFx ledfx;
    ledfx.begin(LedFx::Pattern::FadeIn, 3000, LEDColor(0, 40, 255));
    auto ms = millis();
    while (millis() - ms < 3000) {
      dwell(1);
      ledfx.update();
    }
    ledfx.stop();
  }

  else if (progID == 6) {
    LedFx ledfx;
    ledfx.begin(LedFx::Pattern::FadeOut, 3000, LEDColor(0, 40, 255));
    auto ms = millis();
    while (millis() - ms < 3000) {
      dwell(1);
      ledfx.update();
    }
    ledfx.stop();
  }

//************************************
#endif
}
