#include "dsp_finger.h"
#include "hal_mcu.h"
#include "hal_board_cfg.h"
#include "hal_defs.h"
#include "hal_drivers.h"
#include "hal_types.h"
#include "hal_uart.h"
#include "OnBoard.h"
#include "PN532.h"
#include "hal_i2c.h"
#include "hal_sensor.h"
#include "simpleBLEPeripheral.h"
#include <stdlib.h>
extern uint8_t nfcs; 
extern uint8_t UID[4];


/*void PN532WakeUp()
{
  HalI2CInit(0x24, i2cClock_197KHZ);
  uint8_t res[]={0,0,0xff,3,0xfd,0xd4,0x14,0x01,0x17,0};//{0x00,0x00, 0xFF, 0x06 ,0xFA, 0xD4, 0x32, 0x05,0xff,0x01,0xff,0xF6, 0x00};// {0,0,0xff,3,0xfd,0xd4,0x14,0x01,0x17,0};
 // uint8_t res=0x32;
  HalSensorWriteReg(0x24, res, 10);
   
}

int PN532_W(uint8_t* write ,uint8_t len)
{
  uint8_t* res= (uint8_t*)calloc(len, 1*sizeof(uint8_t));
  memcpy(res,write, len);
  HalSensorWriteReg(0x24, res, len);
  free(res);
  return 0;
}
int PN532_R(uint8_t* read ,uint8_t len)
{
  uint8_t* readbuffer=(uint8_t*)calloc(len, 1*sizeof(uint8_t));
    
   HalSensorReadReg(0x24, readbuffer, len);
   memcpy(read,readbuffer, len);
    free( readbuffer);
   return 0;
}
void SearchIC()
{
  uint8_t command[]={0x00,0x00, 0xFF, 0x04 ,0xFC, 0xD4, 0x4A, 0x01, 0x00, 0xE1, 0x00};
  PN532_W(command,11);
}*/
void PN532WakeUp()
{
    uint8_t* data=(uint8_t*)calloc(24, 1*sizeof(uint8_t));

  
  
  
        data[0]=0x55;
        data[1]=0x55;
        data[2]=0x00;
        data[3]=0x00;
        data[4]=0x00;
        data[5]=0x00;
        data[6]=0x00;
        data[7]=0x00;
        data[8]=0x00;
        data[9]=0x00;
        data[10]=0x00;
        data[11]=0x00;
        data[12]=0x00;
        data[13]=0x00;
        data[14]=0x00;
        data[15]=0x00;
        
        data[16]=0xFF;
        data[17]=0x03; //�㨹 3��?��
        data[18]=0xFD; //�㨹 3��?�� D��?��  0x100-data[3]
        data[19]=0xD4; //?����?������???
        data[20]=0x14; //?����?������???
        data[21]=0x01;
        data[22]=0x17; //��y?Y D��?��   0x100-
        data[23]=0x00;
        
        UartSendString1(data,24);//����USART1��?����?�� length3��?����?��y?Ydata
  
       
       nfcs=1;
   //00 00 FF 00 FF 00 00 00 FF 02 FE D5 15 16 00    

    

   
}
//???? 106 kbps type A (ISO/IEC14443 Type A),
//00 00 FF 04 FC D4 4A 01 00 E1 00
void  nfc_InListPassiveTarget(void)
{
    uint8_t* data=(uint8_t*)calloc(11, 1*sizeof(uint8_t));
  

        data[0]=0x00;
        data[1]=0x00;
        data[2]=0xFF;
        data[3]=0x04; //�㨹 3��?��
        data[4]=0xFC; //�㨹 3��?�� D��?��  0x100-data[3]
        data[5]=0xD4; //?����?������???
        data[6]=0x4A; //?����?������???
        data[7]=0x01;
        data[8]=0x00;
        data[9]=0xE1; //��y?Y D��?��   0x100-
        data[10]=0x00;
        
        UartSendString1(data,11);//����USART1��?����?�� length3��?����?��y?Ydata
        nfcs=2;
}


