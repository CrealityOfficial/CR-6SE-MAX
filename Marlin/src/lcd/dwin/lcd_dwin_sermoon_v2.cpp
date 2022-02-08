/*
* @Author: 103066
* @Date:   2021-05-27 14:42:08
* @Last Modified by:   103066
* @Last Modified time: 2021-06-16 10:09:21
*/
#include <stdio.h>
#include <arduino.h>
#include <wstring.h>
// #include <libmaple/usart.h>
#include "lcd_dwin_sermoon_v2.h"
#include "dwin.h"
#include "../../inc/MarlinConfig.h"
#include "../../../Version.h"
#include "../../MarlinCore.h"
#include "../../sd/cardreader.h"
#include "../../module/temperature.h"
#include "../../module/planner.h"
#include "../../module/stepper.h"
// #include "../../module/configuration_store.h"
#include "../../module/printcounter.h"
#include "../../module/probe.h"
#include "../../feature/babystep.h"
#if ENABLED(POWER_LOSS_RECOVERY)
  #include "../../feature/powerloss.h"
#endif
#include "../../gcode/gcode.h"
// #include "../../feature/bedlevel/mbl/mesh_bed_leveling.h"
#include "../../feature/bedlevel/bedlevel.h"
#include "../../libs/duration_t.h"
#include "../../../Configuration.h"
#include "../../module/settings.h"
#ifdef USB_FLASH_DRIVE_SUPPORT
    #include "../../sd/usb_flashdrive/Sd2Card_FlashDrive.h"
#endif
/* global variable of the Automatic-style-UI module */
LcdAutoUIStruct_t gLcdSermoonV2UI;

/* touch-response functions */
static void TouVarConfirmFuncPic001(void);
static void TouVarConfirmFuncPic004(void);
static void TouVarConfirmFuncPic005(void);
static void TouVarConfirmFuncPic006(void);
static void TouVarPrintFileFuncPic008(void);
static void TouVarPrintModeFuncPic008(void);
static void TouVarPrintSetFuncPic008(void);
static void TouVarDevInfoFuncPic008(void);
static void TouVarHotendTempFuncPic008(void);
static void TouVarBedTempFuncPic008(void);
static void TouVarReturn(void);
static void TouVarFileSelect(void);
static void TouVarFileNextPage(void);
static void TouVarFileLastPage(void);
static void TouVarPrintSetPic014(void);
static void TouVarPrintPausePic014(void);
static void TouVarPrintStopPic014(void);
static void TouVarPrintFinishPic015(void);
static void TouVarBoxFanPic016(void);
static void TouVarBoxLedPic016(void);
static void TouVarWifiLedPic016(void);
static void TouVarDoorPausePic016(void);
static void TouVarPrintStopConfirmPic017(void);
static void TouVarPrintStopCancelPic017(void);
static void TouVarPrintPauseRecoPic018(void);
static void TouVarPrintStopPic018(void);
static void TouVarPrintInOuMatPic018(void);
static void TouVarConfirmPrintPic019(void);
static void TouVarCancelPrintPic019(void);
static void TouVarPLASelectPic020(void);
static void TouVarABSSelectPic020(void);
static void TouVarUserDefPic020(void);
static void TouVarDisableHeatPic020(void);
static void TouVarInOutMatPic020(void);
static void TouVarInMatPic021(void);
static void TouVarOutMatPic021(void);
static void TouVarOutMatConfirmPic023(void);
static void TouVarSetHotendFanPic024(void);
static void TouVarSetBoxFanPic024(void);
static void TouVarBedCaliPic025(void);
static void TouVarAxisMovePic025(void);
static void TouVarStepUnitMM1(void);
static void TouVarStepUnitMM01(void);
static void TouVarXBackward(void);
static void TouVarXForward(void);
static void TouVarYForward(void);
static void TouVarYBackward(void);
static void TouVarZUp(void);
static void TouVarZDown(void);
static void TouVarGoHome(void);
static void TouVarStepUnitMM10(void);
static void TouVarLangSelectPic031(void);
static void TouVarDevResetPic031(void);
static void TouVarLangTypePic032(void);
static void TouVarConfirmResetPic033(void);
static void TouVarCancelResetPic033(void);
static void TouVarContinuePrintPic036(void);
static void TouVarCancelPrintPic036(void);
static void TouVarKeybrdInputX(void);
static void TouVarKeybrdInputY(void);
static void TouVarKeybrdInputZ(void);
static void TouVarBedCaliUpPic027(void);
static void TouVarBedCaliDownPic027(void);
static void TouVarBedCaliSavePic027(void);
static void TouVarStartPrint(void);
static void TouVarConfirmLoadMatPic039(void);
static void TouVarStopPrintPic039(void);
static void TouVarContinuePrintPic040(void);
static void TouVarStopPrintPic040(void);
static void TouVarZOffsetUpPic041(void);
static void TouVarZOffsetDownPic041(void);
static void TouVarAuxLevelPic041(void);
static void TouVarAutoLevelPic041(void);  
static void TouVarLevelEnablePic041(void);  
static void TouVarWifiReset(void);
static void TouVarWifiEnable(void);
static void TouVarFeedrateFunc(void);
      
// 文件界面 ===
typedef struct
{
    char filename[FILENAME_LENGTH];
    char longfilename[LONG_FILENAME_LENGTH];
    unsigned char month;
    unsigned char day;
    unsigned char hour;
    unsigned char min;
}PrintFile_InfoTypeDef;

AutoUITouVarResponse_t gAutoUITouVarResponseArray[TOUVAR_NUM] =
{
    { TOUVAR_PIC001_CONFIRM,            TouVarConfirmFuncPic001     },
    { TOUVAR_PIC004_CONFIRM,            TouVarConfirmFuncPic004     },
    { TOUVAR_PIC005_CONFIRM,            TouVarConfirmFuncPic005     },
    { TOUVAR_PIC006_CONFIRM,            TouVarConfirmFuncPic006     },
    { TOUVAR_PIC008_PRINTFILE,          TouVarPrintFileFuncPic008   },
    { TOUVAR_PIC008_PRINTMODE,          TouVarPrintModeFuncPic008   },
    { TOUVAR_PIC008_PRINTSET,           TouVarPrintSetFuncPic008    },
    { TOUVAR_PIC008_DEVINFO,            TouVarDevInfoFuncPic008     },
    { TOUVAR_PIC008_HOTENDTEMP,         TouVarHotendTempFuncPic008  },
    { TOUVAR_PIC008_BEDTEMP,            TouVarBedTempFuncPic008     },
    { TOUVAR_PIC_RETURN,                TouVarReturn                },
    { TOUVAR_PIC_FILE_SELECT,           TouVarFileSelect            },
    { TOUVAR_PIC_NEXT_PAGE,             TouVarFileNextPage          },
    { TOUVAR_PIC_LAST_PAGE,             TouVarFileLastPage          },
    { TOUVAR_PIC014_PRINT_SET,          TouVarPrintSetPic014        },
    { TOUVAR_PIC014_PRINT_PAUSE,        TouVarPrintPausePic014      },
    { TOUVAR_PIC014_PRINT_STOP,         TouVarPrintStopPic014       },
    { TOUVAR_PIC015_FINISH,             TouVarPrintFinishPic015     },
    { TOUVAR_PIC016_BOX_FAN,            TouVarBoxFanPic016          },
    { TOUVAR_PIC016_BOX_LED,            TouVarBoxLedPic016          },
    { TOUVAR_PIC016_WIFI_LED,           TouVarWifiLedPic016         },
    { TOUVAR_PIC016_DOOR_PAUSE,         TouVarDoorPausePic016       },
    { TOUVAR_PIC017_CONFIRM,            TouVarPrintStopConfirmPic017},
    { TOUVAR_PIC017_CANCEL,             TouVarPrintStopCancelPic017 },
    { TOUVAR_PIC018_CONTINUE,           TouVarPrintPauseRecoPic018  },
    { TOUVAR_PIC018_STOP,               TouVarPrintStopPic018       },
    { TOUVAR_PIC018_IN_OUT_MAT,         TouVarPrintInOuMatPic018    },
    { TOUVAR_PIC019_CONFIRM,            TouVarConfirmPrintPic019    },
    { TOUVAR_PIC019_CANCEL,             TouVarCancelPrintPic019     },
    { TOUVAR_PIC020_PLA_SELECT,         TouVarPLASelectPic020       },
    { TOUVAR_PIC020_ABS_SELECT,         TouVarABSSelectPic020       },
    { TOUVAR_PIC020_USER_DEF,           TouVarUserDefPic020         },
    { TOUVAR_PIC020_DISABLE_HEAT,       TouVarDisableHeatPic020     },
    { TOUVAR_PIC020_IN_OUT_MAT,         TouVarInOutMatPic020        },
    { TOUVAR_PIC021_IN_MAT,             TouVarInMatPic021           },
    { TOUVAR_PIC021_OUT_MAT,            TouVarOutMatPic021          },
    { TOUVAR_PIC023_OUTMAT_CONF,        TouVarOutMatConfirmPic023   },
    { TOUVAR_PIC024_HOTEND_FAN,         TouVarSetHotendFanPic024    },
    { TOUVAR_PIC024_BOX_FAN,            TouVarSetBoxFanPic024       },
    { TOUVAR_PIC025_BED_CALI,           TouVarBedCaliPic025         },
    { TOUVAR_PIC025_AXIS_MOVE,          TouVarAxisMovePic025        },
    { TOUVAR_PIC027_BEDCALI_UP,         TouVarBedCaliUpPic027       },
    { TOUVAR_PIC027_BEDCALI_DOWN,       TouVarBedCaliDownPic027     },
    { TOUVAR_PIC027_BEDCALI_SAVE,       TouVarBedCaliSavePic027     },
    { TOUVAR_PIC_UNIT_1MM,              TouVarStepUnitMM1           },
    { TOUVAR_PIC_UNIT_01MM,             TouVarStepUnitMM01          },
    { TOUVAR_PIC_X_BACKWARD,            TouVarXBackward             },
    { TOUVAR_PIC_X_FORWARD,             TouVarXForward              },
    { TOUVAR_PIC_Y_FORWARD,             TouVarYForward              },
    { TOUVAR_PIC_Y_BACKWARD,            TouVarYBackward             },
    { TOUVAR_PIC_Z_UP,                  TouVarZUp                   },
    { TOUVAR_PIC_Z_DOWN,                TouVarZDown                 },
    { TOUVAR_PIC_GO_HOME,               TouVarGoHome                },
    { TOUVAR_PIC_UNIT_10MM,             TouVarStepUnitMM10          },
    { TOUVAR_PIC031_LANG_SELECT,        TouVarLangSelectPic031      },
    { TOUVAR_PIC031_DEV_RESET,          TouVarDevResetPic031        },
    { TOUVAR_PIC032_LANG_TYPE,          TouVarLangTypePic032        },
    { TOUVAR_PIC033_CONFIRM,            TouVarConfirmResetPic033    },
    { TOUVAR_PIC033_CANCEL,             TouVarCancelResetPic033     },
    { TOUVAR_PIC036_CONTINUE,           TouVarContinuePrintPic036   },
    { TOUVAR_PIC036_CANCEL,             TouVarCancelPrintPic036     },
    { TOUVAR_PIC_X_KBD_INPUT,           TouVarKeybrdInputX          },
    { TOUVAR_PIC_Y_KBD_INPUT,           TouVarKeybrdInputY          },
    { TOUVAR_PIC_Z_KBD_INPUT,           TouVarKeybrdInputZ          },
    { TOUVAR_PIC_START_PRINT,           TouVarStartPrint            },
    { TOUVAR_PIC039_CONFIRM,            TouVarConfirmLoadMatPic039  },
    { TOUVAR_PIC039_STOPPRINT,          TouVarStopPrintPic039       },
    { TOUVAR_PIC040_CONTIPRINT,         TouVarContinuePrintPic040   },
    { TOUVAR_PIC040_STOPPRINT,          TouVarStopPrintPic040       },
    { TOUVAR_PIC024_SAVE_SELECT,        0},
    { TOUVAR_PIC042_CONFIRM,            0},
    { TOUVAR_PIC042_CANCEL,             0},
    { TOUVAR_PIC_PRINT_FEESRATE,        TouVarFeedrateFunc          },
    { TOUVAR_PIC041_Z_OFFSET_UP,        TouVarZOffsetUpPic041       },
    { TOUVAR_PIC041_Z_OFFSET_DOWN,      TouVarZOffsetDownPic041     },
    { TOUVAR_PIC041_AUX_LEVEL,          TouVarAuxLevelPic041        },
    { TOUVAR_PIC041_AUTO_LEVEL,         TouVarAutoLevelPic041       },
    { TOUVAR_PIC041_LEVEL_ENABLE,       TouVarLevelEnablePic041     },
    { TOUVAR_PIC0XX_WIFI_RESET,         TouVarWifiReset             },
    { TOUVAR_PIC0XX_WIFI_ENABLE,        TouVarWifiEnable            },
};
/**
 * PLA print mode parameters' value
 */
const AutoUIPrintModeParas_t PLAMode =
{
    .pmpHotendTemp             = 200,
    .pmpBedTemp                = 60,
    .pmpHotendFanFlag          = true,
    .pmpBoxFanFlag             = true
};

/**
 * ABS print mode parameters' value
 */
const AutoUIPrintModeParas_t ABSMode =
{
    .pmpHotendTemp             = 240,
    .pmpBedTemp                = 80,
    .pmpHotendFanFlag          = false,
    .pmpBoxFanFlag             = false
};

/**
 * user-define print mode parameters' value
 */
AutoUIPrintModeParas_t userDefMode =
{
    .pmpHotendTemp             = 0,
    .pmpBedTemp                = 0,
    .pmpHotendFanFlag          = false,
    .pmpBoxFanFlag             = false
};

/**
 * user-define print mode parameters' value
 */
AutoUIWifiCtrl_t wifiCtrlInit =
{
    .wifiState                 = 0,
    .resetWifiCnt              = 0,
};

const float manual_feedrate_mm_m[] = { 50*60, 50*60, 4*60, 3*60 };

// 配置存储 ========================
#define AUDIO_VOLUME_MAX       15
#define HEAD_NUM_MAX           2
#define LCD_LUMINANCE_MAX      100
#define SYSTEM_LANGUAGE_MAX    7
#define Z_AXIS_OFFSET_MIN      (Z_PROBE_OFFSET_RANGE_MIN)
#define Z_AXIS_OFFSET_MAX      (Z_PROBE_OFFSET_RANGE_MAX)
typedef struct
{
    unsigned char System_Language;
    unsigned char Head_Num;
    unsigned char LCD_Luminance;
    unsigned char Audio_Volume;
    #if !HAS_BED_PROBE
        float         Z_Axis_Offset; // 若沒有探針，则使用自定义Z轴补偿
    #endif
}Config_StoreTypeDef;

Config_StoreTypeDef Config_StoreStruct = {0, 1, 100, 3};
#if ENABLED(EEPROM_SETTINGS)
#include "../../HAL/shared/eeprom_api.h"
#include "../../module/settings.h"
#if 0
#define EEPROM_OFFSET 100 // 需与Settings.cpp中的EEPROM_OFFSET一致
static void Eeprom_Write(uint16_t addr,uint8_t *buffer,uint16_t size){
    persistentStore.access_start();
    persistentStore.write_data(EEPROM_OFFSET + settings.datasize() + addr, buffer, size);
    persistentStore.access_finish();
}

static void Eeprom_Read(uint16_t addr,uint8_t *buffer,uint16_t size){
    persistentStore.access_start();
    persistentStore.read_data(EEPROM_OFFSET + settings.datasize() + addr, buffer, size);
    persistentStore.access_finish();
}
#endif
#endif
inline void DWIN_line_to_current(AxisEnum axis) 
{
    if (!planner.is_full())
    {
        planner.buffer_line(current_position, MMM_TO_MMS(manual_feedrate_mm_m[(int8_t)axis]), active_extruder);
    }
}

/***********************************************************************************************************************************
                                                          common functions
***********************************************************************************************************************************/
/**
 * [LcdAutoUISetHotendTemp :set hotend temperature]
 * @Author Creality
 * @Time   2021-06-01
 * @param  _targetTemp [value of target temperature]
 */
void LcdAutoUISetTempHotend(int16_t _targetTemp)
{
    thermalManager.temp_hotend[0].target = _targetTemp;
    thermalManager.setTargetHotend(thermalManager.temp_hotend[0].target, 0);
}

/**
 * [LcdAutoUISetTempHotendBlock :set hotend temperature and wait for it to be reached]
 * @Author Creality
 * @Time   2021-06-10
 * @param  _targetTemp [value of target temperature]
 */
void LcdAutoUISetTempHotendBlock(int16_t _targetTemp)
{
    // char lCmdBuf[20] = {0};

    /* set hotend target temperature */
    LcdAutoUISetTempHotend(_targetTemp);

    /* wait current hotend temperature to traget */
    thermalManager.wait_for_hotend(0, _targetTemp);
    // sprintf(lCmdBuf, "M109 S%d", _targetTemp);
    // queue.enqueue_one_now(lCmdBuf);
}

/**
 * [LcdAutoUIGetTempHotend :get hotend temperature]
 * @Author Creality
 * @Time   2021-06-02
 * @return            [value of hotend temperature]
 */
float LcdAutoUIGetTempHotend(void)
{
    return thermalManager.temp_hotend[0].celsius;
}

/**
 * [LcdAutoUIGetTarTempHotend :get target hotend temperature]
 * @Author Creality
 * @Time   2021-08-11
 * @return            [description]
 */
float LcdAutoUIGetTarTempHotend(void)
{
    return thermalManager.temp_hotend[0].target;
}

/**
 * [LcdAutoUISetTempBed :set bed temperature]
 * @Author Creality
 * @Time   2021-06-01
 * @param  _targetTemp [value of target temperature]
 */
void LcdAutoUISetTempBed(int16_t _targetTemp)
{
    thermalManager.temp_bed.target = _targetTemp;
    thermalManager.setTargetBed(thermalManager.temp_bed.target);
}

/**
 * [LcdAutoUISetTempBedBlock :set bed temperature and wait for it to be reached]
 * @Author Creality
 * @Time   2021-06-10
 * @param  _targetTemp [value of target temperature]
 */
void LcdAutoUISetTempBedBlock(int16_t _targetTemp)
{
    // char lCmdBuf[20] = {0};

    /* set bed target temperature */
    LcdAutoUISetTempBed(_targetTemp);

    /* wait current bed temperature to traget */
    thermalManager.wait_for_bed(_targetTemp);
    // sprintf(lCmdBuf, "M190 S%d", _targetTemp);
    // queue.enqueue_one_now(lCmdBuf);
}

/**
 * [LcdAutoUISetTempBed :get bed temperature]
 * @Author Creality
 * @Time   2021-06-04
 * @return             [value of bed temperature]
 */
float LcdAutoUIGetTempBed(void)
{
    return thermalManager.temp_bed.celsius;
}

