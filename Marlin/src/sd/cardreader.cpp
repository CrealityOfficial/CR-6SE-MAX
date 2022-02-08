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

#include "../inc/MarlinConfig.h"

#if ENABLED(SDSUPPORT)

<<<<<<< HEAD
#include "cardreader.h"

#include "../Marlin.h"
#include "../lcd/ultralcd.h"
#ifdef DWIN_LCDDISPLAY
  #include "../lcd/dwin/dwin.h"
#endif
#include "../lcd/dwin/i2c_eeprom.h"

#include "../module/planner.h"
#include "../module/printcounter.h"
#include "../core/language.h"
#include "../gcode/queue.h"
#include "../module/configuration_store.h"

#if ENABLED(EMERGENCY_PARSER)
  #include "../feature/emergency_parser.h"
#endif

#if ENABLED(POWER_LOSS_RECOVERY)
  #include "../feature/power_loss_recovery.h"
=======
//#define DEBUG_CARDREADER

#include "cardreader.h"

#include "../MarlinCore.h"
#include "../lcd/marlinui.h"

#if ENABLED(DWIN_CREALITY_LCD)
  #include "../lcd/dwin/e3v2/dwin.h"
#endif

#include "../module/planner.h"        // for synchronize
#include "../module/printcounter.h"
#include "../gcode/queue.h"
#include "../module/settings.h"
#include "../module/stepper/indirection.h"

#if ENABLED(EMERGENCY_PARSER)
  #include "../feature/e_parser.h"
#endif

#if ENABLED(POWER_LOSS_RECOVERY)
  #include "../feature/powerloss.h"
>>>>>>> mcu_ctrl
#endif

#if ENABLED(ADVANCED_PAUSE_FEATURE)
  #include "../feature/pause.h"
#endif

<<<<<<< HEAD
=======
#define DEBUG_OUT EITHER(DEBUG_CARDREADER, MARLIN_DEV_MODE)
#include "../core/debug_out.h"
#include "../libs/hex_print.h"

// extern

PGMSTR(M23_STR, "M23 %s");
PGMSTR(M24_STR, "M24");

>>>>>>> mcu_ctrl
// public:

card_flags_t CardReader::flag;
char CardReader::filename[FILENAME_LENGTH], CardReader::longFilename[LONG_FILENAME_LENGTH];
<<<<<<< HEAD
int8_t CardReader::autostart_index;

#if ENABLED(BINARY_FILE_TRANSFER) && NUM_SERIAL > 1
  int8_t CardReader::transfer_port_index;
=======

IF_DISABLED(NO_SD_AUTOSTART, uint8_t CardReader::autofile_index); // = 0

#if BOTH(HAS_MULTI_SERIAL, BINARY_FILE_TRANSFER)
  serial_index_t CardReader::transfer_port_index;
>>>>>>> mcu_ctrl
#endif

// private:

SdFile CardReader::root, CardReader::workDir, CardReader::workDirParents[MAX_DIR_DEPTH];
uint8_t CardReader::workDirDepth;

#if ENABLED(SDCARD_SORT_ALPHA)

  uint16_t CardReader::sort_count;
  #if ENABLED(SDSORT_GCODE)
    bool CardReader::sort_alpha;
    int CardReader::sort_folders;
    //bool CardReader::sort_reverse;
  #endif

  #if ENABLED(SDSORT_DYNAMIC_RAM)
    uint8_t *CardReader::sort_order;
  #else
    uint8_t CardReader::sort_order[SDSORT_LIMIT];
  #endif

  #if ENABLED(SDSORT_USES_RAM)

    #if ENABLED(SDSORT_CACHE_NAMES)
      uint16_t CardReader::nrFiles; // Cached total file count
      #if ENABLED(SDSORT_DYNAMIC_RAM)
        char **CardReader::sortshort, **CardReader::sortnames;
      #else
        char CardReader::sortshort[SDSORT_LIMIT][FILENAME_LENGTH];
        char CardReader::sortnames[SDSORT_LIMIT][SORTED_LONGNAME_STORAGE];
      #endif
    #elif DISABLED(SDSORT_USES_STACK)
      char CardReader::sortnames[SDSORT_LIMIT][SORTED_LONGNAME_STORAGE];
    #endif

    #if HAS_FOLDER_SORTING
      #if ENABLED(SDSORT_DYNAMIC_RAM)
        uint8_t *CardReader::isDir;
      #elif ENABLED(SDSORT_CACHE_NAMES) || DISABLED(SDSORT_USES_STACK)
        uint8_t CardReader::isDir[(SDSORT_LIMIT+7)>>3];
      #endif
      #define IS_DIR(n) TEST(isDir[(n) >> 3], (n) & 0x07)
    #endif

  #endif // SDSORT_USES_RAM

#endif // SDCARD_SORT_ALPHA

<<<<<<< HEAD
Sd2Card CardReader::sd2card;
SdVolume CardReader::volume;
SdFile CardReader::file;

uint8_t CardReader::file_subcall_ctr;
uint32_t CardReader::filespos[SD_PROCEDURE_DEPTH];
char CardReader::proc_filenames[SD_PROCEDURE_DEPTH][MAXPATHNAMELENGTH];
=======
#if SHARED_VOLUME_IS(USB_FLASH_DRIVE) || ENABLED(USB_FLASH_DRIVE_SUPPORT)
  DiskIODriver_USBFlash CardReader::media_usbFlashDrive;
#endif
#if NEED_SD2CARD_SDIO
  DiskIODriver_SDIO CardReader::media_sdio;
#elif NEED_SD2CARD_SPI
  DiskIODriver_SPI_SD CardReader::media_sd_spi;
#endif

DiskIODriver* CardReader::driver = nullptr;
SdVolume CardReader::volume;
SdFile CardReader::file;

#if HAS_MEDIA_SUBCALLS
  uint8_t CardReader::file_subcall_ctr;
  uint32_t CardReader::filespos[SD_PROCEDURE_DEPTH];
  char CardReader::proc_filenames[SD_PROCEDURE_DEPTH][MAXPATHNAMELENGTH];
#endif
>>>>>>> mcu_ctrl

uint32_t CardReader::filesize, CardReader::sdpos;

CardReader::CardReader() {
<<<<<<< HEAD
=======
  changeMedia(&
    #if SHARED_VOLUME_IS(SD_ONBOARD)
      TERN(SDIO_SUPPORT, media_sdio, media_sd_spi)
    #elif SHARED_VOLUME_IS(USB_FLASH_DRIVE) || ENABLED(USB_FLASH_DRIVE_SUPPORT)
      media_usbFlashDrive
    #else
      TERN(SDIO_SUPPORT, media_sdio, media_sd_spi)
    #endif
  );

>>>>>>> mcu_ctrl
  #if ENABLED(SDCARD_SORT_ALPHA)
    sort_count = 0;
    #if ENABLED(SDSORT_GCODE)
      sort_alpha = true;
      sort_folders = FOLDER_SORTING;
      //sort_reverse = false;
    #endif
  #endif
<<<<<<< HEAD
  flag.sdprinting = flag.mounted = flag.saving = flag.logging = false;
  filesize = sdpos = 0;
  file_subcall_ctr = 0;
=======

  flag.sdprinting = flag.sdprintdone = flag.mounted = flag.saving = flag.logging = false;
  filesize = sdpos = 0;

  TERN_(HAS_MEDIA_SUBCALLS, file_subcall_ctr = 0);

  IF_DISABLED(NO_SD_AUTOSTART, autofile_cancel());
>>>>>>> mcu_ctrl

  workDirDepth = 0;
  ZERO(workDirParents);

<<<<<<< HEAD
  // Disable autostart until card is initialized
  autostart_index = -1;
=======
  #if ENABLED(SDSUPPORT) && PIN_EXISTS(SD_DETECT)
    SET_INPUT_PULLUP(SD_DETECT_PIN);
  #endif
>>>>>>> mcu_ctrl

  #if PIN_EXISTS(SDPOWER)
    OUT_WRITE(SDPOWER_PIN, HIGH); // Power the SD reader
  #endif
}

