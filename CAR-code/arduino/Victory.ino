/*
 状态：
      *软串口12，13给MP3
      *Serial0留给数据打印
      *Serial1楼给ESP8266
      *Serial2预留给机械臂
      *Serial3预留给openmv
 团队：搬砖打工人
 */
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "MOTOR_Remove.h"
#include "Xunji.h"
#include "Openmv.h"
#include "./Adafruit_NeoPixel.h"   

//-----------------------------------------------------------------------------------------|
//                                    灯带宏定义                                             |
//                                                                                         |
                                #define PIN 2                                            //|                  
                                #define MAX_LED 5                                        //|
//                                                                                         |                                
//-----------------------------------------------------------------------------------------|
//                                  软串口宏定义                                             |
//                                                                                         |                              
//                                                                                         |
                            #define Software_RX_1  12                                    //|
//                                                                                         |                            
                            #define Software_TX_1  13                                    //|
//                                                                                         |                            
                            #define Software_RX_2  6                                     //|
//                                                                                         |                            
                            #define Software_TX_2  7                                     //|
//                                                                                         |                            
                            #define Software_RX_3  4                                     //|
//                                                                                         |                            
                            #define Software_TX_3  5                                     //|
//                                                                                         |    
//                                                                                         |      
//-----------------------------------------------------------------------------------------|
//                                  软串口初始化                                             |                                                                 
//MP3软串口                                                                                 |
                                                                                         //|
        SoftwareSerial mySoftwareSerial(Software_RX_1, Software_TX_1);                   //|
        DFRobotDFPlayerMini myDFPlayer;                                                  //|
                                                                                         //|
//GSM软串口                                                                                 |
                                                                                         //|
        SoftwareSerial GSMSerial(Software_RX_2, Software_TX_2);                          //|
                                                                                         //|                                                                                         
                                                                                         //|
//openmv软串口                                                                              |
                                                                                         //|
        SoftwareSerial Serial30(Software_RX_3, Software_TX_3);                           //|
                                                                                         //|
//-----------------------------------------------------------------------------------------|
//                                  灯带初始化                                              |
//                                                                                         |
        Adafruit_NeoPixel strip = Adafruit_NeoPixel( MAX_LED, PIN, NEO_RGB + NEO_KHZ800 );//     
        uint32_t color0 = strip.Color(0,0,0);   //Green, red, blue                         |
        uint32_t color1 = strip.Color(50,0,0);   //Green, red, blue                        |
        uint32_t color2 = strip.Color(0,50,0);   //Green, red, blue                        |
        uint32_t color3 = strip.Color(0,0,50);   //Green, red, blue                        |
        uint32_t color4 = strip.Color(50,50,0);   //Green, red, blue                       |
        uint32_t color5 = strip.Color(0,50,50);   //Green, red, blue                       |
//-----------------------------------------------------------------------------------------|


int erweima_value = 0;
int Name = 0;
int Floor = 0;
int a = 1;
int b = 1;

void setup() 
{//-----------------------------------------------------------------------------------------
 
                      Serial.begin(9600);      //数据打印串口
                    
                      Serial1.begin(9600);     //ESP8266串口
                    
                      Serial2.begin(9600);     //机械臂 通信串口
                    
                      Serial3.begin(19200);    //Openmv 串口通信接口
                      
                      Serial30.begin(19200);  //Openmv 串口通信软接口
                      
                      MP3_INIT();  //MP3初始化

                      GSMSerial.begin(9600);     //机械臂 通信串口
                      
                      Xunji_INIT();   //循迹端口初始化
                      
                      MOTOR_INIT(); // 初始化电机端口

                      strip.begin();    
                      strip.show(); 
                      strip.setPixelColor(0,color0);  //点亮第1个RGB灯为红色
                      strip.setPixelColor(1,color0);  //点亮第1个RGB灯为红色
                      strip.setPixelColor(2,color0);  //点亮第1个RGB灯为红色
                      strip.setPixelColor(3,color0);  //点亮第1个RGB灯为红色
                      strip.setPixelColor(4,color0);  //点亮第1个RGB灯为红色
                      strip.show(); 
                      
                      
                      
                      
//--------------------------------------------------------------------------------------------
}


