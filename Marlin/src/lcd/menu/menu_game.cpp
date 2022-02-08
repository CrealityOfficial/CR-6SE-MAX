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

#include "../../inc/MarlinConfigPre.h"

#if HAS_GAME_MENU

<<<<<<< HEAD
#include "menu.h"
=======
#include "menu_item.h"
>>>>>>> mcu_ctrl
#include "game/game.h"

void menu_game() {
  START_MENU();
<<<<<<< HEAD
  BACK_ITEM(MSG_MAIN);
=======
  BACK_ITEM(TERN(LCD_INFO_MENU, MSG_INFO_MENU, MSG_MAIN));
>>>>>>> mcu_ctrl
  #if ENABLED(MARLIN_BRICKOUT)
    SUBMENU(MSG_BRICKOUT, brickout.enter_game);
  #endif
  #if ENABLED(MARLIN_INVADERS)
    SUBMENU(MSG_INVADERS, invaders.enter_game);
  #endif
  #if ENABLED(MARLIN_SNAKE)
    SUBMENU(MSG_SNAKE, snake.enter_game);
  #endif
  #if ENABLED(MARLIN_MAZE)
    SUBMENU(MSG_MAZE, maze.enter_game);
  #endif
  END_MENU();
}

#endif // HAS_GAME_MENU