/**
 * [LcdAutoUIGetTarTempBed :get target bed temperature]
 * @Author Creality
 * @Time   2021-08-11
 * @return            [description]
 */
float LcdAutoUIGetTarTempBed(void)
{
    return thermalManager.temp_bed.target;
}

/**
 * [LcdAutoUISetFeedrate :set printing feedrate]
 * @Author Creality
 * @Time   2021-08-11
 * @return            [description]
 */
void LcdAutoUISetFeedrate(int16_t _feedrate)
{
    feedrate_percentage = _feedrate;

    //这两个备份值也同步赋值，使得在“执行G28期间修改速率不生效”问题解决
    saved_feedrate_mm_s = _feedrate;
    saved_feedrate_percentage = _feedrate;
    /* updata printting feedate */
    gLcdSermoonV2UI.DisplayData(feedrate_percentage, DATAVAR_ADDR_FEEDRARE);
}

/**
 * [LcdAutoUIMoveX :X-Axis moving control]
 * @Author Creality
 * @Time   2021-06-07
 * @param  _distance  [distance that need to move or position that need to arrive]
 * @param  _moveType  [moving type]
 */
void LcdAutoUIMoveX(float _distance, AutoUIAxisMoveType_t _moveType)
{
    float lDistance = _distance > X_BED_SIZE ? X_BED_SIZE : _distance;

    /* if device have not gone home before, and absolute-motion is selected. Do not allow to move axis */
    // if((_moveType == AXIS_MOVE_ABSO) && (!gLcdSermoonV2UI.GetHaGoHoBeFlag()))
    //     return;

    do
    {
        if(_moveType == AXIS_MOVE_RELA)
            current_position[X_AXIS] += lDistance;
        else if(_moveType == AXIS_MOVE_ABSO)
            current_position[X_AXIS] = lDistance;
        else
            break;

        //RTS_line_to_current(X_AXIS);
        DWIN_line_to_current(X_AXIS);
    }while(0);
}

/**
 * [LcdAutoUIMoveY :Y-Axis moving control]
 * @Author Creality
 * @Time   2021-06-07
 * @param  _distance  [distance that need to move or position that need to arrive]
 * @param  _moveType  [moving type]
 */
void LcdAutoUIMoveY(float _distance, AutoUIAxisMoveType_t _moveType)
{
    float lDistance = _distance > Y_BED_SIZE ? Y_BED_SIZE : _distance;

    /* if device have not gone home before, and absolute-motion is selected. Do not allow to move axis */
    // if((_moveType == AXIS_MOVE_ABSO) && (!gLcdSermoonV2UI.GetHaGoHoBeFlag()))
    //     return;

    do
    {
        if(_moveType == AXIS_MOVE_RELA)
            current_position[Y_AXIS] += lDistance;
        else if(_moveType == AXIS_MOVE_ABSO)
            current_position[Y_AXIS] = lDistance;
        else
            break;

        // RTS_line_to_current(Y_AXIS);
        DWIN_line_to_current(Y_AXIS);
    }while(0);
}

/**
 * [LcdAutoUIMoveXY :get to the given postion(x, y), block program running]
 * @Author Creality
 * @Time   2021-06-08
 * @param  _posX      [X coordinate]
 * @param  _posY      [Y coordinate]
 */
void LcdAutoUIMoveXYBlock(float _posX, float _posY)
{
    float lPosX = _posX > X_BED_SIZE ? X_BED_SIZE : _posX;
    float lPosY = _posY > Y_BED_SIZE ? Y_BED_SIZE : _posY;

    do_blocking_move_to_xy(lPosX, lPosY);
}

/**
 * [LcdAutoUIMoveXYCmd :get to the given postion(x, y) by inserting command]
 * @Author Creality
 * @Time   2021-07-13
 * @param  _posX      [X coordinate]
 * @param  _posY      [Y coordinate]
 */
void LcdAutoUIMoveXYCmd(float _posX, float _posY)
{
    char lCmdBuf[64];
    
    memset(lCmdBuf, 0, sizeof(lCmdBuf));
    sprintf(lCmdBuf, "%s%s%f%s%f%s", "G1 ", "X", _posX, " Y", _posY, " F2000");
    queue.enqueue_now_P(lCmdBuf);
}

/**
 * [LcdAutoUIMoveZ :Z-Axis moving control, not block program running]
 * @Author Creality
 * @Time   2021-06-07
 * @param  _distance  [distance that need to move or position that need to arrive]
 * @param  _moveType  [moving type]
 */
void LcdAutoUIMoveZ(float _distance, AutoUIAxisMoveType_t _moveType)
{
    float lDistance = _distance > Z_MAX_POS ? Z_MAX_POS : _distance;

    /* if device have not gone home before, and absolute-motion is selected. Do not allow to move axis */
    // if((_moveType == AXIS_MOVE_ABSO) && (!gLcdSermoonV2UI.GetHaGoHoBeFlag()))
    //     return;

    do
    {
        if(_moveType == AXIS_MOVE_RELA)
            current_position[Z_AXIS] += lDistance;
        else if(_moveType == AXIS_MOVE_ABSO)
            current_position[Z_AXIS] = lDistance;
        else
            break;

        // RTS_line_to_current(Z_AXIS);
        DWIN_line_to_current(Z_AXIS);
    }while(0);
}

/**
 * [LcdAutoUIMoveZBlock :get to the given postion(z), block program running]
 * @Author Creality
 * @Time   2021-06-08
 * @param  _posZ      [Z coordinate]
 */
void LcdAutoUIMoveZBlock(float _posZ)
{
    float lPosZ = _posZ > Z_MAX_POS ? Z_MAX_POS : _posZ;

    do_blocking_move_to_z(lPosZ);
}

/**
 * [LcdAutoUIMoveZCmd :get to the given postion(z) by inserting command]
 * @Author Creality
 * @Time   2021-07-13
 * @param  _posZ      [Z coordinate]
 */
void LcdAutoUIMoveZCmd(float _posZ)
{
    char lCmdBuf[32];
    
    memset(lCmdBuf, 0, sizeof(lCmdBuf));
    sprintf(lCmdBuf, "%s%s%f%s", "G1 ", "Z", _posZ, " F600");
    queue.enqueue_now_P(lCmdBuf);
}

/**
 * [LcdAutoUIMoveXYZBlock :get to the given postion(x, y, z) by inserting command]
 * @Author Creality
 * @Time   2021-07-20
 * @param  _posX      [X coordinate]
 * @param  _posY      [Y coordinate]
 * @param  _posZ      [Z coordinate]
 */
void LcdAutoUIMoveXYZBlock(float _posX, float _posY, float _posZ)
{
    xy_pos_t lPosXY;
    float lPosZ;

    lPosXY.x = _posX > X_BED_SIZE ? X_BED_SIZE : _posX;
    lPosXY.y = _posY > Y_BED_SIZE ? Y_BED_SIZE : _posY;
    lPosZ = _posZ > Z_MAX_POS ? Z_MAX_POS : _posZ;

    do_blocking_move_to_xy_z(lPosXY, lPosZ);
}

/**
 * [LcdAutoUIMoveE :E-Axis moving control, default: relative motion]
 * @Author Creality
 * @Time   2021-06-01
 * @param  _distance  [moving distance]
 * @param  _feedRate  [moving speed]
 */
void LcdAutoUIMoveE(float _distance, uint32_t _feedRate)
{
    current_position[E_AXIS] += _distance;
    line_to_current_position(feedRate_t(_feedRate));
}

/**
 * [LcdAutoUISetECmd :Set E-Axis current position by G-Code]
 * @Author Creality
 * @Time   2021-08-14
 * @param  _PosE      [E-Axis position that need to be set]
 */
void LcdAutoUISetECmd(float _PosE)
{
    char lCmdBuf[32];
    
    memset(lCmdBuf, 0, sizeof(lCmdBuf));
    sprintf(lCmdBuf, "%s%d", "G92 E", (int)(_PosE));
    queue.enqueue_now_P(lCmdBuf);
}

/**
 * [LcdAutoUIGetTimeMs :get current time]
 * @Author Creality
 * @Time   2021-06-04
 * @return            [current time(Ms)]
 */
uint32_t LcdAutoUIGetTimeMs(void)
{
    return millis();
}

/**
 * [GetUserDefModeParas :get user define mode parameters from EEPROM]
 * @Author Creality
 * @Time   2021-06-19
 */
void GetUserDefModeParas(void)
{
    // Eeprom_Read(FONT_EEPROM + EEPROM_ADDR_UDMP_OFFSET, (uint8_t*)&userDefMode, EEPROM_ADDR_UDMP_SIZE);
}

/**
 * [GetSDCardGcodeFileNum :get gcode file number that read from SD card]
 * @Author Creality
 * @Time   2021-06-06
 * @return            [number of gcode file]
 */
int GetSDCardGcodeFileNum(void)
{
    return CardRecbuf.Filesum;
}

/**
 * [IsExistPowerOffDurPrint :does there exist sitution that power off during printing]
 * @Author Creality
 * @Time   2021-06-19
 * @return            [true: exist, false: not exist]
 */
bool IsExistPowerOffDurPrint(void)
{
    // return recovery.info.recovery_flag;
    return false;
}

/**
 * [ClearSDCardGcodeFileRecord :clear record about SD card]
 * @Author Creality
 * @Time   2021-06-08
 */
void ClearSDCardGcodeFileRecord(void)
{
    memset(&CardRecbuf, 0, sizeof(CardRecbuf));

    gLcdSermoonV2UI.gcodeFileSelectedCur = VAULE_INVALIDE;
}

/**
 * [FileSelectBackground :display highlight background when file is selected]
 * @Author Creality
 * @Time   2021-06-06
 * @param  _fileSelected [ID of file selected]
 * @param  _bgStartAddr  [start address of background icon]
 */
uint16_t FileSelectBackground(uint16_t _fileSelectedID, uint16_t _bgStartAddr)
{
    uint16_t lRet = VAULE_INVALIDE;
    int lGcodeFileNum = GetSDCardGcodeFileNum() > GCODE_FILE_NUM_MAX ? GCODE_FILE_NUM_MAX : GetSDCardGcodeFileNum();

    for(int i=0; i<lGcodeFileNum; i++)
    {
        if(i == _fileSelectedID)
        {
            gLcdSermoonV2UI.SwitchIcon(SELECTED_YES, _bgStartAddr + i);
            lRet = i;
        }
        else
        {
            gLcdSermoonV2UI.SwitchIcon(SELECTED_NO, _bgStartAddr + i);
        }
    }

    return lRet;
}

/**
 * [ClearFileBackground :clear file selected highlight icon]
 * @Author Creality
 * @Time   2021-06-08
 */
void ClearFileBackground(void)
{
    for(int i=0; i<GCODE_FILE_NUM_MAX; i++)
        gLcdSermoonV2UI.SwitchIcon(SELECTED_NO, ICONVAR_ADDR_FILESELECT_BG00 + i);
}

/**
 * [IsExistMaterial :if there exist material for printing]
 * @Author Creality
 * @Time   2021-06-17
 * @return            [true: exist, false: not exist]
 */
bool IsExistMaterial(void)
{
    #ifdef ENABLE_MATERIAL_CHECK
        static uint32_t lMs = LcdAutoUIGetTimeMs();
        static uint32_t checkMatweialCnt = 0;
        if((LcdAutoUIGetTimeMs() - lMs) > 1000)
        {
            lMs = LcdAutoUIGetTimeMs();
            checkMatweialCnt ++;
        }
        
        if(0 == READ(CHECK_MATWEIAL)) /* Low Level : exist material */
        {
            checkMatweialCnt = 0;
            return true;
        }
        else if (checkMatweialCnt >= 2) /* High Level : not exist material */
            return false;
        else /* High Level : Waiting for confirmation */
            return true;
    #endif
}

/**
 * [IsDoorOpen :if door is open]
 * @Author Creality
 * @Time   2021-06-19
 * @return            [true: door open , false: door close]
 */
bool IsDoorOpen(void)
{
    /* High Level : door open */
    if(1 == READ(CHECK_DOOR_PIN))
        return true;
    /* Low Level : door close */
    else
        return false;
}

/**
 * [SetHotendFan :hotend fan control]
 * @Author Creality
 * @Time   2021-06-16
 * @param  _en        [true: turn on, false: turn off]
 */
void SetHotendFan(bool _en)
{
    /* turn on */
    if(_en)
        thermalManager.fan_speed[0] = 0xFF;
    /* turn off */
    else
        thermalManager.fan_speed[0] = 0;
}

/**
 * [SetBoxFan :box fan control]
 * @Author Creality
 * @Time   2021-06-16
 * @param  _en        [true: turn on, false: turn off]
 */
void SetBoxFan(bool _en)
{
    /* turn on */
     if(_en)
        digitalWrite(BOX_FAN_PIN, AUTOUI_ENABLE);
    /* turn off */
     else
        digitalWrite(BOX_FAN_PIN, AUTOUI_DISABLE);
}

/**
 * [SetBoxLed :box led control]
 * @Author Creality
 * @Time   2021-06-16
 * @param  _en        [true: turn on, false: turn off]
 */
void SetBoxLed(bool _en)
{
    /* turn on */
    if(_en)//OUT_WRITE
        digitalWrite(LED_CONTROL_PIN, AUTOUI_ENABLE);
    /* turn off */
    else
        digitalWrite(LED_CONTROL_PIN, AUTOUI_DISABLE);
}

/**
 * [SaveSwitchesStatus :save box-fan/box-led/wifi-led/door-pause function status in EEPROM]
 * @Author Creality
 * @Time   2021-07-12
 */
void SaveSwitchesStatus(void)
{
    uint8_t lSwiSta = 0;

    /* record box-fan status */
    if(gLcdSermoonV2UI.enableSwitches.swiBoxFan)
        lSwiSta = lSwiSta | 0x80;
    else
        lSwiSta = lSwiSta & 0x7F;

    /* record box-led status */
    if(gLcdSermoonV2UI.enableSwitches.swiBoxLed)
        lSwiSta = lSwiSta | 0x40;
    else
        lSwiSta = lSwiSta & 0xBF;

    /* record wifi-led status */
    if(gLcdSermoonV2UI.enableSwitches.swiWifiLed)
        lSwiSta = lSwiSta | 0x20;
    else
        lSwiSta = lSwiSta & 0xDF;

    /* record door-pause status */
    if(gLcdSermoonV2UI.enableSwitches.swiDoorPause)
        lSwiSta = lSwiSta | 0x10;
    else
        lSwiSta = lSwiSta & 0xEF;

    /* save to EEPROM */
    //BL24CXX::write(FONT_EEPROM + EEPROM_ADDR_BFLWD_OFFSET, &lSwiSta, EEPROM_ADDR_BFLWD_SIZE);
}

/**
 * [ReadSwitchesStatus :get box-fan/box-led/wifi-led/door-pause function status from EEPROM]
 * @Author Creality
 * @Time   2021-07-12
 */
void ReadSwitchesStatus(void)
{
    uint8_t lSwiSta = 0;

    /* read switches status from EEPROM */
    //BL24CXX::read(FONT_EEPROM + EEPROM_ADDR_BFLWD_OFFSET, &lSwiSta, EEPROM_ADDR_BFLWD_SIZE);

    /* for the first time to read status */
    if(lSwiSta == 0xFF)
        return;

    /* set box-fan status */
    if(lSwiSta & 0x80)
        SetBoxFan(true);
    else
        SetBoxFan(false);

    /* set box-led status */
    if(lSwiSta & 0x40)
        SetBoxLed(true);
    else
        SetBoxLed(false);

    /* set wifi-led status */
    if(lSwiSta & 0x20)
        gLcdSermoonV2UI.enableSwitches.swiWifiLed = true;
    else
        gLcdSermoonV2UI.enableSwitches.swiWifiLed = false;

    /* set door-pause status */
    if(lSwiSta & 0x10)
        gLcdSermoonV2UI.enableSwitches.swiDoorPause = true;
    else
        gLcdSermoonV2UI.enableSwitches.swiDoorPause = false;
}

/**
 * [ClearSwitchesStatus :clear box-fan/box-led/wifi-led/door-pause function status and save in EEPROM]
 * @Author Creality
 * @Time   2021-07-23
 */
void ResetSwitchesStatus(void)
{
    // uint8_t lSwiSta = 0;

    SetBoxFan(false);
    SetBoxLed(false);
    gLcdSermoonV2UI.enableSwitches.swiWifiLed = false;
    gLcdSermoonV2UI.enableSwitches.swiDoorPause = true;

    /* save to EEPROM */
    //BL24CXX::write(FONT_EEPROM + EEPROM_ADDR_BFLWD_OFFSET, &lSwiSta, EEPROM_ADDR_BFLWD_SIZE);
}

/**
 * [PrintParasSetByMode :set print parameters according to print mode]
 * @Author Creality
 * @Time   2021-06-16
 */
void PrintParasSetByMode(void)
{
    memset(&gLcdSermoonV2UI.printModeParas, 0, sizeof(AutoUIPrintModeParas_t));

    if(gLcdSermoonV2UI.printModeType == PRINT_MODE_INVAILD)
    {
        return;
    }
    /* PLA mode */
    if(gLcdSermoonV2UI.printModeType == PRINT_MODE_PLA)
    {
        memcpy(&gLcdSermoonV2UI.printModeParas, &PLAMode, sizeof(AutoUIPrintModeParas_t));
    }
    /* ABS mode */
    else if(gLcdSermoonV2UI.printModeType == PRINT_MODE_ABS)
    {
        memcpy(&gLcdSermoonV2UI.printModeParas, &ABSMode, sizeof(AutoUIPrintModeParas_t));
    }
    /* user define */
    #if 0
    else if(gLcdSermoonV2UI.printModeType == PRINT_MODE_USERDEF)
    {
        memcpy(&gLcdSermoonV2UI.printModeParas, &userDefMode, sizeof(AutoUIPrintModeParas_t));
    }
    #endif

    /* device control by mode parameters */
    if(gLcdSermoonV2UI.AutoUIGetStatus() == DEVSTA_HEATING)
    {
        LcdAutoUISetTempBedBlock(gLcdSermoonV2UI.printModeParas.pmpBedTemp);
    }
    else
    {
        /* if stop printing during 'DEVSTA_HEATING' status */
        wait_for_heatup = false;
        return;
    }
    if(gLcdSermoonV2UI.AutoUIGetStatus() == DEVSTA_HEATING)
    {
        LcdAutoUISetTempHotendBlock(gLcdSermoonV2UI.printModeParas.pmpHotendTemp);
    }
    else
    {
        /* if stop printing during 'DEVSTA_HEATING' status */
        wait_for_heatup = false;
        return;
    }
    SetHotendFan(gLcdSermoonV2UI.printModeParas.pmpHotendFanFlag);
    SetBoxFan(gLcdSermoonV2UI.printModeParas.pmpBoxFanFlag);

    gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_PRINTING);
    /* change device status to 'DEVSTA_PRINTING' */
    gLcdSermoonV2UI.AutoUIToStatus(DEVSTA_PRINTING);
    gLcdSermoonV2UI.SetStaGoingHome(GO_HOME_IDLE);
}

