#include "dsp_finger.h"
#include "hal_mcu.h"
#include "hal_board_cfg.h"
#include "hal_defs.h"
#include "hal_drivers.h"
#include "hal_types.h"
#include "hal_uart.h"
#include "OnBoard.h"
#include "npi.h"
#include "stdio.h"
#define   finger_tx  P0_2
#define   finger_rx  P0_3
#include "simpleBLEPeripheral.h"

//extern uint8_t constFeaturn[1000];
#define WAIT_1MS()      {for(unsigned short i=0;i<32000;i++)asm("NOP"); }

extern void UartSendString(char *Data, int len);
extern uint8 fpprocess;
extern uint8_t nfcs;

uint8_t Featurn[512]={'\0'};

int FeaturnSum = 0;
int overSum = 0;

void finger_fputc(unsigned char *ch)
{
  UartSendString1(ch, 1);//Usart_SendData(FINGER_USART,ch);
}

  	/*if((FingerReceMes[1] == 0x31 || FingerReceMes[1] == 0x23) && FingerReceMes[9] == 1)
	  {
		Featurn[FeaturnSum] = ucTemp;
		if(FeaturnSum >= 496)
		 {
			Featurn[498] = 1;
		  }
		else
			FeaturnSum++;
		}
		else
		{
			FingerReceMes[MessageSum] = ucTemp;
			if(MessageSum >= 7)
			{
				FingerReceMes[9] = 1;
			}
			else
				MessageSum++;
		}*/
   // if(overSum>=2)
    //{
    //  if((FingerReceMes[2] != 0)||(FingerReceMes[3] != 0)) //�Աȳɹ�
    //  {
    //    fpress=0; //Ϊ�´�ָ�ƿ������־λ
     // }
     // UartSendString(FingerReceMes, MessageSum+1);  
    //  overSum=0;  //��ռ���
     // MessageSum=0;//��ս�������
   // }
//}
/*
void Finger_Usart_IRQHandler(void)
{
	uint8_t ucTemp;
	//if(USART_GetITStatus(USART3,USART_IT_RXNE)==SET)
	if(USART_GetITStatus(Usart_Platform[FINGER_USART].USARTx,USART_IT_RXNE)==SET)
  {
		ucTemp = USART_ReceiveData(Usart_Platform[FINGER_USART].USARTx);
		
		if((FingerReceMes[1] == 0x31 || FingerReceMes[1] == 0x23) && FingerReceMes[9] == 1)
		{
			Featurn[FeaturnSum] = ucTemp;
			if(FeaturnSum >= 496)
			{
				Featurn[498] = 1;
			}
			else
				FeaturnSum++;
		}
		else
		{
			FingerReceMes[MessageSum] = ucTemp;
			if(MessageSum >= 7)
			{
				FingerReceMes[9] = 1;
			}
			else
				MessageSum++;
		}
	}
}
*/
void Finger_GPIO_Config(void)
{
		//hiss_gpio_init(vcc_ctrl,GPIO_Mode_OUT);
		//hiss_gpio_init(touch_ctrl,GPIO_Mode_OUT);
		//hiss_gpio_init(touch_out,GPIO_Mode_IN);
    //     P0DIR = 0xFC; // Port 0 pins P0.0 and P0.1 as input (buttons),
                // all others (P0.2-P0.7) as output
 // P1DIR = 0xFF; // All port 1 pins (P1.0-P1.7) as output
  //P2DIR = 0x1F; // All port 1 pins (P2.0-P2.4) as output


}

/***** ����ָ��ģ�� *****/
void Finger_Start(void)
{
	finger_tx=0;    //hiss_gpio_low(finger_tx);
	finger_rx=0;    //hiss_gpio_low(finger_rx);
	/* VCC_CTRL, touch_ctrl Ϊ�͵�ƽʱ��ָ��ģ������ */
	fingerpw=0;     //hiss_gpio_low(vcc_ctrl);
	fingerth=0;     //hiss_gpio_low(touch_ctrl);
}

/***** ����ָ��ģ�� *****/
void Finger_Reset(void)
{
	finger_tx=0;    //hiss_gpio_low(finger_tx);
	finger_rx=0;    //hiss_gpio_low(finger_rx);
	
    fingerpw=1;     //hiss_gpio_low(vcc_ctrl);
	fingerth=1;     //hiss_gpio_low(touch_ctrl);

	/******/
	for(int a=0;a<100;a++)
    {
      WAIT_1MS();
    }
	hp02_Finger_Config();
	Finger_Start();
	fingerpw=0;     //hiss_gpio_low(vcc_ctrl);
	fingerth=0;     //hiss_gpio_low(touch_ctrl);
}

