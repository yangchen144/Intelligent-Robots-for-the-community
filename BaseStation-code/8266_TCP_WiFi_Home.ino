/*
 * 日志:2021/4/5 15:31
 * 作者:夏瑜鸿(one of 搬砖打工人)
 * 功能:
 * 1.自动搜寻附近WiFi（wifi信息被提前写入程序中）,自动连上信号最好的无线网
 * 2.接入巴法云服务器，订阅"Home"主题，分割该主题收到的数据(如:Config:XiaoMing/Floor2/1000)，合成成两串信息
 *   (如:Config:XiaoMing/Floor2和Config:1000)
 *   再分别将这两条信息发送给"Button"主题和"SuperMarket"主题，在另外两块esp8266上做进一步处理
 */
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#define TCP_SERVER_ADDR "bemfa.com"  //巴法云服务器地址
#define TCP_SERVER_PORT "8344"       //服务器端口，tcp创客云端口8344
#define MAX_PACKETSIZE 512          //最大字节数
#define KEEPALIVEATIME 30*1000      //设置心跳值30s
#define upDataTime 1*1000           //设置上传速率2s（1s<=upDataTime<=60s）

ESP8266WiFiMulti wifiMulti;
WiFiClient TCPclient;

String UID = "5e5064495edf833d79cdfd030291460d";  //用户私钥
String Publish_Topic_1 = "Button";//摁下app确定键发送到该主题下
String Publish_Topic_2 = "SuperMarket";//摁下app确定键发送到该主题下
//String Publish_Topic_3 = "Custom";//每隔n秒发送至手机app页面,手机app订阅其主题
String Subcribe_Topic = "Home";

 String TcpClient_Buff = "";
 unsigned int TcpClient_BuffIndex = 0;
 unsigned long TcpClient_preTick = 0;
 unsigned long preHeartTick = 0;//心跳
 unsigned long preTCPStartTick = 0;//连接
 bool preTCPConnected = false;

 String Sendmsg_1,Sendmsg_2,Sendmsg_3;
void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 Multi_Connect_WiFi();
 startTCPClient();              //初始化TCP客户端的连接
}

void loop() {
  // put your main code here, to run repeatedly:
 doTCPClientTick();   //和巴法云服务器进行TCP通信
}

void Multi_Connect_WiFi()
{
  wifiMulti.addAP("Mask","31415926");//手机热点
  wifiMulti.addAP("FAST_C6D0","13914122873XYH81");//宿舍无线网
  wifiMulti.addAP("dz408","dz408408408");//实验室无线网
  wifiMulti.addAP("49-103","13814229164");//家里的无线网

  while(wifiMulti.run()!=WL_CONNECTED)
  {
    delay(1000);
    Serial.print('.');
  }
  Serial.println("\n");
  Serial.print("已经成功连接上WiFi:");
  Serial.println(WiFi.SSID());
  Serial.print("开发板的IP地址:");
  Serial.println(WiFi.localIP());
}

void sendtoTCPServer(String p){
  
  if (!TCPclient.connected()) 
  {
    Serial.println("Client is not readly");
    return;
  }
  TCPclient.print(p);
  Serial.println("[Send to TCPServer]:String");
  Serial.println(p);
}

void startTCPClient(){
  if(TCPclient.connect(TCP_SERVER_ADDR, atoi(TCP_SERVER_PORT))){
    Serial.print("\nConnected to server:");
    Serial.printf("%s:%d\r\n",TCP_SERVER_ADDR,atoi(TCP_SERVER_PORT));
    
    String tcpTemp="";  //初始化字符串
    tcpTemp = "cmd=1&uid="+UID+"&topic="+Subcribe_Topic+"\r\n"; //构建订阅指令
    sendtoTCPServer(tcpTemp); //发送订阅指令
    tcpTemp="";//清空

    preTCPConnected = true;
    preHeartTick = millis();
    TCPclient.setNoDelay(true);
  }
  else{
    Serial.print("Failed connected to server:");
    Serial.println(TCP_SERVER_ADDR);
    TCPclient.stop();
    preTCPConnected = false;
  }
   preTCPStartTick = millis();
}

