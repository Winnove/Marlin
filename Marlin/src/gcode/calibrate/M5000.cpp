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
 * Application custom pour Robobend, fonction de chargement du fil
 *
 */

#include "../../inc/MarlinConfig.h"
#include "../gcode.h"

#include "../../../feature/leds/leds.h"
#include "../../../feature/leds/FxLed.hpp"
#include "../../core/macros.h"
#include "../../module/endstops.h"
#include "../../module/stepper.h"

/**
 *
 * M5000 : Fonction de chargement du fil du Robobend
 *
 */

void GcodeSuite::M5000() {

  leds.set_color(255, 40, 40, 255);

  SERIAL_ECHO_MSG("Preparation machine");

  // met la machine en position pour ouvrir l'extrudeur

  destination[X_AXIS] = 20;
  prepare_internal_move_to_destination(); // set_current_to_destination
  planner.synchronize();

  LedFx ledfx;
  ledfx.begin(LedFx::Pattern::Blink,500,LEDColor(0,143,255),0);

  SERIAL_ECHO_MSG("Inserer fil");

  // lance la detection du fil en butée lors de l'insertion par l'utilisateur

  while ((digitalRead(P1_28) == HIGH)) // using pin P1_28 for endstop
  {
    ledfx.update();
    destination[E_AXIS] += 0.05;
    prepare_internal_move_to_destination(); // set_current_to_destination
    planner.synchronize();
    reset_stepper_timeout();
  }
  ledfx.stop();
  SERIAL_ECHO_MSG("Fil detecte... mise en position");

  leds.set_color(50, 255, 0, 255);

  // ferme l'extudeur

  destination[X_AXIS] = 0;
  prepare_internal_move_to_destination(); // set_current_to_destination
  planner.synchronize();

  // recule le fil pour repalper précisement la butée sans perturbation de
  // l'utilisateur

  destination[E_AXIS] -= 2;
  prepare_internal_move_to_destination(); // set_current_to_destination
  planner.synchronize();
  reset_stepper_timeout();

  // repalpe le fil

  while ((digitalRead(P1_28) == HIGH)) // using pin P1_28 for endstop
  {
    destination[E_AXIS] += 0.05;
    prepare_internal_move_to_destination(); // set_current_to_destination
    planner.synchronize();
    reset_stepper_timeout();
  }

  // met le fil a ras de la buse

  destination[E_AXIS] -= 1.00;
  prepare_internal_move_to_destination(); // set_current_to_destination
  planner.synchronize();
  reset_stepper_timeout();

  SERIAL_ECHO_MSG("Fil en position");

  leds.set_color(50, 255, 0, 255);
}
