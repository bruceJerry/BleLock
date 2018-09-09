#include "hal_mcu.h"
#include "hal_board_cfg.h"
#include "hal_defs.h"
#include "hal_drivers.h"
#include "hal_types.h"
#include "hal_uart.h"
#include "OnBoard.h"
#include "bcomdef.h"
#include "OSAL.h"
#include "AT020.h"
#include "OSAL_PwrMgr.h"
/*
#define WAIT_1MS()      {for(unsigned short i=0;i<32000;i++)asm("NOP"); }
// Wait t [ms]
#define WAIT_MS(t)                      \
    do{                                 \
        for(uint8 i = 0; i<t; i++)      \
            WAIT_1MS();                 \
    }while(0)
#define WAIT_1US()      {for(unsigned short i=0;i<32;i++)asm("NOP"); }
// Wait t [ms]
#define WAIT_US(t)                      \
    do{                                 \
        for(uint8 i = 0; i<t; i++)      \
            WAIT_1US();                 \
    }while(0)


*/
void WAIT_US(uint16 microSecs)  
{  
  while(microSecs--)  
  {  
    /* 32 NOPs == 1 usecs */  
    asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");  
    asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");  
    asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");  
    asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");  
    asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");  
    asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");  
    asm("nop"); asm("nop");  
  }  
}
void WAIT_MS(uint16 microSecs)
{
    for (int i=0;i<microSecs;i++)
    {
      WAIT_US(1000);
    }

}
/***********
 初始化语音芯片

************/
void AT080init()
{
  P0DIR|=0x60; //设为输出 （复位/脉冲）
  P0DIR&=~0x10; //设为输入 （忙碌信号）
  P0&=~0x60;    //初始为低电平

}

/*int PlayVioce(int m)
{
  while(Busy!=0);
  if(m==0)
  return 0;
  AT080init();
  Res=1;
  WAIT_US(1000);
  Res=0;
  WAIT_US(1000);
  //WAIT_MS(5);
  
  Data=1;
  WAIT_US(1000);
  Data=0;
  //WAIT_MS(100);
  WAIT_MS(100);
  
  for(int i=1;i<m;i++)
  {
    Data=1;
    WAIT_US(1000);
    Data=0;
    WAIT_US(1000);

  }   
  Data=0;
  return 1;

}*/
int PlayVoiceP1(int m)
{
  //P1IEN&=~0x21;//播放语音时关掉指纹中断
  bool a;
  AT080init();
 // while(Busy!=1);
  Data=0;
  WAIT_MS(5);
  a=m&0x01;
  for(int j=0;j<8;j++)
  {
  if(a==1)
  {
   Data=1;
  WAIT_US(600);
  Data=0; 
  WAIT_US(200);
  }else
  {
  Data=1;
  WAIT_US(200);
  Data=0; 
  WAIT_US(600);
  }
  m=m>>1;
  a=m&0x01;
  }
   Data=1;
 
  //P1IEN|=0x21;//播放完毕打开
  return 1;

}