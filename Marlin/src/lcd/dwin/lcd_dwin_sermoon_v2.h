#ifndef __LCDAUTOUI_H
#define __LCDAUTOUI_H

#include "../../inc/MarlinConfig.h"

/**
 * function enable
 */
// #ifdef FILAMENT_RUNOUT_SENSOR
    #define ENABLE_MATERIAL_CHECK               1                   /* 1: enable material check, 0: disable material check   */
// #endif
// #define ENABLE_DOOR_OPEN_CHECK              1                   /* 1: enable door-open check, 0: disable door-open check */

/**
 * device configurations
 */
#define FEEDING_TEMP                        240                 /* temperature of feeding material                   */
#define FEEDING_DEF_DISTANCE                1000                /* in material: default distance of feeding material */
#define FEEDING_DEF_SPEED                   3                   /* in material: default speed of feeding             */
#define FEEDING_DEF_OUT_MAT_DIS1            10                  /* out material: default distance of in-material     */
#define FEEDING_DEF_OUT_MAT_SPE1            15                  /* out material: default speed of in-material        */
#define FEEDING_DEF_OUT_MAT_DIS2            -70                 /* out material: default distance of out-material    */
#define FEEDING_DEF_OUT_MAT_SPE2            30                  /* out material: default speed of out-material       */
#define BED_CALI_STEPUNIT                   0.05                /* bed calibration Z axis adjust unit                */
#define BED_CALI_POINT_NUM                  5                   /* number of points(bed calibration)                 */
#define PAUSE_POS_Z_HEIGHT_DIF              5                   /* Z axis height(mm) difference between pause-before and pause-after */
#define CLOHEATMR_TIME                      (5*60*1000)         /* how long the close-heater-timer set               */
#define PRINT_RECOVER_EXTERA_E_POS          (-3)                /* print recovery out extera material                */

/**
 * icon-variable address without words
 * in range: 0x1000 ~ 0x1FFF
 */
#define ICONVAR_ADDR_PROGRESSBAR            0x1000              /* adress of progress-bar      */
#define ICONVAR_ADDR_DYNAHOMING             0x1004              /* dynamic going home          */
#define ICONVAR_ADDR_FILESELECT_BG00        0x100E              /* file selected background 00 */
#define ICONVAR_ADDR_FILESELECT_BG01        0x100F              /* file selected background 01 */
#define ICONVAR_ADDR_FILESELECT_BG02        0x1010              /* file selected background 02 */
#define ICONVAR_ADDR_FILESELECT_BG03        0x1011              /* file selected background 03 */
#define ICONVAR_ADDR_FILESELECT_BG04        0x1012              /* file selected background 04 */
#define ICONVAR_ADDR_FILESELECT_BG05        0x1013              /* file selected background 05 */
#define ICONVAR_ADDR_FILESELECT_BG06        0x1014              /* file selected background 06 */
#define ICONVAR_ADDR_FILESELECT_BG07        0x1015              /* file selected background 07 */
#define ICONVAR_ADDR_FILESELECT_BG08        0x1016              /* file selected background 08 */
#define ICONVAR_ADDR_FILESELECT_BG09        0x1017              /* file selected background 09 */
#define ICONVAR_ADDR_FILESELECT_BG10        0x1018              /* file selected background 10 */
#define ICONVAR_ADDR_FILESELECT_BG11        0x1019              /* file selected background 11 */
#define ICONVAR_ADDR_FILESELECT_BG12        0x101A              /* file selected background 12 */
#define ICONVAR_ADDR_FILESELECT_BG13        0x101B              /* file selected background 13 */
#define ICONVAR_ADDR_FILESELECT_BG14        0x101C              /* file selected background 14 */
#define ICONVAR_ADDR_FILESELECT_BG15        0x101D              /* file selected background 15 */
#define ICONVAR_ADDR_FILESELECT_BG16        0x101E              /* file selected background 16 */
#define ICONVAR_ADDR_FILESELECT_BG17        0x101F              /* file selected background 17 */
#define ICONVAR_ADDR_FILESELECT_BG18        0x1020              /* file selected background 18 */
#define ICONVAR_ADDR_FILESELECT_BG19        0x1021              /* file selected background 19 */
#define ICONVAR_ADDR_FILESELECT_BG20        0x1022              /* file selected background 20 */
#define ICONVAR_ADDR_PRINT_PROGRESS         0x1024              /* display printing progress   */
#define ICONVAR_ADDR_BOX_FAN                0x102E              /* box fan                     */
#define ICONVAR_ADDR_BOX_LED                0x1030              /* box led                     */
#define ICONVAR_ADDR_WIFI_LED               0x1032              /* wifi led                    */
#define ICONVAR_ADDR_DOOR_OPEN_PAUSE        0x1034              /* pause printing if door open */
#define ICONVAR_ADDR_DOOR_OPEN_TIP          0x103F              /* door open warning           */
#define ICONVAR_ADDR_PLA_SELECTED           0x1042              /* PLA mode selected           */
#define ICONVAR_ADDR_ABS_SELECTED           0x1044              /* ABS mode selected           */
#define ICONVAR_ADDR_HOTEND_FAN_STA         0x1053              /* user define hotend fan      */
#define ICONVAR_ADDR_BOX_FAN_STA            0x1055              /* user define box fan         */
#define ICONVAR_ADDR_BEDCALI_CURPOINT       0x1065              /* display current point that need to calibration */
#define ICONVAR_ADDR_INOUTMAT_TIP           0x104C              /* in/out material tips        */
#define ICONVAR_ADDR_HEATING_HOTEND         0x1080              /* heating hotend Dynamic icon */
#define ICONVAR_ADDR_HEATING_BED            0x1082              /* heating bed Dynamic icon    */
#define ICONVAR_ADDR_IN_MAT                 0x1084              /* heating bed Dynamic icon    */
#define ICONVAR_ADDR_OUT_MAT_RETURN_KEY     0x1086              /* out mat return key          */
#define ICONVAR_ADDR_LEVEL_TITLR            0x1090              /* 调平模式界面标题 */
#define ICONVAR_ADDR_AUX_LEVEL              0x1091              /* 辅助调平文本 */
#define ICONVAR_ADDR_AUYO_LEVEL             0x1092              /* 自动调平文本 */
#define ICONVAR_ADDR_AUX_LEVEL_TITLR        0x1093              /* 辅助调平界面标题 */
#define ICONVAR_ADDR_AUX_LEVEL_TIPS         0x1094              /* 辅助调平提示信息 */
#define ICONVAR_ADDR_AUTO_LEVEL_TITLE       0x1095              /* 自动调平界面标题 */
#define ICONVAR_ADDR_AUTO_LEVEL_TIPS        0x1096              /* 自动调平提示信息 */
#define ICONVAR_ADDR_AUTO_LEVEL_PROCESS     0x1097              /* 自动调平过程     */
#define ICONVAR_ADDR_LEVEL_ENABLE           0x1098              /* 调平使能         */
#define ICONVAR_ADDR_WIFI_RESET             0x1099              /* wifi复位         */
#define ICONVAR_ADDR_WIFI_ENABLE            0x109A              /* wifi使能         */
#define ICONVAR_ADDR_WIFI_SWITCH            0x109B              /* wifi开关         */
/**
 * touch-variable address
 * in range: 0x2000 ~ 0x2FFF
 */
