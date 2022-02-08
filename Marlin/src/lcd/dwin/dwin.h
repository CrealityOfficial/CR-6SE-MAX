#ifndef	DWIN_H
#define	DWIN_H

#include "string.h"
#include <arduino.h>

#include "../../inc/MarlinConfig.h"
#include "../../module/temperature.h"

#define	RegAddr_W	0x80
#define	RegAddr_R	0x81
#define	VarAddr_W	0x82
#define	VarAddr_R	0x83
#define	ExchangePageBase    ((unsigned long)0x5A010000)
#define	StartSoundSet       ((unsigned long)0x060480A0)
#define	ExchangepageAddr	0x0084

#define	FONT_EEPROM      0
#define BOX_LED_EEPROM   1        //机箱风扇和LED的状态已经不需要记忆
#define BOX_FAN_EEPROM   2
#define BED_TARGET_TEMP_EEPROM 3

#define FHONE   (0x5A)
#define FHTWO   (0xA5)
#define FHLENG  (0x06)
#define TEXTBYTELEN     18
#define MaxFileNumber   20
#define	FileNum	MaxFileNumber
#define	FileNameLen	TEXTBYTELEN

#define	SDFILE_ADDR			0x200A

#define SizeofDatabuf		300

typedef struct DataBuf
{
    unsigned char len;  
    unsigned char head[2];
    unsigned char command;
    unsigned long addr;
    unsigned long bytelen;
    unsigned short data[256];
    unsigned char reserv[4];
} DB;

typedef struct CardRecord
{
    int recordcount;
    int Filesum;
    unsigned long addr[FileNum];
    char Cardshowfilename[FileNum][FileNameLen];
    char Cardfilename[FileNum][FileNameLen];
}CRec;

#define JPG_PREVIEW_SIZE    2300  //jpg预览图 图片字节数
#define JPG_COMPLETE_SIZE   2300  //jpg完整图 图片字节数
#define JPG_BYTES_PER_FRAME 240   //每一帧发送的字节数（图片数据）
#define JPG_WORD_PER_FRAME  120   //每一帧发送的字数（图片数据）
enum {
  JPG_PREVIEW,  // 预览图
  JPG_COMPLETE, // 完整图
}JpgDispMode;


extern CRec CardRecbuf;

class DWIN_SHOW_t {
  public:
    DWIN_SHOW_t();
    void RTS_Init(void);
    int RTS_RecData();
    bool RTS_SD_Detected(void);
    void RTS_SDCardInit(void);
    void RTS_SDCardUpate(void);
    void RTS_SndData(void);
    void RTS_SndData(const String &, unsigned long, unsigned char = VarAddr_W);
    void RTS_SndData(const char[], unsigned long, unsigned char = VarAddr_W);
    void RTS_SndData(char, unsigned long, unsigned char = VarAddr_W);
    void RTS_SndData(unsigned char*, unsigned long, unsigned char = VarAddr_W);
    void RTS_SndData(int, unsigned long, unsigned char = VarAddr_W);
    void RTS_SndData(float, unsigned long, unsigned char = VarAddr_W);
    void RTS_SndData(unsigned int,unsigned long, unsigned char = VarAddr_W);
    void RTS_SndData(long,unsigned long, unsigned char = VarAddr_W);
    void RTS_SndData(unsigned long,unsigned long, unsigned char = VarAddr_W);
    void RTS_SendJpegDate(const char *str, unsigned long addr, unsigned char cmd/*= VarAddr_W*/);
    void DWIN_SendJpegDate(char *jpeg, unsigned long size, unsigned long jpgAddr);
    void DWIN_DisplayJpeg(unsigned long, unsigned long);

    DB recdat;
    DB snddat;
    private:
    unsigned char databuf[SizeofDatabuf];
  };

extern DWIN_SHOW_t dwinShow;
#endif// RTS_H
