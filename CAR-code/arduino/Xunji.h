#ifndef _Xunji_h_
#define _Xunji_h_

#include "Arduino.h"

#ifndef IN_1
#define IN_1  A8
#endif

#ifndef IN_2
#define IN_2  A9
#endif

#ifndef IN_3
#define IN_3  A10
#endif

#ifndef IN_4
#define IN_4  A11
#endif

struct
{
  //循迹接口
  int value_1 = 0;
  int value_2 = 0;
  int value_3 = 0;
  int value_4 = 0;

  
  //循迹状态
  int STOP = 0;
  int FORWARD = 1;
  int BACKWARD = 2;
  int TURNLEFTa  =3;
  int TURNRIGHTa = 4;
  int TURNLEFTb = 5;
  int TURNRIGHTb = 6;
  int LEFT = 7;
  int RIGHT = 8;

  int PWML_zhixian = 42;
  int PWMR_zhixian = 45;

  //循迹时车左右轮子速度调整
  int PWM_X = 50;  //原来是43

  int PWM_D = 80;

  int PWM_Dawan = 80;
  
}Xunji;

void Xunji_INIT();
void Xunji_Run(int cmd);
void Xunji_JC();

#endif