#define TOUVAR_NUM                          100                 /* number of touch-variables */

/**
 * data-variable address
 * in range: 0x3000 ~ 0x3FFF
 */
#define DATAVAR_ADDR_HOTENDTEMP_CUR         0x3000              /* current hotend temperature */
#define DATAVAR_ADDR_HOTENDTEMP_GIVEN       0x3002              /* given hotend temperature   */
#define DATAVAR_ADDR_BEDTEMP_CUR            0x3004              /* current bed temperature    */
#define DATAVAR_ADDR_BEDTEMP_GIVEN          0x3006              /* given bed temperature      */
#define DATAVAR_ADDR_PRINTTIME_TOTAL        0x3008              /* display total printing time*/
#define DATAVAR_ADDR_CENTRAL_Z_OFFSET       0x300C              /* bed calibration, Z offset of central point   */
#define DATAVAR_ADDR_PRINT_PROGRESS         0x300D              /* display how many percent a file has printed  */
#define DATAVAR_ADDR_PRINT_TIME_H           0x300F              /* display how long a file has printed / hour   */
#define DATAVAR_ADDR_PRINT_TIME_M           0x3011              /* display how long a file has printed / minute */
#define DATAVAR_ADDR_USERDEF_HOTEND_TEMP    0x3013              /* user define mode - set hotend temperature    */
#define DATAVAR_ADDR_USERDEF_BED_TEMP       0x3015              /* user define mode - set bed temperature       */
#define DATAVAR_ADDR_ZOFFSET                0x3017              /* Z offset                   */
#define DATAVAR_ADDR_ZHEIGHT                0x301B              /* Z height that calibration  */
#define DATAVAR_ADDR_CURPOS_X               0x301F              /* current position of X axis */
#define DATAVAR_ADDR_CURPOS_Y               0x3023              /* current position of X axis */
#define DATAVAR_ADDR_CURPOS_Z               0x3027              /* current position of X axis */
#define DATAVAR_ADDR_FEEDRARE               0x302B              /* printing feedrate percentage */
#define DATAVAR_ADDR_AUTO_LEVEL             0x304C              /* 自动调平值 0x304C + 2*25 = 0x307E             */
#define DATAVAR_ADDR_Z_OFFSET               0x3080              /* Z轴补偿                    */

/**
 * text-variable address
 * in range: 0x4000 ~ 0x4FFF
 */
#define TEXTVAR_ADDR_FILENAME_00            0x4020
#define TEXTVAR_ADDR_FILENAME_01            0x4040
#define TEXTVAR_ADDR_FILENAME_02            0x4060
#define TEXTVAR_ADDR_FILENAME_03            0x4080
#define TEXTVAR_ADDR_FILENAME_04            0x40A0
#define TEXTVAR_ADDR_FILENAME_05            0x40C0
#define TEXTVAR_ADDR_FILENAME_06            0x40E0
#define TEXTVAR_ADDR_FILENAME_07            0x4100
#define TEXTVAR_ADDR_FILENAME_08            0x4120
#define TEXTVAR_ADDR_FILENAME_09            0x4140
#define TEXTVAR_ADDR_FILENAME_10            0x4160
#define TEXTVAR_ADDR_FILENAME_11            0x4180
#define TEXTVAR_ADDR_FILENAME_12            0x41A0
#define TEXTVAR_ADDR_FILENAME_13            0x41C0
#define TEXTVAR_ADDR_FILENAME_14            0x41E0
#define TEXTVAR_ADDR_FILENAME_15            0x4200
#define TEXTVAR_ADDR_FILENAME_16            0x4220
#define TEXTVAR_ADDR_FILENAME_17            0x4240
#define TEXTVAR_ADDR_FILENAME_18            0x4260
#define TEXTVAR_ADDR_FILENAME_19            0x4280
#define TEXTVAR_ADDR_FILENAME_PRINTING      0x42B0
#define TEXTVAR_ADDR_FILENAME_INTERRUPT     0x42F0              /* printing file name(interrupt printing because of power off) */
#define TEXTVAR_ADDR_HARDWARE_VER           0x4310
#define TEXTVAR_ADDR_FIRMWARE_VER           0x4330
#define TEXTVAR_ADDR_SCREEN_VER             0x4350              /* screen project version   */
#define TEXTVAR_ADDR_PRINT_TOTAL_TIME       0x4370              /* reserve, unused          */
#define TEXTVAR_ADDR_PRINT_SIZE             0x4390
#define TEXTVAR_ADDR_DEVICE_NAME            0x43B0
#define TEXTVAR_ADDR_OFFICIAL_WEB           0x43D0