/**
 * [RefreshUserDefParasDispaly :refresh user define mode parameter and display on DIWN]
 * @Author Creality
 * @Time   2021-06-19
 */
void RefreshUserDefParas(void)
{
    /* get user define mode parameters from EEPROM */
    GetUserDefModeParas();

    /* refresh hotend and bed temperature */
    gLcdSermoonV2UI.DisplayData(userDefMode.pmpHotendTemp, DATAVAR_ADDR_USERDEF_HOTEND_TEMP);
    gLcdSermoonV2UI.DisplayData(userDefMode.pmpBedTemp, DATAVAR_ADDR_USERDEF_BED_TEMP);

    /* refresh hotend fan status */
    if(userDefMode.pmpHotendFanFlag)
        gLcdSermoonV2UI.SwitchIcon(AUTOUI_ENABLE, ICONVAR_ADDR_HOTEND_FAN_STA);
    else
       gLcdSermoonV2UI.SwitchIcon(AUTOUI_DISABLE, ICONVAR_ADDR_HOTEND_FAN_STA);

    /* refresh box fan status */
    if(userDefMode.pmpBoxFanFlag)
        gLcdSermoonV2UI.SwitchIcon(AUTOUI_ENABLE, ICONVAR_ADDR_BOX_FAN_STA);
    else
       gLcdSermoonV2UI.SwitchIcon(AUTOUI_DISABLE, ICONVAR_ADDR_BOX_FAN_STA);
}

/**
 * [RefreshDevInfo :refresh device information]
 * @Author Creality
 * @Time   2021-06-21
 */
void RefreshDevInfo(void)
{
    // /* hardware version */
    // gLcdSermoonV2UI.DisplayText((char*)HARDWAREVERSION, TEXTVAR_ADDR_HARDWARE_VER);
    // /* firmware version */
    // gLcdSermoonV2UI.DisplayText((char*)SOFTVERSION, TEXTVAR_ADDR_FIRMWARE_VER);
    // /* screen project version */
    // gLcdSermoonV2UI.DisplayText((char*)SCREENVERSION, TEXTVAR_ADDR_SCREEN_VER);
    // /* machine size */
    // gLcdSermoonV2UI.DisplayText((char*)MACHINE_SIZE, TEXTVAR_ADDR_PRINT_SIZE);
    // /* machine name */
    // gLcdSermoonV2UI.DisplayText((char*)MACHINE_NAME, TEXTVAR_ADDR_DEVICE_NAME);
    // /* official website */
    // if(gLcdSermoonV2UI.GetCurLanguage() == AUTOUI_LANGUAGE_CH)
    //     gLcdSermoonV2UI.DisplayText((char*)CORP_WEBSITE_C, TEXTVAR_ADDR_OFFICIAL_WEB);
    // else
    //     gLcdSermoonV2UI.DisplayText((char*)CORP_WEBSITE_E, TEXTVAR_ADDR_OFFICIAL_WEB);
}

/**
 * [RefreshAllTemperature :refresh device all temperature display]
 * @Author Creality
 * @Time   2021-06-09
 */
void RefreshAllTemperature(void)
{
    static int lTempRecoHotendCur = 0;
    static int lTempRecoHotendTar = 0;
    static int lTempRecoBedCur = 0;
    static int lTempRecoBedTar = 0;

    /* refresh current hotend temperature */
    if(lTempRecoHotendCur != LcdAutoUIGetTempHotend())
    {
        lTempRecoHotendCur = LcdAutoUIGetTempHotend();
        gLcdSermoonV2UI.DisplayData(lTempRecoHotendCur, DATAVAR_ADDR_HOTENDTEMP_CUR);
    }
    /* refresh target hotend temperature */
    if(lTempRecoHotendTar != thermalManager.degTargetHotend(0))
    {
        lTempRecoHotendTar = thermalManager.degTargetHotend(0);
        gLcdSermoonV2UI.DisplayData(lTempRecoHotendTar, DATAVAR_ADDR_HOTENDTEMP_GIVEN);
    }
    /* refresh current bed temperature */
    if(lTempRecoBedCur != LcdAutoUIGetTempBed())
    {
        lTempRecoBedCur = LcdAutoUIGetTempBed();
        gLcdSermoonV2UI.DisplayData(lTempRecoBedCur, DATAVAR_ADDR_BEDTEMP_CUR);
    }
    /* refresh target bed temperature */
    if(lTempRecoBedTar != thermalManager.degTargetBed())
    {
        lTempRecoBedTar = thermalManager.degTargetBed();
        gLcdSermoonV2UI.DisplayData(lTempRecoBedTar, DATAVAR_ADDR_BEDTEMP_GIVEN);
    }  
}

/**
 * [RefreshCurPrintProgress :refresh current printing progress when device is at 'DEVSTA_PRINTING']
 * @Author Creality
 * @Time   2021-06-11
 */
void RefreshCurPrintProgress(void)
{
    if(card.isPrinting() && gLcdSermoonV2UI.percentDoneRecord != card.percentDone())
    {
        gLcdSermoonV2UI.percentDoneRecord = card.percentDone();

        gLcdSermoonV2UI.SwitchIcon((int)gLcdSermoonV2UI.percentDoneRecord, ICONVAR_ADDR_PRINT_PROGRESS);
        gLcdSermoonV2UI.DisplayData((int)gLcdSermoonV2UI.percentDoneRecord, DATAVAR_ADDR_PRINT_PROGRESS);
    }
}

/**
 * [RefreshCurPrintProgress :refresh current printing progress when device is at 'DEVSTA_PRINTING']
 * @Author Creality
 * @Time   2021-06-11
 */
void RefreshCurPrintFeedrate(void)
{
    gLcdSermoonV2UI.DisplayData(feedrate_percentage, DATAVAR_ADDR_FEEDRARE);
}

/**
 * [RefreshOutMatReturnKey :Select whether to display the return key]
 * true: display return key
 * false : The return key is not displayed
 * @Author Creality
 * @Time   2021-06-11
 */
void RefreshOutMatReturnKey(bool _dispaly)
{
    gLcdSermoonV2UI.SetStaDynamicIcon(_dispaly, ICONVAR_ADDR_OUT_MAT_RETURN_KEY);
}

/**
 * [ClearCurPrintProgress :clear current printing progress]
 * @Author Creality
 * @Time   2021-06-15
 */
void ClearCurPrintProgress(void)
{
    gLcdSermoonV2UI.SwitchIcon(0, ICONVAR_ADDR_PRINT_PROGRESS);
    gLcdSermoonV2UI.DisplayData(0, DATAVAR_ADDR_PRINT_PROGRESS);
}

/**
 * [RefreshCurPrintTime :refresh current printing time(how long the gcode have printed)]
 * @Author Creality
 * @Time   2021-06-11
 */
void RefreshCurPrintTime(void)
{
    duration_t elapsed = print_job_timer.duration();
    //float lPrintTime = 0.0;

    gLcdSermoonV2UI.DisplayData(elapsed.value/3600, DATAVAR_ADDR_PRINT_TIME_H);
    gLcdSermoonV2UI.DisplayData((elapsed.value%3600)/60, DATAVAR_ADDR_PRINT_TIME_M);

    /* record the printing time once print */
    gLcdSermoonV2UI.printingTimeOnce = (float)elapsed.value/3600.0;
}

/**
 * [ClearCurPrintTime :clear current printing time]
 * @Author Creality
 * @Time   2021-06-15
 */
void ClearCurPrintTime(void)
{
    gLcdSermoonV2UI.DisplayData(0, DATAVAR_ADDR_PRINT_TIME_H);
    gLcdSermoonV2UI.DisplayData(0, DATAVAR_ADDR_PRINT_TIME_M);
}

/**
 * [RefreshCurPosDisplay :refresh current position that display on screen]
 * @Author Creality
 * @Time   2021-06-16
 */
void RefreshCurPosDisplay(void)
{
    static float lXPosRecord = 0;
    static float lYPosRecord = 0;
    static float lZPosRecord = 0;

    /* refresh current X position that display on screen */
    if(lXPosRecord != current_position.x)
    {
        lXPosRecord = current_position.x;
        gLcdSermoonV2UI.DisplayData(lXPosRecord * DWIN_REALVAL_TIMES, DATAVAR_ADDR_CURPOS_X);
    }
    /* refresh current Y position that display on screen */
    if(lYPosRecord != current_position.y)
    {
        lYPosRecord = current_position.y;
        gLcdSermoonV2UI.DisplayData(lYPosRecord * DWIN_REALVAL_TIMES, DATAVAR_ADDR_CURPOS_Y);
    }
    /* refresh current Z position that display on screen */
    if(lZPosRecord != current_position.z)
    {
        lZPosRecord = current_position.z;
        gLcdSermoonV2UI.DisplayData(lZPosRecord * DWIN_REALVAL_TIMES, DATAVAR_ADDR_CURPOS_Z);
    }
}

/**
 * [RefreshCurSwiIconStatus :refresh current icon status of enable switches]
 * @Author Creality
 * @Time   2021-06-18
 */
void RefreshCurSwiIconStatus(void)
{
    static bool lSwiBoxFanRecord    = false;
    static bool lSwiBoxLedRecord    = false;
    static bool lSwiWifiLedRecord   = false;
    static bool lSwiDoorPauseRecord = false;

    /* refresh box fan icon status */
    if((lSwiBoxFanRecord == false) && (gLcdSermoonV2UI.enableSwitches.swiBoxFan == true))
    {
        lSwiBoxFanRecord = true;
        gLcdSermoonV2UI.SwitchIcon(AUTOUI_ENABLE, ICONVAR_ADDR_BOX_FAN);
    }
    else if((lSwiBoxFanRecord == true) && (gLcdSermoonV2UI.enableSwitches.swiBoxFan == false))
    {
        lSwiBoxFanRecord = false;
        gLcdSermoonV2UI.SwitchIcon(AUTOUI_DISABLE, ICONVAR_ADDR_BOX_FAN);
    }

    /* refresh box led icon status */
    if((lSwiBoxLedRecord == false) && (gLcdSermoonV2UI.enableSwitches.swiBoxLed == true))
    {
        lSwiBoxLedRecord = true;
        gLcdSermoonV2UI.SwitchIcon(AUTOUI_ENABLE, ICONVAR_ADDR_BOX_LED);
    }
    else if((lSwiBoxLedRecord == true) && (gLcdSermoonV2UI.enableSwitches.swiBoxLed == false))
    {
        lSwiBoxLedRecord = false;
        gLcdSermoonV2UI.SwitchIcon(AUTOUI_DISABLE, ICONVAR_ADDR_BOX_LED);
    }

    /* refresh WIFI led icon status */
    if((lSwiWifiLedRecord == false) && (gLcdSermoonV2UI.enableSwitches.swiWifiLed == true))
    {
        lSwiWifiLedRecord = true;
        gLcdSermoonV2UI.SwitchIcon(AUTOUI_ENABLE, ICONVAR_ADDR_WIFI_LED);
    }
    else if((lSwiWifiLedRecord == true) && (gLcdSermoonV2UI.enableSwitches.swiWifiLed == false))
    {
        lSwiWifiLedRecord = false;
        gLcdSermoonV2UI.SwitchIcon(AUTOUI_DISABLE, ICONVAR_ADDR_WIFI_LED);
    }

    /* refresh door-open-pause icon status */
    if((lSwiDoorPauseRecord == false) && (gLcdSermoonV2UI.enableSwitches.swiDoorPause == true))
    {
        lSwiDoorPauseRecord = true;
        gLcdSermoonV2UI.SwitchIcon(AUTOUI_ENABLE, ICONVAR_ADDR_DOOR_OPEN_PAUSE);
    }
    else if((lSwiDoorPauseRecord == true) && (gLcdSermoonV2UI.enableSwitches.swiDoorPause == false))
    {
        lSwiDoorPauseRecord = false;
        gLcdSermoonV2UI.SwitchIcon(AUTOUI_DISABLE, ICONVAR_ADDR_DOOR_OPEN_PAUSE);
        SaveSwitchesStatus();
    }
}

/**
 * [RefreshHeatingSta :refresh current hotend/bed heating status]
 * @Author Creality
 * @Time   2021-08-10
 */
void RefreshHeatingStatus(void)
{
    static float lHotendTempRecord = LcdAutoUIGetTarTempHotend();
    static float lBedTempRecord = LcdAutoUIGetTarTempBed();

    /* refresh hotend heating status */
    if((lHotendTempRecord == 0) && (LcdAutoUIGetTarTempHotend() != 0))
    {
        lHotendTempRecord = LcdAutoUIGetTarTempHotend();

        gLcdSermoonV2UI.SetStaDynamicIcon(true, ICONVAR_ADDR_HEATING_HOTEND);
    }
    else if((lHotendTempRecord != 0) && (LcdAutoUIGetTarTempHotend() == 0))
    {
        lHotendTempRecord = LcdAutoUIGetTarTempHotend();

        gLcdSermoonV2UI.SetStaDynamicIcon(false, ICONVAR_ADDR_HEATING_HOTEND);
    }

    /* refresh bed heating status */
    if((lBedTempRecord == 0) && (LcdAutoUIGetTarTempBed() != 0))
    {
        lBedTempRecord = LcdAutoUIGetTarTempBed();

        gLcdSermoonV2UI.SetStaDynamicIcon(true, ICONVAR_ADDR_HEATING_BED);
    }
    else if((lBedTempRecord != 0) && (LcdAutoUIGetTarTempBed() == 0))
    {
        lBedTempRecord = LcdAutoUIGetTarTempBed();

        gLcdSermoonV2UI.SetStaDynamicIcon(false, ICONVAR_ADDR_HEATING_BED);
    }
}

/**
 * [GetTPTFromEEPROM :get total printing time from EEPROM]
 * @Author Creality
 * @Time   2021-06-16
 */
void GetTPTFromEEPROM(void)
{
    uint32_t lTotalTimeInt = 0;
    float lTotalTime = 0.0;//gLcdSermoonV2UI.TotalRuningTime;

    //Eeprom_Read(FONT_EEPROM + EEPROM_ADDR_TPT_OFFSET, (uint8_t*)&lTotalTimeInt, EEPROM_ADDR_TPT_SIZE);

    lTotalTime = (float)(gLcdSermoonV2UI.TotalRuningTime / 100.0);

    gLcdSermoonV2UI.SetPrintTimeTotal(lTotalTime);
    /* refresh on screen */
    gLcdSermoonV2UI.RefreshPrintTimeTotal();
}
/**
 * [ClearPrintTotalTimeRecord :clear printing-total-time]
 * @Author Creality
 * @Time   2021-06-21
 */
void ClearPrintTotalTimeRecord(void)
{
    uint32_t lTotalTimeInt = 0;

    // BL24CXX::write(FONT_EEPROM + EEPROM_ADDR_TPT_OFFSET, (uint8_t*)&lTotalTimeInt, EEPROM_ADDR_TPT_SIZE);

    gLcdSermoonV2UI.SetPrintTimeTotal((float)lTotalTimeInt);
    /* refresh on screen */
    gLcdSermoonV2UI.RefreshPrintTimeTotal();
}

/**
 * [ClearEventPriFlags :clear event priority flags]
 * @Author Creality
 * @Time   2021-07-23
 */
void ClearEventPriFlags(void)
{
    if(gLcdSermoonV2UI.eventPriFlags.epfStopPrint)
        memset(&gLcdSermoonV2UI.eventPriFlags, 0, sizeof(gLcdSermoonV2UI.eventPriFlags));
}

/**
 * [CloHeaTmrStart :start the timer to close all heater]
 * @Author Creality
 * @Time   2021-08-11
 * @param  _howLong   [how long does the timer to time]
 */
void CloHeaTmrStart(uint32_t _howLong)
{
    gLcdSermoonV2UI.cloHeaTmr.cltSwi = true;
    gLcdSermoonV2UI.cloHeaTmr.cltStartTime = LcdAutoUIGetTimeMs();
    gLcdSermoonV2UI.cloHeaTmr.cltHowLongTime = _howLong;
}

/**
 * [CloHeaTmrStop :stop the timer of closing all heater]
 * @Author Creality
 * @Time   2021-08-11
 */
void CloHeaTmrStop(void)
{
    gLcdSermoonV2UI.cloHeaTmr.cltSwi = false;
    gLcdSermoonV2UI.cloHeaTmr.cltStartTime = 0;
    gLcdSermoonV2UI.cloHeaTmr.cltHowLongTime = 0;
}

/**
 * [CloHeaTmrProcess :process of closing-all-heater-timer]
 * @Author Creality
 * @Time   2021-08-11
 */
void CloHeaTmrProcess(void)
{
    if(gLcdSermoonV2UI.cloHeaTmr.cltSwi)
    {
        if((LcdAutoUIGetTimeMs() - gLcdSermoonV2UI.cloHeaTmr.cltStartTime) > gLcdSermoonV2UI.cloHeaTmr.cltHowLongTime)
        {
            CloHeaTmrStop();

            /*disable all heater */
            thermalManager.disable_all_heaters();
        }
    }
}

/**
 * [AutoUIPrintStart :start print]
 * @Author Creality
 * @Time   2021-06-09
 */
void AutoUIPrintStart(void)
{
    char lCmdBuf[30] = {0};
    char* lPLetter = NULL;

    /* 1.no file selected; 2.no SD card */
    if((gLcdSermoonV2UI.gcodeFileSelectedCur == VAULE_INVALIDE) || !IS_SD_INSERTED())
        return;

    /* material check */
    if(!IsExistMaterial())
    {
        gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_LACKMATPW);
        return;
    }
    /* change device status to 'DEVSTA_PRINTING' */
    gLcdSermoonV2UI.AutoUIToStatus(DEVSTA_HEATING);
    gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_HEATING);

    /* make command */
    sprintf_P(lCmdBuf, PSTR("M23 %s"), CardRecbuf.Cardfilename[gLcdSermoonV2UI.gcodeFileSelectedCur]);
    for (lPLetter = &lCmdBuf[4]; *lPLetter; lPLetter++) *lPLetter = tolower(*lPLetter);
    /* excute the command to start print */
    queue.enqueue_one_P(lCmdBuf);
    queue.enqueue_one_P(PSTR("M24"));
    card.removeJobRecoveryFile();

    /* clear printing-filename and display */
    for(uint32_t i=0; i<GCODE_FILE_BYTELEN; i++)
        gLcdSermoonV2UI.DisplayData(0, TEXTVAR_ADDR_FILENAME_PRINTING + i);
    gLcdSermoonV2UI.DisplayText(CardRecbuf.Cardshowfilename[gLcdSermoonV2UI.gcodeFileSelectedCur], TEXTVAR_ADDR_FILENAME_PRINTING);

    /* set device action by mode parameters */
    PrintParasSetByMode();
    
}

/**
 * [AutoUIStopPrint :stop print]
 * @Author Creality
 * @Time   2021-06-09
 */
