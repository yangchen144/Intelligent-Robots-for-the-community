/*
 * 2021/4/3 日志
 * 作者：夏瑜鸿
 * 主体功能:1.Arduino Uno和esp8266串口通信,将8266处理的信息用Arduino接收(格式：1111)
 *         2.能够控制超市对应的四个舵机转动
 * 纠正了一个Bug：        
 * 一共四个舵机,原来第一和第二个舵机打开很快，关闭慢，第三和第四个舵机打开较慢，关闭快，
 * 因为第一和第二个舵机的初始角度为90度(这里纠正cqy一下"QAQ"),现在速度都统一了，该Bug已解决
 */
#include <DFRobotDFPlayerMini.h>
#include <SoftwareSerial.h>
#include <Servo.h>

//SoftwareSerial mySerial(6, 7);//esp8266串口
SoftwareSerial mySoft(10,11);//mp3串口
DFRobotDFPlayerMini myDFPlayer;
Servo myServo_1;
Servo myServo_2;
Servo myServo_3;
Servo myServo_4;

 String A,B,C,D;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
  MP3_INIT();
  
  myServo_1.attach(8);
  myServo_2.attach(9);
  myServo_3.attach(12);
  myServo_4.attach(5);
  
  myServo_1.write(90);
  myServo_2.write(90);
  myServo_3.write(0);
  myServo_4.write(0);
  
}

void loop() {
  //Serial.println("nb");
  // put your main code here, to run repeatedly:
  String p = "";
 
     
 while (Serial1.available() > 0)
  {
    p += char(Serial1.read());
    delay(20);
  }

 if (myDFPlayer.available()) {
    printDetail(myDFPlayer.readType(), myDFPlayer.read()); 
    
//Print the detail message from DFPlayer to handle different errors and states.
  }
  if(p!=""){
    Serial.println(p);
     char P[p.length()+1];
     strcpy(P,p.c_str());
         A = P[0]; B = P[1];
         C = P[2]; D = P[3];
     Servo_remove(A,B,C,D);
     //Voice(A,B,C,D);
    }
}

void Servo_remove(String a,String b,String c,String d)
{
  if(a=="1"){  Serial.println("舵机1开启");
               Servo_Spin(myServo_1,90,0);
               
               myDFPlayer.play(1);delay(1000);
               myServo_1.write(90);
               
               }
  else{
               Serial.println("舵机1关闭");
               myServo_1.write(90);
    }
  
  if(b=="1"){  Serial.println("舵机2开启");
               Servo_Spin(myServo_2,90,0);
               myDFPlayer.play(2);delay(1000);
               myServo_2.write(90);
              
               }
  else{
               Serial.println("舵机2关闭");
               myServo_2.write(90);
    }
  
  if(c=="1"){  Serial.println("舵机3开启");
               Servo_Spin(myServo_3,0,90);
              myDFPlayer.play(3);  delay(1000);
               myServo_3.write(0);
                
               }
  else{
               Serial.println("舵机3关闭");
               myServo_3.write(0);
    }

  if(d=="1"){  Serial.println("舵机4开启");
               Servo_Spin(myServo_4,0,90);
                myDFPlayer.play(4);delay(1000);
               myServo_4.write(0);
               
               }
  else{
               Serial.println("舵机4关闭");
               myServo_4.write(0);
  }
}

void Servo_Spin(Servo servo,int Now_Pos,int To_Pos)
{
  int i;
  if(Now_Pos < To_Pos)
  {
    for(i = Now_Pos;i < To_Pos;i++)
   {
    servo.write(i);
    delay(5);
   }
  }
  else{
    for(i = Now_Pos;i > To_Pos;i--)
   {
    servo.write(i);
    delay(5);
   }
  }
  
}

void Voice(String a,String b,String c,String d)
{
  if(a=="1"){myDFPlayer.volume(25); myDFPlayer.play(1);delay(1200);}
  if(b=="1"){myDFPlayer.volume(25); myDFPlayer.play(2);delay(1200);}
  if(c=="1"){myDFPlayer.volume(25); myDFPlayer.play(3);delay(1200);}
  if(d=="1"){myDFPlayer.volume(25); myDFPlayer.play(4);delay(1200);}
}

void  MP3_INIT()
{
  mySoft.begin(9600);
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  if (!myDFPlayer.begin(mySoft)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  Serial.println("***************************");
  digitalWrite(11,0);
  //设置音量 
  myDFPlayer.volume(30);
   //Set volume value. From 0 to 30
}

void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerUSBInserted:
      Serial.println("USB Inserted!");
      break;
    case DFPlayerUSBRemoved:
      Serial.println("USB Removed!");
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
  
}