//
// Get a DOS 8.3 filename in its useful form
//
char *createFilename(char * const buffer, const dir_t &p) {
  char *pos = buffer;
<<<<<<< HEAD
  for (uint8_t i = 0; i < 11; i++) {
=======
  LOOP_L_N(i, 11) {
>>>>>>> mcu_ctrl
    if (p.name[i] == ' ') continue;
    if (i == 8) *pos++ = '.';
    *pos++ = p.name[i];
  }
  *pos++ = 0;
  return buffer;
}

//
// Return 'true' if the item is a folder or G-code file
//
bool CardReader::is_dir_or_gcode(const dir_t &p) {
<<<<<<< HEAD
  uint8_t pn0 = p.name[0];

  if ( pn0 == DIR_NAME_FREE || pn0 == DIR_NAME_DELETED  // Clear or Deleted entry
    || pn0 == '.' || longFilename[0] == '.'             // Hidden file
    || !DIR_IS_FILE_OR_SUBDIR(&p)                       // Not a File or Directory
    || (p.attributes & DIR_ATT_HIDDEN)                  // Hidden by attribute
=======
  //uint8_t pn0 = p.name[0];

  if ( (p.attributes & DIR_ATT_HIDDEN)                  // Hidden by attribute
    // When readDir() > 0 these must be false:
    //|| pn0 == DIR_NAME_FREE || pn0 == DIR_NAME_DELETED  // Clear or Deleted entry
    //|| pn0 == '.' || longFilename[0] == '.'             // Hidden file
    //|| !DIR_IS_FILE_OR_SUBDIR(&p)                       // Not a File or Directory
>>>>>>> mcu_ctrl
  ) return false;

  flag.filenameIsDir = DIR_IS_SUBDIR(&p);               // We know it's a File or Folder

  return (
    flag.filenameIsDir                                  // All Directories are ok
    || (p.name[8] == 'G' && p.name[9] != '~')           // Non-backup *.G* files are accepted
  );
}

//
// Get the number of (compliant) items in the folder
//
int CardReader::countItems(SdFile dir) {
  dir_t p;
  int c = 0;
  while (dir.readDir(&p, longFilename) > 0)
    c += is_dir_or_gcode(p);

<<<<<<< HEAD
  #if ENABLED(SDCARD_SORT_ALPHA) && SDSORT_USES_RAM && SDSORT_CACHE_NAMES
=======
  #if ALL(SDCARD_SORT_ALPHA, SDSORT_USES_RAM, SDSORT_CACHE_NAMES)
>>>>>>> mcu_ctrl
    nrFiles = c;
  #endif

  return c;
}

//
// Get file/folder info for an item by index
//
void CardReader::selectByIndex(SdFile dir, const uint8_t index) {
  dir_t p;
  for (uint8_t cnt = 0; dir.readDir(&p, longFilename) > 0;) {
    if (is_dir_or_gcode(p)) {
      if (cnt == index) {
        createFilename(filename, p);
        return;  // 0 based index
      }
      cnt++;
    }
  }
}

//
// Get file/folder info for an item by name
//
void CardReader::selectByName(SdFile dir, const char * const match) {
  dir_t p;
  for (uint8_t cnt = 0; dir.readDir(&p, longFilename) > 0; cnt++) {
    if (is_dir_or_gcode(p)) {
      createFilename(filename, p);
      if (strcasecmp(match, filename) == 0) return;
    }
  }
}

//
<<<<<<< HEAD
// Recursive method to list all files within a folder
=======
// Recursive method to print all files within a folder in flat
// DOS 8.3 format. This style of listing is the most compatible
// with legacy hosts.
//
// This method recurses to unlimited depth and lists every
// G-code file within the given parent. If the hierarchy is
// very deep this can blow up the stack, so a 'depth' parameter
// (as with printListingJSON) would be a good addition.
>>>>>>> mcu_ctrl
//
void CardReader::printListing(SdFile parent, const char * const prepend/*=nullptr*/) {
  dir_t p;
  while (parent.readDir(&p, longFilename) > 0) {
    if (DIR_IS_SUBDIR(&p)) {

      // Get the short name for the item, which we know is a folder
      char dosFilename[FILENAME_LENGTH];
      createFilename(dosFilename, p);

      // Allocate enough stack space for the full path to a folder, trailing slash, and nul
      const bool prepend_is_empty = (!prepend || prepend[0] == '\0');
      const int len = (prepend_is_empty ? 1 : strlen(prepend)) + strlen(dosFilename) + 1 + 1;
      char path[len];

      // Append the FOLDERNAME12/ to the passed string.
      // It contains the full path to the "parent" argument.
      // We now have the full path to the item in this folder.
      strcpy(path, prepend_is_empty ? "/" : prepend); // root slash if prepend is empty
      strcat(path, dosFilename);                      // FILENAME_LENGTH characters maximum
      strcat(path, "/");                              // 1 character

      // Serial.print(path);

      // Get a new directory object using the full path
      // and dive recursively into it.
<<<<<<< HEAD
      SdFile child;
      if (!child.open(&parent, dosFilename, O_READ)) {
        SERIAL_ECHO_START();
        SERIAL_ECHOLNPAIR(MSG_SD_CANT_OPEN_SUBDIR, dosFilename);
      }
      printListing(child, path);
      // close() is done automatically by destructor of SdFile
    }
    else if (is_dir_or_gcode(p)) {
      createFilename(filename, p);
      if (prepend) SERIAL_ECHO(prepend);
      SERIAL_ECHO(filename);
=======
      SdFile child; // child.close() in destructor
      if (child.open(&parent, dosFilename, O_READ))
        printListing(child, path);
      else {
        SERIAL_ECHO_MSG(STR_SD_CANT_OPEN_SUBDIR, dosFilename);
        return;
      }
    }
    else if (is_dir_or_gcode(p)) {
      if (prepend) SERIAL_ECHO(prepend);
      SERIAL_ECHO(createFilename(filename, p));
>>>>>>> mcu_ctrl
      SERIAL_CHAR(' ');
      SERIAL_ECHOLN(p.fileSize);
    }
  }
}

//
// List all files on the SD card
//
void CardReader::ls() {
<<<<<<< HEAD
  root.rewind();
  printListing(root);
=======
  if (flag.mounted) {
    root.rewind();
    printListing(root);
  }
>>>>>>> mcu_ctrl
}

#if ENABLED(LONG_FILENAME_HOST_SUPPORT)

  //
  // Get a long pretty path based on a DOS 8.3 path
  //
  void CardReader::printLongPath(char * const path) {

    int i, pathLen = strlen(path);

    // SERIAL_ECHOPGM("Full Path: "); SERIAL_ECHOLN(path);

    // Zero out slashes to make segments
    for (i = 0; i < pathLen; i++) if (path[i] == '/') path[i] = '\0';

    SdFile diveDir = root; // start from the root for segment 1
    for (i = 0; i < pathLen;) {

      if (path[i] == '\0') i++; // move past a single nul

      char *segment = &path[i]; // The segment after most slashes

      // If a segment is empty (extra-slash) then exit
      if (!*segment) break;

      // Go to the next segment
      while (path[++i]) { }

<<<<<<< HEAD
      // SERIAL_ECHOPGM("Looking for segment: "); SERIAL_ECHOLN(segment);
=======
      //SERIAL_ECHOLNPAIR("Looking for segment: ", segment);
>>>>>>> mcu_ctrl

      // Find the item, setting the long filename
      diveDir.rewind();
      selectByName(diveDir, segment);

      // Print /LongNamePart to serial output
      SERIAL_CHAR('/');
      SERIAL_ECHO(longFilename[0] ? longFilename : "???");

      // If the filename was printed then that's it
      if (!flag.filenameIsDir) break;

      // SERIAL_ECHOPGM("Opening dir: "); SERIAL_ECHOLN(segment);

      // Open the sub-item as the new dive parent
      SdFile dir;
      if (!dir.open(&diveDir, segment, O_READ)) {
        SERIAL_EOL();
        SERIAL_ECHO_START();
<<<<<<< HEAD
        SERIAL_ECHOPAIR(MSG_SD_CANT_OPEN_SUBDIR, segment);
=======
        SERIAL_ECHOPAIR(STR_SD_CANT_OPEN_SUBDIR, segment);
>>>>>>> mcu_ctrl
        break;
      }

      diveDir.close();
      diveDir = dir;

    } // while i<pathLen

    SERIAL_EOL();
  }

#endif // LONG_FILENAME_HOST_SUPPORT

//
// Echo the DOS 8.3 filename (and long filename, if any)
//
<<<<<<< HEAD
void CardReader::printFilename() {
=======
void CardReader::printSelectedFilename() {
>>>>>>> mcu_ctrl
  if (file.isOpen()) {
    char dosFilename[FILENAME_LENGTH];
    file.getDosName(dosFilename);
    SERIAL_ECHO(dosFilename);
    #if ENABLED(LONG_FILENAME_HOST_SUPPORT)
      selectFileByName(dosFilename);
      if (longFilename[0]) {
<<<<<<< HEAD
        SERIAL_ECHO(' ');
=======
        SERIAL_CHAR(' ');
>>>>>>> mcu_ctrl
        SERIAL_ECHO(longFilename);
      }
    #endif
  }
  else
    SERIAL_ECHOPGM("(no file)");

  SERIAL_EOL();
}

void CardReader::mount() {
<<<<<<< HEAD
  delay(200);  // Power on
  flag.mounted = false;
  if (root.isOpen()) root.close();

  if (!sd2card.init(SPI_SPEED, SDSS)
    #if defined(LCD_SDSS) && (LCD_SDSS != SDSS)
      && !sd2card.init(SPI_SPEED, LCD_SDSS)
    #endif
  ) SERIAL_ECHO_MSG(MSG_SD_INIT_FAIL);
  else if (!volume.init(&sd2card))
    SERIAL_ERROR_MSG(MSG_SD_VOL_INIT_FAIL);
  else if (!root.openRoot(&volume))
    SERIAL_ERROR_MSG(MSG_SD_OPENROOT_FAIL);
  else {
    flag.mounted = true;
    SERIAL_ECHO_MSG(MSG_SD_CARD_OK);
    #if ENABLED(EEPROM_SETTINGS) && NONE(FLASH_EEPROM_EMULATION, SPI_EEPROM, I2C_EEPROM)
      settings.first_load();
    #endif
  }
  cdroot();
=======
  flag.mounted = false;
  if (root.isOpen()) root.close();

  if (!driver->init(SD_SPI_SPEED, SDSS)
    #if defined(LCD_SDSS) && (LCD_SDSS != SDSS)
      && !driver->init(SD_SPI_SPEED, LCD_SDSS)
    #endif
  ) SERIAL_ECHO_MSG(STR_SD_INIT_FAIL);
  else if (!volume.init(driver))
    SERIAL_ERROR_MSG(STR_SD_VOL_INIT_FAIL);
  else if (!root.openRoot(&volume))
    SERIAL_ERROR_MSG(STR_SD_OPENROOT_FAIL);
  else {
    flag.mounted = true;
    SERIAL_ECHO_MSG(STR_SD_CARD_OK);
  }

  if (flag.mounted)
    cdroot();
  #if ENABLED(USB_FLASH_DRIVE_SUPPORT) || PIN_EXISTS(SD_DETECT)
    else if (marlin_state != MF_INITIALIZING)
      ui.set_status_P(GET_TEXT(MSG_SD_INIT_FAIL), -1);
  #endif
>>>>>>> mcu_ctrl

  ui.refresh();
}

<<<<<<< HEAD
void CardReader::release() {
  stopSDPrint();
  flag.mounted = false;
}

void CardReader::openAndPrintFile(const char *name) {
  char cmd[4 + strlen(name) + 1]; // Room for "M23 ", filename, and null
  extern const char M23_STR[];
  sprintf_P(cmd, M23_STR, name);
  for (char *c = &cmd[4]; *c; c++) *c = tolower(*c);
  queue.enqueue_one_now(cmd);
  queue.enqueue_now_P(M24_STR);
}

void CardReader::startFileprint() {
  if (isMounted()) {
    flag.sdprinting = true;
    #if SD_RESORT
      flush_presort();
    #endif
  }
}

void CardReader::stopSDPrint(
  #if SD_RESORT
    const bool re_sort/*=false*/
  #endif
) {
  #if ENABLED(ADVANCED_PAUSE_FEATURE)
    did_pause_print = 0;
  #endif
  flag.sdprinting = flag.abort_sd_printing = false;
  if (isFileOpen()) file.close();
  #if SD_RESORT
    if (re_sort) presort();
  #endif
}

void CardReader::openLogFile(char * const path) {
  flag.logging = true;
  openFile(path, false);
=======
/**
 * Handle SD card events
 */
#if MB(FYSETC_CHEETAH, FYSETC_AIO_II)
  #include "../module/stepper.h"
#endif

void CardReader::manage_media() {
  static uint8_t prev_stat = 2;       // First call, no prior state
  uint8_t stat = uint8_t(card.isMounted());//uint8_t(IS_SD_INSERTED());
  if (stat == prev_stat) return;

  DEBUG_ECHOLNPAIR("SD: Status changed from ", prev_stat, " to ", stat);

  flag.workDirIsRoot = true;          // Return to root on mount/release

  if (ui.detected()) {

    uint8_t old_stat = prev_stat;
    prev_stat = stat;                 // Change now to prevent re-entry

    if (stat) {                       // Media Inserted
      safe_delay(500);                // Some boards need a delay to get settled
      if (TERN1(SD_IGNORE_AT_STARTUP, old_stat != 2))
        mount();                      // Try to mount the media
      #if MB(FYSETC_CHEETAH, FYSETC_CHEETAH_V12, FYSETC_AIO_II)
        reset_stepper_drivers();      // Workaround for Cheetah bug
      #endif
      if (!isMounted()) stat = 0;     // Not mounted?
    }
    else {
      #if PIN_EXISTS(SD_DETECT)
        release();                    // Card is released
      #endif
    }

    ui.media_changed(old_stat, stat); // Update the UI

    if (stat) {
      TERN_(SDCARD_EEPROM_EMULATION, settings.first_load());
      if (old_stat == 2) {            // First mount?
        DEBUG_ECHOLNPGM("First mount.");
        #if ENABLED(POWER_LOSS_RECOVERY)
          recovery.check();           // Check for PLR file. (If not there then call autofile_begin)
        #elif DISABLED(NO_SD_AUTOSTART)
          autofile_begin();           // Look for auto0.g on the next loop
        #endif
      }
    }
  }
  else
    DEBUG_ECHOLNPGM("SD: No UI Detected.");
}

/**
 * "Release" the media by clearing the 'mounted' flag.
 * Used by M22, "Release Media", manage_media.
 */
void CardReader::release() {
  // Card removed while printing? Abort!
  if (IS_SD_PRINTING())
    abortFilePrintSoon();
  else
    endFilePrintNow();

  flag.mounted = false;
  flag.workDirIsRoot = true;
  #if ALL(SDCARD_SORT_ALPHA, SDSORT_USES_RAM, SDSORT_CACHE_NAMES)
    nrFiles = 0;
  #endif
}

/**
 * Open a G-code file and set Marlin to start processing it.
 * Enqueues M23 and M24 commands to initiate a media print.
 */
void CardReader::openAndPrintFile(const char *name) {
  char cmd[4 + strlen(name) + 1 + 3 + 1]; // Room for "M23 ", filename, "\n", "M24", and null
  sprintf_P(cmd, M23_STR, name);
  for (char *c = &cmd[4]; *c; c++) *c = tolower(*c);
  strcat_P(cmd, PSTR("\nM24"));
  queue.inject(cmd);
}

/**
 * Start or resume a media print by setting the sdprinting flag.
 * The file browser pre-sort is also purged to free up memory,
 * since you cannot browse files during active printing.
 * Used by M24 and anywhere Start / Resume applies.
 */
void CardReader::startOrResumeFilePrinting() {
  if (isMounted()) {
    flag.sdprinting = true;
    flag.sdprintdone = false;
    TERN_(SD_RESORT, flush_presort());
  }
}

//
// Run tasks upon finishing or aborting a file print.
//
void CardReader::endFilePrintNow(TERN_(SD_RESORT, const bool re_sort/*=false*/)) {
  TERN_(ADVANCED_PAUSE_FEATURE, did_pause_print = 0);
  TERN_(DWIN_CREALITY_LCD, HMI_flag.print_finish = flag.sdprinting);
  flag.abort_sd_printing = false;
  if (isFileOpen()) file.close();
  TERN_(SD_RESORT, if (re_sort) presort());
}

void CardReader::abortFilePrintNow(TERN_(SD_RESORT, const bool re_sort/*=false*/)) {
  flag.sdprinting = flag.sdprintdone = false;
  endFilePrintNow(TERN_(SD_RESORT, re_sort));
}

void CardReader::openLogFile(const char * const path) {
  flag.logging = DISABLED(SDCARD_READONLY);
  IF_DISABLED(SDCARD_READONLY, openFileWrite(path));
>>>>>>> mcu_ctrl
}

//
// Get the root-relative DOS path of the selected file
//
<<<<<<< HEAD
void CardReader::getAbsFilename(char *dst) {
=======
void CardReader::getAbsFilenameInCWD(char *dst) {
>>>>>>> mcu_ctrl
  *dst++ = '/';
  uint8_t cnt = 1;

  auto appendAtom = [&](SdFile &file) {
    file.getDosName(dst);
    while (*dst && cnt < MAXPATHNAMELENGTH) { dst++; cnt++; }
    if (cnt < MAXPATHNAMELENGTH) { *dst = '/'; dst++; cnt++; }
  };

<<<<<<< HEAD
  for (uint8_t i = 0; i < workDirDepth; i++)                // Loop down to current work dir
=======
  LOOP_L_N(i, workDirDepth)                // Loop down to current work dir
>>>>>>> mcu_ctrl
    appendAtom(workDirParents[i]);

  if (cnt < MAXPATHNAMELENGTH - (FILENAME_LENGTH) - 1) {    // Leave room for filename and nul
    appendAtom(file);
    --dst;
  }
  *dst = '\0';
}

<<<<<<< HEAD
//
// Open a file by DOS path - for read or write
//
void CardReader::openFile(char * const path, const bool read, const bool subcall/*=false*/) {

  if (!isMounted()) return;

  uint8_t doing = 0;
  if (isFileOpen()) {                     // Replacing current file or doing a subroutine
    if (subcall) {
      if (file_subcall_ctr > SD_PROCEDURE_DEPTH - 1) {
        SERIAL_ERROR_MSG("trying to call sub-gcode files with too many levels. MAX level is:" STRINGIFY(SD_PROCEDURE_DEPTH));
        kill();
        return;
      }

      // Store current filename (based on workDirParents) and position
      getAbsFilename(proc_filenames[file_subcall_ctr]);
      filespos[file_subcall_ctr] = sdpos;

      SERIAL_ECHO_START();
      SERIAL_ECHOLNPAIR("SUBROUTINE CALL target:\"", path, "\" parent:\"", proc_filenames[file_subcall_ctr], "\" pos", sdpos);
      file_subcall_ctr++;
    }
    else
      doing = 1;
  }
  else if (subcall)       // Returning from a subcall?
    SERIAL_ECHO_MSG("END SUBROUTINE");
  else {                  // Opening fresh file
    doing = 2;
    file_subcall_ctr = 0; // Reset procedure depth in case user cancels print while in procedure
  }

  if (doing) {
    SERIAL_ECHO_START();
    SERIAL_ECHOPGM("Now ");
    serialprintPGM(doing == 1 ? PSTR("doing") : PSTR("fresh"));
    SERIAL_ECHOLNPAIR(" file: ", path);
  }

  stopSDPrint();

  SdFile *curDir;
  const char * const fname = diveToFile(curDir, path);
  if (!fname) return;

  if (read) {
    if (file.open(curDir, fname, O_READ)) {
      filesize = file.fileSize();
      sdpos = 0;
      SERIAL_ECHOLNPAIR(MSG_SD_FILE_OPENED, fname, MSG_SD_SIZE, filesize);
      SERIAL_ECHOLNPGM(MSG_SD_FILE_SELECTED);

      selectFileByName(fname);
      ui.set_status(longFilename[0] ? longFilename : fname);
      //if (longFilename[0]) {
      //  SERIAL_ECHOPAIR(MSG_SD_FILE_LONG_NAME, longFilename);
      //}
    }
    else
      SERIAL_ECHOLNPAIR(MSG_SD_OPEN_FILE_FAIL, fname, ".");
  }
  else { //write
    if (!file.open(curDir, fname, O_CREAT | O_APPEND | O_WRITE | O_TRUNC))
      SERIAL_ECHOLNPAIR(MSG_SD_OPEN_FILE_FAIL, fname, ".");
    else {
      flag.saving = true;
      selectFileByName(fname);
      #if ENABLED(EMERGENCY_PARSER)
        emergency_parser.disable();
      #endif
      SERIAL_ECHOLNPAIR(MSG_SD_WRITE_TO_FILE, fname);
      ui.set_status(fname);
    }
  }
=======
void openFailed(const char * const fname) {
  SERIAL_ECHOLNPAIR(STR_SD_OPEN_FILE_FAIL, fname, ".");
}

void announceOpen(const uint8_t doing, const char * const path) {
  if (doing) {
    PORT_REDIRECT(SerialMask::All);
    SERIAL_ECHO_START();
    SERIAL_ECHOPGM("Now ");
    SERIAL_ECHOPGM_P(doing == 1 ? PSTR("doing") : PSTR("fresh"));
    SERIAL_ECHOLNPAIR(" file: ", path);
  }
}

//
// Open a file by DOS path for read
// The 'subcall_type' flag indicates...
//   - 0 : Standard open from host or user interface.
//   - 1 : (file open) Opening a new sub-procedure.
//   - 1 : (no file open) Opening a macro (M98).
//   - 2 : Resuming from a sub-procedure
//
void CardReader::openFileRead(const char * const path, const uint8_t subcall_type/*=0*/) {
  if (!isMounted()) return;

  switch (subcall_type) {
    case 0:      // Starting a new print. "Now fresh file: ..."
      announceOpen(2, path);
      TERN_(HAS_MEDIA_SUBCALLS, file_subcall_ctr = 0);
      break;

    #if HAS_MEDIA_SUBCALLS

      case 1:      // Starting a sub-procedure

        // With no file is open it's a simple macro. "Now doing file: ..."
        if (!isFileOpen()) { announceOpen(1, path); break; }

        // Too deep? The firmware has to bail.
        if (file_subcall_ctr > SD_PROCEDURE_DEPTH - 1) {
          SERIAL_ERROR_MSG("Exceeded max SUBROUTINE depth:", SD_PROCEDURE_DEPTH);
          kill(GET_TEXT(MSG_KILL_SUBCALL_OVERFLOW));
          return;
        }

        // Store current filename (based on workDirParents) and position
        getAbsFilenameInCWD(proc_filenames[file_subcall_ctr]);
        filespos[file_subcall_ctr] = sdpos;

        // For sub-procedures say 'SUBROUTINE CALL target: "..." parent: "..." pos12345'
        SERIAL_ECHO_MSG("SUBROUTINE CALL target:\"", path, "\" parent:\"", proc_filenames[file_subcall_ctr], "\" pos", sdpos);
        file_subcall_ctr++;
        break;

      case 2:      // Resuming previous file after sub-procedure
        SERIAL_ECHO_MSG("END SUBROUTINE");
        break;

    #endif
  }

  abortFilePrintNow();

  SdFile *diveDir;
  const char * const fname = diveToFile(true, diveDir, path);
  if (!fname) return;

  if (file.open(diveDir, fname, O_READ)) {
    filesize = file.fileSize();
    sdpos = 0;

    { // Don't remove this block, as the PORT_REDIRECT is a RAII
      PORT_REDIRECT(SerialMask::All);
      SERIAL_ECHOLNPAIR(STR_SD_FILE_OPENED, fname, STR_SD_SIZE, filesize);
      SERIAL_ECHOLNPGM(STR_SD_FILE_SELECTED);
    }

    selectFileByName(fname);
    ui.set_status(longFilename[0] ? longFilename : fname);
  }
  else
    openFailed(fname);
}

inline void echo_write_to_file(const char * const fname) {
  SERIAL_ECHOLNPAIR(STR_SD_WRITE_TO_FILE, fname);
}

//
// Open a file by DOS path for write
//
void CardReader::openFileWrite(const char * const path) {
  if (!isMounted()) return;

  announceOpen(2, path);
  TERN_(HAS_MEDIA_SUBCALLS, file_subcall_ctr = 0);

  abortFilePrintNow();

  SdFile *diveDir;
  const char * const fname = diveToFile(false, diveDir, path);
  if (!fname) return;

  #if ENABLED(SDCARD_READONLY)
    openFailed(fname);
  #else
    if (file.open(diveDir, fname, O_CREAT | O_APPEND | O_WRITE | O_TRUNC)) {
      flag.saving = true;
      selectFileByName(fname);
      TERN_(EMERGENCY_PARSER, emergency_parser.disable());
      echo_write_to_file(fname);
      ui.set_status(fname);
    }
    else
      openFailed(fname);
  #endif
}

//
// Check if a file exists by absolute or workDir-relative path
// If the file exists, the long name can also be fetched.
//
bool CardReader::fileExists(const char * const path) {
  if (!isMounted()) return false;

  DEBUG_ECHOLNPAIR("fileExists: ", path);

  // Dive to the file's directory and get the base name
  SdFile *diveDir = nullptr;
  const char * const fname = diveToFile(false, diveDir, path);
  if (!fname) return false;

  // Get the longname of the checked file
  //diveDir->rewind();
  //selectByName(*diveDir, fname);
  //diveDir->close();

  // Try to open the file and return the result
  SdFile tmpFile;
  const bool success = tmpFile.open(diveDir, fname, O_READ);
  if (success) tmpFile.close();
  return success;
>>>>>>> mcu_ctrl
}

//
// Delete a file by name in the working directory
//
void CardReader::removeFile(const char * const name) {
  if (!isMounted()) return;

<<<<<<< HEAD
  //stopSDPrint();

  SdFile *curDir;
  const char * const fname = diveToFile(curDir, name);
  if (!fname) return;

  if (file.remove(curDir, fname)) {
    SERIAL_ECHOLNPAIR("File deleted:", fname);
    sdpos = 0;
    #if ENABLED(SDCARD_SORT_ALPHA)
      presort();
    #endif
  }
  else
    SERIAL_ECHOLNPAIR("Deletion failed, File: ", fname, ".");
=======
  //abortFilePrintNow();

  SdFile *itsDirPtr;
  const char * const fname = diveToFile(false, itsDirPtr, name);
  if (!fname) return;

  #if ENABLED(SDCARD_READONLY)
    SERIAL_ECHOLNPAIR("Deletion failed (read-only), File: ", fname, ".");
  #else
    if (file.remove(itsDirPtr, fname)) {
      SERIAL_ECHOLNPAIR("File deleted:", fname);
      sdpos = 0;
      TERN_(SDCARD_SORT_ALPHA, presort());
    }
    else
      SERIAL_ECHOLNPAIR("Deletion failed, File: ", fname, ".");
  #endif
>>>>>>> mcu_ctrl
}

void CardReader::report_status() {
  if (isPrinting()) {
<<<<<<< HEAD
    SERIAL_ECHOPGM(MSG_SD_PRINTING_BYTE);
    SERIAL_ECHO(sdpos);
=======
    SERIAL_ECHOPAIR(STR_SD_PRINTING_BYTE, sdpos);
>>>>>>> mcu_ctrl
    SERIAL_CHAR('/');
    SERIAL_ECHOLN(filesize);
  }
  else
<<<<<<< HEAD
    SERIAL_ECHOLNPGM(MSG_SD_NOT_PRINTING);
}

void CardReader::write_command(char * const buf) {
  char* begin = buf;
  char* npos = nullptr;
  char* end = buf + strlen(buf) - 1;

  file.writeError = false;
  if ((npos = strchr(buf, 'N')) != nullptr) {
=======
    SERIAL_ECHOLNPGM(STR_SD_NOT_PRINTING);
}

void CardReader::write_command(char * const buf) {
  char *begin = buf,
       *npos = nullptr,
       *end = buf + strlen(buf) - 1;

  file.writeError = false;
  if ((npos = strchr(buf, 'N'))) {
>>>>>>> mcu_ctrl
    begin = strchr(npos, ' ') + 1;
    end = strchr(npos, '*') - 1;
  }
  end[1] = '\r';
  end[2] = '\n';
  end[3] = '\0';
  file.write(begin);

<<<<<<< HEAD
  if (file.writeError) SERIAL_ERROR_MSG(MSG_SD_ERR_WRITE_TO_FILE);
}

//
// Run the next autostart file. Called:
// - On boot after successful card init
// - After finishing the previous autostart file
// - From the LCD command to run the autostart file
//

void CardReader::checkautostart() {

  if (autostart_index < 0 || flag.sdprinting) return;

  if (!isMounted()) mount();
  #if ENABLED(EEPROM_SETTINGS) && NONE(FLASH_EEPROM_EMULATION, SPI_EEPROM, I2C_EEPROM)
    else settings.first_load();
  #endif

  if (isMounted()
    #if ENABLED(POWER_LOSS_RECOVERY)
      && !recovery.valid() // Don't run auto#.g when a resume file exists
    #endif
  ) {
    char autoname[8];
    sprintf_P(autoname, PSTR("auto%c.g"), autostart_index + '0');
    dir_t p;
    root.rewind();
    while (root.readDir(&p, nullptr) > 0) {
      for (int8_t i = (int8_t)strlen((char*)p.name); i--;) p.name[i] = tolower(p.name[i]);
      if (p.name[9] != '~' && strncmp((char*)p.name, autoname, 5) == 0) {
        openAndPrintFile(autoname);
        autostart_index++;
        return;
      }
    }
  }
  autostart_index = -1;
}

void CardReader::beginautostart() {
  autostart_index = 0;
  cdroot();
}

void CardReader::closefile(const bool store_location) {
=======
  if (file.writeError) SERIAL_ERROR_MSG(STR_SD_ERR_WRITE_TO_FILE);
}

#if DISABLED(NO_SD_AUTOSTART)
  /**
   * Run all the auto#.g files. Called:
   * - On boot after successful card init.
   * - From the LCD command to Run Auto Files
   */
  void CardReader::autofile_begin() {
    autofile_index = 1;
    (void)autofile_check();
  }

  /**
   * Run the next auto#.g file. Called:
   *   - On boot after successful card init
   *   - After finishing the previous auto#.g file
   *   - From the LCD command to begin the auto#.g files
   *
   * Return 'true' if an auto file was started
   */
  bool CardReader::autofile_check() {
    if (!autofile_index) return false;

    if (!isMounted())
      mount();
    else if (ENABLED(SDCARD_EEPROM_EMULATION))
      settings.first_load();

    // Don't run auto#.g when a PLR file exists
    if (isMounted() && TERN1(POWER_LOSS_RECOVERY, !recovery.valid())) {
      char autoname[10];
      sprintf_P(autoname, PSTR("/auto%c.g"), '0' + autofile_index - 1);
      if (fileExists(autoname)) {
        cdroot();
        openAndPrintFile(autoname);
        autofile_index++;
        return true;
      }
    }
    autofile_cancel();
    return false;
  }
#endif

void CardReader::closefile(const bool store_location/*=false*/) {
>>>>>>> mcu_ctrl
  file.sync();
  file.close();
  flag.saving = flag.logging = false;
  sdpos = 0;
<<<<<<< HEAD
  #if ENABLED(EMERGENCY_PARSER)
    emergency_parser.enable();
  #endif
=======
  TERN_(EMERGENCY_PARSER, emergency_parser.enable());
>>>>>>> mcu_ctrl

  if (store_location) {
    //future: store printer state, filename and position for continuing a stopped print
    // so one can unplug the printer and continue printing the next day.
  }
}

//
// Get info for a file in the working directory by index
//
void CardReader::selectFileByIndex(const uint16_t nr) {
  #if ENABLED(SDSORT_CACHE_NAMES)
    if (nr < sort_count) {
      strcpy(filename, sortshort[nr]);
      strcpy(longFilename, sortnames[nr]);
      flag.filenameIsDir = IS_DIR(nr);
      return;
    }
  #endif
  workDir.rewind();
  selectByIndex(workDir, nr);
}

//
// Get info for a file in the working directory by DOS name
//
void CardReader::selectFileByName(const char * const match) {
  #if ENABLED(SDSORT_CACHE_NAMES)
<<<<<<< HEAD
    for (int nr = 0; nr < sort_count; nr++)
=======
    for (uint16_t nr = 0; nr < sort_count; nr++)
>>>>>>> mcu_ctrl
      if (strcasecmp(match, sortshort[nr]) == 0) {
        strcpy(filename, sortshort[nr]);
        strcpy(longFilename, sortnames[nr]);
        flag.filenameIsDir = IS_DIR(nr);
        return;
      }
  #endif
  workDir.rewind();
  selectByName(workDir, match);
}

uint16_t CardReader::countFilesInWorkDir() {
  workDir.rewind();
  return countItems(workDir);
}

/**
 * Dive to the given DOS 8.3 file path, with optional echo of the dive paths.
 *
<<<<<<< HEAD
 * On exit, curDir contains an SdFile reference to the file's directory.
 *
 * Returns a pointer to the last segment (filename) of the given DOS 8.3 path.
 *
 * A nullptr result indicates an unrecoverable error.
 */
const char* CardReader::diveToFile(SdFile*& curDir, const char * const path, const bool echo/*=false*/) {
  // Track both parent and subfolder
  static SdFile newDir1, newDir2;
  SdFile *sub = &newDir1, *startDir;

  const char *item_name_adr = path;
  if (path[0] == '/') {
    curDir = &root;
    workDirDepth = 0;
    item_name_adr++;
  }
  else
    curDir = &workDir;

  startDir = curDir;

  // Start dive
  while (item_name_adr) {
    // Find next sub
    char * const name_end = strchr(item_name_adr, '/');
    if (name_end <= item_name_adr) break;

    // Set subDirName
    const uint8_t len = name_end - item_name_adr;
    char dosSubdirname[len + 1];
    strncpy(dosSubdirname, item_name_adr, len);
=======
 * On entry:
 *  - The workDir points to the last-set navigation target by cd, cdup, cdroot, or diveToFile(true, ...)
 *
 * On exit:
 *  - Your curDir pointer contains an SdFile reference to the file's directory.
 *  - If update_cwd was 'true' the workDir now points to the file's directory.
 *
 * Returns a pointer to the last segment (filename) of the given DOS 8.3 path.
 * On exit, inDirPtr contains an SdFile reference to the file's directory.
 *
 * A nullptr result indicates an unrecoverable error.
 *
 * NOTE: End the path with a slash to dive to a folder. In this case the
 *       returned filename will be blank (points to the end of the path).
 */
const char* CardReader::diveToFile(const bool update_cwd, SdFile* &inDirPtr, const char * const path, const bool echo/*=false*/) {
  DEBUG_SECTION(est, "diveToFile", true);

  // Track both parent and subfolder
  static SdFile newDir1, newDir2;
  SdFile *sub = &newDir1, *startDirPtr;

  // Parsing the path string
  const char *atom_ptr = path;

  DEBUG_ECHOLNPAIR(" path = '", path, "'");

  if (path[0] == '/') {               // Starting at the root directory?
    inDirPtr = &root;
    atom_ptr++;
    DEBUG_ECHOLNPAIR(" CWD to root: ", hex_address((void*)inDirPtr));
    if (update_cwd) workDirDepth = 0; // The cwd can be updated for the benefit of sub-programs
  }
  else
    inDirPtr = &workDir;              // Dive from workDir (as set by the UI)

  startDirPtr = inDirPtr;

  DEBUG_ECHOLNPAIR(" startDirPtr = ", hex_address((void*)startDirPtr));

  while (atom_ptr) {
    // Find next subdirectory delimiter
    char * const name_end = strchr(atom_ptr, '/');

    // Last atom in the path? Item found.
    if (name_end <= atom_ptr) break;

    // Isolate the next subitem name
    const uint8_t len = name_end - atom_ptr;
    char dosSubdirname[len + 1];
    strncpy(dosSubdirname, atom_ptr, len);
>>>>>>> mcu_ctrl
    dosSubdirname[len] = 0;

    if (echo) SERIAL_ECHOLN(dosSubdirname);

<<<<<<< HEAD
    // Open curDir
    if (!sub->open(curDir, dosSubdirname, O_READ)) {
      SERIAL_ECHOLNPAIR(MSG_SD_OPEN_FILE_FAIL, dosSubdirname, ".");
      return nullptr;
    }

    // Close curDir if not at starting-point
    if (curDir != startDir) curDir->close();

    // curDir now subDir
    curDir = sub;

    // Update workDirParents and workDirDepth
    if (workDirDepth < MAX_DIR_DEPTH) workDirParents[workDirDepth++] = *curDir;

    // Point sub pointer to unused newDir
    sub = (curDir != &newDir1) ? &newDir1 : &newDir2;

    // item_name_adr point to next sub
    item_name_adr = name_end + 1;
  }
  return item_name_adr;
}

void CardReader::cd(const char * relpath) {
  SdFile newDir;
  SdFile *parent = workDir.isOpen() ? &workDir : &root;
=======
    DEBUG_ECHOLNPAIR(" sub = ", hex_address((void*)sub));

    // Open inDirPtr (closing first)
    sub->close();
    if (!sub->open(inDirPtr, dosSubdirname, O_READ)) {
      openFailed(dosSubdirname);
      atom_ptr = nullptr;
      break;
    }

    // Close inDirPtr if not at starting-point
    if (inDirPtr != startDirPtr) {
      DEBUG_ECHOLNPAIR(" closing inDirPtr: ", hex_address((void*)inDirPtr));
      inDirPtr->close();
    }

    // inDirPtr now subDir
    inDirPtr = sub;
    DEBUG_ECHOLNPAIR(" inDirPtr = sub: ", hex_address((void*)inDirPtr));

    // Update workDirParents and workDirDepth
    if (update_cwd) {
      DEBUG_ECHOLNPAIR(" update_cwd");
      if (workDirDepth < MAX_DIR_DEPTH)
        workDirParents[workDirDepth++] = *inDirPtr;
    }

    // Point sub at the other scratch object
    sub = (inDirPtr != &newDir1) ? &newDir1 : &newDir2;
    DEBUG_ECHOLNPAIR(" swapping sub = ", hex_address((void*)sub));

    // Next path atom address
    atom_ptr = name_end + 1;
  }

  if (update_cwd) {
    workDir = *inDirPtr;
    DEBUG_ECHOLNPAIR(" final workDir = ", hex_address((void*)inDirPtr));
    flag.workDirIsRoot = (workDirDepth == 0);
    TERN_(SDCARD_SORT_ALPHA, presort());
  }

  DEBUG_ECHOLNPAIR(" returning string ", atom_ptr ?: "nullptr");
  return atom_ptr;
}

void CardReader::cd(const char * relpath) {
  SdFile newDir, *parent = &getWorkDir();
>>>>>>> mcu_ctrl

  if (newDir.open(parent, relpath, O_READ)) {
    workDir = newDir;
    flag.workDirIsRoot = false;
    if (workDirDepth < MAX_DIR_DEPTH)
      workDirParents[workDirDepth++] = workDir;
<<<<<<< HEAD
    #if ENABLED(SDCARD_SORT_ALPHA)
      presort();
    #endif
  }
  else {
    SERIAL_ECHO_START();
    SERIAL_ECHOLNPAIR(MSG_SD_CANT_ENTER_SUBDIR, relpath);
  }
=======
    TERN_(SDCARD_SORT_ALPHA, presort());
  }
  else
    SERIAL_ECHO_MSG(STR_SD_CANT_ENTER_SUBDIR, relpath);
>>>>>>> mcu_ctrl
}

int8_t CardReader::cdup() {
  if (workDirDepth > 0) {                                               // At least 1 dir has been saved
    workDir = --workDirDepth ? workDirParents[workDirDepth - 1] : root; // Use parent, or root if none
<<<<<<< HEAD
    #if ENABLED(SDCARD_SORT_ALPHA)
      presort();
    #endif
=======
    TERN_(SDCARD_SORT_ALPHA, presort());
>>>>>>> mcu_ctrl
  }
  if (!workDirDepth) flag.workDirIsRoot = true;
  return workDirDepth;
}

void CardReader::cdroot() {
  workDir = root;
  flag.workDirIsRoot = true;
<<<<<<< HEAD
  #if ENABLED(SDCARD_SORT_ALPHA)
    presort();
  #endif
=======
  TERN_(SDCARD_SORT_ALPHA, presort());
>>>>>>> mcu_ctrl
}

#if ENABLED(SDCARD_SORT_ALPHA)

  /**
   * Get the name of a file in the working directory by sort-index
   */
  void CardReader::getfilename_sorted(const uint16_t nr) {
<<<<<<< HEAD
    selectFileByIndex(
      #if ENABLED(SDSORT_GCODE)
        sort_alpha &&
      #endif
      (nr < sort_count) ? sort_order[nr] : nr
    );
=======
    selectFileByIndex(TERN1(SDSORT_GCODE, sort_alpha) && (nr < sort_count)
      ? sort_order[nr] : nr);
>>>>>>> mcu_ctrl
  }

  #if ENABLED(SDSORT_USES_RAM)
    #if ENABLED(SDSORT_DYNAMIC_RAM)
      // Use dynamic method to copy long filename
      #define SET_SORTNAME(I) (sortnames[I] = strdup(longest_filename()))
      #if ENABLED(SDSORT_CACHE_NAMES)
        // When caching also store the short name, since
        // we're replacing the selectFileByIndex() behavior.
        #define SET_SORTSHORT(I) (sortshort[I] = strdup(filename))
      #else
        #define SET_SORTSHORT(I) NOOP
      #endif
    #else
      // Copy filenames into the static array
      #define _SET_SORTNAME(I) strncpy(sortnames[I], longest_filename(), SORTED_LONGNAME_MAXLEN)
      #if SORTED_LONGNAME_MAXLEN == LONG_FILENAME_LENGTH
        // Short name sorting always use LONG_FILENAME_LENGTH with no trailing nul
        #define SET_SORTNAME(I) _SET_SORTNAME(I)
      #else
        // Copy multiple name blocks. Add a nul for the longest case.
        #define SET_SORTNAME(I) do{ _SET_SORTNAME(I); sortnames[I][SORTED_LONGNAME_MAXLEN] = '\0'; }while(0)
      #endif
      #if ENABLED(SDSORT_CACHE_NAMES)
        #define SET_SORTSHORT(I) strcpy(sortshort[I], filename)
      #else
        #define SET_SORTSHORT(I) NOOP
      #endif
    #endif
  #endif

  /**
   * Read all the files and produce a sort key
   *
   * We can do this in 3 ways...
   *  - Minimal RAM: Read two filenames at a time sorting along...
   *  - Some RAM: Buffer the directory just for this sort
   *  - Most RAM: Buffer the directory and return filenames from RAM
   */
  void CardReader::presort() {

    // Throw away old sort index
    flush_presort();

    // Sorting may be turned off
<<<<<<< HEAD
    #if ENABLED(SDSORT_GCODE)
      if (!sort_alpha) return;
    #endif
=======
    if (TERN0(SDSORT_GCODE, !sort_alpha)) return;
>>>>>>> mcu_ctrl

    // If there are files, sort up to the limit
    uint16_t fileCnt = countFilesInWorkDir();
    if (fileCnt > 0) {

      // Never sort more than the max allowed
      // If you use folders to organize, 20 may be enough
      NOMORE(fileCnt, uint16_t(SDSORT_LIMIT));

      // Sort order is always needed. May be static or dynamic.
<<<<<<< HEAD
      #if ENABLED(SDSORT_DYNAMIC_RAM)
        sort_order = new uint8_t[fileCnt];
      #endif
=======
      TERN_(SDSORT_DYNAMIC_RAM, sort_order = new uint8_t[fileCnt]);
>>>>>>> mcu_ctrl

      // Use RAM to store the entire directory during pre-sort.
      // SDSORT_LIMIT should be set to prevent over-allocation.
      #if ENABLED(SDSORT_USES_RAM)

        // If using dynamic ram for names, allocate on the heap.
        #if ENABLED(SDSORT_CACHE_NAMES)
          #if ENABLED(SDSORT_DYNAMIC_RAM)
            sortshort = new char*[fileCnt];
            sortnames = new char*[fileCnt];
          #endif
        #elif ENABLED(SDSORT_USES_STACK)
          char sortnames[fileCnt][SORTED_LONGNAME_STORAGE];
        #endif

        // Folder sorting needs 1 bit per entry for flags.
        #if HAS_FOLDER_SORTING
          #if ENABLED(SDSORT_DYNAMIC_RAM)
            isDir = new uint8_t[(fileCnt + 7) >> 3];
          #elif ENABLED(SDSORT_USES_STACK)
            uint8_t isDir[(fileCnt + 7) >> 3];
          #endif
        #endif

      #else // !SDSORT_USES_RAM

        // By default re-read the names from SD for every compare
        // retaining only two filenames at a time. This is very
        // slow but is safest and uses minimal RAM.
        char name1[LONG_FILENAME_LENGTH];

      #endif

      if (fileCnt > 1) {

        // Init sort order.
        for (uint16_t i = 0; i < fileCnt; i++) {
<<<<<<< HEAD
          sort_order[i] = (
            #if ENABLED(SDCARD_RATHERRECENTFIRST)
              fileCnt - 1 -
            #endif
          i);
=======
          sort_order[i] = i;
>>>>>>> mcu_ctrl
          // If using RAM then read all filenames now.
          #if ENABLED(SDSORT_USES_RAM)
            selectFileByIndex(i);
            SET_SORTNAME(i);
            SET_SORTSHORT(i);
            // char out[30];
            // sprintf_P(out, PSTR("---- %i %s %s"), i, flag.filenameIsDir ? "D" : " ", sortnames[i]);
            // SERIAL_ECHOLN(out);
            #if HAS_FOLDER_SORTING
              const uint16_t bit = i & 0x07, ind = i >> 3;
              if (bit == 0) isDir[ind] = 0x00;
<<<<<<< HEAD
              if (flag.filenameIsDir) isDir[ind] |= _BV(bit);
=======
              if (flag.filenameIsDir) SBI(isDir[ind], bit);
>>>>>>> mcu_ctrl
            #endif
          #endif
        }

        // Bubble Sort
        for (uint16_t i = fileCnt; --i;) {
          bool didSwap = false;
          uint8_t o1 = sort_order[0];
          #if DISABLED(SDSORT_USES_RAM)
<<<<<<< HEAD
            selectFileByIndex(o1);                // Pre-fetch the first entry and save it
            strcpy(name1, longest_filename());  // so the loop only needs one fetch
            #if HAS_FOLDER_SORTING
=======
            selectFileByIndex(o1);              // Pre-fetch the first entry and save it
            strcpy(name1, longest_filename());  // so the loop only needs one fetch
            #if ENABLED(HAS_FOLDER_SORTING)
>>>>>>> mcu_ctrl
              bool dir1 = flag.filenameIsDir;
            #endif
          #endif

          for (uint16_t j = 0; j < i; ++j) {
            const uint16_t o2 = sort_order[j + 1];

            // Compare names from the array or just the two buffered names
            #if ENABLED(SDSORT_USES_RAM)
              #define _SORT_CMP_NODIR() (strcasecmp(sortnames[o1], sortnames[o2]) > 0)
            #else
              #define _SORT_CMP_NODIR() (strcasecmp(name1, name2) > 0)
            #endif

            #if HAS_FOLDER_SORTING
              #if ENABLED(SDSORT_USES_RAM)
                // Folder sorting needs an index and bit to test for folder-ness.
<<<<<<< HEAD
                #define _SORT_CMP_DIR(fs) IS_DIR(o1) == IS_DIR(o2) ? _SORT_CMP_NODIR() : IS_DIR(fs > 0 ? o1 : o2)
=======
                #define _SORT_CMP_DIR(fs) (IS_DIR(o1) == IS_DIR(o2) ? _SORT_CMP_NODIR() : IS_DIR(fs > 0 ? o1 : o2))
>>>>>>> mcu_ctrl
              #else
                #define _SORT_CMP_DIR(fs) ((dir1 == flag.filenameIsDir) ? _SORT_CMP_NODIR() : (fs > 0 ? dir1 : !dir1))
              #endif
            #endif

            // The most economical method reads names as-needed
            // throughout the loop. Slow if there are many.
            #if DISABLED(SDSORT_USES_RAM)
              selectFileByIndex(o2);
              const bool dir2 = flag.filenameIsDir;
              char * const name2 = longest_filename(); // use the string in-place
            #endif // !SDSORT_USES_RAM

            // Sort the current pair according to settings.
            if (
              #if HAS_FOLDER_SORTING
                #if ENABLED(SDSORT_GCODE)
                  sort_folders ? _SORT_CMP_DIR(sort_folders) : _SORT_CMP_NODIR()
                #else
                  _SORT_CMP_DIR(FOLDER_SORTING)
                #endif
              #else
                _SORT_CMP_NODIR()
              #endif
            ) {
              // Reorder the index, indicate that sorting happened
              // Note that the next o1 will be the current o1. No new fetch needed.
              sort_order[j] = o2;
              sort_order[j + 1] = o1;
              didSwap = true;
            }
            else {
              // The next o1 is the current o2. No new fetch needed.
              o1 = o2;
              #if DISABLED(SDSORT_USES_RAM)
<<<<<<< HEAD
                #if HAS_FOLDER_SORTING
                  dir1 = dir2;
                #endif
=======
                TERN_(HAS_FOLDER_SORTING, dir1 = dir2);
>>>>>>> mcu_ctrl
                strcpy(name1, name2);
              #endif
            }
          }
          if (!didSwap) break;
        }
        // Using RAM but not keeping names around
        #if ENABLED(SDSORT_USES_RAM) && DISABLED(SDSORT_CACHE_NAMES)
          #if ENABLED(SDSORT_DYNAMIC_RAM)
            for (uint16_t i = 0; i < fileCnt; ++i) free(sortnames[i]);
<<<<<<< HEAD
            #if HAS_FOLDER_SORTING
              free(isDir);
            #endif
=======
            TERN_(HAS_FOLDER_SORTING, free(isDir));
>>>>>>> mcu_ctrl
          #endif
        #endif
      }
      else {
        sort_order[0] = 0;
        #if BOTH(SDSORT_USES_RAM, SDSORT_CACHE_NAMES)
          #if ENABLED(SDSORT_DYNAMIC_RAM)
            sortnames = new char*[1];
            sortshort = new char*[1];
            isDir = new uint8_t[1];
          #endif
          selectFileByIndex(0);
          SET_SORTNAME(0);
          SET_SORTSHORT(0);
          isDir[0] = flag.filenameIsDir;
        #endif
      }

      sort_count = fileCnt;
    }
  }

  void CardReader::flush_presort() {
    if (sort_count > 0) {
      #if ENABLED(SDSORT_DYNAMIC_RAM)
        delete sort_order;
        #if ENABLED(SDSORT_CACHE_NAMES)
<<<<<<< HEAD
          for (uint8_t i = 0; i < sort_count; ++i) {
=======
          LOOP_L_N(i, sort_count) {
>>>>>>> mcu_ctrl
            free(sortshort[i]); // strdup
            free(sortnames[i]); // strdup
          }
          delete sortshort;
          delete sortnames;
        #endif
      #endif
      sort_count = 0;
    }
  }

#endif // SDCARD_SORT_ALPHA

uint16_t CardReader::get_num_Files() {
<<<<<<< HEAD
  return
    #if ENABLED(SDCARD_SORT_ALPHA) && SDSORT_USES_RAM && SDSORT_CACHE_NAMES
=======
  if (!isMounted()) return 0;
  return (
    #if ALL(SDCARD_SORT_ALPHA, SDSORT_USES_RAM, SDSORT_CACHE_NAMES)
>>>>>>> mcu_ctrl
      nrFiles // no need to access the SD card for filenames
    #else
      countFilesInWorkDir()
    #endif
<<<<<<< HEAD
  ;
=======
  );
>>>>>>> mcu_ctrl
}

//
// Return from procedure or close out the Print Job
//
<<<<<<< HEAD
void CardReader::printingHasFinished() {
  planner.synchronize();
  file.close();
  if (file_subcall_ctr > 0) { // Heading up to a parent file that called current as a procedure.
    file_subcall_ctr--;
    openFile(proc_filenames[file_subcall_ctr], true, true);
    setIndex(filespos[file_subcall_ctr]);
    startFileprint();
  }
  else {
    stopSDPrint();

    #ifdef DWIN_LCDDISPLAY
      HMI_flag.print_finish = 1;
    #endif

    #if ENABLED(POWER_LOSS_RECOVERY)
      removeJobRecoveryFile();
    #endif

    #if ENABLED(SD_FINISHED_STEPPERRELEASE) && defined(SD_FINISHED_RELEASECOMMAND)
      planner.finish_and_disable();
    #endif

    print_job_timer.stop();
    queue.enqueue_now_P(print_job_timer.duration() > 60 ? PSTR("M31") : PSTR("M117"));

    #if ENABLED(SDCARD_SORT_ALPHA)
      presort();
    #endif

    #if ENABLED(LCD_SET_PROGRESS_MANUALLY)
      ui.set_progress_done();
    #endif

    #if ENABLED(SD_REPRINT_LAST_SELECTED_FILE)
      ui.reselect_last_file();
    #endif
  }
}

#if ENABLED(AUTO_REPORT_SD_STATUS)
  uint8_t CardReader::auto_report_sd_interval = 0;
  millis_t CardReader::next_sd_report_ms;
  #if NUM_SERIAL > 1
    int8_t CardReader::auto_report_port;
  #endif

  void CardReader::auto_report_sd_status() {
    millis_t current_ms = millis();
    if (auto_report_sd_interval && ELAPSED(current_ms, next_sd_report_ms)) {
      next_sd_report_ms = current_ms + 1000UL * auto_report_sd_interval;
      PORT_REDIRECT(auto_report_port);
      report_status();
    }
  }
#endif // AUTO_REPORT_SD_STATUS
=======
void CardReader::fileHasFinished() {
  file.close();
  #if HAS_MEDIA_SUBCALLS
    if (file_subcall_ctr > 0) { // Resume calling file after closing procedure
      file_subcall_ctr--;
      openFileRead(proc_filenames[file_subcall_ctr], 2); // 2 = Returning from sub-procedure
      setIndex(filespos[file_subcall_ctr]);
      startOrResumeFilePrinting();
      return;
    }
  #endif

  endFilePrintNow(TERN_(SD_RESORT, true));

  flag.sdprintdone = true;        // Stop getting bytes from the SD card
  marlin_state = MF_SD_COMPLETE;  // Tell Marlin to enqueue M1001 soon
}

#if ENABLED(AUTO_REPORT_SD_STATUS)
  AutoReporter<CardReader::AutoReportSD> CardReader::auto_reporter;
#endif
>>>>>>> mcu_ctrl

#if ENABLED(POWER_LOSS_RECOVERY)

  bool CardReader::jobRecoverFileExists() {
    const bool exists = recovery.file.open(&root, recovery.filename, O_READ);
    if (exists) recovery.file.close();
    return exists;
  }

  void CardReader::openJobRecoveryFile(const bool read) {
    if (!isMounted()) return;
    if (recovery.file.isOpen()) return;
    if (!recovery.file.open(&root, recovery.filename, read ? O_READ : O_CREAT | O_WRITE | O_TRUNC | O_SYNC))
<<<<<<< HEAD
      SERIAL_ECHOLNPAIR(MSG_SD_OPEN_FILE_FAIL, recovery.filename, ".");
    else if (!read)
      SERIAL_ECHOLNPAIR(MSG_SD_WRITE_TO_FILE, recovery.filename);
=======
      openFailed(recovery.filename);
    else if (!read)
      echo_write_to_file(recovery.filename);
>>>>>>> mcu_ctrl
  }

  // Removing the job recovery file currently requires closing
  // the file being printed, so during SD printing the file should
  // be zeroed and written instead of deleted.
  void CardReader::removeJobRecoveryFile() {
<<<<<<< HEAD
    #ifdef EEPROM_PLR
      recovery.init();
      BL24CXX_Write(PLR_ADDR, (uint8_t*)&recovery.info, sizeof(recovery.info));
    #else
      if (jobRecoverFileExists()) {
        recovery.init();
        removeFile(recovery.filename);
        #if ENABLED(DEBUG_POWER_LOSS_RECOVERY)
          SERIAL_ECHOPGM("Power-loss file delete");
          serialprintPGM(jobRecoverFileExists() ? PSTR(" failed.\n") : PSTR("d.\n"));
        #endif
      }
    #endif
=======
    if (jobRecoverFileExists()) {
      recovery.init();
      removeFile(recovery.filename);
      #if ENABLED(DEBUG_POWER_LOSS_RECOVERY)
        SERIAL_ECHOPGM("Power-loss file delete");
        SERIAL_ECHOPGM_P(jobRecoverFileExists() ? PSTR(" failed.\n") : PSTR("d.\n"));
      #endif
    }
>>>>>>> mcu_ctrl
  }

#endif // POWER_LOSS_RECOVERY

#endif // SDSUPPORT