void AutoUIPrintStop(void)
{
    if(card.isPrinting())
    {
        card.flag.abort_sd_printing = true;
    }
    /* close sd card file */
    // card.endFilePrint();
    #if ENABLED(SDSUPPORT)
      wait_for_heatup = false;//= wait_for_user = false;
      card.flag.abort_sd_printing = true;
    #endif
    /* clear command in queue */
    queue.clear();
    /* quick stop all motors' moving */
    quickstop_stepper();
    /* stop print-job timer */
    print_job_timer.stop();
    /* close all heater */
    thermalManager.disable_all_heaters();
    /* close fans */
    thermalManager.zero_fan_speeds();
    /* go home */
    //queue.enqueue_now_P(PSTR(EVENT_GCODE_SD_ABORT));
	queue.inject_P(PSTR(EVENT_GCODE_SD_ABORT));
    /* remove file that record information print-job recovery */
    #if ENABLED(SDSUPPORT) && ENABLED(POWER_LOSS_RECOVERY)
      card.removeJobRecoveryFile();
    #endif

    /* clear current printing progress and time */
    ClearCurPrintProgress();
    ClearCurPrintTime();
    /* refresh total printing time */
    gLcdSermoonV2UI.RefreshPrintTimeTotal();
    /* change device status to 'DEVSTA_IDLE' */
    gLcdSermoonV2UI.AutoUIToStatus(DEVSTA_IDLE);
    LcdAutoUISetFeedrate(100);
}

/**
 * [AutoUIPrintPause :pause print]
 * @Author Creality
 * @Time   2021-06-09
 */
void AutoUIPrintPause(void)
{
    /* record some device status */
    memset(&gLcdSermoonV2UI.pauseStaRecord, 0, sizeof(gLcdSermoonV2UI.pauseStaRecord));
    gLcdSermoonV2UI.pauseStaRecord.tempHotend = thermalManager.degTargetHotend(0);
    gLcdSermoonV2UI.pauseStaRecord.tempBed = thermalManager.degTargetBed();
    gLcdSermoonV2UI.pauseStaRecord.posPauseBefore = current_position;

    /* close all heater */
    thermalManager.disable_all_heaters();
    /* pause SD card print */
    queue.inject_P(PSTR("M25"));
    /* clear command in queue */
    // queue.clear();
    /* change device status to 'DEVSTA_PRINT_PAUSE' */
    gLcdSermoonV2UI.AutoUIToStatus(DEVSTA_PRINT_PAUSE);

    // card.pauseSDPrint();
}

/**
 * [AutoUIPrintRecovery :recovery print]
 * @Author Creality
 * @Time   2021-06-09
 */
void AutoUIPrintRecovery(void)
{
    if(IS_SD_INSERTED())
    {
        gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_HEATING);
        /* change device status to 'DEVSTA_HEATING' */
        gLcdSermoonV2UI.AutoUIToStatus(DEVSTA_HEATING);
        /* 先送料3mm */
        //LcdAutoUIMoveE(4, FEEDING_DEF_OUT_MAT_SPE1); 
        /* recovery temperature that device pause before */
        LcdAutoUISetTempBedBlock(gLcdSermoonV2UI.pauseStaRecord.tempBed);
        LcdAutoUISetTempHotendBlock(gLcdSermoonV2UI.pauseStaRecord.tempHotend);
        current_position = gLcdSermoonV2UI.pauseStaRecord.posPauseBefore;
        // 恢复坐标时，将其-4，用于打印后的吐料
        LcdAutoUISetECmd(gLcdSermoonV2UI.pauseStaRecord.posPauseBefore.e + PRINT_RECOVER_EXTERA_E_POS - 2);

        if(gLcdSermoonV2UI.AutoUIGetStatus() == DEVSTA_HEATING)
        {
            current_position = gLcdSermoonV2UI.pauseStaRecord.posPauseBefore;
            LcdAutoUIMoveXYZBlock(current_position.x, current_position.y, current_position.z);
            memset(&gLcdSermoonV2UI.pauseStaRecord, 0, sizeof(gLcdSermoonV2UI.pauseStaRecord));
        }
        if(gLcdSermoonV2UI.AutoUIGetStatus() == DEVSTA_HEATING)
        {
            /* change device status to 'DEVSTA_PRINTING' */
            gLcdSermoonV2UI.AutoUIToStatus(DEVSTA_PRINTING);
            /* recover print */
            queue.inject_P(PSTR("M24"));

            gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_PRINTING);
        }
    }
}

/**
 * [AutoUIPullOutUDiskRecovery :打印中拔出U盘，插入后，恢复打印]
 * @Author Creality
 * @Time   2021-07-20
 */
void AutoUIPullOutUDiskRecovery(void)
{
    /* recovery status that device pause before */
    LcdAutoUISetTempHotendBlock(gLcdSermoonV2UI.pauseStaRecord.tempHotend);
    LcdAutoUISetTempBedBlock(gLcdSermoonV2UI.pauseStaRecord.tempBed);
    current_position = gLcdSermoonV2UI.pauseStaRecord.posPauseBefore;
    // LcdAutoUIMoveXYBlock(current_position.x, current_position.y);
    LcdAutoUIMoveZBlock(current_position.z);
    memset(&gLcdSermoonV2UI.pauseStaRecord, 0, sizeof(gLcdSermoonV2UI.pauseStaRecord));
}

/**
 * [AutoUIPowerOffRecoveryPW :popup window(startup), device is power off when printing]
 * @Author Creality
 * @Time   2021-06-19
 */
void AutoUIPowerOffRecoveryPW(void)
{
    gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_INTERCONTPW);

    /* clear printing-filename and display */
    for(uint32_t i=0; i<GCODE_FILE_BYTELEN; i++)
        gLcdSermoonV2UI.DisplayData(0, TEXTVAR_ADDR_FILENAME_INTERRUPT + i);
    /* find the file name that is printing before power off */
    for(uint32_t i=0; i<(uint32_t)GetSDCardGcodeFileNum(); i++)
    {
        if(!strcmp(CardRecbuf.Cardfilename[i], &recovery.info.sd_filename[1]))
        {
            gLcdSermoonV2UI.DisplayText(CardRecbuf.Cardshowfilename[i], TEXTVAR_ADDR_FILENAME_INTERRUPT);
            break;
        }
    }
}

/**
 * [AutoUIPowerOffRecovery :click 'yes' to recovery to print]
 * @Author Creality
 * @Time   2021-06-19
 */
void AutoUIPowerOffRecovery(void)
{
    /* clear printing-filename and display */
    for(uint32_t i=0; i<GCODE_FILE_BYTELEN; i++)
        gLcdSermoonV2UI.DisplayData(0, TEXTVAR_ADDR_FILENAME_PRINTING + i);
    /* find the file name that is printing before power off */
    for(uint32_t i=0; i<(uint32_t)GetSDCardGcodeFileNum(); i++)
    {
        if(!strcmp(CardRecbuf.Cardfilename[i], &recovery.info.sd_filename[1]))
        {
            gLcdSermoonV2UI.DisplayText(CardRecbuf.Cardshowfilename[i], TEXTVAR_ADDR_FILENAME_PRINTING);
            break;
        }
    }

    gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_PRINTING);
    //recovery.resume();
    queue.enqueue_now_P(PSTR("M1000"));
    /* change device status to 'DEVSTA_PRINTING' */
    gLcdSermoonV2UI.AutoUIToStatus(DEVSTA_PRINTING);
}

/**
 * [AutoUIPrintFinished :if print finished or not, and what the device need to do if finished]
 * @Author Creality
 * @Time   2021-06-15
 */
void AutoUIPrintFinished(void)
{
    if(gLcdSermoonV2UI.GetPrintFinishFlag() && !planner.has_blocks_queued() && (gLcdSermoonV2UI.percentDoneRecord >= 99))
    {
        gLcdSermoonV2UI.percentDoneRecord = 0;
        gLcdSermoonV2UI.SetPrintFinishFlag(false);
        gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_PRINTFINISHED);
        gLcdSermoonV2UI.SwitchIcon(100, ICONVAR_ADDR_PRINT_PROGRESS);
        gLcdSermoonV2UI.DisplayData(100, DATAVAR_ADDR_PRINT_PROGRESS);
        /* clear command in queue */
        queue.clear();
        /* stop print-job timer */
        print_job_timer.stop();
        /* close all heater */
        wait_for_heatup = false;
        thermalManager.disable_all_heaters();
        /* close fans */
        thermalManager.zero_fan_speeds();
        /* Z axis go to the max position */
        //LcdAutoUIMoveZ(Z_MAX_POS, AXIS_MOVE_ABSO);
        /* XY axis go to the special position */
        LcdAutoUIMoveX(0, AXIS_MOVE_ABSO);
        LcdAutoUIMoveY(Y_BED_SIZE, AXIS_MOVE_ABSO);
        /* remove file that record information print-job recovery */
        #if ENABLED(SDSUPPORT) && ENABLED(POWER_LOSS_RECOVERY)
          card.removeJobRecoveryFile();
        #endif
  
        /* refresh total printing time */
        gLcdSermoonV2UI.RefreshPrintTimeTotal();
        /* change device status to 'DEVSTA_IDLE' */
        gLcdSermoonV2UI.AutoUIToStatus(DEVSTA_IDLE);
        LcdAutoUISetFeedrate(100);
    }
}

/**
 * [MaterialCheckProcess :process of checking material status and response to status]
 * @Author Creality
 * @Time   2021-06-17
 */
void MaterialCheckProcess(void)
{
    /* 1.lack of material; 2.is printing; */
    if(!IsExistMaterial() && card.isPrinting())
    {
        // gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_LACKMATPW);
        AutoUIPrintPause();
        /* change device status to 'DEVSTA_PRINT_PAUSE' */
        // gLcdSermoonV2UI.AutoUIToStatus(DEVSTA_PRINT_PAUSE);
		gLcdSermoonV2UI.matRunoutAtPrintingFlag = true;
        /* change device status to 'DEVSTA_PRINT_PAUSE' */
        // gLcdSermoonV2UI.AutoUIToStatus(DEVSTA_PRINT_PAUSE);
    }
}

/**
 * [UdiskCheckProcess :打印中检测U盘状态]
 * @Author Creality
 * @Time   2021-06-17
 */
void UdiskCheckProcess(void)
{
    /* 打印中拔掉U盘 */
    if (!DiskIODriver_USBFlash::isInserted())
    {
        gLcdSermoonV2UI.SetPullOutUDiskFlag(true);
        SERIAL_ECHO("pull out u disk when printing");
        TouVarPrintPausePic014();
    }
}

/**
 * [DoorOpenPauseProcess :process of checking door-open status and response to status]
 * @Author Creality
 * @Time   2021-06-19
 */
void DoorOpenPauseProcess(void)
{
    /* 1.door is open; 2.is printing; */
    if(IsDoorOpen() && card.isPrinting())
    {
        AutoUIPrintPause();

        /* change device status to 'DEVSTA_PRINT_PAUSE' */
        gLcdSermoonV2UI.AutoUIToStatus(DEVSTA_PRINT_PAUSE);
    }
}

/***********************************************************************************************************************************
                                                      touch-response functions
***********************************************************************************************************************************/
/**
 * [TouVarConfirmFuncPic001 :confirm touch response function on picture 001]
 * @Author Creality
 * @Time   2021-06-07
 */
static void TouVarConfirmFuncPic001(void)
{
     gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_BOOTGUIDE_02);
    /* enable Dynamic icon */
    gLcdSermoonV2UI.SetStaDynamicIcon(true, ICONVAR_ADDR_DYNAHOMING);
    /* make sure base-point */
    queue.enqueue_now_P(PSTR("G28"));
}

static void TouVarConfirmFuncPic004(void)
{
    /* do nothing */
}

static void TouVarConfirmFuncPic005(void)
{
    if (gLcdSermoonV2UI.matRunoutAtPrintingFlag == true) // 打印中断料分支
        gLcdSermoonV2UI.flowStepCnt.fscInOutMat = 0;
    else
    /* change device status to 'DEVSTA_IN_OUT_MAT' */
    gLcdSermoonV2UI.AutoUIToStatus(DEVSTA_IN_OUT_MAT);
    /* select in-material */
    gLcdSermoonV2UI.inOutMatFlag = true;
    gLcdSermoonV2UI.SetStaDynamicIcon(false, ICONVAR_ADDR_HEATING_BED);
}

static void TouVarConfirmFuncPic006(void)
{
    /* feed material finished */
    gLcdSermoonV2UI.flowStepCnt.fscInOutMat = 3;
    gLcdSermoonV2UI.feedFinishedFlag = true;
    /* switch picture */
	if (gLcdSermoonV2UI.matRunoutAtPrintingFlag == true) // 打印中断料分支
    {
        if (IsExistMaterial()) 
        {
            TERN_(HAS_RESUME_CONTINUE, wait_for_user = false);
            wait_for_heatup = false;
            gLcdSermoonV2UI.matRunoutAtPrintingFlag = false;
            gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_LOADMATPW);
            RefreshOutMatReturnKey(true);
        }
        else 
        {
            // gLcdSermoonV2UI.flowStepCnt.fscInOutMat = 4;
            // gLcdSermoonV2UI.feedFinishedFlag = false;
            gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_LACKMATPW);
        }
        
        //gLcdSermoonV2UI.AutoUIToStatus(DEVSTA_PRINT_PAUSE);
        SERIAL_ECHOLNPAIR("\r\n ok!!! continue!!! run!!!, flag = ", gLcdSermoonV2UI.matRunoutAtPrintingFlag);
        return;
    } 
	
    if(gLcdSermoonV2UI.devStatusLastRecord == DEVSTA_STARTUP_FIR)
    {
        /* startup for first time */
        gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_BOOTGUIDE_07);
    }
    else if(gLcdSermoonV2UI.devStatusLastRecord == DEVSTA_PRINT_PAUSE)
    {
        if(IsExistMaterial())
            gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_LOADMATPW);
        else
            gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_LACKMATPW);
    }
    else
    {
        gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_INOUTMAT);
    }
}

static void TouVarPrintFileFuncPic008(void)
{
    gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_FILESELECT_01);
}

static void TouVarPrintModeFuncPic008(void)
{
    gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_PRINTMODE);
}

static void TouVarPrintSetFuncPic008(void)
{
    gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_PRINTSETTING);
}

static void TouVarDevInfoFuncPic008(void)
{
    gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_DEVINFO);
}

static void TouVarHotendTempFuncPic008(void)
{
    LcdAutoUISetTempHotend(dwinShow.recdat.data[0]);
}

static void TouVarBedTempFuncPic008(void)
{
    LcdAutoUISetTempBed(dwinShow.recdat.data[0]);
}

static void TouVarFeedrateFunc(void)
{
    LcdAutoUISetFeedrate(dwinShow.recdat.data[0]);
}

/**
 * [TouVarReturn :response to "return" touch-variable]
 * @Author Creality
 * @Time   2021-06-06
 */
static void TouVarReturn(void)
{
    switch(dwinShow.recdat.data[0])
    {
        /* picture 009,010,011,012,013 */
        case 0x00:
        case 0x01:
        case 0x02:
        case 0x03:
        case 0x04:
            gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_MAIN_WINDOW);
            break;

        case 0x05:
            if(gLcdSermoonV2UI.AutoUIGetStatus() == DEVSTA_HEATING)
                gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_HEATING);
            else if(gLcdSermoonV2UI.AutoUIGetStatus() == DEVSTA_PRINTING)
                gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_PRINTING);
            break;

        case 0x06:
            gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_MAIN_WINDOW);
            break;

        case 0x07:
            if(gLcdSermoonV2UI.AutoUIGetStatus() == DEVSTA_PRINT_PAUSE)
                gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_PRINTPAUSE);
            else
                gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_PRINTMODE);
            break;

        case 0x08:
            if (gLcdSermoonV2UI.matRunoutAtPrintingFlag == true) // 打印中断料分支
            {
                SERIAL_ECHOLNPAIR("\r\n cancel in mat when heating, flag = ", gLcdSermoonV2UI.matRunoutAtPrintingFlag);
                break;
            }
            /* stop feed(out) material */
            gLcdSermoonV2UI.flowStepCnt.fscInOutMat = 3;
            gLcdSermoonV2UI.feedFinishedFlag = true;
            gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_INOUTMAT);
            break;

        case 0x09:
            break;

        case 0x0A:
            gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_PRINTMODE);
            break;

        case 0x0B:
            gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_MAIN_WINDOW);
            break;

        case 0x0C: /* 免调平界面返回 */
            gLcdSermoonV2UI.AutoUIToStatus(DEVSTA_IDLE);
            gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_PRINTSETTING);
            gLcdSermoonV2UI.SetFlowStep(&gLcdSermoonV2UI.flowStepCnt.fscBedCali, 0);
            break;

        case 0x0D:
            gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_PRINTSETTING);
            break;

        case 0x0E:
            gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_MAIN_WINDOW);
            break;

        case 0x0F:
            break;

        case 0x10: /* 从调平模式界面返回 */
            gLcdSermoonV2UI.bedCaliFinishedFlag = true;
            gLcdSermoonV2UI.SetFlowStep(&gLcdSermoonV2UI.flowStepCnt.fscBedCali, 0);
            gLcdSermoonV2UI.AutoUIToStatus(DEVSTA_IDLE);
            gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_PRINTSETTING);
            gLcdSermoonV2UI.isBedLeveling = false;
            break;
        default:
            break;
    }
}

static void TouVarFileSelect(void)
{
    /* dwinShow.recdat.data[0] : mean index of file */
    gLcdSermoonV2UI.gcodeFileSelectedCur = FileSelectBackground(dwinShow.recdat.data[0], ICONVAR_ADDR_FILESELECT_BG00);
}

static void TouVarFileNextPage(void)
{
    switch(dwinShow.recdat.data[0])
    {
        case 0:
            gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_FILESELECT_02);
            break;

        case 1:
            gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_FILESELECT_03);
            break;

        case 2:
            gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_FILESELECT_04);
            break;

        case 3:
            gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_FILESELECT_05);
            break;

        default:
            break;
    }
}

static void TouVarFileLastPage(void)
{
    switch(dwinShow.recdat.data[0])
    {
        case 0:
            gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_FILESELECT_01);
            break;

        case 1:
            gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_FILESELECT_02);
            break;

        case 2:
            gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_FILESELECT_03);
            break;
        
        case 3:
            gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_FILESELECT_04);
            break;

        default:
            break;
    }
}

static void TouVarPrintSetPic014(void)
{
    gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_PRINTADJUST);
}

static void TouVarPrintPausePic014(void)
{
    gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_GOINGHOME);
    AutoUIPrintPause();
}

static void TouVarPrintStopPic014(void)
{
    gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_PRINTSTOPPW);
}

static void TouVarPrintFinishPic015(void)
{
    gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_MAIN_WINDOW);

    /* clear current printing progress and time */
    ClearCurPrintProgress();
    ClearCurPrintTime();
}

