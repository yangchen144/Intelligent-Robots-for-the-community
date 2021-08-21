/*
 * 2021.4.3  日志
 * 作者:夏瑜鸿（搬砖打工人一员）
 * 功能:
 * 1.自动连接附近信号强的WiFi(wifi信息已提前写在代码里)
 * 2.通过TCP协议将8266接入巴法云服务器进行无线通信
 * 3.超市端订阅Home主题，接收家庭端向主题Home发送过来的字符串信息
 * 4.将发过来的字符串处理，然后通过串口通信将分割过的字符串发送给arduino板
 */
 #include <ESP8266WiFi.h>
 #include <ESP8266WiFiMulti.h>
 #include <SoftwareSerial.h>

 #define TCP_SERVER_ADDR "bemfa.com"  //巴法云服务器地址
 #define TCP_SERVER_PORT "8344"       //服务器端口，tcp创客云端口8344
 #define MAX_PACKETSIZE 512          //最大字节数
 #define KEEPALIVEATIME 30*1000      //设置心跳值30s
 #define upDataTime 1*1000           //设置上传速率2s（1s<=upDataTime<=60s）

 ESP8266WiFiMulti wifiMulti;
 WiFiClient TCPclient;
 SoftwareSerial Esp_Serial(D6,D7);

 String UID = "5e5064495edf833d79cdfd030291460d";  //用户私钥
 String Subcribe_Topic = "SuperMarket";

 String TcpClient_Buff = "";
 unsigned int TcpClient_BuffIndex = 0;
 unsigned long TcpClient_preTick = 0;
 unsigned long preHeartTick = 0;//心跳
 unsigned long preTCPStartTick = 0;//连接
 bool preTCPConnected = false;

 String Send_Message = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Esp_Serial.begin(9600);
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

void doTCPClientTick()
{
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
  }
  if((TcpClient_Buff.length() >= 1) && (millis() - TcpClient_preTick>=200))
  {//data ready
    TCPclient.flush();
    Serial.println("Buff");
    Serial.println(TcpClient_Buff);
 if((TcpClient_Buff.indexOf("&msg=config:") > 0)) 
 {
  Send_Message = "";
  char Array_Send_Msg[TcpClient_Buff.length()+1];
  strcpy(Array_Send_Msg,TcpClient_Buff.c_str());
  for(int i = 72;i < 76;i++){
  Send_Message += Array_Send_Msg[i];
  }
  
  if(Send_Message != " ")
  {
    Esp_Serial.println(Send_Message);
    Serial.println(Send_Message);
  }
 }
    TcpClient_Buff="";
    TcpClient_BuffIndex = 0;
  }
}
