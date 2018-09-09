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
void mpr121QuickConfig(void) {    
  // Section A   
  // This group controls filtering when data is > baseline.
  unsigned char res=0x63;
   HalSensorWriteReg(0x80,  &res, 1);
     unsigned char para7[1]={0x00};
   HalSensorWriteReg(ELE_CFG,  para7, 1);
  // unsigned char reda[5]={0xff,0xff,0xff,0xff,0xff};
    //HalSensorWriteReg(0x73, reda, 5);
   //unsigned char reda1[4]={0,0,0,0};
   // HalSensorWriteReg(0x81, reda1, 4);
  unsigned char para[4]={1,1,5,0};
   HalSensorWriteReg(MHD_R,  para, 4);
 // I2C_Write(MHD_R, 0x01);  
 // I2C_Write(NHD_R, 0x01);  
//  I2C_Write(NCL_R, 0x00);   
 // I2C_Write(FDL_R, 0x00);      
  // Section B    
  // This group controls filtering when data is < baseline. 
    unsigned char para1[4]={1,1,0xff,0x02};
   HalSensorWriteReg(MHD_F,  para1, 4);
      unsigned char para11[14]={0,0,0,0x0f,0x0f,0,0,0x01,0x01,0xff,0xff,0x00,0x00,0x00};
   HalSensorWriteReg(0x33,  para11, 14);
  //I2C_Write(MHD_F, 0x01);   
  //I2C_Write(NHD_F, 0x01);   
 // I2C_Write(NCL_F, 0xFF);   
  //I2C_Write(FDL_F, 0x02);    
  // Section C    
  // This group sets touch and release thresholds for each electrode  
    unsigned char para2[24]={TOU_THRESH,REL_THRESH,TOU_THRESH,REL_THRESH,TOU_THRESH,REL_THRESH,TOU_THRESH,REL_THRESH,TOU_THRESH,REL_THRESH,TOU_THRESH,REL_THRESH,TOU_THRESH,REL_THRESH,TOU_THRESH,REL_THRESH
    ,TOU_THRESH,REL_THRESH,TOU_THRESH,REL_THRESH,TOU_THRESH,REL_THRESH,TOU_THRESH,REL_THRESH};
   HalSensorWriteReg(ELE0_T,  para2, 24);
 /* I2C_Write(ELE0_T, TOU_THRESH);   
  I2C_Write(ELE0_R, REL_THRESH);   
  I2C_Write(ELE1_T, TOU_THRESH);   
  I2C_Write(ELE1_R, REL_THRESH);   
  I2C_Write(ELE2_T, TOU_THRESH);   
  I2C_Write(ELE2_R, REL_THRESH);   
  I2C_Write(ELE3_T, TOU_THRESH);   
  I2C_Write(ELE3_R, REL_THRESH);   
  I2C_Write(ELE4_T, TOU_THRESH);   
  I2C_Write(ELE4_R, REL_THRESH);   
  I2C_Write(ELE5_T, TOU_THRESH);   
  I2C_Write(ELE5_R, REL_THRESH);   
  I2C_Write(ELE6_T, TOU_THRESH);   
  I2C_Write(ELE6_R, REL_THRESH);   
  I2C_Write(ELE7_T, TOU_THRESH);   
  I2C_Write(ELE7_R, REL_THRESH);   
  I2C_Write(ELE8_T, TOU_THRESH);   
  I2C_Write(ELE8_R, REL_THRESH);   
  I2C_Write(ELE9_T, TOU_THRESH);   
  I2C_Write(ELE9_R, REL_THRESH);   
  I2C_Write(ELE10_T, TOU_THRESH);   
  I2C_Write(ELE10_R, REL_THRESH);   
  I2C_Write(ELE11_T, TOU_THRESH);   
  I2C_Write(ELE11_R, REL_THRESH);  */   
  // Section D    
  // Set the Filter Configuration   
  // Set ESI2    
      unsigned char para5[3]={0x05,0x00,0x00};
   HalSensorWriteReg(0x59,  para5, 3);
   unsigned char para3[1]={0x04};
   HalSensorWriteReg(FIL_CFG,  para3, 1);
   unsigned char para31[1]={0x80};
   HalSensorWriteReg(0x5c,  para31, 1);
 // I2C_Write(FIL_CFG, 0x04);    
  // Section E   
  // Electrode Configuration   
  // Enable 6 Electrodes and set to run mode  
  // Set ELE_CFG to 0x00 to return to standby mode  // 
 // I2C_Write(ELE_CFG, 0x0C); // Enables all 12 Electrodes  I2C_Write(ELE_CFG, 0x06);  // Enable first 6 electrodes   
  // Section F  
  // Enable Auto Config and auto Reconfig 
   unsigned char para4[4]={0x8f,0xe4,0x94,0xcb};
   HalSensorWriteReg(ATO_CFG0 ,  para4, 4);
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
   HalSensorReadReg(0x00, readbuffer, 2);
   HalSensorReadReg(0x5e, (readbuffer+2), 1);
}