/**
 * gcode filename
 */
#define GCODE_FILE_BYTELEN                  32                  /* length of gcode filename */
#define GCODE_FILE_NUM_MAX                  20                  /* max number of gcode file */

/**
 * selected status
 */
#define SELECTED_YES                        1
#define SELECTED_NO                         0

/**
 * enable switch
 */
#define AUTOUI_ENABLE                       1
#define AUTOUI_DISABLE                      0

/**
 * times --- X/Y/Z position value that get from DWIN bigger than their real value
 */
#define DWIN_REALVAL_TIMES                  10

/**
 * flag value, recorded in EEPROM
 */
#define STARTUP_FIR_TIME_VAL                0xA5                /* to express if something happen or not */

/**
 * EEPROM address(offset) to record some value, base on 'FONT_EEPROM'
 */
#define EEPROM_ADDR_STTF_OFFSET             5                   /* record flag value for 'startupFirstTimeFlag', length: 1Byte */
#define EEPROM_ADDR_STTF_SIZE               1                   /* size of 'startupFirstTimeFlag', uint/Byte                   */
#define EEPROM_ADDR_TPT_OFFSET              6                   /* record Total-Printing-Time                                  */
#define EEPROM_ADDR_TPT_SIZE                4                   /* size of Total-Printing-Time, uint/Byte                      */
#define EEPROM_ADDR_UDMP_OFFSET             10                  /* record User-Define-Mode-Parameter                           */
#define EEPROM_ADDR_UDMP_SIZE               6                   /* size of User-Define-Mode-Parameter, uint/Byte               */
#define EEPROM_ADDR_OTA_OFFSET              16                  /* record OTA flags                                            */
#define EEPROM_ADDR_OTA_SIZE                10                  /* size uint/Byte                                              */
#define EEPROM_ADDR_BFLWD_OFFSET            26                  /* record box-fan/box-led/wifi-led/door-pause function status  */
#define EEPROM_ADDR_BFLWD_SIZE              1                   /* size uint/Byte                                              */
#define EEPROM_ADDR_ZAXIS_OFFSET            27                  /* record Z axis offset when bed calibreation                  */
#define EEPROM_ADDR_ZAXIS_SIZE              4                   /* size uint/Byte                                              */

/**
 * default: language that device display
 */
#define DEFAULT_LANGUAGE                    0                   /* Chinese, according to 'AutoUILanguage_t' */

/**
 * value means invalid(for example - no file selected/not display icon)
 */
#define VAULE_INVALIDE                      0xFFFF
#define VAULE_INVALIDE_8BIT                 0xFF

/**
 * icon-variable address with words
 */
#define ICONVAR_WITHWORDS_NUM               10
const unsigned long gIconVariAddrArray[ICONVAR_WITHWORDS_NUM] = 
{
    0x1001,                                /* in background picture : 001 */
    0x1002,                                /* in background picture : 001 */
    0x1003,                                /* in background picture : 002 */
    0x1005,                                /* in background picture : 003 */
    0x1006,                                /* in background picture : 004/005 */
    0x1007,                                /* in background picture : 006 */
    0x1008,                                /* in background picture : 007 */
    0x1009,                                /* in background picture : 008 */
    0x100A,                                /* in background picture : 008 */
    0x104C,                                /* in background picture : 021 */
};

/**
 * DWIN touch-variables address
 */
