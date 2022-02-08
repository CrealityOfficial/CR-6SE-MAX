
#include <wstring.h>
#include <stdio.h>
#include <string.h>
#include <Arduino.h>
#include "DWIN.h"
// #include <libmaple/usart.h>

#include "../../MarlinCore.h"
#include "../../inc/MarlinConfig.h"
#include "../../module/settings.h"
#include "../../core/serial.h"
#include "../../core/macros.h"

#include "../fontutils.h"
#include "../../sd/cardreader.h"
#include "../../feature/powerloss.h"
#include "../../feature/babystep.h"
#include "../../module/temperature.h"
#include "../../module/printcounter.h"
#include "../../module/motion.h"
#include "../../module/planner.h"
#include "../../module/stepper/indirection.h"
#include "../../gcode/queue.h"
#include "../../gcode/gcode.h"
#include "../../module/probe.h"

#include "../../../Version.h"
#include "../../../Configuration.h"
#include "../../feature/bedlevel/bedlevel.h"
#include "../../module/planner.h"

#ifdef USB_DISK_SUPPORT
  #include "../../sd/usb_disk/Sd2Card_UDisk.h"
#endif

#if ENABLED(EEPROM_SETTINGS)
  #include "../../HAL/shared/eeprom_api.h"
  #include "../../module/settings.h"
#endif

#ifdef LCD_SERIAL_PORT
  #define LCDSERIAL LCD_SERIAL
#elif SERIAL_PORT_2
  #define LCDSERIAL LCDSERIAL