/***** ָֹͣ��ģ�� *****/
void Finger_Stop(void)
{
	finger_tx=0;    //hiss_gpio_low(finger_tx);
	finger_rx=0;    //hiss_gpio_low(finger_rx);
	finger_tx=1;    //hiss_gpio_low(finger_tx);
	finger_rx=1;    //hiss_gpio_low(finger_rx);
    fingerpw=1;     //hiss_gpio_low(vcc_ctrl);
	fingerth=1;     //hiss_gpio_low(touch_ctrl);
}
void hp02_Usart_Config(void)

{
  
	//����һ��ʼ����//Usart_Init(FINGER_USART);
}
/*****��ȡgpio��״̬*****/
int Finger_getTouch(void)
{
	//hiss_gpio_init(touch_out,GPIO_Mode_IN);
    // P1DIR&=~0x04;
    // int status = touch_out;
	return 1;//status;//hiss_gpio_GetStatus(touch_out);
}

void hp02_Finger_Config(void)
{
	hp02_Usart_Config();
	//hiss_usart_init(finger_usart);
	Finger_GPIO_Config();
}
/**********************************Cmd*************************************/
/**
  * @brief ָ������д��ָ��ģ��
  * @param  �������
	*	@param	�����߰�λ
	* @param			�Ͱ�λ
	* @param	�û�Ȩ��
	* @param	��λ	Ĭ���봫0
  * @retval None
  */
void Finger_Cmd(uint8_t Type,uint8_t p1,uint8_t p2,uint8_t UserRole,uint8_t u6)
{
	uint8 i = 0;
	unsigned char cmd=0;
	uint8_t sendData[9] = {'\0'};
	sendData[0] = 0xF5;
	sendData[1] = Type;
	sendData[2] = p1;
	sendData[3] = p2;
	sendData[4] = UserRole;
	sendData[5] = u6;
	for(i=1;i<6;i++)
         sendData[6] ^= sendData[i];
	sendData[7] = 0xF5;
        nfcs=0;
    if(fpprocess==0)
    {
	for(i=0;i<8;i++)
	{
        cmd=sendData[i];
	finger_fputc(&cmd);
	}
    fpprocess=1;
    }
}
/****************************************Send Data*******************************************/
/**
  * @brief ָ����������д��ָ��ģ��
  * @param 
	*	@param	
	* @param	
	* @param	
  * @retval None
  */
void Finger_Cmd_Package(uint8_t Type,uint8_t p1,uint8_t p2,uint8_t UserRole,uint8_t u6,uint16_t userId,UserRole_TypeDef userRole,uint8_t * feature)
{
//	char sendData[499] = {'\0'};
	int i = 0;
        unsigned char a=0;
	uint8_t temp = 0;
	Featurn[0] = 0xF5;
	Featurn[1] = Type;
	Featurn[2]	= p1;
	Featurn[3] = p2;
	Featurn[4] = UserRole;
	Featurn[5] = u6;
	Featurn[6] = 0x00;
	for(i=1;i<6;i++)
		Featurn[6] ^= Featurn[i];
	
	Featurn[7] = 0xF5;
	
	Featurn[8] = 0xF5;
	Featurn[9] = userId>>8;
	Featurn[10] = userId;
	Featurn[11] = userRole;
	temp ^=Featurn[9];
	temp ^=Featurn[10];
	temp ^=Featurn[11];
	for(i=0;i<494;i++)								
	{	
		Featurn[i+12] = feature[i];
		temp ^= feature[i];
	}
	Featurn[506] = temp;
	Featurn[507] = 0xF5;
	for(i=0;i<508;i++)
	{
        a=Featurn[i];
		finger_fputc(&a);
	}
}
/**
  * @brief  ָ��ע�᷽ʽ
  * @param  �û�id
	*	@param	�û�Ȩ��
  * @retval None
  */
void User_Registration(uint16_t userID,uint8_t role)
{
	#if REGISTER_MODE == CMD_REGISTER_1C3R
			Finger_Cmd(CMD_REGISTER_1C3R,userID>>8,userID,role,0x00);
	#elif REGISTER_MODE == CMD_REGISTER_2C2R
			Finger_Cmd(CMD_REGISTER_2C2R,userID>>8,userID,role,0x00);
	#else
			Finger_Cmd(CMD_REGISTER_3C3R,userID>>8,userID,role,0x00);
	#endif
}
/**
  * @brief  ???? 1C3R
  * @param  ??id
	*	@param	???��
  * @retval None
  */
