#include "dsp_finger.h"
#include "hal_mcu.h"
#include "hal_board_cfg.h"
#include "hal_defs.h"
#include "hal_drivers.h"
#include "hal_types.h"
#include "hal_uart.h"
#include "OnBoard.h"
#include "MPR121.h"
#include "hal_i2c.h"
#include "hal_sensor.h"
extern uint8 MPR121;
void APT8L16QuickConfig(void)
{
   unsigned char res=0x5A;
   HalSensorWriteReg(0x3A, &res, 1); //省电模式寄存器，配置寄存器时需要先写5a
   /*
   * 00-0f 灵敏度控制寄存器默认为0想0x10，值越大灵敏度越低反之灵敏度越高
   先复位这些寄存器
   */
   res=0x10;            
   HalSensorWriteReg(0x09, &res, 1);
   res=0x10;
   HalSensorWriteReg(0x0a, &res, 1);
   res=0x10;
   HalSensorWriteReg(0x0b, &res, 1);
   res=0x10;
   HalSensorWriteReg(0x0c, &res, 1);
   res=0x10;
   HalSensorWriteReg(0x0d, &res, 1);
   res=0x10;
   HalSensorWriteReg(0x0e, &res, 1);
   res=0x10;
   HalSensorWriteReg(0x0f, &res, 1);
     /*
   * 20：全局灵敏度寄存器 默认02
     21：工作模式寄存器   默认01（00为1Mhz全速工作模式）
     22：滤波器寄存器     默认20 （01按键检测一阶滤波）
     23/24：触摸按键/功能按键选择 初始为00均为感应按键
     25：接近感应控制寄存器 默认00
     26：接近感应灵敏度
   */
   res=0x02;
   HalSensorWriteReg(0x20, &res, 1);
   res=0x84;
   HalSensorWriteReg(0x21, &res, 1);
   res=0x20;
   HalSensorWriteReg(0x22, &res, 1);
   res=0x03;
   HalSensorWriteReg(0x23, &res, 1);
   res=0xC0;
   HalSensorWriteReg(0x24, &res, 1);
   res=0x00;
   HalSensorWriteReg(0x25, &res, 1);
   res=0x00;//值越大感应距离越近，值越小感应距离越远
   HalSensorWriteReg(0x26, &res, 1);
   
   res=0x00;
   HalSensorWriteReg(0x27, &res, 1);
   res=0x00;
   HalSensorWriteReg(0x28, &res, 1);
   res=0x10;
   HalSensorWriteReg(0x29, &res, 1);
   res=0x10;
   HalSensorWriteReg(0x2a, &res, 1);
   res=0x04;
   HalSensorWriteReg(0x2b, &res, 1);//按键有效后的释放距离避免出现一次按下多次中断
   res=0x00;
   HalSensorWriteReg(0x2c, &res, 1);
   res=0x00;
   HalSensorWriteReg(0x2d, &res, 1);
   
   res=0x00;
   HalSensorWriteReg(0x18, &res, 1);
   res=0x00;
   HalSensorWriteReg(0x19, &res, 1);
   
   /*
   * 此处为真正配置的感应按键的灵敏度
   */
#define offsetx 4
   res=offsetx+1;               
   HalSensorWriteReg(0x02, &res, 1);
   res=offsetx;
   HalSensorWriteReg(0x03, &res, 1);
   res=offsetx;
   HalSensorWriteReg(0x04, &res, 1);
   res=offsetx;
   HalSensorWriteReg(0x05, &res, 1);
   res=offsetx;
   HalSensorWriteReg(0x06, &res, 1);   
   res=offsetx+1;
   HalSensorWriteReg(0x07, &res, 1);
   res=offsetx;
   HalSensorWriteReg(0x08, &res, 1);
   
   res=offsetx;
   HalSensorWriteReg(0x09, &res, 1);
   res=offsetx;
   HalSensorWriteReg(0x0a, &res, 1);
   res=offsetx;
   HalSensorWriteReg(0x0b, &res, 1);
   res=offsetx+1;
   HalSensorWriteReg(0x0c, &res, 1);
   res=offsetx+1;
   HalSensorWriteReg(0x0d, &res, 1);
   res=0x01;
   HalSensorWriteReg(0x0f, &res, 1);
   //zheli
   //开始工作
   res=0x00;
   HalSensorWriteReg(0x3A, &res, 1);
}

