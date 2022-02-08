/**
 * Marlin 3D Printer Firmware
<<<<<<< HEAD
 * Copyright (c) 2019 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
=======
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
>>>>>>> mcu_ctrl
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
<<<<<<< HEAD
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
=======
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
>>>>>>> mcu_ctrl
 *
 */
#pragma once

#include "../lcdprint.h"
<<<<<<< HEAD
#if HAS_GRAPHICAL_LCD
  #include "../dogm/ultralcd_DOGM.h"
#endif

#define MENU_ITEM_ADDON_START(X) do{ \
  if (ui.should_draw() && _menuLineNr == _thisItemNr - 1) { \
    SETCURSOR(X, _lcdLineNr)
=======

#define _MENU_ITEM_ADDON_START(N,X) do{ \
  if (ui.should_draw() && _menuLineNr == _thisItemNr - 1) { \
    N(X)

#define MENU_ITEM_ADDON_START(X)    _MENU_ITEM_ADDON_START(SETCURSOR_X,    X)
#define MENU_ITEM_ADDON_START_RJ(X) _MENU_ITEM_ADDON_START(SETCURSOR_X_RJ, X)
>>>>>>> mcu_ctrl

#define MENU_ITEM_ADDON_END() } }while(0)