#endif
// LCDSERIAL --> LCDSERIAL
//#define DWIN_SHOW_t
//#if ENABLED(DWIN_SHOW_t)
  DWIN_SHOW_t dwinShow;
 
  CRec CardRecbuf;

  int recnum = 0;
 

  bool PrintMode = true;
  bool PrintModeChange = true;

  // represents to update file list
  bool CardUpdate = false;

  extern CardReader card;

  char CardCheckStatus[2] = {0};

  // represents SD-card status, true means SD is available, false means opposite.
  bool RTS_lcd_sd_status;



  

  DWIN_SHOW_t::DWIN_SHOW_t()
  {
    recdat.head[0] = snddat.head[0] = FHONE;
    recdat.head[1] = snddat.head[1] = FHTWO;
    memset(databuf,0, sizeof(databuf));
  }

  void DWIN_SHOW_t::RTS_SDCardInit(void)
  {
    if(RTS_SD_Detected()) {
      #ifndef USB_DISK_SUPPORT && USB_FLASH_DRIVE_SUPPORT
        card.mount();
      #endif

      if(CardReader::flag.mounted) {
        //SD卡挂载成功
        SERIAL_ECHOLN("***sd card mount success***");

        uint16_t fileCnt = card.get_num_Files();
        card.getWorkDirName();
        if (card.filename[0] != '/') {
          card.cdup();
        }

        // Clear filename list
        // memset(CardRecbuf.Cardshowfilename, 0, FileNum * FileNameLen);

        int addrnum =0;
        int num = 0;
        for (uint16_t i = 0; i < fileCnt && i < MaxFileNumber + addrnum; i++) 
        {
          card.selectFileByIndex(fileCnt-1-i);
          char *pointFilename = card.longFilename;//longFilename这个数组存放的是真实的文件名
          int filenamelen = strlen(card.longFilename);
          int j = 1;
          while((strncmp(&pointFilename[j],".gcode",6) && strncmp(&pointFilename[j],".GCODE",6)) && (j++) < filenamelen);
          if(j >= filenamelen)
          {
            addrnum++;
            continue;
          }
          if(j >= TEXTBYTELEN)	
          {
            strncpy(&card.longFilename[TEXTBYTELEN -3],"..",2);
            card.longFilename[TEXTBYTELEN-1] = '\0';
            j = TEXTBYTELEN-1;
          }
          //delay(3);
          strncpy(CardRecbuf.Cardshowfilename[num], card.longFilename,j);
          strcpy(CardRecbuf.Cardfilename[num], card.filename);
          CardRecbuf.addr[num] = SDFILE_ADDR +num*10;
          // RTS_SndData(CardRecbuf.Cardshowfilename[num],CardRecbuf.addr[num]);
          CardRecbuf.Filesum = (++num);
          // RTS_SndData(1, FilenameIcon + CardRecbuf.Filesum);
        }
        // if(LanguageRecbuf != 0)
        // {
        //   // 0 for Ready
        //   RTS_SndData(0,IconPrintstatus);
        // }
        // else
        // {
        //   RTS_SndData(0 + CEIconGrap,IconPrintstatus);
        // }
        RTS_lcd_sd_status = true;
        return;
      }
    }
    //未检测到SD卡，或者挂载失败
    SERIAL_ECHOLN("***sd not detected, or init failed***");
    // if(LanguageRecbuf != 0)
    // {
    //   // 6 for Card Removed
    //   RTS_SndData(6, IconPrintstatus);
    // }
    // else
    // {
    //   RTS_SndData(6 + CEIconGrap, IconPrintstatus);
    // }
  }

  bool DWIN_SHOW_t::RTS_SD_Detected(void)
  {
    static bool last, state, flag_stable;
    static uint32_t stable_point_time;

    #ifdef USB_DISK_SUPPORT
      return Sd2Card::isInserted();
    #else
    return DiskIODriver_USBFlash::isInserted();
      bool tmp = IS_SD_INSERTED();

      if(tmp != last)
        flag_stable = false;
      else {
        //两次检测到引脚状态相同,标记引脚稳定
        if(!flag_stable) {
          flag_stable = true;
          stable_point_time = millis();
        }
      }

      if(flag_stable) {
        if(millis() - stable_point_time > 30) state = tmp;
      }

      last = tmp;

      return state;
    #endif
  }

  void DWIN_SHOW_t::RTS_SDCardUpate(void)
  {	
    const bool sd_status = RTS_SD_Detected();
    if (sd_status != RTS_lcd_sd_status)
    {
      if (sd_status)
      {
        SERIAL_ECHOLN("sd_status changed, sd_status = yes");
        //safe_delay(100);
        RTS_SDCardInit();
      }
      else
      {
        SERIAL_ECHOLN("sd_status changed, sd_status = no");
        card.release();
        // heating or printing
        if(CardCheckStatus[0] == 1)
        {
					card.flag.abort_sd_printing = 1;
					wait_for_heatup = false;
          // cancel to check card during printing the gcode file 
          CardCheckStatus[0] = 0;
          // back main page
          // if(LanguageRecbuf != 0)
          // {
          //   // exchange to 1 page
          //   RTS_SndData(ExchangePageBase + 1, ExchangepageAddr);
          // }
          // else
          // {
          //   // exchange to 45 page
          //   RTS_SndData(ExchangePageBase + 45, ExchangepageAddr);
          // }
        }

        // if(LanguageRecbuf != 0)
        // {
        //   // 6 for Card Removed
        //   RTS_SndData(6,IconPrintstatus);
        // }
        // else
        // {
        //   RTS_SndData(6+CEIconGrap,IconPrintstatus);
        // }
        for(int i = 0;i < CardRecbuf.Filesum;i++)
        {
          for(int j = 0;j < 10;j++)
          RTS_SndData(0,CardRecbuf.addr[i]+j);
          // RTS_SndData(4,FilenameIcon+1+i);
          // white
          // RTS_SndData((unsigned long)0xFFFF,FilenameNature + (i+1)*16);
        }

        for(int j = 0;j < 10;j++)	
        {
          // clean screen.
          // RTS_SndData(0,Printfilename+j);
          // clean filename
          // RTS_SndData(0,Choosefilename+j);
        }
        for(int j = 0;j < 8;j++)
        {
          // RTS_SndData(0,FilenameCount+j);
        }
        // clean filename Icon
        for(int j = 1;j <= 20;j++)
        {
          // RTS_SndData(10,FilenameIcon+j);
          // RTS_SndData(10,FilenameIcon1+j);
        }
        memset(&CardRecbuf,0,sizeof(CardRecbuf));
      }
      RTS_lcd_sd_status = sd_status;
    }
    

    // represents to update file list
    if (CardUpdate && RTS_lcd_sd_status && RTS_SD_Detected())
    {
      SERIAL_ECHOLN("update card files");

      // clean filename
      for(int j = 0;j < 10;j++)
      {
        // RTS_SndData(0,Choosefilename+j);
      }
      for(int j = 0;j < 8;j++)
      {
        // RTS_SndData(0,FilenameCount+j);
      }
      for (uint16_t i = 0; i < CardRecbuf.Filesum ; i++) 
      {
        //delay(3);
        delay(1);
        RTS_SndData(CardRecbuf.Cardshowfilename[i],CardRecbuf.addr[i]);
        // RTS_SndData(1,FilenameIcon+1+i);
        // RTS_SndData((unsigned long)0xFFFF,FilenameNature + (i+1)*16);		// white
        // RTS_SndData(10,FilenameIcon1+1+i);
      }
      CardUpdate = false;
    }
  }




  int DWIN_SHOW_t::RTS_RecData()
  {
    while(LCDSERIAL.available() > 0 && (recnum < SizeofDatabuf))
    {
      delay(1);
      databuf[recnum] = LCDSERIAL.read();
        // SERIAL_ECHOLNPAIR("\r\ndatabuf: ", databuf[recnum]);//用于测试，打印出触摸屏反馈的字节数据，调试触摸屏响应问题
      if(databuf[0] == FHONE)
      {
        recnum++;
      }
      else if(databuf[0] == FHTWO)
      {
        databuf[0] = FHONE;
        databuf[1] = FHTWO;
        recnum += 2;
      }
      else if(databuf[0] == FHLENG)
      {
        databuf[0] = FHONE;
        databuf[1] = FHTWO;
        databuf[2] = FHLENG;
        recnum += 3;
      }
      else if(databuf[0] == VarAddr_R)
      {
        databuf[0] = FHONE;
        databuf[1] = FHTWO;
        databuf[2] = FHLENG;
        databuf[3] = VarAddr_R;
        recnum += 4;
      }
      else
      {
        recnum = 0;
      }
    }

    // receive nothing  	
    if(recnum < 1)
    {
      return -1;
    }
    else  if((recdat.head[0] == databuf[0]) && (recdat.head[1] == databuf[1]) && recnum > 2)
    {
      recdat.len = databuf[2];
      recdat.command = databuf[3];
      if(recdat.len == 0x03 && (recdat.command == 0x82 || recdat.command == 0x80) && (databuf[4] == 0x4F) && (databuf[5] == 0x4B))  //response for writing byte
      {   
        memset(databuf,0, sizeof(databuf));
        recnum = 0;
        return -1;
      }
      else if(recdat.command == 0x83)
      {
        // response for reading the data from the variate
        recdat.addr = databuf[4];
        recdat.addr = (recdat.addr << 8 ) | databuf[5];
        recdat.bytelen = databuf[6];
        for(unsigned int i = 0;i < recdat.bytelen;i+=2)
        {
          recdat.data[i/2]= databuf[7+i];
          recdat.data[i/2]= (recdat.data[i/2] << 8 )| databuf[8+i];
        }
      }
      else if(recdat.command == 0x81)
      {
        // response for reading the page from the register
        recdat.addr = databuf[4];
        recdat.bytelen = databuf[5];
        for(unsigned int i = 0;i < recdat.bytelen;i++)
        {
          recdat.data[i]= databuf[6+i];
          // recdat.data[i]= (recdat.data[i] << 8 )| databuf[7+i];
        }
      }
    }
    else
    {
      memset(databuf,0, sizeof(databuf));
      recnum = 0;
      // receive the wrong data
      return -1;
    }
    memset(databuf,0, sizeof(databuf));
    recnum = 0;
    return 2;
  }

  static inline void dwin_uart_write(unsigned char *buf, int len) {
    LOOP_L_N(n, len) { LCDSERIAL.write(buf[n]); }
  }

  void DWIN_SHOW_t::RTS_SndData(void)
  {
    if((snddat.head[0] == FHONE) && (snddat.head[1] == FHTWO) && snddat.len >= 3)
    {
      databuf[0] = snddat.head[0];
      databuf[1] = snddat.head[1];
      databuf[2] = snddat.len;
      databuf[3] = snddat.command;
      // to write data to the register
      if(snddat.command ==0x80)
      {
        databuf[4] = snddat.addr;
        for(int i =0;i <(snddat.len - 2);i++)
        {
          databuf[5+i] = snddat.data[i];
        }
      }
      else if(snddat.len == 3 && (snddat.command ==0x81))
      {
        // to read data from the register
        databuf[4] = snddat.addr;
        databuf[5] = snddat.bytelen;
      }
      else if(snddat.command ==0x82)
      {
        // to write data to the variate
        databuf[4] = snddat.addr >> 8;
        databuf[5] = snddat.addr & 0xFF;
        for(int i =0;i <(snddat.len - 3);i += 2)
        {
          databuf[6 + i] = snddat.data[i/2] >> 8;
          databuf[7 + i] = snddat.data[i/2] & 0xFF;
        }
      }
      else if(snddat.len == 4 && (snddat.command ==0x83))
      {
        // to read data from the variate
        databuf[4] = snddat.addr >> 8;
        databuf[5] = snddat.addr & 0xFF;
        databuf[6] = snddat.bytelen;
      }
      // usart_tx(LCDSERIAL.c_dev(), databuf, snddat.len + 3);
      // LCDSERIAL.flush();
      // for(int i = 0;i < (snddat.len + 3);i++)
      // {
      //   LCDSERIAL.write(databuf[i]);
      //   delayMicroseconds(1);
      // }

      dwin_uart_write(databuf, snddat.len + 3);

      memset(&snddat,0,sizeof(snddat));
      memset(databuf,0, sizeof(databuf));
      snddat.head[0] = FHONE;
      snddat.head[1] = FHTWO;
    }
  }

  void DWIN_SHOW_t::RTS_SndData(const String &s, unsigned long addr, unsigned char cmd /*= VarAddr_W*/)
  {
    if(s.length() < 1)
    {
      return;
    }
    RTS_SndData(s.c_str(), addr, cmd);
  }

  void DWIN_SHOW_t::RTS_SndData(const char *str, unsigned long addr, unsigned char cmd/*= VarAddr_W*/)
  {
    int len = strlen(str);
    if( len > 0)
    {
      databuf[0] = FHONE;
      databuf[1] = FHTWO;
      databuf[2] = 3+len;
      databuf[3] = cmd;
      databuf[4] = addr >> 8;
      databuf[5] = addr & 0x00FF;
      for(int i =0;i <len ;i++)
      {
        databuf[6 + i] = str[i];
      }

      dwin_uart_write(databuf, len + 6);

      memset(databuf,0, sizeof(databuf));
    }
  }

  void DWIN_SHOW_t::RTS_SndData(char c, unsigned long addr, unsigned char cmd/*= VarAddr_W*/)
  {
    snddat.command = cmd;
    snddat.addr = addr;
    snddat.data[0] = (unsigned long)c;
    snddat.data[0] = snddat.data[0] << 8;
    snddat.len = 5;
    RTS_SndData();
  }

  void DWIN_SHOW_t::RTS_SndData(unsigned char* str, unsigned long addr, unsigned char cmd){RTS_SndData((char *)str, addr, cmd);}

  void DWIN_SHOW_t::RTS_SndData(int n, unsigned long addr, unsigned char cmd/*= VarAddr_W*/)
  {
    if(cmd == VarAddr_W )
    {
      if(n > 0xFFFF)
      {
        snddat.data[0] = n >> 16;
        snddat.data[1] = n & 0xFFFF;
        snddat.len = 7;
      }
      else
      {
        snddat.data[0] = n;
        snddat.len = 5;
      }
    }
    else if(cmd == RegAddr_W)
    {
      snddat.data[0] = n;
      snddat.len = 3;
    }
    else if(cmd == VarAddr_R)
    {
      snddat.bytelen = n;
      snddat.len = 4;
    }
    snddat.command = cmd;
    snddat.addr = addr;
    RTS_SndData();
  }

  void DWIN_SHOW_t::RTS_SndData(unsigned int n, unsigned long addr, unsigned char cmd){ RTS_SndData((int)n, addr, cmd); }

  void DWIN_SHOW_t::RTS_SndData(float n, unsigned long addr, unsigned char cmd){ RTS_SndData((int)n, addr, cmd); }

  void DWIN_SHOW_t::RTS_SndData(long n, unsigned long addr, unsigned char cmd){ RTS_SndData((unsigned long)n, addr, cmd); }

  void DWIN_SHOW_t::RTS_SndData(unsigned long n, unsigned long addr, unsigned char cmd/*= VarAddr_W*/)
  {
    if(cmd == VarAddr_W )
    {
      if(n > 0xFFFF)
      {
        snddat.data[0] = n >> 16;
        snddat.data[1] = n & 0xFFFF;
        snddat.len = 7;
      }
      else
      {
        snddat.data[0] = n;
        snddat.len = 5;
      }
    }
    else if(cmd == VarAddr_R)
    {
      snddat.bytelen = n;
      snddat.len = 4;
    }
    snddat.command = cmd;
    snddat.addr = addr;
    RTS_SndData();
  }


  // dwin模块初始化
  void DWIN_SHOW_t::RTS_Init(void)
  {
    LCDSERIAL.begin(BAUDRATE_LCD);
  }
