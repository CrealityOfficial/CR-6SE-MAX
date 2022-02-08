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

#include "../../../inc/MarlinConfig.h"

#if ENABLED(POWER_LOSS_RECOVERY)

#include "../../gcode.h"
<<<<<<< HEAD
#include "../../../feature/power_loss_recovery.h"
#include "../../../module/motion.h"
#include "../../../lcd/ultralcd.h"
=======
#include "../../../feature/powerloss.h"
#include "../../../module/motion.h"
#include "../../../lcd/marlinui.h"
#if ENABLED(EXTENSIBLE_UI)
  #include "../../../lcd/extui/ui_api.h"
#endif
>>>>>>> mcu_ctrl

#define DEBUG_OUT ENABLED(DEBUG_POWER_LOSS_RECOVERY)
#include "../../../core/debug_out.h"

void menu_job_recovery();

inline void plr_error(PGM_P const prefix) {
  #if ENABLED(DEBUG_POWER_LOSS_RECOVERY)
    DEBUG_ECHO_START();
<<<<<<< HEAD
    serialprintPGM(prefix);
    DEBUG_ECHOLNPGM(" Power-Loss Recovery Data");
=======
    DEBUG_ECHOPGM_P(prefix);
    DEBUG_ECHOLNPGM(" Job Recovery Data");
>>>>>>> mcu_ctrl
  #else
    UNUSED(prefix);
  #endif
}

<<<<<<< HEAD
=======
#if HAS_LCD_MENU
  void lcd_power_loss_recovery_cancel();
#endif

>>>>>>> mcu_ctrl
/**
 * M1000: Resume from power-loss (undocumented)
 *   - With 'S' go to the Resume/Cancel menu
 *   - With no parameters, run recovery commands
 */
void GcodeSuite::M1000() {

  if (recovery.valid()) {
<<<<<<< HEAD
    if (parser.seen('S')) {
      #if HAS_LCD_MENU
        ui.goto_screen(menu_job_recovery);
=======
    if (parser.seen_test('S')) {
      #if HAS_LCD_MENU
        ui.goto_screen(menu_job_recovery);
      #elif ENABLED(DWIN_CREALITY_LCD)
        recovery.dwin_flag = true;
      #elif ENABLED(EXTENSIBLE_UI)
        ExtUI::onPowerLossResume();
>>>>>>> mcu_ctrl
      #else
        SERIAL_ECHO_MSG("Resume requires LCD.");
      #endif
    }
<<<<<<< HEAD
=======
    else if (parser.seen_test('C')) {
      #if HAS_LCD_MENU
        lcd_power_loss_recovery_cancel();
      #else
        recovery.cancel();
      #endif
      TERN_(EXTENSIBLE_UI, ExtUI::onPrintTimerStopped());
    }
>>>>>>> mcu_ctrl
    else
      recovery.resume();
  }
  else
    plr_error(recovery.info.valid_head ? PSTR("No") : PSTR("Invalid"));

}

#endif // POWER_LOSS_RECOVERY
