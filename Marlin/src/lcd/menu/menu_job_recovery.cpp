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
// Job Recovery Menu
//

#include "../../inc/MarlinConfigPre.h"

<<<<<<< HEAD
#if HAS_LCD_MENU && ENABLED(POWER_LOSS_RECOVERY)

#include "menu.h"
#include "../../gcode/queue.h"
#include "../../sd/cardreader.h"
#include "../../feature/power_loss_recovery.h"
=======
#if BOTH(HAS_LCD_MENU, POWER_LOSS_RECOVERY)

#include "menu_item.h"
#include "../../gcode/queue.h"
#include "../../sd/cardreader.h"
#include "../../feature/powerloss.h"
>>>>>>> mcu_ctrl

static void lcd_power_loss_recovery_resume() {
  ui.return_to_status();
  queue.inject_P(PSTR("M1000"));
}

<<<<<<< HEAD
static void lcd_power_loss_recovery_cancel() {
  card.removeJobRecoveryFile();
  card.autostart_index = 0;
=======
void lcd_power_loss_recovery_cancel() {
  recovery.cancel();
>>>>>>> mcu_ctrl
  ui.return_to_status();
}

// TODO: Display long filename with Cancel/Resume buttons
//       Requires supporting methods in PLR class.
void menu_job_recovery() {
  ui.defer_status_screen();
  START_MENU();
  STATIC_ITEM(MSG_OUTAGE_RECOVERY);
  ACTION_ITEM(MSG_RESUME_PRINT, lcd_power_loss_recovery_resume);
  ACTION_ITEM(MSG_STOP_PRINT, lcd_power_loss_recovery_cancel);
  END_MENU();
}

#endif // HAS_LCD_MENU && POWER_LOSS_RECOVERY
