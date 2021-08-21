#ifndef _Openmv_h_
#define _Openmv_h_

#include "Arduino.h"

struct
{
  String return_value;
  int erweima_value;
  int a ;
  int data[3];
}Openmv;

void Openmv_began();
void Openmv_began_erweima();
void Openmv_jianche_return_value();
void jixiebi_guiwei();
void Jixiebi_choose();
void jixiebi_shiyan();
void Fenge(String zifuchuan,String fengefu);
void jixiebi_kongzhi(int A,int B,int C);

#endif
