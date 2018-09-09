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
  PROVIDED �AS IS?WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
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
#define   keylight     P1_1     //�����ʹ�ܣ����������ж�ʹ�ܣ�����͹��Ĺر�
#define   fingerth     P1_2     //ָ�ƴ�����ص�Դ�ݶ�һֱ����
#define   fingerpw     P1_3     //ָ�ƹ����Դ��ָ�ƻ��Ѻ�򿪴�������͹���ǰ�ر�
#define   klpower      P1_4     //����Ƶ�Դ���������̴򿪣�������Ϲر�
#define   wakewifi     P2_0     //��������3165

/*
  P1_5 ָ�ƴ���IO
  P1_0 ��������IO
**/  
  
  //ϵͳ��Ϣ
  #define   LockIfo            0x00 //����Ϣ
  #define   BleIfo             0x01 //������Ϣ
  #define   WifiIfo            0x02 //wifi��Ϣ
  #define   ResWifiIfo         0x03 //��λwifi
  #define   SleepWifIfo        0x04 //����wifi
  #define   WakeWifIfo         0x05 //����wifi
  #define   ResBleIfo          0x06 //��λ����
  #define   SleepBleIfo        0x07 //��������
  #define   WakeBleIfo         0x08 //��������
  #define   WifiCPIfo          0x09 //wifi�¼����
  #define   BleCPIfo           0x0a //�����¼����
  #define   WifiInIfo          0x0b  //wifi��ʼ�����֪ͨ
  #define   BleInIfo           0x0c  //BLE��ʼ�����֪ͨ
  #define   StLink             0x10  //��ʼ����
  #define   LinkSuc            0x11  //�����ɹ�
  #define   LinkFail           0x12  //����ʧ��
  #define   LockOpen           0x20  //����
  #define   OpenStatus         0x21  //�������
  #define   BleOpen            0x22  //��������
  #define   BleError           0x23  //������������
  #define   FingerOpen         0x24  //ָ�ƿ���
  #define   FingError          0x25  //ָ�ƴ���
  #define   CodeOpen           0x26  //���뿪��
  #define   CodeError          0x27  //�������
  #define   ICOpen             0x28  //IC������
  #define   ICError            0x29  //IC������
  #define   FingerGet          0x30  //¼��ָ��
  #define   FingerVfy          0x31   //��ָ֤��
  #define   GetFigFeature      0x32  //��ȡָ������ֵ
  #define   SdFigFeature       0x33  //����ָ������ֵ
  #define   RemFinger          0x34  //ɾ���ض�ָ��
  #define   RemAllFinger       0x35  //ɾ������ָ��
  #define   FingerAllVfy       0x36  //һ��������ָ֤��
  #define   NoUseID            0x37  //��ȡδʹ��ID
  #define   Getcode            0x50  //��ȡ����
  #define   Changecode         0x51  //�޸�����
  #define   ssid               0x60  //��ȡ����
  #define   password           0x61  //�޸�����
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
