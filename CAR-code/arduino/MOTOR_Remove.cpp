#include "MOTOR_Remove.h"
#include "Arduino.h"
#include "Xunji.h"

void MOTOR_INIT(){
  // 左电机
  pinMode(MOTOR_L_ahead_1,OUTPUT);              
  pinMode(MOTOR_L_ahead_2,OUTPUT);
  pinMode(MOTOR_L_back_1,OUTPUT);
  pinMode(MOTOR_L_back_2,OUTPUT);
  //右电机-
  pinMode(MOTOR_R_ahead_1,OUTPUT);
  pinMode(MOTOR_R_ahead_1,OUTPUT);
  pinMode(MOTOR_R_back_1,OUTPUT);
  pinMode(MOTOR_R_back_1,OUTPUT);
  // PWM引脚输出
  pinMode(MOTOR_L_ahead_PWM,OUTPUT);
  pinMode(MOTOR_L_back_PWM,OUTPUT);
  pinMode(MOTOR_R_ahead_PWM,OUTPUT);
  pinMode(MOTOR_R_back_PWM,OUTPUT);
  // pwm引脚电平拉低
  digitalWrite(MOTOR_L_ahead_PWM,0);
  digitalWrite(MOTOR_L_back_PWM,0);
  digitalWrite(MOTOR_R_ahead_PWM,0);
  digitalWrite(MOTOR_R_back_PWM,0);     
}

//PWM定义？？？
//************************************************************************************************
void MOTOR_Remove_Site_PWM(uint MOTOR_Site, int pwm){
  analogWrite(MOTOR_Site, pwm);
}

//单个舵机运动函数
//*************************************************************************************************
void MOTOR_L_ahead_go(){
  /*
   * MOTOR_L_ahead_1 接 IN3 
   * MOTOR_L_ahead_2 接 IN4
   */
  digitalWrite(MOTOR_L_ahead_1,HIGH);    
  digitalWrite(MOTOR_L_ahead_2,LOW);      
}

void MOTOR_L_ahead_back(){
    /*
   * MOTOR_L_ahead_1 接 IN3 
   * MOTOR_L_ahead_2 接 IN4
   */
  digitalWrite(MOTOR_L_ahead_1,LOW);    
  digitalWrite(MOTOR_L_ahead_2,HIGH); 
}

void MOTOR_L_back_back(){
    /*
   * MOTOR_L_back_1 接 IN2 
   * MOTOR_L_back_2 接 IN1
   */
  digitalWrite(MOTOR_L_back_1,HIGH);    
  digitalWrite(MOTOR_L_back_2,LOW); 
}

 
void MOTOR_L_back_go(){
    /*
   * MOTOR_L_back_1 接 IN2 
   * MOTOR_L_back_2 接 IN1
   */
  digitalWrite(MOTOR_L_back_1,LOW);    
  digitalWrite(MOTOR_L_back_2,HIGH); 
}

void MOTOR_R_ahead_back(){
    /*
   * MOTOR_R_ahead_1 接 IN1 
   * MOTOR_R_ahead_2 接 IN2
   */
  digitalWrite(MOTOR_R_ahead_1,HIGH);    
  digitalWrite(MOTOR_R_ahead_2,LOW); 
}
void MOTOR_R_ahead_go(){
    /*
   * MOTOR_R_ahead_1 接 IN1 
   * MOTOR_R_ahead_2 接 IN2
   */
  digitalWrite(MOTOR_R_ahead_1,LOW);    
  digitalWrite(MOTOR_R_ahead_2,HIGH); 
}

void MOTOR_R_back_back(){
    /*
   * MOTOR_R_back_1 接 IN3 
   * MOTOR_R_back_2 接 IN4
   */
  digitalWrite(MOTOR_R_back_1,HIGH);    
  digitalWrite(MOTOR_R_back_2,LOW); 
}


void MOTOR_R_back_go(){
    /*
   * MOTOR_R_back_1 接 IN3 
   * MOTOR_R_back_2 接 IN4
   */
  digitalWrite(MOTOR_R_back_1,LOW);    
  digitalWrite(MOTOR_R_back_2,HIGH); 
}

//小车整体的运动
//**********************************************************************************************
void Car_go(){//OK
  MOTOR_L_ahead_go();
  MOTOR_L_back_go();
  MOTOR_R_ahead_go();
  MOTOR_R_back_go();
  MOTOR_Remove_Site_PWM(MOTOR_L_ahead_PWM, Xunji.PWML_zhixian);
  MOTOR_Remove_Site_PWM(MOTOR_L_back_PWM, Xunji.PWML_zhixian);
  MOTOR_Remove_Site_PWM(MOTOR_R_ahead_PWM, Xunji.PWMR_zhixian);
  MOTOR_Remove_Site_PWM(MOTOR_R_back_PWM, Xunji.PWMR_zhixian);
}
void Car_go_fast(){//OK
  MOTOR_L_ahead_go();
  MOTOR_L_back_go();
  MOTOR_R_ahead_go();
  MOTOR_R_back_go();
  MOTOR_Remove_Site_PWM(MOTOR_L_ahead_PWM, Xunji.PWML_zhixian+25);
  MOTOR_Remove_Site_PWM(MOTOR_L_back_PWM, Xunji.PWML_zhixian+25);
  MOTOR_Remove_Site_PWM(MOTOR_R_ahead_PWM, Xunji.PWMR_zhixian+25);
  MOTOR_Remove_Site_PWM(MOTOR_R_back_PWM, Xunji.PWMR_zhixian+25);
}
void Car_back(){//OK
  MOTOR_L_ahead_back();
  MOTOR_L_back_back();
  MOTOR_R_ahead_back();
  MOTOR_R_back_back();
  MOTOR_Remove_Site_PWM(MOTOR_L_ahead_PWM, 53);
  MOTOR_Remove_Site_PWM(MOTOR_L_back_PWM, 53);
  MOTOR_Remove_Site_PWM(MOTOR_R_ahead_PWM, 56);
  MOTOR_Remove_Site_PWM(MOTOR_R_back_PWM, 56);
  
}
void Car_shun(){
  MOTOR_L_ahead_go();
  MOTOR_L_back_go();
  MOTOR_R_ahead_back();
  MOTOR_R_back_back();
}
void Car_ni(){
  MOTOR_L_ahead_back();
  MOTOR_L_back_back();
  MOTOR_R_ahead_go();
  MOTOR_R_back_go();
}
void Car_left(){
  MOTOR_L_ahead_back();
  MOTOR_L_back_go();
  MOTOR_R_ahead_go();
  MOTOR_R_back_back();
}
void Car_right(){
  MOTOR_L_ahead_go();
  MOTOR_L_back_back();
  MOTOR_R_ahead_back();
  MOTOR_R_back_go();
}
void Car_stop(){//OK
  MOTOR_Remove_Site_PWM(MOTOR_L_ahead_PWM, 0);
  MOTOR_Remove_Site_PWM(MOTOR_L_back_PWM, 0);
  MOTOR_Remove_Site_PWM(MOTOR_R_ahead_PWM, 0);
  MOTOR_Remove_Site_PWM(MOTOR_R_back_PWM, 0);
}
//待写：顺时针90，逆时针90，顺时针45，逆时针45，掉头