typedef enum
{
    TOUVAR_PIC001_CONFIRM      = 0x2000,
    TOUVAR_PIC004_CONFIRM      = 0x2001,
    TOUVAR_PIC005_CONFIRM      = 0x2002,
    TOUVAR_PIC006_CONFIRM      = 0x2003,
    TOUVAR_PIC008_PRINTFILE    = 0x2004,
    TOUVAR_PIC008_PRINTMODE    = 0x2005,
    TOUVAR_PIC008_PRINTSET     = 0x2006,
    TOUVAR_PIC008_DEVINFO      = 0x2007,
    TOUVAR_PIC008_HOTENDTEMP   = 0x2054,   /* special, get data from DWIN, the address must be the same with the data-variable */
    TOUVAR_PIC008_BEDTEMP      = 0x2058,   /* special, get data from DWIN, the address must be the same with the data-variable */
    TOUVAR_PIC_RETURN          = 0x2008,   /* exist in many pages               */
    TOUVAR_PIC_FILE_SELECT     = 0x2009,   /* exist in page 009,010,011,012,013 */
    TOUVAR_PIC_NEXT_PAGE       = 0x200A,   /* go to next page                   */
    TOUVAR_PIC_LAST_PAGE       = 0x200B,   /* go to last page                   */
    TOUVAR_PIC014_PRINT_SET    = 0x200C,   /* settings in printing              */
    TOUVAR_PIC014_PRINT_PAUSE  = 0x200D,   /* pause print                       */
    TOUVAR_PIC014_PRINT_STOP   = 0x200E,   /* stop print                        */
    TOUVAR_PIC015_FINISH       = 0x200F,   /* print finished confirm            */
    TOUVAR_PIC016_BOX_FAN      = 0x2010,   /* box fan control                   */
    TOUVAR_PIC016_BOX_LED      = 0x2011,   /* box led control                   */
    TOUVAR_PIC016_WIFI_LED     = 0x2012,   /* wifi led control                  */
    TOUVAR_PIC016_DOOR_PAUSE   = 0x2013,   /* switch of function - pause if door open during printing */
    TOUVAR_PIC017_CONFIRM      = 0x2014,   /* confirm to stop print             */
    TOUVAR_PIC017_CANCEL       = 0x2015,   /* cancel stopping print             */
    TOUVAR_PIC018_CONTINUE     = 0x2016,   /* continue to print                 */
    TOUVAR_PIC018_STOP         = 0x2017,   /* stop print                        */
    TOUVAR_PIC018_IN_OUT_MAT   = 0x2018,   /* in/out material                   */
    TOUVAR_PIC019_CONFIRM      = 0x2019,   /* door open pause, confirm to print */
    TOUVAR_PIC019_CANCEL       = 0x201A,   /* door open pause, cancel to print  */
    TOUVAR_PIC020_PLA_SELECT   = 0x201B,   /* select PLA print-mode             */
    TOUVAR_PIC020_ABS_SELECT   = 0x201C,   /* select ABS print-mode             */
    TOUVAR_PIC020_USER_DEF     = 0x201D,   /* set users' parameters             */
    TOUVAR_PIC020_DISABLE_HEAT = 0x201E,   /* disable all heating, cool down    */
    TOUVAR_PIC020_IN_OUT_MAT   = 0x201F,   /* in/out material                   */
    TOUVAR_PIC021_IN_MAT       = 0x2021,   /* in material                       */
    TOUVAR_PIC021_OUT_MAT      = 0x2022,   /* out material                      */
    TOUVAR_PIC023_OUTMAT_CONF  = 0x2023,   /* out material confirm button       */
    TOUVAR_PIC024_HOTEND_FAN   = 0x2024,   /* set status of hotend fan          */
    TOUVAR_PIC024_BOX_FAN      = 0x2025,   /* set status of box fan             */
    TOUVAR_PIC025_BED_CALI     = 0x202A,   /* bed calibration                   */
    TOUVAR_PIC025_AXIS_MOVE    = 0x202B,   /* X/Y/Z axis move function          */
    TOUVAR_PIC027_BEDCALI_UP   = 0x202C,   /* bed calibration, ZAxis move up, step/0.05mm   */
    TOUVAR_PIC027_BEDCALI_DOWN = 0x202D,   /* bed calibration, ZAxis move down, step/0.05mm */
    TOUVAR_PIC027_BEDCALI_SAVE = 0x202E,   /* bed calibration, save Z offset                */
    TOUVAR_PIC_UNIT_1MM        = 0x202F,
    TOUVAR_PIC_UNIT_01MM       = 0x2030,
    TOUVAR_PIC_X_BACKWARD      = 0x2031,
    TOUVAR_PIC_X_FORWARD       = 0x2032,
    TOUVAR_PIC_Y_FORWARD       = 0x2033,
    TOUVAR_PIC_Y_BACKWARD      = 0x2034,
    TOUVAR_PIC_Z_UP            = 0x2035,
    TOUVAR_PIC_Z_DOWN          = 0x2036,
    TOUVAR_PIC_GO_HOME         = 0x2037,
    TOUVAR_PIC_UNIT_10MM       = 0x2038,
    TOUVAR_PIC031_LANG_SELECT  = 0x2039,   /* to select language                 */
    TOUVAR_PIC031_DEV_RESET    = 0x203A,   /* factory reset                      */
    TOUVAR_PIC032_LANG_TYPE    = 0x2040,   /* select language type               */
    TOUVAR_PIC033_CONFIRM      = 0x2041,   /* confirm to excute factory reset    */
    TOUVAR_PIC033_CANCEL       = 0x2042,   /* cancle to excute factory reset     */
    TOUVAR_PIC036_CONTINUE     = 0x2044,   /* continue to print when power off   */
    TOUVAR_PIC036_CANCEL       = 0x2045,   /* cancel to print when power off     */
    TOUVAR_PIC_START_PRINT     = 0x2046,   /* start to print file selected       */
    TOUVAR_PIC039_CONFIRM      = 0x2047,   /* confirm to load material           */
    TOUVAR_PIC039_STOPPRINT    = 0x2048,   /* stop printing                      */
    TOUVAR_PIC040_CONTIPRINT   = 0x2049,   /* continue printing                  */
    TOUVAR_PIC040_STOPPRINT    = 0x204A,   /* stop printing                      */
    TOUVAR_PIC024_SAVE_SELECT  = 0x204B,   /* save parameters and select the mode*/
    TOUVAR_PIC042_CONFIRM      = 0x204C,   /* confirm to stop heating(bed/hotend)*/
    TOUVAR_PIC042_CANCEL       = 0x204D,   /* cancel to stop heating(bed/hotend) */
	TOUVAR_PIC_PRINT_FEESRATE  = 0x2050,   /* set printing feedrate by user      */
    TOUVAR_PIC041_Z_OFFSET_UP  = 0x2070,   /* Z轴补偿-加                         */
    TOUVAR_PIC041_Z_OFFSET_DOWN= 0x2071,   /* Z轴补偿-减                         */
    TOUVAR_PIC041_AUX_LEVEL    = 0x2072,   /* 辅助调平                           */
    TOUVAR_PIC041_AUTO_LEVEL   = 0x2073,   /* 自动调平                           */
    TOUVAR_PIC041_LEVEL_ENABLE = 0x2074,   /* 调平使能                           */
    TOUVAR_PIC0XX_WIFI_RESET   = 0x2075,   /* WIFI复位                           */
    TOUVAR_PIC0XX_WIFI_ENABLE  = 0x2076,   /* WIFI使能                           */
	TOUVAR_PIC_USERDEF_HOTEND  = 0x3013,   /* set hotend temperature by user     */
    TOUVAR_PIC_USERDEF_BED     = 0x3015,   /* set bed temperature by user        */
    TOUVAR_PIC_X_KBD_INPUT     = 0x301F,   /* special, get data from DWIN, the address must be the same with the data-variable */
    TOUVAR_PIC_Y_KBD_INPUT     = 0x3023,   /* special, get data from DWIN, the address must be the same with the data-variable */
    TOUVAR_PIC_Z_KBD_INPUT     = 0x3027,   /* special, get data from DWIN, the address must be the same with the data-variable */
    
}AutoUITouVarAddr_t;

