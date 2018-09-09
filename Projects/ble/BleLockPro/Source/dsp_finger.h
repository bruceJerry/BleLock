/**
	@brief	指纹模块协议，图正指纹模块
	@date		2016-04-08
	@auther	Micheal
	*/
#ifndef __HISS_HP_02_FINGER_H__
#define __HISS_HP_02_FINGER_H__

#include "string.h"
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;

#define FINGER_TIMEOUT								    1000		//touch_ctrl 重启指纹模块时间
//#define FINGER_USART_IRQ						USART3_IRQn
#define HEADER											0xF5

/*****指纹模块返回值*****/
#define ACK_SUCCESS									    0x00	//成功
#define ACK_FAIL										0x01	//指纹失败
#define ACK_FULL										0x04	//数据库已经满
#define ACK_NOUSER									    0x05	//没有这个用户
#define ACK_USER_EXIST							        0x07	//用户已经存在
#define ACK_TIMEOUT									    0x08	//录入超时
#define ACK_BREAK										0x18	//强制关闭当前命令
#define ACK_IMAGEFAIL								    0x84	//图像采集不合格


/*****命令参数*****/
#define CMD_REGISTER_1C3R                               0x01	//单次命令多次返回
#define CMD_REGISTER_2C2R                               0x02    //多次按压注册
#define CMD_REGISTER_3C3R          	                0x03    //多次按压注册
#define CMD_DELETE_SPECIFIC_USER                        0x04    //删除指定用户
#define CMD_DELETE_ALL_USER                             0x05	//删除所有用户
#define CMD_GET_TOTAL_USER_NUM                          0x09    //获取已有用户的个数
#define CMD_GET_ROLE_USER			        0x0A    //获取用户权限
#define CMD_VERIFY_ONE_TO_ONE                           0x0B    //一对一验证
#define CMD_VERIFY_ONE_TO_ALL                           0X0C    //一对全部验证
#define CMD_GET_NOUSE_ID			        0x0D    //获取未使用的用户ID
#define CMD_SET_BAUDRATE				0x21    //设置波特率
#define CMD_GET_FEA                                     0X23    //获取指纹特征值
#define CMD_GET_FINGER_IMAGE                            0X24    //获取指纹图像
#define CMD_GETVERSION                                  0X26    //获取版本信息
#define CMD_SETGETMATCHLEVEL			        0x28    //设置获取图像对比等级
#define CMD_GET_USERID_ROLE	      	                0x2B    //获取注册用户的ID和权限
#define CMD_GET_SPECIFIC_FEATURE                        0X31    //获取指定用户的特征值

#define CMD_LOAD_FEATURE				0x41    //下传特征值
#define CMD_LOAD_FEATURE_MATCH_USERID			0x42    //下传特征值与指定ID的用户对比
#define CMD_LOAD_FEATURE_MATCH_ALL			0x43    //下传特征值与所有的用户对比
#define CMD_LOAD_FEATURE_MATCH_COLLECTION		0x44    //下传特征值与采集的对比

#define FEATURE_LENGTH							        494	//
#define REGISTER_MODE								CMD_REGISTER_1C3R //注册模式

/*****指纹权限*****/
typedef enum 
{
	USER_ROLE_NULL = 0x00,
	USER_ROLE_1	=	0x01,
	USER_ROLE_2	=	0x02,
	USER_ROLE_3	=	0x03
}UserRole_TypeDef;

/*****波特率*****/
typedef enum
{
	BaudRate_9600   = 0x01,
	BaudRate_19200	= 0x02,
	BaudRate_38400	= 0x03,
	BaudRate_57600	= 0x04,
	BaudRate_115200	= 0x05
}BaudRate_TypeDef;

/*****硬件模式*****/
typedef enum
{
	RegisterMode_AS = 0,			//
	RegisterMode_DS	= 1				//
}RegisterMode_TypeDef;

/*****活动模式*****/
typedef enum 
{
	ActiveMode_Set = 0,				//
	ActiveMode_Get = 1				//
}ActiveMode_TypeDef;
/*****uint8_t 的字符串*****/
typedef struct uintString
{
	uint8_t data[8];
	int length;
}uString;
/*****格式化指纹模块的值*****/
typedef struct fingerReturnValue
{
	uint8_t type;
	uint16_t userid;
	uint8_t message;
	uint8_t ack5bit;
}fReturn;
/**返回值**/
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
/*****?φ???*****/
void hp02_Finger_Config(void);
void Finger_GPIO_Config(void);
/*****?φ ??*****/
void Finger_Start(void);
/*****?φ?? ??*****/
void Finger_Reset(void);
/*****?φ ??*****/
void Finger_Stop(void);
/*****获取是否有指纹按下*****/
int Finger_getTouch(void);
/*****写入指纹命令*****/
void Finger_Cmd(uint8_t Type,uint8_t p1,uint8_t p2,uint8_t p3,uint8_t u6);