static void TouVarBoxFanPic016(void)
{
    if(gLcdSermoonV2UI.enableSwitches.swiBoxFan)
    {
        gLcdSermoonV2UI.enableSwitches.swiBoxFan = false;

        SetBoxFan(false);
        gLcdSermoonV2UI.SwitchIcon(AUTOUI_DISABLE, ICONVAR_ADDR_BOX_FAN);
    }
    else
    {
        gLcdSermoonV2UI.enableSwitches.swiBoxFan = true;

        SetBoxFan(true);
        gLcdSermoonV2UI.SwitchIcon(AUTOUI_ENABLE, ICONVAR_ADDR_BOX_FAN);
    }
}

static void TouVarBoxLedPic016(void)
{
    if(gLcdSermoonV2UI.enableSwitches.swiBoxLed)
    {
        gLcdSermoonV2UI.enableSwitches.swiBoxLed = false;

        SetBoxLed(false);
        gLcdSermoonV2UI.SwitchIcon(AUTOUI_DISABLE, ICONVAR_ADDR_BOX_LED);
    }
    else
    {
        gLcdSermoonV2UI.enableSwitches.swiBoxLed = true;

        SetBoxLed(true);
        gLcdSermoonV2UI.SwitchIcon(AUTOUI_ENABLE, ICONVAR_ADDR_BOX_LED);
    }
}

static void TouVarWifiLedPic016(void)
{
    // if(gLcdSermoonV2UI.enableSwitches.swiWifiLed)
    // {
    //     gLcdSermoonV2UI.enableSwitches.swiWifiLed = false;

    //     gLcdSermoonV2UI.SwitchIcon(AUTOUI_DISABLE, ICONVAR_ADDR_WIFI_LED);
    // }
    // else
    // {
    //     gLcdSermoonV2UI.enableSwitches.swiWifiLed = true;

    //     gLcdSermoonV2UI.SwitchIcon(AUTOUI_ENABLE, ICONVAR_ADDR_WIFI_LED);
    // }
    TouVarWifiEnable();
}

static void TouVarDoorPausePic016(void)
{
    if(gLcdSermoonV2UI.enableSwitches.swiDoorPause)
    {
        gLcdSermoonV2UI.enableSwitches.swiDoorPause = false;

        gLcdSermoonV2UI.SwitchIcon(AUTOUI_DISABLE, ICONVAR_ADDR_DOOR_OPEN_PAUSE);
    }
    else
    {
        gLcdSermoonV2UI.enableSwitches.swiDoorPause = true;

        gLcdSermoonV2UI.SwitchIcon(AUTOUI_ENABLE, ICONVAR_ADDR_DOOR_OPEN_PAUSE);
    }
}

static void TouVarPrintStopConfirmPic017(void)
{
    gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_MAIN_WINDOW);
    /* stop print */
    AutoUIPrintStop();
}

static void TouVarPrintStopCancelPic017(void)
{
    if(gLcdSermoonV2UI.AutoUIGetStatus() == DEVSTA_HEATING)
        gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_HEATING);
    if(gLcdSermoonV2UI.AutoUIGetStatus() == DEVSTA_PRINTING)
        gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_PRINTING);
    else if(gLcdSermoonV2UI.AutoUIGetStatus() == DEVSTA_PRINT_PAUSE)
        gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_PRINTPAUSE);
}

static void TouVarPrintPauseRecoPic018(void)
{   
    /* recovery to print */
    AutoUIPrintRecovery();
}

static void TouVarPrintStopPic018(void)
{
    gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_PRINTSTOPPW);
}

static void TouVarPrintInOuMatPic018(void)
{
    gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_INOUTMAT);
}

static void TouVarConfirmPrintPic019(void)
{
    if(!IsDoorOpen())
    {
        gLcdSermoonV2UI.SwitchIcon(VAULE_INVALIDE_8BIT, ICONVAR_ADDR_DOOR_OPEN_TIP);
        gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_PRINTING);
        AutoUIPrintRecovery();
    }
    else
    {
        gLcdSermoonV2UI.SwitchIcon(AUTOUI_LANGUAGE_CH, ICONVAR_ADDR_DOOR_OPEN_TIP);
    }
}

static void TouVarCancelPrintPic019(void)
{
    gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_MAIN_WINDOW);
    AutoUIPrintStop();
}

static void TouVarPLASelectPic020(void)
{
    /* current print mode is 'PRINT_MODE_INVAILD' or 'PRINT_MODE_ABS' */
    if(gLcdSermoonV2UI.printModeType == PRINT_MODE_INVAILD || gLcdSermoonV2UI.printModeType == PRINT_MODE_ABS)
    {
        gLcdSermoonV2UI.printModeType = PRINT_MODE_PLA;

        gLcdSermoonV2UI.SwitchIcon(SELECTED_YES, ICONVAR_ADDR_PLA_SELECTED);
        gLcdSermoonV2UI.SwitchIcon(SELECTED_NO, ICONVAR_ADDR_ABS_SELECTED);
    }
    /* current print mode is 'PRINT_MODE_PLA' */
    else if(gLcdSermoonV2UI.printModeType == PRINT_MODE_PLA)
    {
        gLcdSermoonV2UI.printModeType = PRINT_MODE_INVAILD;

        gLcdSermoonV2UI.SwitchIcon(SELECTED_NO, ICONVAR_ADDR_PLA_SELECTED);
        gLcdSermoonV2UI.SwitchIcon(SELECTED_NO, ICONVAR_ADDR_ABS_SELECTED);
    }
}

static void TouVarABSSelectPic020(void)
{
    /* current print mode is 'PRINT_MODE_INVAILD' or 'PRINT_MODE_PLA' */
    if(gLcdSermoonV2UI.printModeType == PRINT_MODE_INVAILD || gLcdSermoonV2UI.printModeType == PRINT_MODE_PLA)
    {
        gLcdSermoonV2UI.printModeType = PRINT_MODE_ABS;

        gLcdSermoonV2UI.SwitchIcon(SELECTED_NO, ICONVAR_ADDR_PLA_SELECTED);
        gLcdSermoonV2UI.SwitchIcon(SELECTED_YES, ICONVAR_ADDR_ABS_SELECTED);
    }
    /* current print mode is 'PRINT_MODE_ABS' */
    else if(gLcdSermoonV2UI.printModeType == PRINT_MODE_ABS)
    {
        gLcdSermoonV2UI.printModeType = PRINT_MODE_INVAILD;

        gLcdSermoonV2UI.SwitchIcon(SELECTED_NO, ICONVAR_ADDR_PLA_SELECTED);
        gLcdSermoonV2UI.SwitchIcon(SELECTED_NO, ICONVAR_ADDR_ABS_SELECTED);
    }
}

static void TouVarUserDefPic020(void)
{
    GetUserDefModeParas();
    
    gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_MODEUSERDEF);
}

static void TouVarDisableHeatPic020(void)
{
    LcdAutoUISetTempHotend(0);
    LcdAutoUISetTempBed(0);
}

static void TouVarInOutMatPic020(void)
{
    gLcdSermoonV2UI.SwitchIcon(VAULE_INVALIDE, ICONVAR_ADDR_INOUTMAT_TIP);
    gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_INOUTMAT);
}

static void TouVarInMatPic021()
{
    gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_BOOTGUIDE_05);
    gLcdSermoonV2UI.SetStaDynamicIcon(true, ICONVAR_ADDR_IN_MAT);  
}

static void TouVarOutMatPic021()
{
    gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_OUTMAT_01);
    /* change device status to 'DEVSTA_IN_OUT_MAT' */
    gLcdSermoonV2UI.AutoUIToStatus(DEVSTA_IN_OUT_MAT);
    /* select out-material */
    gLcdSermoonV2UI.inOutMatFlag = false;
}

static void TouVarOutMatConfirmPic023(void)
{
    if (gLcdSermoonV2UI.matRunoutAtPrintingFlag == true) // 打印中断料分支
    {
        gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_BOOTGUIDE_05);
        gLcdSermoonV2UI.SetStaDynamicIcon(true, ICONVAR_ADDR_IN_MAT);
        SERIAL_ECHOLNPAIR("\r\n continue!!!! start to in mat, flag = ", gLcdSermoonV2UI.matRunoutAtPrintingFlag);
    } 
    else{
	    gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_INOUTMAT);
	    /* feed(out) material finished */
	    gLcdSermoonV2UI.feedFinishedFlag = true;
    }
}

static void TouVarSetHotendFanPic024(void)
{
    if(userDefMode.pmpHotendFanFlag)
    {
        userDefMode.pmpHotendFanFlag = false;

        gLcdSermoonV2UI.SwitchIcon(AUTOUI_DISABLE, ICONVAR_ADDR_HOTEND_FAN_STA);
    }
    else
    {
        userDefMode.pmpHotendFanFlag = true;

        gLcdSermoonV2UI.SwitchIcon(AUTOUI_ENABLE, ICONVAR_ADDR_HOTEND_FAN_STA);
    }
}

static void TouVarSetBoxFanPic024(void)
{
    if(userDefMode.pmpBoxFanFlag)
    {
        userDefMode.pmpBoxFanFlag = false;

        gLcdSermoonV2UI.SwitchIcon(AUTOUI_DISABLE, ICONVAR_ADDR_BOX_FAN_STA);
    }
    else
    {
        userDefMode.pmpBoxFanFlag = true;

        gLcdSermoonV2UI.SwitchIcon(AUTOUI_ENABLE, ICONVAR_ADDR_BOX_FAN_STA);
    }
}

static void TouVarBedCaliPic025(void)
{
    /* change device status - 'DEVSTA_BED_CALI', start bed calibration flow */
    gLcdSermoonV2UI.AutoUIToStatus(DEVSTA_BED_CALI);
}

static void TouVarAxisMovePic025(void)
{
    /* refresh current position that display on screen */
    RefreshCurPosDisplay();

    gLcdSermoonV2UI.SetAxisStepUnit(STEP_UNIT_10MM);
    gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_AXISCONTR_10);
}

static void TouVarStepUnitMM1(void)
{
    gLcdSermoonV2UI.SetAxisStepUnit(STEP_UNIT_1MM);
    gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_AXISCONTR_1);
}

static void TouVarStepUnitMM01(void)
{
    gLcdSermoonV2UI.SetAxisStepUnit(STEP_UNIT_01MM);
    gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_AXISCONTR_01);
}

static void TouVarXBackward(void)
{
    current_position.x -= gLcdSermoonV2UI.GetAxisStepUnit();

    /* X axis lower limit */
    current_position.x = current_position.x < 0 ? 0 : current_position.x;

    LcdAutoUIMoveX(current_position.x, AXIS_MOVE_ABSO);
    gLcdSermoonV2UI.DisplayData(current_position.x * DWIN_REALVAL_TIMES, DATAVAR_ADDR_CURPOS_X);
}

static void TouVarXForward(void)
{
    current_position.x += gLcdSermoonV2UI.GetAxisStepUnit();

    /* X axis upper limit */
    current_position.x = current_position.x > X_BED_SIZE ? X_BED_SIZE : current_position.x;

    LcdAutoUIMoveX(current_position.x, AXIS_MOVE_ABSO);
    gLcdSermoonV2UI.DisplayData(current_position.x * DWIN_REALVAL_TIMES, DATAVAR_ADDR_CURPOS_X);
}

static void TouVarYForward(void)
{
    current_position.y += gLcdSermoonV2UI.GetAxisStepUnit();

    /* Y axis upper limit */
    current_position.y = current_position.y > Y_BED_SIZE ? Y_BED_SIZE : current_position.y;

    LcdAutoUIMoveY(current_position.y, AXIS_MOVE_ABSO);
    gLcdSermoonV2UI.DisplayData(current_position.y * DWIN_REALVAL_TIMES, DATAVAR_ADDR_CURPOS_Y);
}

static void TouVarYBackward(void)
{
    current_position.y -= gLcdSermoonV2UI.GetAxisStepUnit();

    /* Y axis lower limit */
    current_position.y = current_position.y < 0 ? 0 : current_position.y;

    LcdAutoUIMoveY(current_position.y, AXIS_MOVE_ABSO);
    gLcdSermoonV2UI.DisplayData(current_position.y * DWIN_REALVAL_TIMES, DATAVAR_ADDR_CURPOS_Y);
}

static void TouVarZUp(void)
{
    current_position.z -= gLcdSermoonV2UI.GetAxisStepUnit();

    /* Z axis lower limit */
    current_position.z = current_position.z < 0 ? 0 : current_position.z;

    LcdAutoUIMoveZ(current_position.z, AXIS_MOVE_ABSO);
    gLcdSermoonV2UI.DisplayData(current_position.z * DWIN_REALVAL_TIMES, DATAVAR_ADDR_CURPOS_Z);
}

static void TouVarZDown(void)
{
    current_position.z += gLcdSermoonV2UI.GetAxisStepUnit();

    /* Z axis upper limit */
    current_position.z = current_position.z > Z_MAX_POS ? Z_MAX_POS : current_position.z;

    LcdAutoUIMoveZ(current_position.z, AXIS_MOVE_ABSO);
    gLcdSermoonV2UI.DisplayData(current_position.z * DWIN_REALVAL_TIMES, DATAVAR_ADDR_CURPOS_Z);
}

static void TouVarGoHome(void)
{
    /* make sure base-point */
    queue.enqueue_now_P(PSTR("G28"));
    /* refresh current postion display */
    gLcdSermoonV2UI.DisplayData(X_MAX_POS * DWIN_REALVAL_TIMES, DATAVAR_ADDR_CURPOS_X);
    gLcdSermoonV2UI.DisplayData(Y_MAX_POS * DWIN_REALVAL_TIMES, DATAVAR_ADDR_CURPOS_Y);
    gLcdSermoonV2UI.DisplayData(Z_MAX_POS * DWIN_REALVAL_TIMES, DATAVAR_ADDR_CURPOS_Z);
}

static void TouVarStepUnitMM10(void)
{
    gLcdSermoonV2UI.SetAxisStepUnit(STEP_UNIT_10MM);
    gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_AXISCONTR_10);
}

static void TouVarLangSelectPic031(void)
{
    gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_LANGSELECT);
}

static void TouVarDevResetPic031(void)
{
    gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_FACTORRESETPW);
}

static void TouVarLangTypePic032(void)
{
    gLcdSermoonV2UI.SetSaveCurLang((AutoUILanguage_t)dwinShow.recdat.data[0]);
    gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_DEVINFO);
}

static void TouVarConfirmResetPic033(void)
{
    /* factory reset  */
    /* get to the status that device has never used */
    // Eeprom_Write(FONT_EEPROM + EEPROM_ADDR_STTF_OFFSET, 0, EEPROM_ADDR_STTF_SIZE);
    /* default language: Chinese */
    // gLcdSermoonV2UI.SetSaveCurLang(AUTOUI_LANGUAGE_CH);

    settings.reset();
    settings.save();
    gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_DEVINFO);
}

static void TouVarCancelResetPic033(void)
{
    gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_DEVINFO);
}

static void TouVarContinuePrintPic036(void)
{
    if (gLcdSermoonV2UI.GetPullOutUDiskFlag()) // 打印过程中拔卡
    {
        gLcdSermoonV2UI.SetPullOutUDiskFlag(false);
        AutoUIPullOutUDiskRecovery();
    }
    AutoUIPowerOffRecovery();
}

static void TouVarCancelPrintPic036(void)
{
    gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_MAIN_WINDOW);
    /* remove file that record information print-job recovery */
    #if ENABLED(SDSUPPORT) && ENABLED(POWER_LOSS_RECOVERY)
      card.removeJobRecoveryFile();
    #endif
}

static void TouVarKeybrdInputX(void)
{
    current_position.x = dwinShow.recdat.data[0]/DWIN_REALVAL_TIMES;
    LcdAutoUIMoveX(current_position.x, AXIS_MOVE_ABSO);
}

static void TouVarKeybrdInputY(void)
{
    current_position.y = dwinShow.recdat.data[0]/DWIN_REALVAL_TIMES;
    LcdAutoUIMoveY(current_position.y, AXIS_MOVE_ABSO);
}

static void TouVarKeybrdInputZ(void)
{
    current_position.z = dwinShow.recdat.data[0]/DWIN_REALVAL_TIMES;
    LcdAutoUIMoveZ(current_position.z, AXIS_MOVE_ABSO);
}

static void TouVarBedCaliUpPic027(void)
{
    /* move Z Axis and refresh current Z coordinate */
    LcdAutoUIMoveZ((-1)*BED_CALI_STEPUNIT, AXIS_MOVE_RELA);

    gLcdSermoonV2UI.DisplayData((int)(100*current_position.z), DATAVAR_ADDR_ZOFFSET);
    gLcdSermoonV2UI.DisplayData((int)(100*((-1)*current_position.z + Z_MAX_POS)), DATAVAR_ADDR_ZHEIGHT);
}

static void TouVarBedCaliDownPic027(void)
{
    /* move Z Axis and refresh current Z coordinate */
    LcdAutoUIMoveZ(BED_CALI_STEPUNIT, AXIS_MOVE_RELA);
    
    gLcdSermoonV2UI.DisplayData((int)(100*current_position.z), DATAVAR_ADDR_ZOFFSET);
    gLcdSermoonV2UI.DisplayData((int)(100*((-1)*current_position.z + Z_MAX_POS)), DATAVAR_ADDR_ZHEIGHT);
}

static void TouVarBedCaliSavePic027(void)
{
    /* save Z offset */
    // mbl.z_offset = current_position.z;
    settings.save();
    /* go to next point */
    queue.inject_P(PSTR("G29 S2"));

    if(gLcdSermoonV2UI.pointCntCaliCur >= BED_CALI_POINT_NUM)
    {
        /* bed calibration finished */
        gLcdSermoonV2UI.bedCaliFinishedFlag = true;
    } 
    else
    {
        gLcdSermoonV2UI.DisplayData(0, DATAVAR_ADDR_ZOFFSET);
        gLcdSermoonV2UI.DisplayData((int)(100*Z_MAX_POS), DATAVAR_ADDR_ZHEIGHT);
        /* next point(display by dynamic icon) */
        gLcdSermoonV2UI.SwitchIcon(gLcdSermoonV2UI.pointCntCaliCur++, ICONVAR_ADDR_BEDCALI_CURPOINT);
    }
}

static void TouVarStartPrint(void)
{
    AutoUIPrintStart();
}

static void TouVarConfirmLoadMatPic039(void)
{
    if (gLcdSermoonV2UI.matRunoutAtPrintingFlag == true) // 打印中断料分支
    {
        RefreshOutMatReturnKey(false);
        TouVarOutMatPic021();  // 调用进入退料处理函数;
        SERIAL_ECHOLNPAIR("\r\n mat runout ,and start remove mat ,flag = ", gLcdSermoonV2UI.matRunoutAtPrintingFlag);
    }
    else 
    {
        gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_BOOTGUIDE_05);
        gLcdSermoonV2UI.SetStaDynamicIcon(true, ICONVAR_ADDR_IN_MAT);
    }
}