/**
 * type of language
 */
typedef enum
{
    AUTOUI_LANGUAGE_CH   = 0,              /* Chinese    */
    AUTOUI_LANGUAGE_EN   = 1,              /* English    */
    AUTOUI_LANGUAGE_SP   = 2,              /* Spanish    */
    AUTOUI_LANGUAGE_GE   = 3,              /* German     */
    AUTOUI_LANGUAGE_FR   = 4,              /* French     */
    AUTOUI_LANGUAGE_RU   = 5,              /* Russian    */
    AUTOUI_LANGUAGE_PO   = 6,              /* Portuguese */
    AUTOUI_LANGUAGE_IT   = 7,              /* Italian    */
    AUTOUI_LANGUAGE_TU   = 8,              /* Turkish    */
    AUTOUI_LANGUAGE_NUM
}AutoUILanguage_t;

typedef enum
{
    AUTOUI_LEVEL_STU_FALSE = 0,              /* Chinese    */
    AUTOUI_LEVEL_STU_TRUE  = 1,              /* English    */
    AUTOUI_LEVEL_NUM
}AutoUILevelStu_t;

/**
 * type of device status
 */
typedef enum 
{
    DEVSTA_INIT          = 0,              /* initialization            */
    DEVSTA_STARTUP_FIR   = 1,              /* startup first             */
    DEVSTA_IDLE          = 2,              /* idle                      */
    DEVSTA_HEATING       = 3,              /* heating(hotbed/hotend)    */
    DEVSTA_IN_OUT_MAT    = 4,              /* In and out materials      */
    DEVSTA_PRINTING      = 5,              /* printing                  */
    DEVSTA_PRINT_PAUSE   = 6,              /* printing is paused        */
    DEVSTA_BED_CALI      = 7,              /* bed calibration status    */
    DEVSTA_ERROR         = 8,              /* device error              */
    DEVSTA_NUM
}AutoUIDevStatus_t;

/**
 * background picture IDs
 */
