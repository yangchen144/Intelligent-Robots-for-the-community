#include "Arduino.h"
#include "MOTOR_Remove.h"
#include "Xunji.h"

void Xunji_INIT(){
  pinMode(IN_1, INPUT_PULLUP);    //循迹接口初始化
  pinMode(IN_2, INPUT_PULLUP);
  pinMode(IN_3, INPUT_PULLUP);
  pinMode(IN_4, INPUT_PULLUP);
}

void Xunji_Run(int cmd){
  switch(cmd){
    case 1:
      Car_go();
      break;
    case 3:// TURNLEFTa,往左拐一点

      MOTOR_L_ahead_go();
      MOTOR_L_back_go();
      MOTOR_R_ahead_go();
      MOTOR_R_back_go();
    
      MOTOR_Remove_Site_PWM(MOTOR_L_ahead_PWM,  0); 
      MOTOR_Remove_Site_PWM(MOTOR_L_back_PWM,  0);
      MOTOR_Remove_Site_PWM(MOTOR_R_ahead_PWM,  Xunji.PWM_D+35); 
      MOTOR_Remove_Site_PWM(MOTOR_R_back_PWM,  Xunji.PWM_D); 
      break;
    case 5://TURNLEFTb，往左拐大点
      MOTOR_L_ahead_back();
      MOTOR_L_back_back();
      MOTOR_Remove_Site_PWM(MOTOR_L_ahead_PWM,  40); 
      MOTOR_Remove_Site_PWM(MOTOR_L_back_PWM,  40);
      MOTOR_Remove_Site_PWM(MOTOR_R_ahead_PWM,  Xunji.PWM_Dawan+45); 
      MOTOR_Remove_Site_PWM(MOTOR_R_back_PWM,  Xunji.PWM_Dawan);   
      break;
    case 4:// TURNRIGHTa，往右拐小点

      MOTOR_L_ahead_go();
      MOTOR_L_back_go();
      MOTOR_R_ahead_go();
      MOTOR_R_back_go();
    
      MOTOR_Remove_Site_PWM(MOTOR_L_ahead_PWM,  Xunji.PWM_D+35); 
      MOTOR_Remove_Site_PWM(MOTOR_L_back_PWM,  Xunji.PWM_D);
      MOTOR_Remove_Site_PWM(MOTOR_R_ahead_PWM,  0); 
      MOTOR_Remove_Site_PWM(MOTOR_R_back_PWM,  0);  
      break;      
    case 6://TURNRIGHTb，往右拐大点
      MOTOR_R_ahead_back();
      MOTOR_R_back_back();
      MOTOR_Remove_Site_PWM(MOTOR_L_ahead_PWM,  Xunji.PWM_Dawan+45); 
      MOTOR_Remove_Site_PWM(MOTOR_L_back_PWM,  Xunji.PWM_Dawan);
      MOTOR_Remove_Site_PWM(MOTOR_R_ahead_PWM,  40); 
      MOTOR_Remove_Site_PWM(MOTOR_R_back_PWM,  40);    
      break;  
    case 7:
//      MOTOR_L_ahead_back();
//      MOTOR_L_back_back();
//      MOTOR_R_ahead_go();
//      MOTOR_R_back_go();
//      MOTOR_Remove_Site_PWM(MOTOR_L_ahead_PWM,  Xunji.PWML+33); 
//      MOTOR_Remove_Site_PWM(MOTOR_L_back_PWM,  Xunji.PWML+33);
//      MOTOR_Remove_Site_PWM(MOTOR_R_ahead_PWM,  Xunji.PWMR+33); 
//      MOTOR_Remove_Site_PWM(MOTOR_R_back_PWM,  Xunji.PWMR+33);  
      break;        
    case 8:
//      MOTOR_L_ahead_go();
//      MOTOR_L_back_go();
//      MOTOR_R_ahead_back();
//      MOTOR_R_back_back();
//      MOTOR_Remove_Site_PWM(MOTOR_L_ahead_PWM,  Xunji.PWML+33); 
//      MOTOR_Remove_Site_PWM(MOTOR_L_back_PWM,  Xunji.PWML+33);
//      MOTOR_Remove_Site_PWM(MOTOR_R_ahead_PWM,  Xunji.PWMR+33); 
//      MOTOR_Remove_Site_PWM(MOTOR_R_back_PWM,  Xunji.PWMR+33);  
      break;        
    case 0:
      Car_stop();
      //while(1);
      break;               
  }
}

void Xunji_JC(){
   while(1){//进入循迹函数
            Xunji.value_1 = digitalRead(IN_1);
            Xunji.value_2 = digitalRead(IN_2);
            Xunji.value_3 = digitalRead(IN_3);
            Xunji.value_4 = digitalRead(IN_4);
           if(Xunji.value_2 == HIGH && Xunji.value_1 == LOW && Xunji.value_3 ==LOW && Xunji.value_4 == HIGH){//直线
                   Xunji_Run(Xunji.FORWARD);//1
                }
           else if(Xunji.value_2 == HIGH && Xunji.value_1 == HIGH && Xunji.value_3 ==LOW && Xunji.value_4 == HIGH){//左小白，已经往左偏小       
                   Xunji_Run(Xunji.TURNRIGHTa);//4
                }
           else if(Xunji.value_2 ==HIGH && Xunji.value_1 == HIGH && Xunji.value_3 ==HIGH && Xunji.value_4 == LOW){//左大白，已经往左偏大            
                   Xunji_Run(Xunji.TURNRIGHTb);//6
                }
           else if(Xunji.value_2 ==HIGH && Xunji.value_1 == LOW && Xunji.value_3 ==HIGH && Xunji.value_4 == HIGH){//右小白，已经往右偏小       
                  Xunji_Run(Xunji.TURNLEFTa);//3
                }
           else if(Xunji.value_2 ==LOW && Xunji.value_1 == HIGH && Xunji.value_3 ==HIGH && Xunji.value_4 == HIGH){//右大白，已经往右偏大
                  Xunji_Run(Xunji.TURNLEFTb);//5
                }      
           else if(Xunji.value_2 == HIGH && Xunji.value_1 == LOW && Xunji.value_3 ==LOW && Xunji.value_4 == LOW){//往右直拐***待优化***
                  Xunji_Run(Xunji.RIGHT);       
                }   
           else if(Xunji.value_2 == LOW && Xunji.value_1 == HIGH && Xunji.value_3 ==HIGH && Xunji.value_4 == HIGH){//往左直拐***待优化***
                  Xunji_Run(Xunji.LEFT);       
                }               
           else if(Xunji.value_2 ==LOW && Xunji.value_1 == LOW && Xunji.value_3 ==LOW && Xunji.value_4 == LOW){//ting
                  Xunji_Run(Xunji.STOP);
                  break;
                }   
             }//while到此为止
}