static void TouVarStopPrintPic039(void)
{
    if (gLcdSermoonV2UI.matRunoutAtPrintingFlag == true) // 打印中断料分支
    {
        gLcdSermoonV2UI.matRunoutAtPrintingFlag = false;
        SERIAL_ECHOLNPAIR("\r\n cancel mat runout deal,flag = ", gLcdSermoonV2UI.matRunoutAtPrintingFlag);
    }
    gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_MAIN_WINDOW);
    if(gLcdSermoonV2UI.AutoUIGetStatus() != DEVSTA_IDLE)
    {
        /* stop print */
        AutoUIPrintStop();
    }  
}

static void TouVarContinuePrintPic040(void)
{
    AutoUIPrintRecovery();
}

static void TouVarStopPrintPic040(void)
{
    gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_MAIN_WINDOW);
    /* stop print */
    AutoUIPrintStop();
}

static void TouVarZOffsetUpPic041(void)
{
#ifdef BLTOUCH
    gLcdSermoonV2UI.zOffsetVtrl.zlast_zoffset = gLcdSermoonV2UI.zOffsetVtrl.zprobe_zoffset;
    SERIAL_ECHOLNPAIR("befor zlast_zoffset = ", gLcdSermoonV2UI.zOffsetVtrl.zlast_zoffset * 1000,
                      "befor zprobe_zoffset = ", gLcdSermoonV2UI.zOffsetVtrl.zprobe_zoffset * 1000);
    if (WITHIN((gLcdSermoonV2UI.zOffsetVtrl.zprobe_zoffset + 0.1), Z_PROBE_OFFSET_RANGE_MIN, Z_PROBE_OFFSET_RANGE_MAX)) 
    {
        gLcdSermoonV2UI.zOffsetVtrl.zprobe_zoffset = (gLcdSermoonV2UI.zOffsetVtrl.zprobe_zoffset + 0.1);
        #if HAS_LEVELING
            probe.offset.z += gLcdSermoonV2UI.zOffsetVtrl.zprobe_zoffset - gLcdSermoonV2UI.zOffsetVtrl.zlast_zoffset;
        #endif
        babystep.add_mm(Z_AXIS, gLcdSermoonV2UI.zOffsetVtrl.zprobe_zoffset - gLcdSermoonV2UI.zOffsetVtrl.zlast_zoffset);  
        //settings.save();
        gLcdSermoonV2UI.DisplayData(probe.offset.z*1000, DATAVAR_ADDR_Z_OFFSET);

        // 设置保存标志与延时保存时间
        gLcdSermoonV2UI.zOffsetVtrl.saveFlag = true;
        gLcdSermoonV2UI.zOffsetVtrl.saveParmCnt = Z_OFFSET_SAVE_COUNT;
    }
    SERIAL_ECHOLNPAIR("befor zlast_zoffset = ", gLcdSermoonV2UI.zOffsetVtrl.zlast_zoffset * 1000,
                      "befor zprobe_zoffset = ", gLcdSermoonV2UI.zOffsetVtrl.zprobe_zoffset * 1000);
#endif
}

static void TouVarZOffsetDownPic041(void)
{
#ifdef BLTOUCH
    gLcdSermoonV2UI.zOffsetVtrl.zlast_zoffset = gLcdSermoonV2UI.zOffsetVtrl.zprobe_zoffset;
    if (WITHIN((gLcdSermoonV2UI.zOffsetVtrl.zprobe_zoffset - 0.1), Z_PROBE_OFFSET_RANGE_MIN, Z_PROBE_OFFSET_RANGE_MAX)) 
    {
        gLcdSermoonV2UI.zOffsetVtrl.zprobe_zoffset = (gLcdSermoonV2UI.zOffsetVtrl.zprobe_zoffset - 0.1);
        #if HAS_LEVELING
            probe.offset.z += gLcdSermoonV2UI.zOffsetVtrl.zprobe_zoffset - gLcdSermoonV2UI.zOffsetVtrl.zlast_zoffset;
        #endif
        babystep.add_mm(Z_AXIS, gLcdSermoonV2UI.zOffsetVtrl.zprobe_zoffset - gLcdSermoonV2UI.zOffsetVtrl.zlast_zoffset);
        //settings.save();
        gLcdSermoonV2UI.DisplayData(probe.offset.z*1000, DATAVAR_ADDR_Z_OFFSET);

        // 设置保存标志与延时保存时间
        gLcdSermoonV2UI.zOffsetVtrl.saveFlag = true;
        gLcdSermoonV2UI.zOffsetVtrl.saveParmCnt = Z_OFFSET_SAVE_COUNT;
    }
#endif
}
static void TouVarAuxLevelPic041(void)
{

}

static void TouVarAutoLevelPic041(void)
{
    gLcdSermoonV2UI.SwitchIcon(1, ICONVAR_ADDR_AUTO_LEVEL_PROCESS);
    gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_AUTOLEVELING);
    queue.enqueue_now_P(PSTR("G29"));
    // queue.enqueue_now_P(PSTR("G0 Z0")); 
    queue.enqueue_now_P(PSTR("M410 S1")); 
}

static void TouVarLevelEnablePic041(void)
{
    if (gLcdSermoonV2UI.GetLevelStatus() == AUTOUI_LEVEL_STU_FALSE)
    {
        queue.enqueue_now_P(PSTR("M420 S1"));
        gLcdSermoonV2UI.SetSaveLevelStatus(AUTOUI_LEVEL_STU_TRUE);
    }
    else
    {
        queue.enqueue_now_P(PSTR("M420 S0"));
        gLcdSermoonV2UI.SetSaveLevelStatus(AUTOUI_LEVEL_STU_FALSE);
    }
    gLcdSermoonV2UI.SwitchIcon((int)gLcdSermoonV2UI.GetLevelStatus(), ICONVAR_ADDR_LEVEL_ENABLE);
}

static void TouVarWifiReset(void)
{
    #if ENABLED(HAS_MENU_RESET_WIFI)
        gLcdSermoonV2UI.wifiCtrl.resetWifiCnt = WIFI_RESET_OUTPUT_COUNT;
        SERIAL_ECHO("reset wifi start");
    #endif
    // gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_AUTOLEVELING);
}

static void TouVarWifiEnable(void)
{
    if(gLcdSermoonV2UI.wifiCtrl.wifiState != WIFI_DISABLE)
    {
        gLcdSermoonV2UI.wifiCtrl.wifiState = WIFI_DISABLE;
        queue.inject_P(PSTR("M115"));
        // gLcdSermoonV2UI.DisplayData(0, ICONVAR_ADDR_WIFI_SWITCH);
        gLcdSermoonV2UI.DisplayData(0, ICONVAR_ADDR_WIFI_LED);
        settings.save();
    }
    else
    {
        gLcdSermoonV2UI.wifiCtrl.wifiState = WIFI_ENABLE;
        queue.inject_P(PSTR("M115"));
        // gLcdSermoonV2UI.DisplayData(1, ICONVAR_ADDR_WIFI_SWITCH);
        gLcdSermoonV2UI.DisplayData(1, ICONVAR_ADDR_WIFI_LED);
        settings.save();
    }
}
/***********************************************************************************************************************************
                                                 functions for 'LcdAutoUIStruct_t'
***********************************************************************************************************************************/
/**
 * [LcdAutoUIStruct_t :Initialize Automatic-style-UI struct]
 * @Author Creality
 * @Time   2021-05-27
 */
LcdAutoUIStruct_t::LcdAutoUIStruct_t(void)
{
    /* default:Execute the guidance process */
    startupFirstTimeFlag = false;
    /* deault:display in Chinese */
    curLanguage = (AutoUILanguage_t)AUTOUI_LANGUAGE_CH;
    /* default device status */
    devStatus = DEVSTA_INIT;
    goHomeSta = GO_HOME_IDLE;
    printModeType = PRINT_MODE_PLA;
    gcodeFileSelectedCur = VAULE_INVALIDE;
    isBedLeveling = false;
    memset(&flowStepCnt, 0, sizeof(flowStepCnt));
    memset(&enableSwitches, 0, sizeof(enableSwitches));
    matRunoutAtPrintingFlag = false;
}

/**
 * [SetStartupFirstTimeFlag :set StartupFirstTimeFlag]
 * @Author Creality
 * @Time   2021-05-27
 * @param  _flag      [true:startup for first time, false:other situation]
 */
void LcdAutoUIStruct_t::SetStartupFirstTimeFlag(bool _flag)
{
    startupFirstTimeFlag = _flag;
}

/**
 * [GetStartupFirstTimeFlag :get the value of StartupFirstTimeFlag]
 * @Author Creality
 * @Time   2021-05-27
 */
bool LcdAutoUIStruct_t::GetStartupFirstTimeFlag(void)
{
    if (startupFirstTimeFlag != true && startupFirstTimeFlag != false)
    {
        startupFirstTimeFlag = false;
        settings.save();
    }
    return startupFirstTimeFlag;
}

/**
 * [GetCurLang :get current language]
 * @Author Creality
 * @Time   2021-07-23
 */
void LcdAutoUIStruct_t::GetCurLang(void)
{
    if(curLanguage < AUTOUI_LANGUAGE_CH || curLanguage > (AUTOUI_LANGUAGE_NUM - AUTOUI_LANGUAGE_CH))
    {
        /* 'curLanguage' is out of range or loading language firstly, so display deault language */
        curLanguage = (AutoUILanguage_t)DEFAULT_LANGUAGE;
        /* record language type that display now in EEPROM at address of 'FONT_EEPROM' */
        settings.save();
    }
    else
    {
        /* display language by value of 'curLanguage' that load from 'EEPROM' */
    }

    #if 1
    // curLanguage = (AutoUILanguage_t)DEFAULT_LANGUAGE;
    // settings.save();
    #endif
}

/**
 * [LcdAutoUIStruct_t::SetSaveCurLang :set current language and save in EEPROM]
 * @Author Creality
 * @Time   2021-06-17
 * @param  _language  [language to be set]
 */
void LcdAutoUIStruct_t::SetSaveCurLang(AutoUILanguage_t _language)
{
    if(curLanguage < AUTOUI_LANGUAGE_CH || curLanguage > (AUTOUI_LANGUAGE_NUM - AUTOUI_LANGUAGE_CH))
    {
        return;
    }

    curLanguage = _language;

    //Eeprom_Write(FONT_EEPROM, (uint8_t*)&curLanguage, 1);
    settings.save();
    RefreshCurLanguage();
}

/**
 * [LcdAutoUIStruct_t::SetSaveCurLang :set current language and save in EEPROM]
 * @Author Creality
 * @Time   2021-07-23
 * @param  _language  [language to be set]
 */
void LcdAutoUIStruct_t::ResetCurLang()
{
    curLanguage = (AutoUILanguage_t)DEFAULT_LANGUAGE;

    RefreshCurLanguage();
}

/**
 * [CheckStartFirstTime :检查是否是第一次启动]
 * @Author Creality
 * @Time   2021-07-23
 */
void LcdAutoUIStruct_t::CheckStartFirstTime(void)
{
    /* device startup for first time or not */
    //Eeprom_Read(FONT_EEPROM + EEPROM_ADDR_STTF_OFFSET, &lFlagVal, 1);
    if(startupFirstTimeVal != STARTUP_FIR_TIME_VAL)
    {
        /* startup for first time */
        SetStartupFirstTimeFlag(true);
        startupFirstTimeVal = STARTUP_FIR_TIME_VAL;
        //Eeprom_Write(FONT_EEPROM + EEPROM_ADDR_STTF_OFFSET, &lFlagVal, 1);
        settings.save();
    }
}

/**
 * [ResetStartFirstTimeVal :复位第一次启动值]
 * @Author Creality
 * @Time   2021-07-23
 */
void LcdAutoUIStruct_t::ResetStartFirstTimeVal(void)
{
    startupFirstTimeVal = 0;
}

/**
 * [LcdAutoUIStruct_t::SetzCoordinateOffset :保存复位两个坐标（z下限位和bltouch建立的坐标系）的差值到eeprom]
 * @Author Creality
 * @Time   2021-06-17
 * @param  _language  [language to be set]
 */
float LcdAutoUIStruct_t::GetzCoordinateOffset(void)
{
    return zCoordinateOffset;
}

/**
 * [LcdAutoUIStruct_t::SetzCoordinateOffset :保存复位两个坐标（z下限位和bltouch建立的坐标系）的差值到eeprom]
 * @Author Creality
 * @Time   2021-06-17
 * @param  _language  [language to be set]
 */
void LcdAutoUIStruct_t::SetzCoordinateOffset(float _offset)
{
    zCoordinateOffset = _offset;
}

/**
 * [ResetzCoordinateOffsetVal :复位两个坐标（z下限位和bltouch建立的坐标系）的差值]
 * @Author Creality
 * @Time   2021-08-10
 */
void LcdAutoUIStruct_t::ResetzCoordinateOffsetVal(void)
{
    zCoordinateOffset = 0;
}

/**
 * [LcdAutoUIStruct_t::GetCurLevelStatusFromEEPROM :从eeprom获取调平状态]
 * @Author Creality
 * @Time   2021-07-19
 */
void LcdAutoUIStruct_t::GetCurLevelStatusFromEEPROM(void)
{
    //Eeprom_Read(FONT_EEPROM, (uint8_t*)&autoLevelStatus, 1);

    if(autoLevelStatus >= AUTOUI_LEVEL_NUM)
    {
        /* startup for first time */
        autoLevelStatus = AUTOUI_LEVEL_STU_FALSE;
        //Eeprom_Write(FONT_EEPROM + EEPROM_ADDR_STTF_OFFSET, (uint8_t*)&autoLevelStatus, sizeof(autoLevelStatus));
        settings.save();
    }
}

/**
 * [LcdAutoUIStruct_t::GetLevelStatus :从eeprom获取调平状态]
 * @Author Creality
 * @Time   2021-07-19
 */
AutoUILevelStu_t LcdAutoUIStruct_t::GetLevelStatus(void)
{
    return autoLevelStatus;
}

/**
 * [LcdAutoUIStruct_t::SetSaveAutoLevelStatus :保存调平状态到EEPROM]
 * @Author Creality
 * @Time   2021-06-17
 * @param  
 */
void LcdAutoUIStruct_t::SetSaveLevelStatus(AutoUILevelStu_t _status)
{
    autoLevelStatus = _status;
    //Eeprom_Write(FONT_EEPROM, (uint8_t*)&autoLevelStatus, 1);
    settings.save();
}

/**
 * [LcdAutoUIStruct_t::ResetLevelStatus :复位自动调平状态]
 * @Author Creality
 * @Time   2021-06-17
 * @param   
 */
void LcdAutoUIStruct_t::ResetLevelStatus(void)
{
    autoLevelStatus = AUTOUI_LEVEL_STU_FALSE;
}

/**
 * [SetStaGoingHome :Set status of going home]
 * @Author Creality
 * @Time   2021-06-01
 * @param  _sta       [status of going home]
 */
void LcdAutoUIStruct_t::SetStaGoingHome(AutoUIGoHomeSta_t _sta)
{
    goHomeSta = _sta;
}

/**
 * [LcdAutoUIStruct_t::GetStaGoingHome :get status of going home]
 * @Author Creality
 * @Time   2021-06-16
 * @return            [status of going home]
 */
AutoUIGoHomeSta_t LcdAutoUIStruct_t::GetStaGoingHome(void)
{
    return goHomeSta;
}

/**
 * [LcdAutoUIStruct_t::GetCurPrintMode :get current print-mode]
 * @Author Creality
 * @Time   2021-06-23
 * @return            [current print-mode]
 */
AutoUIPrintModeType_t LcdAutoUIStruct_t::GetCurPrintMode(void)
{
    return printModeType;
}

/**
 * [LcdAutoUIStruct_t::SetHaGoHoBeFlag :set flag of 'haveGoneHomeBeforeFlag']
 * @Author Creality
 * @Time   2021-06-11
 * @param  _flag      [true: have gone home before, false:have not gone home]
 */
void LcdAutoUIStruct_t::SetHaGoHoBeFlag(bool _flag)
{
    haveGoneHomeBeforeFlag = _flag;
}

/**
 * [LcdAutoUIStruct_t::GetHaGoHoBeFlag :get flag of 'haveGoneHomeBeforeFlag']
 * @Author Creality
 * @Time   2021-06-11
 * @return            [true: have gone home before, false:have not gone home]
 */
bool LcdAutoUIStruct_t::GetHaGoHoBeFlag(void)
{
    return haveGoneHomeBeforeFlag;
}

/**
 * [LcdAutoUIStruct_t::SetPowerLossFlag :set flag of 'powerLossRecoveryFlag']
 * @Author Creality
 * @Time   2021-06-24
 * @param  _flag      [true:断电时有打印 , false:断电时无打印]
 */
void LcdAutoUIStruct_t::SetPowerLossFlag(bool _flag)
{
    powerLossRecoveryFlag = _flag;
}

/**
 * [LcdAutoUIStruct_t::GetPowerLossFlag :get flag of 'powerLossRecoveryFlag']
 * @Author Creality
 * @Time   2021-06-24
 * @return            [true:断电时有打印 , false:断电时无打印]
 */
bool LcdAutoUIStruct_t::GetPowerLossFlag(void)
{
    return powerLossRecoveryFlag;
}

/**
 * [LcdAutoUIStruct_t::SetPullOutUDiskFlag :set flag of 'pullOutUDiskWhenPrintFlag']
 * @Author Creality
 * @Time   2021-06-24
 * @param  _flag      [true:打印中拔出U盘 , false:打印中没拔出U盘]
 */
void LcdAutoUIStruct_t::SetPullOutUDiskFlag(bool _flag)
{
    pullOutUDiskWhenPrintFlag = _flag;
}

/**
 * [LcdAutoUIStruct_t::GetPullOutUDiskFlag :get flag of 'pullOutUDiskWhenPrintFlag']
 * @Author Creality
 * @Time   2021-06-24
 * @return            [true:打印中拔出U盘 , false:打印中没拔出U盘]
 */
bool LcdAutoUIStruct_t::GetPullOutUDiskFlag(void)
{
    return pullOutUDiskWhenPrintFlag;
}

/**
 * [LcdAutoUIStruct_t::SetPrintFinishFlag :set flag of 'printFinishFlag']
 * @Author Creality
 * @Time   2021-07-10
 * @param  _flag      [true:print has finished, false:other situation]
 */
void LcdAutoUIStruct_t::SetPrintFinishFlag(bool _flag)
{
    printFinishFlag = _flag;
}

/**
 * [LcdAutoUIStruct_t::GetPrintFinishFlag :get flag of 'printFinishFlag']
 * @Author Creality
 * @Time   2021-07-10
 * @param  _flag      [true:print has finished, false:other situation]
 */
bool LcdAutoUIStruct_t::GetPrintFinishFlag(void)
{
    return printFinishFlag;
}

/**
 * [LcdAutoUIStruct_t::SetFlowStep :set current step of flow]
 * @Author Creality
 * @Time   2021-06-07
 * @param  _flowCntType [type of flow-count, refer to variable 'gLcdSermoonV2UI.flowStepCnt']
 * @param  _stepVal     [description]
 */
void LcdAutoUIStruct_t::SetFlowStep(uint8_t* _flowCntType, uint8_t _stepVal)
{
    *_flowCntType = _stepVal;
}

