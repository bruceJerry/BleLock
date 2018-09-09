/**
	@brief	ָ��ģ��Э�飬ͼ��ָ��ģ��
	@date		2016-04-08
	@auther	Micheal
	*/
#ifndef __HISS_HP_02_FINGER_H__
#define __HISS_HP_02_FINGER_H__

#include "string.h"
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;

#define FINGER_TIMEOUT								    1000		//touch_ctrl ����ָ��ģ��ʱ��
//#define FINGER_USART_IRQ						USART3_IRQn
#define HEADER											0xF5

/*****ָ��ģ�鷵��ֵ*****/
#define ACK_SUCCESS									    0x00	//�ɹ�
#define ACK_FAIL										0x01	//ָ��ʧ��
#define ACK_FULL										0x04	//���ݿ��Ѿ���
#define ACK_NOUSER									    0x05	//û������û�
#define ACK_USER_EXIST							        0x07	//�û��Ѿ�����
#define ACK_TIMEOUT									    0x08	//¼�볬ʱ
#define ACK_BREAK										0x18	//ǿ�ƹرյ�ǰ����
#define ACK_IMAGEFAIL								    0x84	//ͼ��ɼ����ϸ�


/*****�������*****/
#define CMD_REGISTER_1C3R                               0x01	//���������η���
#define CMD_REGISTER_2C2R                               0x02    //��ΰ�ѹע��
#define CMD_REGISTER_3C3R          	                0x03    //��ΰ�ѹע��
#define CMD_DELETE_SPECIFIC_USER                        0x04    //ɾ��ָ���û�
#define CMD_DELETE_ALL_USER                             0x05	//ɾ�������û�
#define CMD_GET_TOTAL_USER_NUM                          0x09    //��ȡ�����û��ĸ���
#define CMD_GET_ROLE_USER			        0x0A    //��ȡ�û�Ȩ��
#define CMD_VERIFY_ONE_TO_ONE                           0x0B    //һ��һ��֤
#define CMD_VERIFY_ONE_TO_ALL                           0X0C    //һ��ȫ����֤
#define CMD_GET_NOUSE_ID			        0x0D    //��ȡδʹ�õ��û�ID
#define CMD_SET_BAUDRATE				0x21    //���ò�����
#define CMD_GET_FEA                                     0X23    //��ȡָ������ֵ
#define CMD_GET_FINGER_IMAGE                            0X24    //��ȡָ��ͼ��
#define CMD_GETVERSION                                  0X26    //��ȡ�汾��Ϣ
#define CMD_SETGETMATCHLEVEL			        0x28    //���û�ȡͼ��Աȵȼ�
#define CMD_GET_USERID_ROLE	      	                0x2B    //��ȡע���û���ID��Ȩ��
#define CMD_GET_SPECIFIC_FEATURE                        0X31    //��ȡָ���û�������ֵ

#define CMD_LOAD_FEATURE				0x41    //�´�����ֵ
#define CMD_LOAD_FEATURE_MATCH_USERID			0x42    //�´�����ֵ��ָ��ID���û��Ա�
#define CMD_LOAD_FEATURE_MATCH_ALL			0x43    //�´�����ֵ�����е��û��Ա�
#define CMD_LOAD_FEATURE_MATCH_COLLECTION		0x44    //�´�����ֵ��ɼ��ĶԱ�

#define FEATURE_LENGTH							        494	//
#define REGISTER_MODE								CMD_REGISTER_1C3R //ע��ģʽ

/*****ָ��Ȩ��*****/
typedef enum 
{
	USER_ROLE_NULL = 0x00,
	USER_ROLE_1	=	0x01,
	USER_ROLE_2	=	0x02,
	USER_ROLE_3	=	0x03
}UserRole_TypeDef;

/*****������*****/
typedef enum
{
	BaudRate_9600   = 0x01,
	BaudRate_19200	= 0x02,
	BaudRate_38400	= 0x03,
	BaudRate_57600	= 0x04,
	BaudRate_115200	= 0x05
}BaudRate_TypeDef;

/*****Ӳ��ģʽ*****/
typedef enum
{
	RegisterMode_AS = 0,			//
	RegisterMode_DS	= 1				//
}RegisterMode_TypeDef;

/*****�ģʽ*****/
typedef enum 
{
	ActiveMode_Set = 0,				//
	ActiveMode_Get = 1				//
}ActiveMode_TypeDef;
/*****uint8_t ���ַ���*****/
typedef struct uintString
{
	uint8_t data[8];
	int length;
}uString;
/*****��ʽ��ָ��ģ���ֵ*****/
typedef struct fingerReturnValue
{
	uint8_t type;
	uint16_t userid;
	uint8_t message;
	uint8_t ack5bit;
}fReturn;
/**����ֵ**/
typedef struct returnString
{
	uint8_t type;
	uint8_t message;
	uint16_t userId;
	int temp;
//	char * fingerValue;
//	int fingerSum;
}retString;
void hp02_Usart_Config(void);