void loop(){ 
//-----------------------------------------------------------------------------------------|
  if(b)
  {
              b = 0;//确保程序只执行一次
                            
//-----------------------------------------------------------------------------------------|               
//                           第0部分，接收esp8266指令
//-----------------------------------------------------------------------------------------|
  
                  strip.setPixelColor(0,color1);  //点亮第1个RGB灯为红色
                  strip.show(); 

                  a = 0;
                  Name = 1;
                  Floor = 2;
                                   
                      while(a)
                    {
                        String p = "";
                        while(Serial1.available())
                        {
                            Serial.println("开始");
                            a = 0;
                            p += char(Serial1.read());    //esp8266的字符串 
                            Serial.print("p= ");
                            Serial.print(p);
          
                            if (p == "4") //小明住二楼
                                {
                                   Name = 1;
                                   Floor = 2;
                                   Serial.println("小明的身份已确认");
                                 }
                            else if (p == "5") //小红住一楼
                                { 
                                   Name = 2;
                                   Floor = 1;
                                   Serial.println("小红的身份已确认");
                                 }
                        }
                     }//至此处理完8266的数据
                     
//-----------------------------------------------------------------------------------------|                  
//                           第一部分，从出生点到超市
//-----------------------------------------------------------------------------------------|
                      
                      myDFPlayer.play(6);//开始前往超市
                      strip.setPixelColor(1,color2);  //点亮第2个RGB灯为红色
                      strip.show();  
                      delay(4000);
                      Xunji_JC();
                      GSMSerial.println("atd15152305898;");
    
//-----------------------------------------------------------------------------------------|    
//                           第二部分，在超市调用机械臂
//-----------------------------------------------------------------------------------------|

                      myDFPlayer.play(8);//到达超市，开始取货
                      strip.setPixelColor(2,color3);  //点亮第2个RGB灯为红色
                      strip.show(); 
                      delay(4000);
          
                      Openmv_began(); // 给openmv 发送指令 启动测试距离程序
          
                      while(1)//似乎不需要这个循环
                      {
                          Serial.println("机械臂准备执行");
                          Jixiebi_choose();    // 选择机械臂的动作
                          delay(10000);        //给机械臂执行时间
                          break;
                      }
                      
//-----------------------------------------------------------------------------------------|
//                          第三部分，从超市前往电梯
//-----------------------------------------------------------------------------------------|
  
                       myDFPlayer.play(7);//取货完毕，开始前往电梯
                       strip.setPixelColor(3,color4);  //点亮第2个RGB灯为红色
                       strip.show(); 
                       delay(4000);
                       Xunji_JC(); 

//-----------------------------------------------------------------------------------------|
//                           第四部分，打电话
//-----------------------------------------------------------------------------------------|

                      if(Floor == 2){//小明
                          GSMSerial.println("atd15152305898;");
                      }
                      delay(2000);//给打电话的时间

//-----------------------------------------------------------------------------------------|      
//                           第五部分，开始识别二维码
//-----------------------------------------------------------------------------------------|

                       myDFPlayer.play(9);//请出示二维码
                       delay(4000);
                       Openmv_began_erweima();     // 二维码检测开始
                       delay(1000);
       
                       while(1){                       
                        if(Serial3.available()){
                           while(1){
                             Openmv.erweima_value = Serial3.read();
                             Serial.print("Openmv.erweima_value = ");
                             Serial.println(Openmv.erweima_value);
                             delay(500);
                             switch(Openmv.erweima_value){
                                case 55 :
                                  // 对应未识别到二维码 播放重新识别二维码的声音 55 —>7
                                  Serial.println("未识别到二维码 等待Openmv识别");
                                  myDFPlayer.play(9);//请出示二维码
                                  delay(500);
                                  break;
                                case 54 :
                                  // 54 ->6 对应识别到二维码的声音 和其他相关代码 小明
                                  Serial.println("识别到小明的二维码");
                                  if (Name == 1){
                                    Serial.println("小明的身份码确认");
                                    erweima_value = 1;
                                  }else{
                                    // 不是小明的身份码 播放身份码错误 并重新发送识别二维码指令
                                    Serial.println("小明身份码错误 重新发送二维码指令");
                                    myDFPlayer.play(9);//请出示二维码
                                    delay(500);
                                    Openmv_began_erweima();
                                    delay(500);
                                  }
                                  break;
                                case 53 :
                                  Serial.println("识别到小鸿的二维码");
                                  if (Name == 2){
                                    Serial.println("小鸿的身份码确认");
                                    erweima_value = 1;
                                  }else{
                                    // 不是小鸿的身份码 播放身份码错误 并重新发送识别二维码指令
                                    Serial.println("小鸿身份码错误 重新发送二维码指令");
                                    myDFPlayer.play(9);//请出示二维码
                                    delay(500);
                                    Openmv_began_erweima();
                                    delay(500);
                                  }
                                  break;
                                case 52:
                                  //52->4
                                  Serial.println("识别了2000次还是没有检测到二维码 程序将重新执行");
                                  delay(500);
                                  Openmv_began_erweima();
                                  //erweima_value = 1;
                                  break;
                              }
                            delay(500);
                            if(erweima_value == 1){
                              erweima_value = 0;
                              break;
                            }
                           }
                           break;
                        }
                      }

//-----------------------------------------------------------------------------------------|
//                                       收尾
//-----------------------------------------------------------------------------------------|          
                       strip.setPixelColor(3,color4);  //点亮第2个RGB灯为红色
                       strip.show(); 
                        Serial.println("已执行完程序 程序结束");
                        delay(500);
                        myDFPlayer.play(4);//识别成功，谢谢惠顾
                        delay(1000);
                        jixiebi_guiwei();
                        Serial.println("已松机械臂");
                        //break;
                        delay(6000);
                    
                        a = 0;  
                        b = 0;
                     
  }//if(b) 
}//loop  
//-----------------------------------------------------------------------------------------|

 void MP3_INIT(){
  //串口监视
  mySoftwareSerial.begin(9600);
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  Serial.println("***************************");

  //设置音量 
  myDFPlayer.volume(30);  //Set volume value. From 0 to 30
   
  // myDFPlayer.volumeUp(); //Volume Up
  // myDFPlayer.volumeDown(); //Volume Down
  //myDFPlayer.play(1);
  //myDFPlayer.next();
  //myDFPlayer.pause();  //pause the mp3
  //myDFPlayer.start();  //start the mp3 from the pause
}
