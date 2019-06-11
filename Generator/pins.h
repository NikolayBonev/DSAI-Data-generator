/**
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
 */

/**
 * Include pins definitions
 *
 * Pins numbering schemes:
 *
 *  - Digital I/O pin number if used by READ/WRITE macros.
 *    The FastIO headers map digital pins to their ports and functions.
 *
 *  - Analog Input number if used by analogRead.
 *    These numbers are the same in any pin mapping.
 */

#ifndef __PINS_H__
#define __PINS_H__

#if MB(BOARD_MEGACONTROLLER)
  #include "pins_MEGACONTROLLER.h" // ATmega2560
#elif MB(BOARD_UNOCONTROLLER)
  #include "pins_UNOCONTROLLER.h" // ATmega 326P
#else
  #error "Unknown MOTHERBOARD value set in Configuration.h"
#endif

#endif // __PINS_H__