/**
  * @brief  注册
  * @param  ??id
	*	@param	???О
  * @retval None
  */
void User_Registration(uint16_t userID,uint8_t role);

/**
  * @brief  单次命令多次返回的注册（ 1C3R）
  * @param  ??id
	*	@param	???О
  * @retval None
  */
void User_Registration_1C3R(uint16_t userID,uint8_t role);
/**
  * @brief  多次按压注册（ 2C2R）
  * @param  ??id
	*	@param	???О
  * @retval None
  */
void User_Registration_2C2R(uint16_t userID,uint8_t role);
/**
  * @brief  多次按压注册（ 3C3R）
  * @param  ??id
	*	@param	???О
  * @retval None
  */
void User_Registration_3C3R(uint16_t userID,uint8_t role);
/**
  * @brief  删除特定用户
  * @param  ??id
  * @retval None
  */
void User_DeleteSpecific(uint16_t userID);
/**
  * @brief  删除所有用户
  * @param  null
  * @retval null
  */
void FingerUser_DeleteAll(void);
/**
  * @brief  获取用户总数
  * @param  null
  * @retval null
  */
void FingerUser_getAllSum(void);

/**
  * @brief 	获取用户权限
	* @param  null
  * @retval null
  */
void Finger_Version(void);
/**
  * @brief 	??δ???id
	* @param  null
  * @retval null
  */
void User_GetNoUseID(void);

//1 比 1 比对
void User_FingerOneToOne(uint16_t userID);

//1 比 N比对
void User_FingerOneToAll(void);

/**
  * @brief 	????ê
	* @param  enum `BaudRate_TypeDef
  * @retval null
  */
void User_SetBaudRate(BaudRate_TypeDef baudrate);

/**
  * @brief 	获取指纹特征值
	* @param  用户id
  * @retval null
  */
void User_GetFeatureValue(uint16_t userid);
/**
  * @brief 	????д??φ??б-176*176
	* @param  null
  * @retval null
  */
void User_GetIamge(void);

/**
  * @brief 	????х?
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
  * @brief 	???????id???О?
	* @param  null
  * @retval null
  */
void User_GetUserID_Role(void);
/**
  * @brief 	?????????
	* @param  ????ìASìDS
	*	@param	????setìget
  * @retval null
  */
void Finger_SetGetRegisterMode(RegisterMode_TypeDef mode,ActiveMode_TypeDef active);

/**
  * @brief 	????????φ???
	* @param  user id
  * @retval null
  */
void User_GetID_FeatureValue(uint16_t userId);

/**
  * @brief 	????????id??????
	* @param  user id
	* @param	?О
	* @param	???
  * @retval null
  */
void User_Load_Deposit_FeatureValue(uint16_t userId,UserRole_TypeDef userRole,uint8_t *feature);
/**
  * @brief 	??????????????
	* @param  user id
	* @param	?О
	* @param	???
  * @retval null
  */
void User_Load_Match_FeatureValue(uint16_t userId,UserRole_TypeDef userRole,uint8_t * feature);
/**
	* @brief ???????????φ???
	* @param	??id
	* @param	???
	* @retval	null
	*/
void User_Load_Match_AllFeatureValue(uint8_t * feature);

/**
	* @brief  ??????????φ?????
	* @param	??id
	* @param	???
	* @retval	null
	*/
void User_Load_Match_Collection(uint16_t userId,uint8_t * feature);

//返回值的处理
retString Receive_isType(fReturn receMessage);

//提取指纹特征值
uint8_t * get_featurn(void);
//等待指纹返回值超时
fReturn Wait_Finger_Return(void);
// memset FingerReceMes
void ClearFingerReceMes(void);
//clear Featurn
void ClearFingerFeaturn(void);
//有指纹按下时
int FingerOutDealwith(void);

//Start
int Start_FingerStatus(void);
//stop
int Stop_FingerStatus(void);

#endif /*hiss_hp02_finger.h*/