/**
 * [LcdAutoUIStruct_t::SetAxisStepUnit :set axis move step unit]
 * @Author Creality
 * @Time   2021-06-10
 * @param  _uint      [value of unit]
 */
void LcdAutoUIStruct_t::SetAxisStepUnit(AutoUIAxisStepUnit_t _uint)
{
    axisStepUnit = (float)_uint/STEP_UNIT_TIMES;
}

/**
 * [LcdAutoUIStruct_t::SetAxisStepUnit :get axis move step unit]
 * @Author Creality
 * @Time   2021-06-10
 * @return            [current step unit]
 */
float LcdAutoUIStruct_t::GetAxisStepUnit(void)
{
    return axisStepUnit;
}

/**
 * [SwitchBackgroundPic :switch background picture]
 * @Author Creality
 * @Time   2021-05-27
 * @param  _picId     [ID of background-picture]
 */
void LcdAutoUIStruct_t::SwitchBackgroundPic(AutoUIPictureID_t _picId)
{
    dwinShow.RTS_SndData(ExchangePageBase + (uint8_t)_picId, ExchangepageAddr);
    /* record current and last picture ID */
    lastPicID = curPicID;
    curPicID = _picId;
}

/**
 * [SwitchIcon :switch icon]
 * @Author Creality
 * @Time   2021-05-27
 * @param  _iconId     [ID of icon]
 * @param  _iconAdress [adress of icon]
 */
void LcdAutoUIStruct_t::SwitchIcon(int _iconId, unsigned long _iconAdress)
{
    dwinShow.RTS_SndData(_iconId, _iconAdress);
}

/**
 * [LcdAutoUIStruct_t::DisplayData :display data]
 * @Author Creality
 * @Time   2021-06-04
 * @param  _data       [value of data]
 * @param  _dataAdress [address of data]
 */
void LcdAutoUIStruct_t::DisplayData(int _data, unsigned long _dataAdress)
{
    dwinShow.RTS_SndData(_data, _dataAdress);
}

/**
 * [LcdAutoUIStruct_t::DisplayText :display text]
 * @Author Creality
 * @Time   2021-06-09
 * @param  _str        [text string]
 * @param  _dataAdress [address of text variable]
 */
void LcdAutoUIStruct_t::DisplayText(char* _str, unsigned long _dataAdress)
{
    dwinShow.RTS_SndData(_str, _dataAdress);
}

/**
 * [SetStaDynamicIcon :enable/disable dynamic icon]
 * @Author Creality
 * @Time   2021-06-01
 * @param  _en         [true: start to loop icon, false: stop ]
 * @param  _iconAdress [adress of dynamic-icon]
 */
void LcdAutoUIStruct_t::SetStaDynamicIcon(bool _en, unsigned long _iconAdress)
{
    dwinShow.RTS_SndData(_en, _iconAdress);
}

/**
 * [RefreshCurLanguage :refresh current language according to 'curLanguage']
 * @Author Creality
 * @Time   2021-05-28
 */
void LcdAutoUIStruct_t::RefreshCurLanguage(void)
{
    for(uint32_t i=0; i<ICONVAR_WITHWORDS_NUM; i++)
    {
        SwitchIcon(curLanguage, gIconVariAddrArray[i]);
    }
}
/**
 * [LcdAutoUIStruct_t::RefreshCurDisplayData :refresh data that display currently]
 * @Author Creality
 * @Time   2021-06-10
 */
void LcdAutoUIStruct_t::RefreshCurDisplayData(void)
{
    DisplayData(LcdAutoUIGetTempHotend(), DATAVAR_ADDR_HOTENDTEMP_CUR);
    DisplayData(LcdAutoUIGetTempBed(), DATAVAR_ADDR_BEDTEMP_CUR);
    DisplayData(0, DATAVAR_ADDR_HOTENDTEMP_GIVEN);
    DisplayData(0, DATAVAR_ADDR_BEDTEMP_GIVEN);
    /* display bed calibration Z axis offset at center point */
    // DisplayData((int)(100*bedCaliZOffsetCenter), DATAVAR_ADDR_CENTRAL_Z_OFFSET);
}

/**
 * [LcdAutoUIStruct_t::RefreshCurDisplayIcon :refresh icon that display currently]
 * @Author Creality
 * @Time   2021-06-16
 */
void LcdAutoUIStruct_t::RefreshCurDisplayIcon(void)
{
    SwitchIcon(SELECTED_YES, ICONVAR_ADDR_PLA_SELECTED);
    SwitchIcon(SELECTED_NO, ICONVAR_ADDR_ABS_SELECTED);
}

void LcdAutoUIStruct_t::RefreshCurLevelData(void)
{
    #if ENABLED(AUTO_BED_LEVELING_BILINEAR)
        gLcdSermoonV2UI.GetCurLevelStatusFromEEPROM();

        bool zig = true;
        int8_t inStart, inStop, inInc, showcount;
        showcount = 0;
        for(int y = 0;y < GRID_MAX_POINTS_Y;y++)
        {
            // away from origin
            if (zig) 
            {
                inStart = 0;
                inStop = GRID_MAX_POINTS_X;
                inInc = 1;
            }
            else
            {
                // towards origin
                inStart = GRID_MAX_POINTS_X - 1;
                inStop = -1;
                inInc = -1;
            }
            zig ^= true;
            for(int x = inStart;x != inStop; x += inInc)
            {
                gLcdSermoonV2UI.DisplayData(z_values[x][y]*1000, DATAVAR_ADDR_AUTO_LEVEL + (showcount)*2);
                showcount++;
            }

            if((GetLevelStatus() == AUTOUI_LEVEL_STU_FALSE)) 
            {   
                // queue.enqueue_now_P(PSTR("M420 S0"));
                queue.inject_P(PSTR("M420 S0"));
            }
            else 
            {
                // queue.enqueue_now_P(PSTR("M420 S1"));
                queue.inject_P(PSTR("M420 S1"));
            }
            // 显示Z轴补偿
            
        }
        gLcdSermoonV2UI.DisplayData((probe.offset.z*1000), DATAVAR_ADDR_Z_OFFSET);
    #endif
}

/**
 * [LcdAutoUIStruct_t::RefreshPrintTimeTotal :refresh current total printing time]
 * @Author Creality
 * @Time   2021-06-15
 * @param  _printTime [description]
 */
void LcdAutoUIStruct_t::RefreshPrintTimeTotal(void)
{
    SERIAL_ECHOLNPAIR("\r\n printingTimeTotal = ", printingTimeTotal * 100,
                      "\r\n printingTimeOnce = ", printingTimeOnce * 100,
                      "\r\n TotalRuningTime = ", TotalRuningTime * 100);
    //uint32_t lTotalTimeInt = 0;
    printingTimeTotal = ((float)TotalRuningTime)/100;
    printingTimeTotal += printingTimeOnce;
    printingTimeOnce = 0.0;
    /* two decimal fraction was set in DWIN project, need to zoom in ten times */
    dwinShow.RTS_SndData((unsigned int)(100 * printingTimeTotal), DATAVAR_ADDR_PRINTTIME_TOTAL);
    SERIAL_ECHOLNPAIR("\r\n after printingTimeTotal = ", printingTimeTotal * 100,
                      "\r\n after printingTimeOnce = ", printingTimeOnce * 100,
                      "\r\n TotalRuningTime = ", TotalRuningTime * 100);
    /* record total printing time in EEPROM */
    // lTotalTimeInt = (uint32_t)(100 * printingTimeTotal);
    // Eeprom_Write(FONT_EEPROM + EEPROM_ADDR_TPT_OFFSET, (uint8_t*)&lTotalTimeInt, EEPROM_ADDR_TPT_SIZE);
    TotalRuningTime = (uint32_t)(100 * printingTimeTotal);
    settings.save();
}

/**
 * [LcdAutoUIStruct_t::ResetPrintTimeTotal :复位总打印时间]
 * @Author Creality
 * @Time   2021-06-15
 * @param  _printTime [description]
 */
void LcdAutoUIStruct_t::ResetPrintTimeTotal(void)
{
    TotalRuningTime = 0;
    // settings.save();
}

/**
 * [LcdAutoUIStruct_t::GetPrintTimeTotal :set current total printing time]
 * @Author Creality
 * @Time   2021-06-16
 */
void LcdAutoUIStruct_t::SetPrintTimeTotal(float _totalTime)
{
    printingTimeTotal = _totalTime;
}

/**
 * [LcdAutoUIStruct_t::GetPrintTimeTotal :get current total printing time]
 * @Author Creality
 * @Time   2021-06-16
 */
float LcdAutoUIStruct_t::GetPrintTimeTotal(void)
{
    return printingTimeTotal;
}

/**
 * [LcdAutoUIStruct_t::ResetWifiStatus :复位Wifi状态，默认为开启]
 * @Author Creality
 * @Time   2021-06-16
 */
void LcdAutoUIStruct_t::ResetWifiStatus(void)
{
    gLcdSermoonV2UI.wifiCtrl.wifiState = WIFI_ENABLE;
    queue.inject_P(PSTR("M115"));
    gLcdSermoonV2UI.DisplayData(1, ICONVAR_ADDR_WIFI_SWITCH);
}

/**
 * [DevicePowerOnProgressBar :power on progress bar]
 * @Author Creality
 * @Time   2021-05-27
 */
void LcdAutoUIStruct_t::DevicePowerOnProgressBar(void)
{
    SwitchBackgroundPic(AUTOUI_STARTING);
    for(int i=0; i<=100; i++)
    {
        SwitchIcon(i, ICONVAR_ADDR_PROGRESSBAR);
        delay(30);
        watchdog_refresh();
    }
}


/**
 * [LcdAutoUIStruct_t::SDCardUpdate :refresh gcode file on DWIN screen]
 * @Author Creality
 * @Time   2021-06-04
 */
void LcdAutoUIStruct_t::SDCardUpdate(void)
{
    static bool lSDCardStatus = false;
    char lFileName[GCODE_FILE_BYTELEN] = {0};

    if(!lSDCardStatus && DiskIODriver_USBFlash::isInserted())
    {
        lSDCardStatus = DiskIODriver_USBFlash::isInserted();
        //SERIAL_ECHO("\r\n\r\n u disk inserted \r\n\r\n");
        /* to do: there exist situation that "SD init fail" */

        /* sd card init */
        card.mount();
        dwinShow.RTS_SDCardInit();
        /* display gocde file name on DWIN screen */
        for(uint16_t i=0; i<GetSDCardGcodeFileNum(); i++) 
        {
            delay(3);
            memcpy(lFileName, CardRecbuf.Cardshowfilename[i], GCODE_FILE_BYTELEN);
            DisplayText(lFileName, TEXTVAR_ADDR_FILENAME_00 + GCODE_FILE_BYTELEN * i);
        }
    }
    /* sd card removed */
    else if(lSDCardStatus && !DiskIODriver_USBFlash::isInserted())
    {
        lSDCardStatus = DiskIODriver_USBFlash::isInserted();

        //SERIAL_ECHO("\r\n\r\n u disk removed \r\n\r\n");
        /* clean all file name */
        for(uint16_t i=0; i<GCODE_FILE_NUM_MAX; i++) 
        {
            delay(3);
            for(uint32_t j=0; j<GCODE_FILE_BYTELEN; j++)
                 DisplayData(0, TEXTVAR_ADDR_FILENAME_00 + GCODE_FILE_BYTELEN * i + j);
        }
        /* clear record about SD card */
        ClearSDCardGcodeFileRecord();
        /* clear file selected highlight icon */
        ClearFileBackground();
    }
}

/**
 * [LcdAutoUIStruct_t::AutoUIToStatus :change device status]
 * @Author Creality
 * @Time   2021-06-02
 * @param  _sta       [status to change]
 */
void LcdAutoUIStruct_t::AutoUIToStatus(AutoUIDevStatus_t _sta)
{
    /* record current device status */
    devStatusLastRecord = devStatus;
    /* set status */
    devStatus = _sta;

    switch(devStatus)
    {
        case DEVSTA_INIT:
            gLcdSermoonV2UI.gcodeFileSelectedCur = VAULE_INVALIDE;
            break;

        case DEVSTA_STARTUP_FIR:
            
            break;

        case DEVSTA_IDLE:
            gLcdSermoonV2UI.SetPullOutUDiskFlag(false);
            break;

        case DEVSTA_HEATING:
            /* set preheatFinishFlags status to "heating" */
            memset(&gLcdSermoonV2UI.preheatFinishFlags, 0, sizeof(gLcdSermoonV2UI.preheatFinishFlags));
            break;

        case DEVSTA_IN_OUT_MAT:
            feedFinishedFlag = false;
            SetFlowStep(&flowStepCnt.fscInOutMat, 0);
            break;

        case DEVSTA_PRINTING:

            break;

        case DEVSTA_PRINT_PAUSE:
            if(gLcdSermoonV2UI.devStatusLastRecord != DEVSTA_IN_OUT_MAT)
                SetFlowStep(&flowStepCnt.fscPrintPause, 0);
            break;

        case DEVSTA_BED_CALI:
            bedCaliFinishedFlag = false;
            SetFlowStep(&flowStepCnt.fscBedCali, 0);
            break;
            
        case DEVSTA_ERROR:

            break;
        default:
            break;
    }
}

/**
 * [LcdAutoUIStruct_t::AutoUIGetStatus :get device current status]
 * @Author Creality
 * @Time   2021-06-09
 * @return            [device current status]
 */
AutoUIDevStatus_t LcdAutoUIStruct_t::AutoUIGetStatus(void)
{
    return devStatus;
}

/**
 * [AutoUIRecDataHandle :receive data handle]
 * @Author Creality
 * @Time   2021-05-28
 */
void LcdAutoUIStruct_t::AutoUIRecDataHandle(void)
{
    for(uint32_t i=0; i<TOUVAR_NUM; i++)
    {
        if(gAutoUITouVarResponseArray[i].touchVarAddr == dwinShow.recdat.addr)
        {
            dwinShow.recdat.addr = 0x0000;
            if(gAutoUITouVarResponseArray[i].touchVarFunc != (void*)0)
                gAutoUITouVarResponseArray[i].touchVarFunc();
        }
    }
    
}

/**
 * [AutoUIResponseToDWIN :response to DWIN touch]
 * @Author Creality
 * @Time   2021-05-28
 */
void LcdAutoUIStruct_t::AutoUIResponseToDWIN(void)
{
    if(dwinShow.RTS_RecData() > 0)
    {
        #if 0
        /* variable-address got from DWIN */
        SERIAL_ECHO("dwinShow.recdat.addr: 0x");
        SERIAL_PRINT(dwinShow.recdat.addr, HEX);
        SERIAL_ECHOLN("");
        /* variable-address got from DWIN */
        SERIAL_ECHO("dwinShow.recdat.data[0]: 0x");
        SERIAL_PRINT(dwinShow.recdat.data[0], HEX);
        SERIAL_ECHOLN("");
        #endif

        AutoUIRecDataHandle();
    }
}

/**
 * [AutoUITimerUpdate :定时处理函数，处理定时输出或]
 * @Author Creality
 * @Time   2021-07-22
 */
void LcdAutoUIStruct_t::AutoUITimerUpdate(void)
{
    static uint32_t lMs = LcdAutoUIGetTimeMs();

    if((LcdAutoUIGetTimeMs() - lMs) > 1000)
    {
        lMs = LcdAutoUIGetTimeMs();
        #ifdef HAS_MENU_RESET_WIFI
            if (gLcdSermoonV2UI.wifiCtrl.resetWifiCnt > 0) {
                OUT_WRITE(RESET_WIFI_PIN, AUTOUI_DISABLE);
            } else {
                OUT_WRITE(RESET_WIFI_PIN, AUTOUI_ENABLE);
            }
            if (gLcdSermoonV2UI.wifiCtrl.resetWifiCnt > 0) gLcdSermoonV2UI.wifiCtrl.resetWifiCnt--;
        #endif

        #if ENABLED(BLTOUCH)
        if (gLcdSermoonV2UI.zOffsetVtrl.saveFlag == true) {
            if (gLcdSermoonV2UI.zOffsetVtrl.saveParmCnt <= 0) {
                gLcdSermoonV2UI.zOffsetVtrl.saveFlag = false;
                settings.save();
            } else {
                gLcdSermoonV2UI.zOffsetVtrl.saveParmCnt --;
            }
        }
        #endif
    }
}

/**
 * [AutoUIInit :startup process]
 * @Author Creality
 * @Time   2021-05-27
 */
void LcdAutoUIStruct_t::AutoUIInit(void)
{
    /*设定背光亮度 luminance:亮度(0~100)*/
    dwinShow.RTS_SndData((unsigned short int)100<<8, 0x0082);
    
    settings.load();

    GetCurLang();

    CheckStartFirstTime();

    /* wait for DWIN LCD ready to communication */
    delay(500);

    DevicePowerOnProgressBar();

    RefreshCurLanguage();

    RefreshDevInfo();

    RefreshCurDisplayData();

    RefreshCurDisplayIcon();

    RefreshCurLevelData();
	
	RefreshCurPrintFeedrate();

    gLcdSermoonV2UI.wifiCtrl.wifiState = WIFI_DISABLE;
    RefreshOutMatReturnKey(true);

    /* startup for first time or not */
    if(GetStartupFirstTimeFlag())
    {
        /* yes, change status to 'DEVSTA_STARTUP_FIR' */
        AutoUIToStatus(DEVSTA_STARTUP_FIR);

        /* Initial value(total-printing-time stored in EEPROM) setting */
        RefreshPrintTimeTotal();

        SwitchBackgroundPic(AUTOUI_BOOTGUIDE_01);
    }  
    else
    {
        /* no, change status to 'DEVSTA_IDLE' */
        AutoUIToStatus(DEVSTA_IDLE);

        //if(IsExistPowerOffDurPrint() && IS_SD_INSERTED())
        if(GetPowerLossFlag() && IS_SD_INSERTED())
        {
            SetPowerLossFlag(false);
            AutoUIPowerOffRecoveryPW();
        }
        else
            SwitchBackgroundPic(AUTOUI_MAIN_WINDOW);
    }
// AutoUIToStatus(DEVSTA_IDLE);
// SwitchBackgroundPic(AUTOUI_MAIN_WINDOW);
    /* 给电机驱动供电 */
    OUT_WRITE(STEPPER_DRIVER_POWER_PIN, AUTOUI_ENABLE);
    GetTPTFromEEPROM();
}

/**
 * [AutoUIStartupFirstTime :logic flow of 'DEVSTA_STARTUP_FIR' status]
 * @Author Creality
 * @Time   2021-05-28
 */