// ?��??����������??��?��KeyA
//00 00 FF 0F F1 D4 40 01 60 03 FF FF FF FF FF FF UID1 UID2 UID3 UID4 2A 00
//00 00 FF 0F F1 D4 40 01 60 03 FF FF FF FF FF FF 94 8A 3B 0B 2A 00
void  nfc_PsdVerifyKeyA(void)
{
    uint8_t* data=(uint8_t*)calloc(22, 1*sizeof(uint8_t));
    uint8_t temp=0; 
    uint8_t i;
 
     
    data[0]=0x00;
    data[1]=0x00;
    data[2]=0xFF;
    
    data[3]=0x0F; //�㨹 3��?��
    data[4]=0xF1; //�㨹 3��?�� D��?��  0x100-data[3]
    
    data[5]=0xD4; //?����?������???
    data[6]=0x40; //?����?������???
    
    data[7]=0x01;
    data[8]=0x60;
    data[9]=0x03; 
    
    data[10]=0xFF; //KEY A ?��?? FF FF FF FF FF FF
    data[11]=0xFF;
    data[12]=0xFF;
    data[13]=0xFF;
    data[14]=0xFF;
    data[15]=0xFF;
    
    data[16]=UID[0];
    data[17]=UID[1];
    data[18]=UID[2];
    data[19]=UID[3];
    
    for(i=5;i<20;i++)
    {
        temp+=data[i];
    }

    data[20]=0x100-temp;   //��y?Y D��?��   0x100-
    
    data[21]=0x00;
    
    UartSendString1(data,22);//����USART1��?����?�� length3��?����?��y?Ydata
    nfcs=3;
    
    
  
}
//??��? ?�� 02??��?16??��??��
//00 00 FF 05 FB D4 40 01 30 02 B9 00
void  nfc_read(void)
{
    uint8_t* data=(uint8_t*)calloc(12, 1*sizeof(uint8_t));


    data[0]=0x00;
    data[1]=0x00;
    data[2]=0xFF;
    
    data[3]=0x05; //�㨹 3��?��
    data[4]=0xFB; //�㨹 3��?�� D��?��  0x100-data[3]
    
    data[5]=0xD4; //?����?������???
    data[6]=0x40; //?����?������???
    
    data[7]=0x01;
    data[8]=0x30;
    data[9]=0x02; //?���̨�?t?����?16��??����y?Y 
    
    data[10]=0xB9; //��y?YD��?��
    data[11]=0x00;

    UartSendString1(data,12);//����USART1��?����?�� length3��?����?��y?Ydata
    
    
    //while(!flag_rev_finish)
   // ;
  // flag_rev_finish=0;
  
  /* temp=0;
    for(i=11;i<30;i++)
    {
        temp+=RxBuffer1[i];
    }
    CheckCode=0x100-temp;
    if(CheckCode==RxBuffer1[30])
    {       
         if(RxBuffer1[14]==0xAA)
         {
            LED1=0;//��?���� D1
         }
         else if(RxBuffer1[14]==0x55)
         {
            LED1=1;//?��?e D1
         }
         
         if((UID_backup[0]!=UID[0])|(UID_backup[1]!=UID[1])|(UID_backup[2]!=UID[2])|(UID_backup[3]!=UID[3]))
         {
            GPIO_ResetBits(GPIOD,GPIO_Pin_3);//��??��?�� ?D
            delay_ms(150);
            GPIO_SetBits(GPIOD, GPIO_Pin_3);//��??��?�� 2??D
          
         }
         UID_backup[0]=UID[0];
         UID_backup[1]=UID[1];
         UID_backup[2]=UID[2];
         UID_backup[3]=UID[3];
         
         CleanBuffer(40);//??3y ��??��?����??o3????��40 ??��??����y?Y
    }*/
}



//??��?���� 02??D�� 16??��??����?�̨���???��??��
//00 00 FF 15 EB D4 40 01 A0 02 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F D1 00
void  nfc_write(void)
{
      uint8_t* data=(uint8_t*)calloc(28, 1*sizeof(uint8_t));
      uint8_t temp=0; 
      uint8_t i;
  
      uint8 TempMacAddress[6];
      TempMacAddress[5]=XREG(0x780E); // ֱ��ָ��ָ������  
      TempMacAddress[4]=XREG(0x780F);  
      TempMacAddress[3]=XREG(0x7810);  
      TempMacAddress[2]=XREG(0x7811);                // define ����ֱ�Ӷ�������  
      TempMacAddress[1]=XREG(0x7812);  
      TempMacAddress[0]=XREG(0x7813);  
    data[0]=0x00;
    data[1]=0x00;
    data[2]=0xFF;
    
    data[3]=0x15; //�㨹 3��?��
    data[4]=0xEB; //�㨹 3��?�� D��?��  0x100-data[3]
    
    data[5]=0xD4; //?����?������???
    data[6]=0x40; //?����?������???
    
    data[7]=0x01; //?��D��䨮����6��??�� ?��??1��??�䨺?2��
    data[8]=0xA0; //D��
    data[9]=0x02; //D��̨�?t?����?16��??����y?Y 
    
    data[10]=TempMacAddress[0]; //�̨� 1 ��??�� ��y?Y
    data[11]=TempMacAddress[1];
    data[12]=TempMacAddress[2]; //�̨� 3 ��??�� ��y?Y
    data[13]=TempMacAddress[3];
    data[14]=TempMacAddress[4]; //�̨� 5 ��??�� ��y?Y
    data[15]=TempMacAddress[5];
    data[16]=TempMacAddress[0]; //�̨� 7 ��??�� ��y?Y
    data[17]=TempMacAddress[0];
    data[18]=0x00; //�̨� 9 ��??�� ��y?Y
    data[19]=0x00;
    data[20]=0x00; //�̨� 11 ��??�� ��y?Y
    data[21]=0x00;
    data[22]=0x00; //�̨� 13 ��??�� ��y?Y
    data[23]=0x00;
    data[24]=0x00; //�̨� 15 ��??�� ��y?Y
    data[25]=0x00;
    
    for(i=5;i<26;i++)
    {
        temp+=data[i];
    }
    data[26]=0x100-temp; //��y?Y D��?��??
    data[27]=0x00;

    UartSendString1(data,28);//����USART1��?����?�� length3��?����?��y?Ydata
    

    //while(!flag_rev_finish)
   // ;
  // flag_rev_finish=0;
  //00 00 FF 00 FF 00 00 00 FF 03 FD D5 41 00 EA 00
/*    temp=0;
    for(i=11;i<14;i++)
    {
        temp+=RxBuffer1[i];
    }
    CheckCode=0x100-temp;
    if(CheckCode==RxBuffer1[14])
    {
         CleanBuffer(40);//??3y ��??��?����??o3????��40 ??��??����y?Y
         
         if((UID_backup[0]!=UID[0])|(UID_backup[1]!=UID[1])|(UID_backup[2]!=UID[2])|(UID_backup[3]!=UID[3]))
         {
            GPIO_ResetBits(GPIOD,GPIO_Pin_3);//��??��?�� ?D
            delay_ms(10);
            GPIO_SetBits(GPIOD, GPIO_Pin_3);//��??��?�� 2??D
           
         }
         UID_backup[0]=UID[0];
         UID_backup[1]=UID[1];
         UID_backup[2]=UID[2];
         UID_backup[3]=UID[3];
    }*/
}