void finger_fputc(unsigned char *ch);
int finger_fgetc(void);
/*****?��???*****/
void hp02_Finger_Config(void);
void Finger_GPIO_Config(void);
/*****?�� ??*****/
void Finger_Start(void);
/*****?��?? ??*****/
void Finger_Reset(void);
/*****?�� ??*****/
void Finger_Stop(void);
/*****��ȡ�Ƿ���ָ�ư���*****/
int Finger_getTouch(void);
/*****д��ָ������*****/
void Finger_Cmd(uint8_t Type,uint8_t p1,uint8_t p2,uint8_t p3,uint8_t u6);

/**
  * @brief  ע��
  * @param  ??id
	*	@param	???��
  * @retval None
  */
void User_Registration(uint16_t userID,uint8_t role);

/**
  * @brief  ���������η��ص�ע�ᣨ 1C3R��
  * @param  ??id
	*	@param	???��
  * @retval None
  */
void User_Registration_1C3R(uint16_t userID,uint8_t role);
/**
  * @brief  ��ΰ�ѹע�ᣨ 2C2R��
  * @param  ??id
	*	@param	???��
  * @retval None
  */
void User_Registration_2C2R(uint16_t userID,uint8_t role);
/**
  * @brief  ��ΰ�ѹע�ᣨ 3C3R��
  * @param  ??id
	*	@param	???��
  * @retval None
  */
void User_Registration_3C3R(uint16_t userID,uint8_t role);
/**
  * @brief  ɾ���ض��û�
  * @param  ??id
  * @retval None
  */
void User_DeleteSpecific(uint16_t userID);
/**
  * @brief  ɾ�������û�
  * @param  null
  * @retval null
  */
void FingerUser_DeleteAll(void);
/**
  * @brief  ��ȡ�û�����
  * @param  null
  * @retval null
  */
void FingerUser_getAllSum(void);

/**
  * @brief 	��ȡ�û�Ȩ��
	* @param  null
  * @retval null
  */
void Finger_Version(void);
/**
  * @brief 	??��???id
	* @param  null
  * @retval null
  */
void User_GetNoUseID(void);

//1 �� 1 �ȶ�
void User_FingerOneToOne(uint16_t userID);

//1 �� N�ȶ�
void User_FingerOneToAll(void);

/**
  * @brief 	????��
	* @param  enum `BaudRate_TypeDef
  * @retval null
  */
void User_SetBaudRate(BaudRate_TypeDef baudrate);

/**
  * @brief 	��ȡָ������ֵ
	* @param  �û�id
  * @retval null
  */
void User_GetFeatureValue(uint16_t userid);
/**
  * @brief 	????��??��??��-176*176
	* @param  null
  * @retval null
  */
void User_GetIamge(void);

/**
  * @brief 	????��?
	* @param  null
  * @retval null
  */
void Finger_Version(void);

/**
  * @brief 	???? ????
	* @param  ??????
  * @retval null
  */
void Finger_SetGetMatchLevel(uint8_t level);

/**
  * @brief 	???????id???��?
	* @param  null
  * @retval null
  */
void User_GetUserID_Role(void);
/**
  * @brief 	?????????
	* @param  ????��AS��DS
	*	@param	????set��get
  * @retval null
  */
void Finger_SetGetRegisterMode(RegisterMode_TypeDef mode,ActiveMode_TypeDef active);

/**
  * @brief 	????????��???
	* @param  user id
  * @retval null
  */
void User_GetID_FeatureValue(uint16_t userId);

/**
  * @brief 	????????id??????
	* @param  user id
	* @param	?��
	* @param	???
  * @retval null
  */
void User_Load_Deposit_FeatureValue(uint16_t userId,UserRole_TypeDef userRole,uint8_t *feature);
/**
  * @brief 	??????????????
	* @param  user id
	* @param	?��
	* @param	???
  * @retval null
  */
void User_Load_Match_FeatureValue(uint16_t userId,UserRole_TypeDef userRole,uint8_t * feature);
/**
	* @brief ???????????��???
	* @param	??id
	* @param	???
	* @retval	null
	*/
void User_Load_Match_AllFeatureValue(uint8_t * feature);

/**
	* @brief  ??????????��?????
	* @param	??id
	* @param	???
	* @retval	null
	*/
void User_Load_Match_Collection(uint16_t userId,uint8_t * feature);

//����ֵ�Ĵ���
retString Receive_isType(fReturn receMessage);

//��ȡָ������ֵ
uint8_t * get_featurn(void);
//�ȴ�ָ�Ʒ���ֵ��ʱ
fReturn Wait_Finger_Return(void);
// memset FingerReceMes
void ClearFingerReceMes(void);
//clear Featurn
void ClearFingerFeaturn(void);
//��ָ�ư���ʱ
int FingerOutDealwith(void);

//Start
int Start_FingerStatus(void);
//stop
int Stop_FingerStatus(void);

#endif /*hiss_hp02_finger.h*/
