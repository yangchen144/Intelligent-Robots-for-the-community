#include "Arduino.h"
#include "Openmv.h"
#include "SoftwareSerial.h"
#include "DMREG.h"
#include "MOTOR_Remove.h"

String  m= "";
extern SoftwareSerial Serial30;

void Openmv_began(){
  Serial30.write("began");
  Serial.println("定位指令发送");
}
void Openmv_began_erweima(){
  Serial30.write("erweima");
  Serial.println("二维码检测发送");
}

void Openmv_jianche_return_value(){
       while (Serial3.available() > 0)//循环串口是否有数据
        {
        m += char(Serial3.read());//叠加数据到comdata
        delay(2);//延时等待响应
        }
        Serial.print("m = ");
        Serial.println(m);
}
void jixiebi_shiyan(){
  Serial2.write(DM_Action2, 5);
  Serial.println("已发送动作组2");
}
void jixiebi_guiwei(){
  Serial2.write(DM_Action1, 5);
  Serial.println("已发送归位动作组");
}
void Jixiebi_choose(){
  while(1){
    if(Serial3.available()){
      m = "";
      Openmv_jianche_return_value();
      Fenge(m,",");
      Serial.println("下面三个是接受到的数值：");
      Serial.println(Openmv.data[0]);
      Serial.println(Openmv.data[1]);
      Serial.println(Openmv.data[2]);
//      jixiebi_kongzhi(159, 90, 60);
      jixiebi_kongzhi(Openmv.data[0],Openmv.data[1],Openmv.data[2]);
      break;
    }
  }
}


void Fenge(String zifuchuan,String fengefu)
 {
  int weizhi; //找查的位置
  int x;
  int i;
  String temps = "";//临时字符串
  do
  {
      weizhi = zifuchuan.indexOf(fengefu);//找到位置
      if(weizhi != -1)//如果位置不为空
      {
          temps=zifuchuan.substring(0,weizhi);//打印取第一个字符
          zifuchuan = zifuchuan.substring(weizhi+fengefu.length(), zifuchuan.length());
          //分隔后只取后面一段内容 以方便后面找查
      }
      else
      {  //上面实在找不到了就把最后的 一个分割值赋值出来以免遗漏
         if(zifuchuan.length() > 0)
          temps=zifuchuan; 
      }
//      Serial.println(temps);//在这里执行分割出来的字符下面不然又清空了
      x = atoi(temps.c_str());
      if(temps == "90")
        Serial.println("ok");
      Openmv.data[i] = x;
      Serial.print("i = ");
      Serial.println(i);
      Serial.println(Openmv.data[i]);
      temps="";
      i++;
   }
   while(weizhi >=0);   
} 

