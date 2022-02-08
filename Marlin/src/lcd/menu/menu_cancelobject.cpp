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

//
// Cancel Object Menu
//

#include "../../inc/MarlinConfigPre.h"

<<<<<<< HEAD
#if HAS_LCD_MENU && ENABLED(CANCEL_OBJECTS)

#include "menu.h"
=======
#if BOTH(HAS_LCD_MENU, CANCEL_OBJECTS)

#include "menu_item.h"
>>>>>>> mcu_ctrl
#include "menu_addon.h"

#include "../../feature/cancel_object.h"

static void lcd_cancel_object_confirm() {
  const int8_t v = MenuItemBase::itemIndex;
  const char item_num[] = {
    ' ',
    char((v > 9) ? '0' + (v / 10) : ' '),
    char('0' + (v % 10)),
    '\0'
  };
  MenuItem_confirm::confirm_screen(
    []{
<<<<<<< HEAD
      cancelable.cancel_object(MenuItemBase::itemIndex - 1);
      #if HAS_BUZZER
        ui.completion_feedback();
      #endif
=======
      cancelable.cancel_object(MenuItemBase::itemIndex);
      ui.completion_feedback();
>>>>>>> mcu_ctrl
      ui.goto_previous_screen();
    },
    ui.goto_previous_screen,
    GET_TEXT(MSG_CANCEL_OBJECT), item_num, PSTR("?")
  );
}

void menu_cancelobject() {
<<<<<<< HEAD
=======
  const int8_t ao = cancelable.active_object;

>>>>>>> mcu_ctrl
  START_MENU();
  BACK_ITEM(MSG_MAIN);

  // Draw cancelable items in a loop
<<<<<<< HEAD
  int8_t a = cancelable.active_object;
  for (int8_t i = -1; i < cancelable.object_count; i++) {
    if (i == a) continue;
    int8_t j = i < 0 ? a : i;
    if (!cancelable.is_canceled(j))
      SUBMENU_N(j, MSG_CANCEL_OBJECT_N, lcd_cancel_object_confirm);
    if (i < 0) SKIP_ITEM();
=======
  for (int8_t i = -1; i < cancelable.object_count; i++) {
    if (i == ao) continue;                                          // Active is drawn on -1 index
    const int8_t j = i < 0 ? ao : i;                                // Active or index item
    if (!cancelable.is_canceled(j)) {                               // Not canceled already?
      SUBMENU_N(j, MSG_CANCEL_OBJECT_N, lcd_cancel_object_confirm); // Offer the option.
      if (i < 0) SKIP_ITEM();                                       // Extra line after active
    }
>>>>>>> mcu_ctrl
  }

  END_MENU();
}

#endif // HAS_LCD_MENU && CANCEL_OBJECTS
