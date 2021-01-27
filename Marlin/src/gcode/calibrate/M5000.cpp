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

 #include "../../module/stepper.h"
 #include "../../module/endstops.h"
 #include "../../core/macros.h"

/**
*
* M5000 : Fonction de chargement du fil du Robobend
*
*/

void GcodeSuite::M5000()
{
while ((digitalRead(P1_25) == HIGH))      //using pin P1_25 for endstop
{
  destination[E_AXIS] += 0.05;
  prepare_internal_move_to_destination();         // set_current_to_destination
  planner.synchronize();
  reset_stepper_timeout();
}
SERIAL_ECHO_MSG("Fil en position");
}