void mpr121QuickConfig(void) 
{    
  // Section A   
  // This group controls filtering when data is > baseline.
  unsigned char res=0x63;
   HalSensorWriteReg(0x80,  &res, 1);
     unsigned char para7[1]={0x00};
   HalSensorWriteReg(ELE_CFG,  para7, 1);
   res=1;
   HalSensorWriteReg(MHD_R,  &res, 1);
   res=1;
   HalSensorWriteReg(NHD_R,  &res, 1);
   
   res=0;
   HalSensorWriteReg(NCL_R,  &res, 1);
   
   res=0;
   HalSensorWriteReg(FDL_R,  &res, 1);
  
   res=1;
   HalSensorWriteReg(MHD_F,  &res, 1);
	
  res=1;
  HalSensorWriteReg(NHD_F,&res, 1);
  
  res=0xff;
  HalSensorWriteReg(NCL_F, &res, 1);
  
  res=2;
  HalSensorWriteReg(FDL_F, &res, 1);
	
    res=0;
	HalSensorWriteReg(0x33, &res, 1);
	HalSensorWriteReg(0x34, &res, 1);
	HalSensorWriteReg(0x35, &res, 1);
    res=0xff;
	HalSensorWriteReg(0x36, &res, 1);
	HalSensorWriteReg(0x37, &res, 1);
    res=0;
	HalSensorWriteReg(0x38, &res, 1);
	HalSensorWriteReg(0x39, &res, 1);
    res=1;
	HalSensorWriteReg(0x3A, &res, 1);
	HalSensorWriteReg(0x3B, &res, 1);
    res=0xff;
	HalSensorWriteReg(0x3C, &res, 1);
	HalSensorWriteReg(0x3D, &res, 1);
    res=0;
	HalSensorWriteReg(0x3E, &res, 1);
	HalSensorWriteReg(0x3F, &res, 1);
	HalSensorWriteReg(0x40, &res, 1);
	
	
  // Section C
  // This group sets touch and release thresholds for each electrode
    res=0x05;
  HalSensorWriteReg(ELE0_T, &res, 1);
   res=0x03;
  HalSensorWriteReg(ELE0_R, &res, 1);
   res=0x05;
  HalSensorWriteReg(ELE1_T, &res, 1);
  res=0x03;
  HalSensorWriteReg(ELE1_R, &res, 1);
   res=0x05;
  HalSensorWriteReg(ELE2_T, &res, 1);
  res=0x03;
  HalSensorWriteReg(ELE2_R, &res, 1);
   res=0x05;
  HalSensorWriteReg(ELE3_T, &res, 1);
  res=0x03;
  HalSensorWriteReg(ELE3_R, &res, 1);
   res=0x05;
  HalSensorWriteReg(ELE4_T, &res, 1);
  res=0x03;
  HalSensorWriteReg(ELE4_R, &res, 1);
   res=0x05;
  HalSensorWriteReg(ELE5_T, &res, 1);
  res=0x03;
  HalSensorWriteReg(ELE5_R, &res, 1);
   res=0x05;
  HalSensorWriteReg(ELE6_T, &res, 1);
  res=0x03;
  HalSensorWriteReg(ELE6_R, &res, 1);
   res=0x05;
  HalSensorWriteReg(ELE7_T, &res, 1);
  res=0x03;
  HalSensorWriteReg(ELE7_R, &res, 1);
   res=0x05;
  HalSensorWriteReg(ELE8_T, &res, 1);
  res=0x03;
  HalSensorWriteReg(ELE8_R, &res, 1);
   res=0x05;
  HalSensorWriteReg(ELE9_T, &res, 1);
  res=0x03;
  HalSensorWriteReg(ELE9_R, &res, 1);
   res=0x05;
  HalSensorWriteReg(ELE10_T, &res, 1);
  res=0x03;
  HalSensorWriteReg(ELE10_R, &res, 1);
   res=0x05;
  HalSensorWriteReg(ELE11_T, &res, 1);
  res=0x03;
  HalSensorWriteReg(ELE11_R, &res, 1);

	res=0x05;
	HalSensorWriteReg(0x59, &res, 1);
    res=0x00;
	HalSensorWriteReg(0x5A, &res, 1);
	HalSensorWriteReg(0x5B, &res, 1);
    res=0x04;
	HalSensorWriteReg(0x5D, &res, 1);
    res=0x80;
	HalSensorWriteReg(0x5C, &res, 1);
	
// Section D
// Set the Filter Configuration
// Set ESI2
//  TouchKey_Write(FIL_CFG, 0x04);

	
// Section E
// Electrode Configuration
// Enable 6 Electrodes and set to run mode
  // Set ELE_CFG to 0x00 to return to standby mode
	// TouchKey_Write(ELE_CFG, 0x0C);	// Enables all 12 Electrodes
//	TouchKey_Write(ELE_CFG, 0x06);		// Enable first 6 electrodes
 
	
  // Section F
  // Enable Auto Config and auto Reconfig
    res=0x8f;
  HalSensorWriteReg(ATO_CFG0, &res, 1);
  res=0xe4;
  HalSensorWriteReg(ATO_CFGU, &res, 1);	// USL = (Vdd-0.7)/vdd*256 = 0xC9 @3.3V   TouchKey_Write(ATO_CFGL, 0x82);	// LSL = 0.65*USL = 0x82 @3.3V
  res=0x94;
  HalSensorWriteReg(ATO_CFGL, &res, 1);
  res=0xcb;
  HalSensorWriteReg(ATO_CFGT, &res, 1);	// Target = 0.9*USL = 0xB5 @3.3V
	
  //I2C_Write(ATO_CFG0, 0x0B);   
  //I2C_Write(ATO_CFGU, 0xC9); // USL = (Vdd-0.7)/vdd*256 = 0xC9 @3.3V  
 // I2C_Write(ATO_CFGL, 0x82); // LSL = 0.65*USL = 0x82 @3.3V  
  //I2C_Write(ATO_CFGT, 0xB5); // Target = 0.9*USL = 0xB5 @3.3V
    
   
      unsigned char para6[1]={0xCC};
   HalSensorWriteReg(ELE_CFG,  para6, 1);
}
void ReadTouchKey(unsigned char *readbuffer)
{
   //mpr121QuickConfig();
  if(MPR121==1)
  {
   HalSensorReadReg(0x00, readbuffer, 2);
   //HalSensorReadReg(0x5e, (readbuffer+2), 1);
  }
  

}
void ReadTouchKey1(unsigned char *readbuffer)
{
   //mpr121QuickConfig();
if(MPR121==0)
  {
    HalSensorReadReg(0x34, readbuffer, 2);
   HalSensorReadReg(0x5e, (readbuffer+2), 1);
  }
}
void ReadTouch121(unsigned char *readbuffer)
{
  
   HalSensorReadReg(0x00, readbuffer, 94);
}