//#endif
  void DWIN_SHOW_t::RTS_SendJpegDate(const char *str, unsigned long addr, unsigned char cmd/*= VarAddr_W*/)
  {
    int len = JPG_BYTES_PER_FRAME;//strlen(str);
    if( len > 0)
    {
      databuf[0] = FHONE;
      databuf[1] = FHTWO;
      databuf[2] = 3+len;
      databuf[3] = cmd;
      databuf[4] = addr >> 8;
      databuf[5] = addr & 0x00FF;
      for(int i =0;i <len ;i++)
      {
        databuf[6 + i] = str[i];
      }

      dwin_uart_write(databuf, len + 6);

      memset(databuf,0, sizeof(databuf));
    }
  }

  void DWIN_SHOW_t::DWIN_SendJpegDate(char *jpeg, unsigned long size, unsigned long jpgAddr)
  {
    int jpgSize = size;

    //SERIAL_ECHOPAIR("\r\nlen = ", len);
    char buf[JPG_BYTES_PER_FRAME];
    int i,j;
    // 开始发送数据，每帧240字节。
    for (i = 0; i < jpgSize / JPG_BYTES_PER_FRAME; i++) {
      //SERIAL_ECHOPAIR("\r\nnum = ", i*JPG_BYTES_PER_FRAME);
      memset(buf, 0, JPG_BYTES_PER_FRAME);
      memcpy(buf, &jpeg[i * JPG_BYTES_PER_FRAME], JPG_BYTES_PER_FRAME);
      // for (j = 0; j < JPG_BYTES_PER_FRAME; j++) {
      //     SERIAL_ECHOPAIR(" ", j,
      //                     " = ", buf[j]);
      //     if ((j+1) % 8 == 0) SERIAL_ECHO("\r\n");
      // }
      watchdog_refresh();
      // RTS_SndDataTest(buf, (0x8000 + (0x78 * i)), 0x82);
      RTS_SendJpegDate(buf, (jpgAddr + (JPG_WORD_PER_FRAME * i)), 0x82);
    }
    memset(buf, 0, JPG_BYTES_PER_FRAME);
    memcpy(buf, &jpeg[i * JPG_BYTES_PER_FRAME], (jpgSize - i * JPG_BYTES_PER_FRAME));
    RTS_SendJpegDate(buf, (jpgAddr + (JPG_WORD_PER_FRAME * i)), 0x82);
    // for (j = 0; j < JPG_BYTES_PER_FRAME; j++) {
    //     SERIAL_ECHOPAIR(" ", j,
    //                     " = ", buf[j]);
    //     if ((j+1) % 8 == 0) SERIAL_ECHO("\r\n");
    // }
  }

  void DWIN_SHOW_t::DWIN_DisplayJpeg(unsigned long addr, unsigned long vp)
  {
    unsigned char buf[10];
    buf[0] = 0x5A;
    buf[1] = 0xA5;
    buf[2] = 0x07;
    buf[3] = 0x82;
    buf[4] = addr >> 8;     //控件地址
    buf[5] = addr & 0x00FF;
    buf[6] = 0x5A;
    buf[7] = 0xA5;
    buf[8] = vp >> 8;       //图片存储地址
    buf[9] = vp & 0x00FF;

    dwin_uart_write(buf, 10);
  }