typedef enum 
{
    AUTOUI_STARTING      = 0,              /* starting page              */
    AUTOUI_BOOTGUIDE_01  = 1,              /* boot guide page 1          */
    AUTOUI_BOOTGUIDE_02  = 2,              /* boot guide page 2          */
    AUTOUI_BOOTGUIDE_03  = 3,              /* boot guide page 3          */
    AUTOUI_BOOTGUIDE_04  = 4,              /* boot guide page 4          */
    AUTOUI_BOOTGUIDE_05  = 5,              /* boot guide page 5          */
    AUTOUI_BOOTGUIDE_06  = 6,              /* boot guide page 6          */
    AUTOUI_BOOTGUIDE_07  = 7,              /* boot guide page 7          */
    /* main widnow */
    AUTOUI_MAIN_WINDOW   = 8,              /* main window                */
    /* print file branch */
    AUTOUI_FILESELECT_01 = 9,              /* file select window 1       */
    AUTOUI_FILESELECT_02 = 10,             /* file select window 2       */
    AUTOUI_FILESELECT_03 = 11,             /* file select window 3       */
    AUTOUI_FILESELECT_04 = 12,             /* file select window 4       */
    AUTOUI_FILESELECT_05 = 13,             /* file select window 5       */
    AUTOUI_PRINTING      = 14,             /* printing page              */
    AUTOUI_PRINTFINISHED = 15,             /* print finished page        */
    AUTOUI_PRINTADJUST   = 16,             /* print adjust page          */
    AUTOUI_PRINTSTOPPW   = 17,             /* print stop popup page      */
    AUTOUI_PRINTPAUSE    = 18,             /* print pause page           */
    AUTOUI_PRINTDOOROPEN = 19,             /* print pause when door open */
    /* print mode branch */
    AUTOUI_PRINTMODE     = 20,             /* print mode page            */
    AUTOUI_INOUTMAT      = 21,             /* in/out material            */
    AUTOUI_OUTMAT_01     = 22,             /* out material page 1        */
    AUTOUI_OUTMAT_02     = 23,             /* out material page 2        */
    AUTOUI_MODEUSERDEF   = 24,             /* print mode user define page*/
    /* print settings branch */
    AUTOUI_PRINTSETTING  = 25,             /* print setting page         */
    AUTOUI_GOINGHOME     = 26,             /* going home tips page       */
    AUTOUI_BED_CALI      = 27,             /* bed calibartion page       */
    AUTOUI_AXISCONTR_10  = 28,             /* axis control page, 10mm/step    */
    AUTOUI_AXISCONTR_1   = 29,             /* axis control page, 1mm/step     */
    AUTOUI_AXISCONTR_01  = 30,             /* axis control page, 0.1mm/step   */
    /* device information branch */
    AUTOUI_DEVINFO       = 31,             /* device information page    */
    AUTOUI_LANGSELECT    = 32,             /* language select page       */
    AUTOUI_FACTORRESETPW = 33,             /* factor reset popup page    */
    /* others */
    AUTOUI_ERRORPW       = 34,             /* error popup page           */
    AUTOUI_ERRORTIPS     = 35,             /* error tips page            */
    AUTOUI_INTERCONTPW   = 36,             /* power off then continue printing popup page */
    AUTOUI_KEYBOARD      = 37,             /* keyboard page              */
    AUTOUI_KEYBOARDBACK  = 38,             /* keyboard background page   */

    /* add */
    AUTOUI_LACKMATPW     = 39,             /* popup window: lack of material  */
    AUTOUI_LOADMATPW     = 40,             /* popup window: material already  */
    AUTOUI_BUTBACKGROUND = 41,             /* button push down background     */
	AUTOUI_CLOSEHEATPW   = 42,             /* popup window: close heat        */
    AUTOUI_HEATING       = 43,             /* heating before print            */
    /* 自动调平 */
    AUTOUI_LEVELINGMODE  = 44,             /* 调平模式选择界面            */
    AUTOUI_AUXLEVELING   = 45,             /* 辅助调平界面               */
    AUTOUI_AUTOLEVELING  = 46,             /* 自动调平中界面             */
    AUTOUI_PAGENUM
}AutoUIPictureID_t;

/**
 * status of going home
 */
typedef enum 
{
    GO_HOME_IDLE         = 0,              /* idle status          */
    GO_HOME_DOING        = 1,              /* it's going home      */
    GO_HOME_DONE         = 2,              /* it has gone home     */
}AutoUIGoHomeSta_t;

/**
 * axis-move type
 */
typedef enum 
{
    AXIS_MOVE_RELA       = 0,              /* relative motion      */
    AXIS_MOVE_ABSO       = 1,              /* absolute motion      */
}AutoUIAxisMoveType_t;

/**
 * axis-move step unit
 */
typedef enum 
{
    STEP_UNIT_01MM       = 1,            /* move 0.1mm(*10) one step              */
    STEP_UNIT_1MM        = 10,           /* move 1mm(*10) one step                */
    STEP_UNIT_10MM       = 100,          /* move 10mm(*10) one step               */
    
    STEP_UNIT_TIMES      = 10,           /* value is 10 times than its real value */
}AutoUIAxisStepUnit_t;

/**
 * print mode type
 */
typedef enum 
{
    PRINT_MODE_INVAILD   = 0,            /* invalid mode     */
    PRINT_MODE_PLA       = 1,            /* PLA mode         */
    PRINT_MODE_ABS       = 2,            /* ABS mode         */
    PRINT_MODE_USERDEF   = 3,            /* user define mode */
}AutoUIPrintModeType_t;

#pragma pack(1)
/**
 * map touch-variable-address to touch-variable-function
 */
typedef void (*AutoUITouVarFunc)(void);
typedef struct 
{
    AutoUITouVarAddr_t   touchVarAddr;     /* DWIN touch-variables address         */
    AutoUITouVarFunc     touchVarFunc;     /* function to response touch-variables */
}AutoUITouVarResponse_t;
#pragma pack()
/**
 * print mode parameters
 */
typedef struct
{
    uint16_t             pmpHotendTemp;    /* default hotend temperature in the print mode */
    uint16_t             pmpBedTemp;       /* default bed temperature in the print mode    */
    bool                 pmpHotendFanFlag; /* if enable hotend fan or not                  */
    bool                 pmpBoxFanFlag;    /* if enable box fan or not                     */
}AutoUIPrintModeParas_t;

/**
 * wifi控制部分
 */
typedef struct
{
    __uint8_t            wifiState;      /* wifi状态          */
    __uint8_t            resetWifiCnt;   /* wifi复位输出完成  */
}AutoUIWifiCtrl_t;
#define WIFI_RESET_OUTPUT_COUNT     6    /* wifi复位输出计数 */
// wifi状态
enum {
    WIFI_ENABLE = 0,
    WIFI_DISABLE,
    WIFI_RESET,
};

/* Z轴补偿设置部分 */
typedef struct
{
    float               zlast_zoffset;
    float               zprobe_zoffset;
    __uint8_t           saveFlag;       /* 保存标志          */
    __uint8_t           saveParmCnt;    /* 保存计数          */
}AutoUIZOffsetCtrl_t;
#define Z_OFFSET_SAVE_COUNT     3       /* z轴补偿延时保存计数 */