void LcdAutoUIStruct_t::AutoUIStartupFirstTimeFlow(void)
{
    switch(flowStepCnt.fscStartupFir)
    {
        case 0:
            if(goHomeSta == GO_HOME_DONE)
            {
                SetStaGoingHome(GO_HOME_IDLE);

                /* disable Dynamic icon */
                gLcdSermoonV2UI.SetStaDynamicIcon(false, ICONVAR_ADDR_DYNAHOMING);

                SwitchBackgroundPic(AUTOUI_BOOTGUIDE_05);
                gLcdSermoonV2UI.SetStaDynamicIcon(true, ICONVAR_ADDR_IN_MAT);

                flowStepCnt.fscStartupFir ++;
            }
            break;

        case 1:
            /* wait for inserting SD card */
            if((IS_SD_INSERTED()) && (curPicID == AUTOUI_BOOTGUIDE_07))
            {
                SwitchBackgroundPic(AUTOUI_FILESELECT_01);

                AutoUIToStatus(DEVSTA_IDLE);

                flowStepCnt.fscStartupFir ++;
            }
            break;

        default:
            break;
    }
}

/**
 * [LcdAutoUIStruct_t::AutoUIIdleFlow :logic flow of 'DEVSTA_IDLE' status]
 * @Author Creality
 * @Time   2021-06-04
 */
void LcdAutoUIStruct_t::AutoUIIdleFlow(void)
{
    static uint32_t lMs1000 = LcdAutoUIGetTimeMs();
    static uint32_t lMs5000 = LcdAutoUIGetTimeMs();

    if((LcdAutoUIGetTimeMs() - lMs1000) > 1000)
    {
        lMs1000 = LcdAutoUIGetTimeMs();

        RefreshAllTemperature();

        RefreshCurSwiIconStatus();

        RefreshHeatingStatus();

        // RefreshSDCardGcodeFiles();
    }

    if((LcdAutoUIGetTimeMs() - lMs5000) > 5000)
    {
        lMs5000 = LcdAutoUIGetTimeMs();

        ClearEventPriFlags();

        /* 断电续打、打印中拔卡 */
        if(GetPowerLossFlag()) 
        { 
            SetPowerLossFlag(false);
            AutoUIPowerOffRecoveryPW();
        }
    }
}

/**
 * [LcdAutoUIStruct_t::AutoUIHeatFlow :logic flow of 'DEVSTA_HEATING' status]
 * @Author Creality
 * @Time   2021-07-13
 */
void LcdAutoUIStruct_t::AutoUIHeatFlow(void)
{
    static uint32_t lMs = LcdAutoUIGetTimeMs();

    if((LcdAutoUIGetTimeMs() - lMs) > 1000)
    {
        lMs = LcdAutoUIGetTimeMs();

        RefreshAllTemperature();

        RefreshCurSwiIconStatus();
		
		RefreshHeatingStatus();

        /* 断电续打、打印中拔卡 */
        if(GetPowerLossFlag()) 
        { 
            SetPowerLossFlag(false);
            AutoUIPowerOffRecoveryPW();
        }
    }
}

/**
 * [LcdAutoUIStruct_t::AutoUIInOutMatFlow :logic flow of 'DEVSTA_IN_OUT_MAT' status]
 * @Author Creality
 * @Time   2021-06-02
 */
void LcdAutoUIStruct_t::AutoUIInOutMatFlow(void)
{
    static float lTempTarHotend = 0.0;
    static uint32_t lMs1000 = LcdAutoUIGetTimeMs();

    if((LcdAutoUIGetTimeMs() - lMs1000) > 1000)
    {
        lMs1000 = LcdAutoUIGetTimeMs();
        RefreshAllTemperature();
    }
    switch(flowStepCnt.fscInOutMat)
    {
        case 0:
            if(!flowStepCnt.fscInOutMat)
                lTempTarHotend = LcdAutoUIGetTarTempHotend();
            flowStepCnt.fscInOutMat = 1;
            /* Hotend heating up to feeding-material-temperature */
            LcdAutoUISetTempHotend(FEEDING_TEMP);
            SERIAL_ECHOLNPAIR("\r\n AutoUIInOutMatFlow ,feedFinishedFlag = ", feedFinishedFlag,
                              "\r\n AutoUIInOutMatFlow ,inOutMatFlag = ", inOutMatFlag,
                              "\r\n AutoUIInOutMatFlow ,flowStepCnt.fscInOutMat = ", flowStepCnt.fscInOutMat);
            break;

        case 1:
            /* if the temperature is satisfied */
            if(LcdAutoUIGetTempHotend() >= FEEDING_TEMP)
            {
                flowStepCnt.fscInOutMat ++;
            }
            break;

        case 2:
            if(inOutMatFlag)
            {
                /* in material, start E-Axis moving */
                LcdAutoUIMoveE(FEEDING_DEF_DISTANCE, FEEDING_DEF_SPEED);
                SERIAL_ECHOLNPAIR("\r\n AutoUIInOutMatFlow ,feedFinishedFlag = ", feedFinishedFlag,
                              "\r\n AutoUIInOutMatFlow ,inOutMatFlag = ", inOutMatFlag,
                              "\r\n AutoUIInOutMatFlow ,flowStepCnt.fscInOutMat = ", flowStepCnt.fscInOutMat);
            }
            else
            {
                /* out material */
                LcdAutoUIMoveE(FEEDING_DEF_OUT_MAT_DIS1, FEEDING_DEF_OUT_MAT_SPE1);
                LcdAutoUIMoveE(FEEDING_DEF_OUT_MAT_DIS2, FEEDING_DEF_OUT_MAT_SPE2);
                SERIAL_ECHOLNPAIR("\r\n AutoUIInOutMatFlow ,feedFinishedFlag = ", feedFinishedFlag,
                              "\r\n AutoUIInOutMatFlow ,inOutMatFlag = ", inOutMatFlag,
                              "\r\n AutoUIInOutMatFlow ,flowStepCnt.fscInOutMat = ", flowStepCnt.fscInOutMat);
                SwitchBackgroundPic(AUTOUI_OUTMAT_02);
            }
            flowStepCnt.fscInOutMat ++;
            break;

        case 3:
            if(feedFinishedFlag)
            {
                SERIAL_ECHOLNPAIR("\r\n AutoUIInOutMatFlow ,feedFinishedFlag = ", feedFinishedFlag,
                              "\r\n AutoUIInOutMatFlow ,inOutMatFlag = ", inOutMatFlag,
                              "\r\n AutoUIInOutMatFlow ,flowStepCnt.fscInOutMat = ", flowStepCnt.fscInOutMat);
                feedFinishedFlag = false;
                AutoUIToStatus(devStatusLastRecord);
                /* stop All Axis moving */
                quickstop_stepper();
                /* recovery the E-Axis position */
                if(AutoUIGetStatus() == DEVSTA_PRINT_PAUSE)
                    LcdAutoUISetECmd(pauseStaRecord.posPauseBefore.e + PRINT_RECOVER_EXTERA_E_POS);
                /* recovery hotend temperature */
                LcdAutoUISetTempHotend(lTempTarHotend);
                /* clear hotend temperature record */
                lTempTarHotend = 0.0;

                SetFlowStep(&flowStepCnt.fscInOutMat, 0);
            }
            break;

        default:
            break;
    }
}

/**
 * [LcdAutoUIStruct_t::AutoUIPrintingFlow :logic flow of 'DEVSTA_PRINTING' status]
 * @Author Creality
 * @Time   2021-06-09
 */
void LcdAutoUIStruct_t::AutoUIPrintingFlow(void)
{
    static uint32_t lMs = LcdAutoUIGetTimeMs();

    if((LcdAutoUIGetTimeMs() - lMs) > 1000)
    {
        lMs = LcdAutoUIGetTimeMs();

        RefreshAllTemperature();

        RefreshCurPrintProgress();

        RefreshCurPrintTime();

        RefreshCurSwiIconStatus();

        RefreshHeatingStatus();

        UdiskCheckProcess();

        #if ENABLE_MATERIAL_CHECK
            if(GetStaGoingHome() != GO_HOME_DOING)
                MaterialCheckProcess();
        #endif

        #if ENABLE_DOOR_OPEN_CHECK
            if(enableSwitches.swiDoorPause)
                if(GetStaGoingHome() != GO_HOME_DOING)
                    DoorOpenPauseProcess();
        #endif

        AutoUIPrintFinished();
    }
}

/**
 * [LcdAutoUIStruct_t::AutoUIPrintPauseFlow :logic flow of 'DEVSTA_PRINT_PAUSE' status]
 * @Author Creality
 * @Time   2021-06-09
 */
void LcdAutoUIStruct_t::AutoUIPrintPauseFlow(void)
{
    /* record the count of no-command-in-queue */
    static uint8_t lNoCmdInQueueCnt = 0;
    /* type of printing pause, 0:Manual pause, 1:lack of material, 2:door open */
    static uint8_t lPauseType = 0;

   

    switch(flowStepCnt.fscPrintPause)
    {
        case 0:
            /* device is going home */
            if(GetStaGoingHome() == GO_HOME_DOING)
                break;

             /* material check */
            #if ENABLE_MATERIAL_CHECK
            if(!IsExistMaterial())
                lPauseType = 1;
            #endif

            /* door open check */
            #if ENABLE_DOOR_OPEN_CHECK
            if(enableSwitches.swiDoorPause && IsDoorOpen())
                lPauseType = 2;
            #endif

            if(!planner.has_blocks_queued())
            {
                /* be sure that there is no commands in queue */
                if(lNoCmdInQueueCnt < 5)
                {
                    lNoCmdInQueueCnt ++;
                    break;
                }
                else
                {
                    lNoCmdInQueueCnt = 0;
                }
                /* 先退料2mm */
                LcdAutoUIMoveE(-2, FEEDING_DEF_OUT_MAT_SPE1); 
                
                switch(lPauseType)
                {
                    case 0:
						/* block to get to pause position */
	                	// LcdAutoUIMoveZ((float)(current_position.z + PAUSE_POS_Z_HEIGHT_DIF), AXIS_MOVE_ABSO);
                        LcdAutoUIMoveZBlock((float)(current_position.z + PAUSE_POS_Z_HEIGHT_DIF));
	                	// LcdAutoUIMoveX(0, AXIS_MOVE_ABSO);
                    	// LcdAutoUIMoveY(Y_BED_SIZE, AXIS_MOVE_ABSO);
                        LcdAutoUIMoveXYBlock(0, Y_BED_SIZE);
                    	break;

                    /* material check */
                    #if ENABLE_MATERIAL_CHECK
                    case 1:
                        LcdAutoUIMoveY(0, AXIS_MOVE_ABSO);
                        break;
                    #endif

                    /* door open check */
                    #if ENABLE_DOOR_OPEN_CHECK
                    case 2:
                        if(enableSwitches.swiDoorPause)
                        {
                        	LcdAutoUIMoveY(Y_BED_SIZE, AXIS_MOVE_ABSO);
                        }
                        break;
                    #endif

                    default:
                        break;
                }
                flowStepCnt.fscPrintPause ++;
            }
            break;
        case 1:
            uint32_t lMs = LcdAutoUIGetTimeMs();
            if((lPauseType == 1) && (planner.has_blocks_queued()))
                break;

            switch(lPauseType)
            {
                case 0:
                    SwitchBackgroundPic(AUTOUI_PRINTPAUSE);
                    if((LcdAutoUIGetTimeMs() - lMs) > 1000)
                    {
                        lMs = LcdAutoUIGetTimeMs();
                        /* 打印中拔卡,走暂停流程 */
                        if(gLcdSermoonV2UI.GetPullOutUDiskFlag() && GetPowerLossFlag() && IS_SD_INSERTED())
                        {
                            //gLcdSermoonV2UI.SetPullOutUDiskFlag(false);
                            // SetPowerLossFlag(false);
                            SetPullOutUDiskFlag(false);
                            AutoUIPowerOffRecoveryPW();
                        }       
                    }
                    break;

                /* material check */
                #if ENABLE_MATERIAL_CHECK
                case 1:
                    //if (planner.has_blocks_queued())    break;

                    gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_LACKMATPW);
                    /* start close-heater-timer */
                    CloHeaTmrStart(CLOHEATMR_TIME);
                    /* out material */
                    // LcdAutoUIMoveE(FEEDING_DEF_OUT_MAT_DIS1, FEEDING_DEF_OUT_MAT_SPE1);
                    // LcdAutoUIMoveE(FEEDING_DEF_OUT_MAT_DIS2, FEEDING_DEF_OUT_MAT_SPE2);
                    break;
                    flowStepCnt.fscPrintPause ++;
                #endif

                /* door open check */
                #if ENABLE_DOOR_OPEN_CHECK
                case 2:
                    if(enableSwitches.swiDoorPause)
                    {
                        gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_PRINTDOOROPEN);
                        gLcdSermoonV2UI.SwitchIcon(VAULE_INVALIDE_8BIT, ICONVAR_ADDR_DOOR_OPEN_TIP);
                    }
                    flowStepCnt.fscPrintPause ++;
                    break;
                #endif

                default:
                    break;
            }
            lPauseType = 0;
            flowStepCnt.fscPrintPause ++;
            break;

        // default:
        //     break;
    }
}

/**
 * [LcdAutoUIStruct_t::AutoUIBedCaliFlow :logic flow of 'DEVSTA_BED_CALI' status]
 * @Author Creality
 * @Time   2021-06-07
 */
void LcdAutoUIStruct_t::AutoUIBedCaliFlow(void)
{
    switch(flowStepCnt.fscBedCali)
    {
        case 0:
            queue.enqueue_now_P(PSTR("M420 S0"));
            isBedLeveling = true;
            /* set go-home status - 'GO_HOME_IDLE' */
            SetStaGoingHome(GO_HOME_IDLE);
            /* switch picture to wait for going home */
            gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_GOINGHOME);
            /* 使用下限位时，两坐标的差值 */
            #if ENABLED(BLTOUCH_AND_Z_LIMIT)
                if (DEBUGGING(LEVELING)) {
                    SERIAL_ECHOLNPAIR("\r\n bed leveling start zCoordinateOffset * 100 = ", GetzCoordinateOffset());
                }
            #endif
            /* start bed calibration */
            #ifdef BLTOUCH
                queue.enqueue_now_P(PSTR("G28"));
            #else
                queue.inject_P(PSTR("G29 S1"));
            #endif
            
            flowStepCnt.fscBedCali ++;

            break;

        case 1:
            /* wait for going home */
            if(goHomeSta == GO_HOME_DONE)
            {
                /* set go-home status - 'GO_HOME_IDLE' */
                SetStaGoingHome(GO_HOME_IDLE);
                /* 启用了bltouch+下限位 */
                #if ENABLED(BLTOUCH_AND_Z_LIMIT)
                    destination.set(safe_homing_xy, current_position.z);
                    TERN_(1, destination -= probe.offset_xy);
                    if (position_is_reachable(destination)) {
                        do_blocking_move_to_xy(destination);  // 把bltouch移动至中间
                    }
                    else {
                        SERIAL_ECHO_MSG(STR_ZPROBE_OUT_SER);
                    }

                    homeaxis_bl(Z_AXIS);
                #endif

                /* get to the center(x, y), block */
                LcdAutoUIMoveXYBlock((float)(X_BED_SIZE/2), (float)(Y_BED_SIZE/2));
                /* get to the base height, block */
                LcdAutoUIMoveZBlock(0.0);

                #ifdef BLTOUCH
                    SwitchBackgroundPic(AUTOUI_LEVELINGMODE);
                #else
                    SwitchBackgroundPic(AUTOUI_BED_CALI);
                #endif

                pointCntCaliCur = 0;
                SwitchIcon(pointCntCaliCur++, ICONVAR_ADDR_BEDCALI_CURPOINT);

                /* init display of Z-offset and Z-height */
                gLcdSermoonV2UI.DisplayData((int)(100*current_position.z), DATAVAR_ADDR_ZOFFSET);
                gLcdSermoonV2UI.DisplayData((int)(100*(current_position.z + Z_MAX_POS)), DATAVAR_ADDR_ZHEIGHT);
                gLcdSermoonV2UI.DisplayData((int)(1000 * probe.offset.z), DATAVAR_ADDR_Z_OFFSET);

                flowStepCnt.fscBedCali ++;
            }
            break;

        case 2:
            if(bedCaliFinishedFlag)
            {
                bedCaliFinishedFlag = false;

                SwitchBackgroundPic(AUTOUI_PRINTSETTING);

                AutoUIToStatus(DEVSTA_IDLE);

                SetFlowStep(&flowStepCnt.fscBedCali, 0);

                if((GetLevelStatus() == AUTOUI_LEVEL_STU_FALSE))  
                    queue.inject_P(PSTR("M420 S0 V2"));
                else 
                    queue.inject_P(PSTR("M420 S1 V2"));
            }
            break;

        default:
            break;
    }
}

/**
 * [ShowLevelingProgress :显示调平进度]
 * @Author Creality
 * @Time   2021-07-03
 */
void LcdAutoUIStruct_t::ShowLevelingProgress(xy_int8_t meshCount)
{
#ifdef BLTOUCH
    static uint16_t showcount = 0;
    if(meshCount.x == 0 && meshCount.y == 0) showcount = 0;
    if(((showcount++) < GRID_MAX_POINTS_X * GRID_MAX_POINTS_Y)/* && waitway == 3*/)
    {
        gLcdSermoonV2UI.DisplayData(showcount, ICONVAR_ADDR_AUTO_LEVEL_PROCESS);
    }    
    gLcdSermoonV2UI.DisplayData(z_values[meshCount.x][meshCount.y]*1000, DATAVAR_ADDR_AUTO_LEVEL + (3 - meshCount.x)*2 + (meshCount.y)*8);
#endif
}

/**
 * [LevelingCompleted :自动调平完成处理]
 * @Author Creality
 * @Time   2021-07-03
 */
void LcdAutoUIStruct_t::LevelingCompleted(void)
{
#ifdef BLTOUCH
    gLcdSermoonV2UI.SwitchBackgroundPic(AUTOUI_LEVELINGMODE);
    settings.save();
#endif
}
/**
 * [AutoUIMainProcess :AutoUI main process]
 * @Author Creality
 * @Time   2021-05-28
 */
uint32_t time = 0;
void LcdAutoUIStruct_t::AutoUIMainProcess(void)
{
    /* sd card status check and refresh gcode file name */
    SDCardUpdate();
    /* response to DWIN-touch */
    AutoUIResponseToDWIN();
    /* 定时处理函数 */
    AutoUITimerUpdate();

    switch(devStatus)
    {
        case DEVSTA_INIT:
            AutoUIInit();
            break;

        case DEVSTA_STARTUP_FIR:
            AutoUIStartupFirstTimeFlow();
            break;

        case DEVSTA_IDLE:
            AutoUIIdleFlow();
            break;

        case DEVSTA_HEATING:
            AutoUIHeatFlow();
            break;

        case DEVSTA_IN_OUT_MAT:
            AutoUIInOutMatFlow();
            break;

        case DEVSTA_PRINTING:
            AutoUIPrintingFlow();
            break;

        case DEVSTA_PRINT_PAUSE:
            AutoUIPrintPauseFlow();
            break;

        case DEVSTA_BED_CALI:
            AutoUIBedCaliFlow();
            break;

        case DEVSTA_ERROR:

            break;
        default:
            break;
    }
}