void jixiebi_kongzhi(int A,int B,int C)
{ 
  Serial2.write(DM4_Speed9_Position_0, 10);     //先让爪子张开
    switch(A)
  {
            case 108:
                Serial2.write(DM0_Speed9_Position_108, 10);
                break;
            case 113:
                Serial2.write(DM0_Speed9_Position_113, 10);
                break;
            case 114:
                Serial2.write(DM0_Speed9_Position_114, 10);
                break;
            case 115:
                Serial2.write(DM0_Speed9_Position_115, 10);
                break;
            case 116:
                Serial2.write(DM0_Speed9_Position_116, 10);
                break;
            case 117:
                Serial2.write(DM0_Speed9_Position_117, 10);
                break;
            case 118:
                Serial2.write(DM0_Speed9_Position_118, 10);
                break;
            case 119:
                Serial2.write(DM0_Speed9_Position_119, 10);
                break;
            case 120:
                Serial2.write(DM0_Speed9_Position_120, 10);
                break;
            case 121:
                Serial2.write(DM0_Speed9_Position_121, 10);
                break;
            case 122:
                Serial2.write(DM0_Speed9_Position_122, 10);
                break;
            case 123:
                Serial2.write(DM0_Speed9_Position_123, 10);
                break;
            case 124:
                Serial2.write(DM0_Speed9_Position_124, 10);
                break;
            case 125:
                Serial2.write(DM0_Speed9_Position_125, 10);
                break;
            case 126:
                Serial2.write(DM0_Speed9_Position_126, 10);
                break;
            case 127:
                Serial2.write(DM0_Speed9_Position_127, 10);
               break;
            case 128:
                Serial2.write(DM0_Speed9_Position_128, 10);
               break;
            case 129:
                Serial2.write(DM0_Speed9_Position_129, 10);
               break;
            case 130:
                Serial2.write(DM0_Speed9_Position_130, 10);
                break;
            case 131:
                Serial2.write(DM0_Speed9_Position_131, 10);
                break;
            case 132:
                Serial2.write(DM0_Speed9_Position_132, 10);
                break;
            case 133:
                Serial2.write(DM0_Speed9_Position_133, 10);
               break;
            case 134:
                Serial2.write(DM0_Speed9_Position_134, 10);
                break;
            case 135:
                Serial2.write(DM0_Speed9_Position_135, 10);
               break;
            case 136:
                Serial2.write(DM0_Speed9_Position_136, 10);
               break;
            case 137:
                Serial2.write(DM0_Speed9_Position_137, 10);
                break;
            case 138:
                Serial2.write(DM0_Speed9_Position_138, 10);
                break;
            case 139:
                Serial2.write(DM0_Speed9_Position_139, 10);
                break;
            case 140:
                Serial2.write(DM0_Speed9_Position_140, 10);
               break;
            case 141:
                Serial2.write(DM0_Speed9_Position_141, 10);
               break;
            case 142:    
                Serial2.write(DM0_Speed9_Position_142, 10);
               break;
            case 143:
                Serial2.write(DM0_Speed9_Position_143, 10);
               break;
            case 144:
                Serial2.write(DM0_Speed9_Position_144, 10);
                break;
            case 145:
                Serial2.write(DM0_Speed9_Position_145, 10);
                break;
            case 146:
                Serial2.write(DM0_Speed9_Position_146, 10);
               break;
            case 147:
                Serial2.write(DM0_Speed9_Position_147, 10);
                break;
            case 148:
                Serial2.write(DM0_Speed9_Position_148, 10);
               break;
            case 149:
                Serial2.write(DM0_Speed9_Position_149, 10);
                break;
            case 150:
                Serial2.write(DM0_Speed9_Position_150, 10);
                Serial.println("niubi");
                break;
            case 151:
                Serial2.write(DM0_Speed9_Position_151, 10);
                break;
            case 152:
                Serial2.write(DM0_Speed9_Position_152, 10);
               break;
            case 153:
                Serial2.write(DM0_Speed9_Position_153, 10);
                break;
            case 154:
                Serial2.write(DM0_Speed9_Position_154, 10);
                break;
            case 155:
                Serial2.write(DM0_Speed9_Position_155, 10);
                break;
            case 156:
                Serial2.write(DM0_Speed9_Position_156, 10);
                break;
            case 157:
                Serial2.write(DM0_Speed9_Position_157, 10);
                break;
            case 158:
                Serial2.write(DM0_Speed9_Position_158, 10);
                 break;
            case 159:
                Serial2.write(DM0_Speed9_Position_159, 10);
                break;
            case 160:
                Serial2.write(DM0_Speed9_Position_160, 10);
                 break;
            case 161:
                Serial2.write(DM0_Speed9_Position_161, 10);
                 break;
            case 162:
                Serial2.write(DM0_Speed9_Position_162, 10);
                 break;
            case 163:
                Serial2.write(DM0_Speed9_Position_163, 10);
                 break;
            case 164:
                Serial2.write(DM0_Speed9_Position_164, 10);
                break;
            case 165:
                Serial2.write(DM0_Speed9_Position_165, 10);
               break;
            case 166:
                Serial2.write(DM0_Speed9_Position_166, 10);
               break;
            case 167:
                Serial2.write(DM0_Speed9_Position_167, 10);
               break;
            case 168:
                Serial2.write(DM0_Speed9_Position_168, 10);
               break;
            case 169:
                Serial2.write(DM0_Speed9_Position_169, 10);
               break;
            case 170:
                Serial2.write(DM0_Speed9_Position_170, 10);
               break;
            case 171:
                Serial2.write(DM0_Speed9_Position_171, 10);
               break;
            case 176:
                Serial2.write(DM0_Speed9_Position_176, 10);
                break;
            case 180:
                Serial2.write(DM0_Speed9_Position_180, 10);
                break;
  }


    switch(B)
  {
            case 63:
                Serial2.write(DM1_Speed9_Position_63, 10);
                Serial.println("niubi");
        break;
            case 72:
                Serial2.write(DM1_Speed9_Position_72, 10);
        break;    
            case 81:
                Serial2.write(DM1_Speed9_Position_81, 10);
        break;
           case 90:
                Serial2.write(DM1_Speed9_Position_90, 10);
        break;
            case 99:
                Serial2.write(DM1_Speed9_Position_99, 10);
        break;
            case 108:
                Serial2.write(DM1_Speed9_Position_108, 10);
        break;
            case 117:
                Serial2.write(DM1_Speed9_Position_117, 10);
        break;
            case 126:
                Serial2.write(DM1_Speed9_Position_126, 10);
        break;
            case 135:
                Serial2.write(DM1_Speed9_Position_135, 10);
        break;
  }


    switch(C)
  {
            case 54:
                Serial2.write(DM2_Speed9_Position_54, 10);
        break;
            case 55:
                Serial2.write(DM2_Speed9_Position_55, 10);
        break;
            case 56:
                Serial2.write(DM2_Speed9_Position_56, 10);
        break;
            case 57:
                Serial2.write(DM2_Speed9_Position_57, 10);
        break;
            case 58:
                Serial2.write(DM2_Speed9_Position_58, 10);
        break;
            case 59:
                Serial2.write(DM2_Speed9_Position_59, 10);
        break;
            case 60:
                Serial2.write(DM2_Speed9_Position_60, 10);
        break;
            case 61:
                Serial2.write(DM2_Speed9_Position_61, 10);
        break;
            case 62:
                Serial2.write(DM2_Speed9_Position_62, 10);
        break;
            case 63:
                Serial2.write(DM2_Speed9_Position_63, 10);
        break;
            case 64:
                Serial2.write(DM2_Speed9_Position_64, 10);
        break;
            case 65:
                Serial2.write(DM2_Speed9_Position_65, 10);
        break;
            case 66:
                Serial2.write(DM2_Speed9_Position_66, 10);
        break;
            case 67:
                Serial2.write(DM2_Speed9_Position_67, 10);
        break;
            case 68:
                Serial2.write(DM2_Speed9_Position_68, 10);
        break;
            case 69:
                Serial2.write(DM2_Speed9_Position_69, 10);
        break;
            case 70:
                Serial2.write(DM2_Speed9_Position_70, 10);
        break;
            case 71:
                Serial2.write(DM2_Speed9_Position_71, 10);
        break;
            case 72:
                Serial2.write(DM2_Speed9_Position_72, 10);
                Serial.println("niubi");
        break;
            case 73:
                Serial2.write(DM2_Speed9_Position_73, 10);
        break;
            case 74:
                Serial2.write(DM2_Speed9_Position_74, 10);
        break;
            case 75:
                Serial2.write(DM2_Speed9_Position_75, 10);
        break;
            case 76:
                Serial2.write(DM2_Speed9_Position_76, 10);
        break;
            case 77:
                Serial2.write(DM2_Speed9_Position_77, 10);
        break;
            case 78:
                Serial2.write(DM2_Speed9_Position_78, 10);
        break;
            case 79:
                Serial2.write(DM2_Speed9_Position_79, 10);
        break;
            case 80:
                Serial2.write(DM2_Speed9_Position_80, 10);
        break;
            case 81:
                Serial2.write(DM2_Speed9_Position_81, 10);
        break;
            case 82:
                Serial2.write(DM2_Speed9_Position_82, 10);
        break;
            case 83:
                Serial2.write(DM2_Speed9_Position_83, 10);
        break;
            case 84:
                Serial2.write(DM2_Speed9_Position_84, 10);
        break;
            case 85:
                Serial2.write(DM2_Speed9_Position_85, 10);
        break;
            case 86:
                Serial2.write(DM2_Speed9_Position_86, 10);
        break;
            case 87:
                Serial2.write(DM2_Speed9_Position_87, 10);
        break;
            case 88:
                Serial2.write(DM2_Speed9_Position_88, 10);
        break;
            case 89:
                Serial2.write(DM2_Speed9_Position_89, 10);
        break;
            case 90:
                Serial2.write(DM2_Speed9_Position_90, 10); 
        break;

  }
  //收紧爪子
  delay(2000);
  Serial2.write(DM4_Speed9_Position_90, 10); 
  delay(3000);
  jixiebi_guiwei();
}
