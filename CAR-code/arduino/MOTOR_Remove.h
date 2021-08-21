#ifndef _MOTOR_Remove_H_
#define _MOTOR_Remove_H_

#include"Arduino.h"

#ifndef uint
#define uint unsigned int 
#endif

//电机引脚宏定义
//************************************************************************************************
#ifndef MOTOR_L_ahead_1
#define MOTOR_L_ahead_1   22    // 左前方电机正反转引脚定义
#endif
#ifndef MOTOR_L_ahead_2
#define MOTOR_L_ahead_2   24    // 左前方电机正反转引脚定义
#endif
#ifndef MOTOR_L_back_1
#define MOTOR_L_back_1    26    // 左后方电机正反转引脚定义
#endif
#ifndef MOTOR_L_back_2
#define MOTOR_L_back_2    28    // 左后方电机正反转引脚定义
#endif
#ifndef MOTOR_R_ahead_1
#define MOTOR_R_ahead_1   30    // 右前方电机正反转引脚定义
#endif
#ifndef MOTOR_R_ahead_2
#define MOTOR_R_ahead_2   32    // 右前方电机正反转引脚定义
#endif
#ifndef MOTOR_R_back_1
#define MOTOR_R_back_1    34    // 右后方电机正反转引脚定义
#endif
#ifndef MOTOR_R_back_2
#define MOTOR_R_back_2    36    // 右后方电机正反转引脚定义
#endif
#ifndef MOTOR_L_ahead_PWM
#define MOTOR_L_ahead_PWM   8    // 左前方电机PWM输出
#endif
#ifndef MOTOR_L_back_PWM 
#define MOTOR_L_back_PWM    9    // 左后方电机PWM输出
#endif
#ifndef MOTOR_R_ahead_PWM 
#define MOTOR_R_ahead_PWM   10   // 左前方电机PWM输出
#endif
#ifndef MOTOR_R_back_PWM 
#define MOTOR_R_back_PWM    11   // 左前方电机PWM输出
#endif





//单个电机运动函数定义
//***************************************************************************************************
void MOTOR_INIT();
void MOTOR_L_ahead_go();
void MOTOR_L_ahead_back();
void MOTOR_L_back_go();
void MOTOR_L_back_back();
void MOTOR_R_ahead_go();
void MOTOR_R_ahead_back();
void MOTOR_R_back_go();
void MOTOR_R_back_back();
void MOTOR_Remove_Site_PWM(uint MOTOR_Site, int pwm);

//小车整体运动函数定义
//*******************************************************************************************************
void Car_go();
void Car_go_fast();
void Car_back();
void Car_shun();
void Car_ni();
void Car_left();
void Car_right();
void Car_stop();



#endif