/**
 * class of Automatic-style-UI module
 */
class LcdAutoUIStruct_t
{
    private:
        /**
         * current device status 
         */
        AutoUIDevStatus_t devStatus;
        /**
         * status of going home
         */
        AutoUIGoHomeSta_t goHomeSta;
        /**
         * axis-move step unit
         */
        float axisStepUnit;
        /**
         * true: have gone home before, false:have not gone home
         */
        bool haveGoneHomeBeforeFlag;
        /**
         * record total printing time
         */
        float printingTimeTotal;
        /**
         * 断电续打标志
         */
        bool powerLossRecoveryFlag;
        /**
         * 打印中拔出U盘标志
         */
        bool pullOutUDiskWhenPrintFlag;

    public:
        /**
         * flow step count
         */
        struct
        {
            uint8_t fscStartupFir;
            uint8_t fscIdle;
            uint8_t fscHeating;
            uint8_t fscInOutMat;
            uint8_t fscPrinting;
            uint8_t fscPrintPause;
            uint8_t fscBedCali;
            uint8_t fscError;
        }flowStepCnt;
        /**
         * enable switches
         */
        struct
        {
            bool swiBoxFan;
            bool swiBoxLed;
            bool swiWifiLed;
            bool swiDoorPause;
        }enableSwitches;
        /**
         * pause status records
         */
        struct
        {
            int tempHotend;
            int tempBed;
            xyze_pos_t posPauseBefore;
        }pauseStaRecord;
        /**
         * event priority flags
         */
        struct
        {
            bool epfStopPrint;
        }eventPriFlags;
		/**
         * hotend/bed get to the target temperature or not
         */
        struct
        {
            bool hotendHeat;               /* true:hotend has got to the target temperature, false:heating */
            bool bedHeat;                  /* true:bed has got to the target temperature, false:heating */
        }preheatFinishFlags;
        struct 
        {   
            bool cltSwi;
            uint32_t cltStartTime;
            uint32_t cltHowLongTime;
        }cloHeaTmr;
        /**
         * z轴坐标偏移：使用bltouch探测原点和使用限位开关探测原点的坐标存在偏移，该值用来补偿此偏移
         */
        float  zCoordinateOffset;
        /**
         * 是否正在自动调平
         */
        float  isBedLeveling;
        /**
         * current language that device display now
         */
        AutoUILanguage_t curLanguage;
        /**
         * 第一次上电标志（保存值非0xA5为第一次上电）
         */
        uint32_t startupFirstTimeVal;
        /**
         * status of going home
         */
        AutoUILevelStu_t autoLevelStatus;
        /**
         * 总运行时间
         */
        uint32_t TotalRuningTime;
        /**
         * 'DEVSTA_PRINT_PAUSE' timer count
         */
        uint32_t printPauseTmrMs;
        /**
         * picture ID that display currently
         */
        AutoUIPictureID_t curPicID;
        /**
         * picture ID that display last
         */
        AutoUIPictureID_t lastPicID;
        /**
         * print mode parameters
         */
        AutoUIPrintModeParas_t printModeParas;
        /**
         * print mode type
         */
        AutoUIPrintModeType_t printModeType;
        /**
         * wifi结构体定义
         */
        AutoUIWifiCtrl_t wifiCtrl;
        /**
         * z轴补偿结构体定义
         */
        AutoUIZOffsetCtrl_t zOffsetVtrl;
        /**
        * true:startup for first time, false:other situation
        */
        bool startupFirstTimeFlag;
        /**
         * true:feed/return material finished, false:other situation
         */
        bool feedFinishedFlag;
        /**
         * true:print has finished, false:other situation
         */
        bool printFinishFlag;
        /**
         * true:bed calibration finished, false:other situation
         */
        bool bedCaliFinishedFlag;
        /**
         * in or out material flag
         * true: in material, false: out material
         */
        bool inOutMatFlag;
        /**
         * mat runout at printing or not
         * true:event(mat runout at printing) happen, false:other situation
         */
        bool matRunoutAtPrintingFlag;
        /**
         * last record of device status
         */
        AutoUIDevStatus_t devStatusLastRecord;
        /**
         * percent of sd card print 
         */
        uint8_t percentDoneRecord;
        /**
         * point count that calibrate currentlly
         */
        uint8_t pointCntCaliCur;
        /**
         * record the ID of file selected
         * VAULE_INVALIDE: no file selected, other value: mean the ID of file selected
         */
        uint16_t gcodeFileSelectedCur;
        /**
         * record printing time once print
         */
        float printingTimeOnce;