void User_Registration_1C3R(uint16_t userID,uint8_t role)
{
	Finger_Cmd(CMD_REGISTER_1C3R,userID>>8,userID,role,0x00);
}
/**
  * @brief  ???? 2C2R
  * @param  ??id
	*	@param	???��
  * @retval None
  */
void User_Registration_2C2R(uint16_t userID,uint8_t role)
{
	Finger_Cmd(CMD_REGISTER_2C2R,userID>>8,userID,role,0x00);
}
/**
  * @brief  ???? 3C3R
  * @param  ??id
	*	@param	???��
  * @retval None
  */
void User_Registration_3C3R(uint16_t userID,uint8_t role)
{
	Finger_Cmd(CMD_REGISTER_3C3R,userID>>8,userID,role,0x00);
}
/**
  * @brief  ɾ���û�����ֵ
  * @param  �û�id
  * @retval None
  */
void User_DeleteSpecific(uint16_t userID)
{
	Finger_Cmd(CMD_DELETE_SPECIFIC_USER,userID>>8,userID,0x00,0x00);
}
/**
  * @brief  ɾ��ȫ���û�
  * @param  null
  * @retval null
  */
void FingerUser_DeleteAll(void)
{
	Finger_Cmd(CMD_DELETE_ALL_USER,0x00,0x00,0x00,0x00);
}
/**
  * @brief  ��ȡȫ����ָ����
  * @param  null
  * @retval null
  */
void FingerUser_getAllSum(void)
{
	Finger_Cmd(CMD_GET_TOTAL_USER_NUM,0x00,0x00,0x00,0x00);
}
/**
  * @brief  ��ȡָ�Ƶ�Ȩ��
  * @param  �û�id
  * @retval null
  */
void User_getRole(uint16_t userID)
{
	Finger_Cmd(CMD_GET_ROLE_USER,userID>>8,userID,0x00,0x00);
}
/**
  * @brief 1 �� 1 �ȶ�
	* @param  
  * @retval null
  */
void User_FingerOneToOne(uint16_t userID)
{
  Finger_Cmd(CMD_VERIFY_ONE_TO_ONE,userID>>8,userID,0x00,0x00);
}
/**
  * @brief 1 �� N �ȶ�
	* @param  null
  * @retval null
  */
void User_FingerOneToAll()
{
  Finger_Cmd(CMD_VERIFY_ONE_TO_ALL,0x00,0x00,0x00,0x00);
  
}

/**
  * @brief 	��ȡδʹ�õ��û� ID
	* @param  null
  * @retval null
  */
void User_GetNoUseID()
{
	Finger_Cmd(CMD_GET_NOUSE_ID,0x00,0x00,0x00,0x00);
}
/**
  * @brief 	���ô��ڲ�����
	* @param  enum `BaudRate_TypeDef
  * @retval null
  */
void User_SetBaudRate(BaudRate_TypeDef baudrate)
{
	Finger_Cmd(CMD_SET_BAUDRATE,0x00,baudrate,0x00,0x00);
}
/**
  * @brief 	��ȡͼ����ȡ����ֵ
	* @param  null
  * @retval null
  */

void User_GetFeatureValue(uint16_t userid)
{
	Finger_Cmd(CMD_GET_FEA,userid>>8,userid,0x00,0x00);
}
/**
  * @brief 	��ȡͼ��
	* @param  null
  * @retval null
  */
void User_GetIamge(void)
{
	Finger_Cmd(CMD_GET_FINGER_IMAGE,0x00,0x00,0x00,0x00);
}
/**
  * @brief 	��ȡָ�ư汾��
	* @param  null
  * @retval null
  */
void Finger_Version()
{
	Finger_Cmd(CMD_GETVERSION,0x00,0x00,0x00,0x00);
}
/**
  * @brief 	 ����/��ȡ�ȶԵȼ�
	* @param  
  * @retval null
  */
void Finger_SetGetMatchLevel(uint8_t level)
{
	Finger_Cmd(CMD_SETGETMATCHLEVEL,0x00,0x00,0x00,0x00);
}
/**
  * @brief 	��ȡע���û��� ID ֵ��Ȩ��ֵ
	* @param  null
  * @retval null
  */
void User_GetUserID_Role()
{
	Finger_Cmd(CMD_GET_USERID_ROLE,0x00,0x00,0x00,0x00);
}
/**
  * @brief 	����/��ȡע��ģʽ
	* @param  
	*	@param	
  * @retval null
  */
