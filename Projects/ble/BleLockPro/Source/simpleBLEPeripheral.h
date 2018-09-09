/**************************************************************************************************
  Filename:       simpleBLEperipheral.h
  Revised:        $Date: 2010-08-01 14:03:16 -0700 (Sun, 01 Aug 2010) $
  Revision:       $Revision: 23256 $

  Description:    This file contains the Simple BLE Peripheral sample application
                  definitions and prototypes.

  Copyright 2010 - 2011 Texas Instruments Incorporated. All rights reserved.

  IMPORTANT: Your use of this Software is limited to those specific rights
  granted under the terms of a software license agreement between the user
  who downloaded the software, his/her employer (which must be your employer)
  and Texas Instruments Incorporated (the "License").  You may not use this
  Software unless you agree to abide by the terms of the License. The License
  limits your use, and you acknowledge, that the Software may not be modified,
  copied or distributed unless embedded on a Texas Instruments microcontroller
  or used solely and exclusively in conjunction with a Texas Instruments radio
  frequency transceiver, which is integrated into your product.  Other than for
  the foregoing purpose, you may not use, reproduce, copy, prepare derivative
  works of, modify, distribute, perform, display or sell this Software and/or
  its documentation for any purpose.

  YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
  PROVIDED 揂S IS?WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
  INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE,
  NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
  TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
  NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER
  LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
  INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE
  OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT
  OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
  (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

  Should you have any questions regarding your right to use this Software,
  contact Texas Instruments Incorporated at www.TI.com.
**************************************************************************************************/

#ifndef SIMPLEBLEPERIPHERAL_H
#define SIMPLEBLEPERIPHERAL_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************************************************************
 * INCLUDES
 */

/*********************************************************************
 * CONSTANTS
 */
#define   keylight     P1_1     //背光灯使能：触摸键盘中断使能，进入低功耗关闭
#define   fingerth     P1_2     //指纹触摸监控电源暂定一直工作
#define   fingerpw     P1_3     //指纹供电电源：指纹唤醒后打开处理，进入低功耗前关闭
#define   klpower      P1_4     //背光灯电源：触摸键盘打开，处理完毕关闭
#define   wakewifi     P2_0     //用来唤醒3165

/*
  P1_5 指纹触控IO
  P1_0 按键触控IO
**/  
  
  //系统信息
  #define   LockIfo            0x00 //锁信息
  #define   BleIfo             0x01 //蓝牙信息
  #define   WifiIfo            0x02 //wifi信息
  #define   ResWifiIfo         0x03 //复位wifi
  #define   SleepWifIfo        0x04 //休眠wifi
  #define   WakeWifIfo         0x05 //唤醒wifi
  #define   ResBleIfo          0x06 //复位蓝牙
  #define   SleepBleIfo        0x07 //休眠蓝牙
  #define   WakeBleIfo         0x08 //唤醒蓝牙
  #define   WifiCPIfo          0x09 //wifi事件完成
  #define   BleCPIfo           0x0a //蓝牙事件完成
  #define   WifiInIfo          0x0b  //wifi初始化完成通知
  #define   BleInIfo           0x0c  //BLE初始化完成通知
  #define   StLink             0x10  //开始配网
  #define   LinkSuc            0x11  //配网成功
  #define   LinkFail           0x12  //配网失败
  #define   LockOpen           0x20  //开锁
  #define   OpenStatus         0x21  //开锁结果
  #define   BleOpen            0x22  //蓝牙开锁
  #define   BleError           0x23  //蓝牙开锁错误
  #define   FingerOpen         0x24  //指纹开锁
  #define   FingError          0x25  //指纹错误
  #define   CodeOpen           0x26  //密码开锁
  #define   CodeError          0x27  //密码错误
  #define   ICOpen             0x28  //IC卡开锁
  #define   ICError            0x29  //IC卡开锁
  #define   FingerGet          0x30  //录入指纹
  #define   FingerVfy          0x31   //验证指纹
  #define   GetFigFeature      0x32  //获取指纹特征值
  #define   SdFigFeature       0x33  //发送指纹特征值
  #define   RemFinger          0x34  //删除特定指纹
  #define   RemAllFinger       0x35  //删除所有指纹
  #define   FingerAllVfy       0x36  //一对所有认证指纹
  #define   NoUseID            0x37  //获取未使用ID
  #define   Getcode            0x50  //获取密码
  #define   Changecode         0x51  //修改密码
  #define   ssid               0x60  //获取密码
  #define   password           0x61  //修改密码
  #define   Sdcode             0x70  //
    
  #define   CuserCMD             0x71  //
  #define   CuserRES             0x72  //
  #define   PuserCMD             0x73  //
  #define   PuserRES             0x74  //
  // Simple BLE Peripheral Task Events
#define SBP_START_DEVICE_EVT                              0x0001
#define SBP_PERIODIC_EVT                                  0x0002
#define SBP_ADV_IN_CONNECTION_EVT                         0x0004
#define SBP_PERIODIC_EVT1                                 0x0008
#define FP_Voice_EVT                                      0x0010
#define Wakeup_EVT1                                       0x0020
#define GoSleep_EVT                                       0x0040
#define FPDatafx_EVT                                      0x0080
#define Datacleanfx_EVT                                   0x0100
#define wawf_EVT                                          0x0200
#define FPTIMEOUT_EVT                                     0x0400 
#define FPHSTIMEOUT_EVT                                   0x0800 
#define Delay_Check_EVT                                   0x1000
#define ClearFPLock_EVT                                   0x2000
#define ClearLock_EVT                                     0x4000
/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * FUNCTIONS
 */

/*
 * Task Initialization for the BLE Application
 */
extern void SimpleBLEPeripheral_Init( uint8 task_id );

/*
 * Task Event Processor for the BLE Application
 */
extern uint16 SimpleBLEPeripheral_ProcessEvent( uint8 task_id, uint16 events );
void UartSendString1( unsigned char *Data, uint8 len);
/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* SIMPLEBLEPERIPHERAL_H */