        /**
         * constructors
         */
        LcdAutoUIStruct_t();
        /**
         * set StartupFirstTimeFlag
         */
        void SetStartupFirstTimeFlag(bool _flag);
        /**
         * get StartupFirstTimeFlag
         */
        bool GetStartupFirstTimeFlag(void);
        /**
         * get current language that record in EEPROM
         */
        void GetCurLang(void);
        /**
         * set current language and save in EEPROM
         */
        void SetSaveCurLang(AutoUILanguage_t _language);
        /**
         * 复位语言
         */
        void ResetCurLang(void);
        /**
         * 检查机器是否是第一期启动
         */
        void CheckStartFirstTime(void);
        /**
         * 复位机器第一次启动标志值
         */
        void ResetStartFirstTimeVal(void);
        /**
         * 从eeprom获取调平状态
         */
        void GetCurLevelStatusFromEEPROM(void);
        /**
         * 保存调平状态到eeprom
         */
        void SetSaveLevelStatus(AutoUILevelStu_t _status);
        /**
         * 获取调平状态
         */
        AutoUILevelStu_t GetLevelStatus(void);
        /**
         * 复位自动调平状态
         */
        void ResetLevelStatus(void);
        /**
         * 复位wifi状态
         */
        void ResetWifiStatus(void);
        /**
         * 获取两个坐标（z下限位和bltouch建立的坐标系）的差值
         */
        float GetzCoordinateOffset(void);
        /**
         * 设置两个坐标（z下限位和bltouch建立的坐标系）的差值
         */
        void SetzCoordinateOffset(float _offset);
        /**
         * 复位两个坐标（z下限位和bltouch建立的坐标系）的差值
         */
        void ResetzCoordinateOffsetVal(void);
        /**
         * set status of going home
         */
        void SetStaGoingHome(AutoUIGoHomeSta_t _sta);
        /**
         * get status of going home
         */
        AutoUIGoHomeSta_t GetStaGoingHome(void);
        /**
         * set flag 'haveGoneHomeBeforeFlag'
         */
        void SetHaGoHoBeFlag(bool _flag);
        /**
         * get flag 'haveGoneHomeBeforeFlag'
         */
        bool GetHaGoHoBeFlag(void);
        /**
         * set flag 'powerLossRecoveryFlag'
         */
        void SetPowerLossFlag(bool _flag);
        /**
         * get flag 'powerLossRecoveryFlag'
         */
        bool GetPowerLossFlag(void);
        /**
         * set flag 'pullOutUDiskWhenPrintFlag'
         */
        void SetPullOutUDiskFlag(bool _flag);
        /**
         * get flag 'pullOutUDiskWhenPrintFlag'
         */
        bool GetPullOutUDiskFlag(void);
		/**
		* set flag 'printFinishFlag'
         */
        void SetPrintFinishFlag(bool _flag);
        /**
         * get flag 'printFinishFlag'
         */
        bool GetPrintFinishFlag(void);
        /**
         * set current step of flow
         */
        void SetFlowStep(uint8_t* _flowCntType, uint8_t _stepVal);
        /**
         * set axis move step unit
         */
        void SetAxisStepUnit(AutoUIAxisStepUnit_t _uint);
        /**
         * get axis move step unit
         */
        float GetAxisStepUnit(void);
        /**
         * switch background picture
         */
        void SwitchBackgroundPic(AutoUIPictureID_t _picId);
        /**
         * switch icon
         */
        void SwitchIcon(int _iconId, unsigned long _iconAdress);
        /**
        * display data
        */
        void DisplayData(int _data, unsigned long _dataAdress);
        /**
        * display text
        */
        void DisplayText(char* _str, unsigned long _dataAdress);
        /**
         * enable/disable dynamic icon
         */
        void SetStaDynamicIcon(bool _en, unsigned long _iconAdress);
        /**
         * refresh current language that device display
         */
        void RefreshCurLanguage(void);
        /**
         * refresh data that display currentlly
         */
        void RefreshCurDisplayData(void);
        /**
         * refresh icon that display currentlly
         */
        void RefreshCurDisplayIcon(void);
        /**
         * refresh current total printing time 
         */
        void RefreshPrintTimeTotal(void);
        /**
         * reset current total printing time 
         */
        void ResetPrintTimeTotal(void);
        /**
         * 上电刷新调平数据
         */
        void RefreshCurLevelData(void);
        /**
         * set current total printing time
         */
        void SetPrintTimeTotal(float _totalTime);
        /**
         * get current total printing time
         */
        float GetPrintTimeTotal(void);
        /**
         * power on progress bar
         */
        void DevicePowerOnProgressBar(void);
        /**
         * SD card update
         */
        void SDCardUpdate(void);
        /**
        * change device status
        */
        void AutoUIToStatus(AutoUIDevStatus_t _sta);
        /**
         * get current device status
         */
        AutoUIDevStatus_t AutoUIGetStatus(void);
        /**
         * receive data handle
         */
        void AutoUIRecDataHandle(void);
        /**
         * 定时处理函数
         */
        void AutoUITimerUpdate(void);
        /**
         * response to DWIN touch
         */
        void AutoUIResponseToDWIN(void);
        /**
         * AutoUI initialization
         */
        void AutoUIInit(void);
        /**
         * flow of startup for first time
         */
        void AutoUIStartupFirstTimeFlow(void);
        /**
         * flow of idle status
         */
        void AutoUIIdleFlow(void);
        /**
         * flow of heating status
         */
        void AutoUIHeatFlow(void);
        /**
         * flow of in-out-material
         */
        void AutoUIInOutMatFlow(void);
        /**
         * flow of printing
         */
        void AutoUIPrintingFlow(void);
        /**
         * flow of print-pause
         */
        void AutoUIPrintPauseFlow(void);
        /**
         * flow of bed calibration
         */
        void AutoUIBedCaliFlow(void);
        /**
         * 显示调平进度
        */
        void ShowLevelingProgress(xy_int8_t meshCount);
        /**
         * 自动调平完成处理
        */
        void LevelingCompleted(void);
        /**
         * AutoUI main process
         */
		/**
         * get current print-mode
         */
        AutoUIPrintModeType_t GetCurPrintMode(void);
		
        void AutoUIMainProcess(void);
        
};

/* global variable of the Automatic-style-UI module */
extern LcdAutoUIStruct_t gLcdSermoonV2UI;
#endif/* __LCDAUTOUI_H */