void Finger_SetGetRegisterMode(RegisterMode_TypeDef mode,ActiveMode_TypeDef active)
{
	Finger_Cmd(CMD_GET_USERID_ROLE,0x00,mode,active,0x00);
}
/**
  * @brief 	��ȡ�û���ָ������ֵ
	* @param  user id
  * @retval null
  */
void User_GetID_FeatureValue(uint16_t userId)
{
	uint8_t h,l;
	h = (userId & 0xff00)>>8;
	l = (userId & 0x00ff);
	Finger_Cmd(CMD_GET_SPECIFIC_FEATURE,h,l,0x00,0x00);
}
/**
  * @brief 	�´��û�ָ������ֵ�������û� ID �洢��ģ����
	* @param  user id
	* @param	
	* @param	
  * @retval null
  */
void User_Load_Deposit_FeatureValue(uint16_t userId,UserRole_TypeDef userRole,uint8_t *feature)
{
	uint16_t length = 494 + 3;
	Finger_Cmd_Package(CMD_LOAD_FEATURE,length>>8,length,0x00,0x00,userId,userRole,feature);
}
/**
  * @brief 	�´��û�ָ������ֵ�ʹ洢��ģ���е�ָ���û�ָ�Ʊ�
	* @param  user id
	* @param	
	* @param	
  * @retval null
  */
void User_Load_Match_FeatureValue(uint16_t userId,UserRole_TypeDef userRole,uint8_t * feature)
{
//	Finger_Cmd_Package(userId,userRole,feature);
}
/**
	* @brief �´��û�ָ������ֵ�ʹ洢��ģ���е������û�ָ�Ʊ�
	* @param	
	* @param	
	* @retval	null
	*/
void User_Load_Match_AllFeatureValue(uint8_t * feature)
{
	uint16_t length = 494 + 3;
	Finger_Cmd(CMD_LOAD_FEATURE_MATCH_ALL,length>>8,length,0x00,0x00);
	Finger_Cmd_Package(CMD_LOAD_FEATURE_MATCH_ALL,length>>8,length,0x00,0x00,0x0000,USER_ROLE_NULL,feature);
}
/**
	* @brief  �´��û�ָ������ֵ�Ͳɼ����û�ָ�Ʊȶ�
	* @param	
	* @param	
	* @retval	null
	*/
void User_Load_Match_Collection(uint16_t userId,uint8_t * feature)
{
	uint16_t length = 494 + 3;
	Finger_Cmd(CMD_LOAD_FEATURE_MATCH_COLLECTION,length>>8,length,0x00,0x00);
	Finger_Cmd_Package(CMD_LOAD_FEATURE_MATCH_COLLECTION,length>>8,length,0x00,0x00,userId,USER_ROLE_1,feature);
}
/***********************************DealWith Data*********************************************************/
// memset FingerReceMes

//clear Featurn
void ClearFingerFeaturn(void)
{
	memset(Featurn,0x00,sizeof(Featurn));
	FeaturnSum = 0;
	return;
}
/*****���ָ������ֵ*****/
uint8_t * get_featurn(void)
{
	int i=0,j = 0;
	for(i=4;i<495;i++)
	{
		Featurn[j] = Featurn[i];
		j++;
	}
	return Featurn;
}
/*****����ֵ��ֵ*****/
void retValue(retString * result,fReturn sMessage)
{
	result->type = sMessage.type;
	result->message = sMessage.message;
	result->userId = sMessage.userid;
	return ;
}
/**
	* @brief 	�����Ƿ���ȷ
	* @param  ����
	* @retval	-1:�������-2:��������ʧ�� 1��������ȷ
	*/
int Receive_MessageIsTrue(uint8_t * receMessage)
{
	uint8_t chk = 0;
	int i = 0;
	if(receMessage[0] == 0xF5 && receMessage[7]==0xF5)
	{
		for(i=1;i<6;i++)
			chk ^= receMessage[i];
		if(chk == receMessage[6])
			return 160;
		else
			return 161;
	}
	else
		return 162;
}
/*****���ݷ����ɽṹ��*****/
fReturn ReceString_to_struct(uint8_t * receMessage)
{
	fReturn sStr;
	int mesIsTrue = 0;
	mesIsTrue = Receive_MessageIsTrue(receMessage);
	if(mesIsTrue == 160)
	{
		sStr.type = receMessage[1];
		sStr.userid = receMessage[2]<<8 | receMessage[3];
		sStr.message = receMessage[4];
		sStr.ack5bit = receMessage[5];
	}
	else
	{
		sStr.message = mesIsTrue;
	}
	return sStr;
}