/*
  *检查数据，发送心跳
*/
void doTCPClientTick(){
  if (!TCPclient.connected()) {//断开重连
    if(preTCPConnected == true){

    preTCPConnected = false;
    preTCPStartTick = millis();
    Serial.println(); 
    Serial.println("TCP Client disconnected.");
    TCPclient.stop();
  }
  else if(millis() - preTCPStartTick > 1*1000)//重新连接
    startTCPClient();
  }
  else{
     if (TCPclient.available()) {//收数据
      char c =TCPclient.read();
      TcpClient_Buff +=c;
      TcpClient_BuffIndex++;
      TcpClient_preTick = millis();
      
      if(TcpClient_BuffIndex>=MAX_PACKETSIZE - 1){
        TcpClient_BuffIndex = MAX_PACKETSIZE-2;
        TcpClient_preTick = TcpClient_preTick - 200;
      }
      preHeartTick = millis();
    }
    if(millis() - preHeartTick >= KEEPALIVEATIME){//保持心跳
      preHeartTick = millis();
      Serial.println("--Keep alive:");
      sendtoTCPServer("cmd=0&msg=keep\r\n");
    }
    /*
   if(millis() - preHeartTick >= upDataTime){//上传数据
      preHeartTick = millis();
 /*********************数据上传*******************/
 /*
      String UP_MSG_3 = "";
      UP_MSG_3 = "cmd=2&uid="+UID+"&topic="+Publish_Topic_3+"&msg="+Sendmsg_3+"\r\n"; 
      sendtoTCPServer(UP_MSG_3);
      UP_MSG_3 = "";
    }
    */
  }
  if((TcpClient_Buff.length() >= 1) && (millis() - TcpClient_preTick>=200))
  {//data ready
    TCPclient.flush();
    Serial.println("Buff");
    Serial.println(TcpClient_Buff);
    if((TcpClient_Buff.indexOf("&msg=Config:") > 0)) {////接收手机app发送信息(格式:Config:XiaoMing/Floor2/1000)
      //对信息的处理 1.将Config:XiaoMing/Floor2发送至主题为Button的小车上
     //            2.将Config:1000发送至主题为SuperMarket的超市里
     //在此条件下，尝试发送
     Sendmsg_1 = "";
     Sendmsg_2 = "";
     String UP_MSG_1 = "";
     String UP_MSG_2 = "";
     char Array_Msg[TcpClient_Buff.length()+1];
     strcpy(Array_Msg,TcpClient_Buff.c_str());
     for(int i = 65;i < 80;i++)
      {
        Sendmsg_1 += Array_Msg[i];//XiaoMing/Floor2
      }
      for(int i = 81;i < 85;i++)
      {
        Sendmsg_2 += Array_Msg[i];//1000
      }
      UP_MSG_1 = "cmd=2&uid="+UID+"&topic="+Publish_Topic_1+"&msg="+"Config:"+ Sendmsg_1 + "\r\n";
      UP_MSG_2 = "cmd=2&uid="+UID+"&topic="+Publish_Topic_2+"&msg="+"config:"+ Sendmsg_2 + "\r\n";
      sendtoTCPServer(UP_MSG_1);
      //delay(1000);
      sendtoTCPServer(UP_MSG_2);
    }
    /*
    else if((TcpClient_Buff.indexOf("&msg=Send:") > 0))//接收超市发来的商品信息（格式Send:/Milk/Bread/Cake/Gum）
    {
     Sendmsg_3 = "";
     char Array_msg[TcpClient_Buff.length()+1];
     strcpy(Array_msg,TcpClient_Buff.c_str());
     for(int i = 63;i < 83;i++)
     {
      Sendmsg_3 += Array_msg[i];
     }
    }
    */
    TcpClient_Buff="";
    TcpClient_BuffIndex = 0;
  }
}
