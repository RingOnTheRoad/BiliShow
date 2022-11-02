//导库
#include <ESP8266WiFi.h>
#include <ArduinoHttpClient.h>
#include <ArduinoJson.h>
#include "setting.h"
#include <U8g2lib.h>
#include <WiFiUdp.h>
#include <TimeLib.h>
#include <NTPClient.h>
#include <EasyNTPClient.h>

// dweet目标地址
const char *host="dweet.io";

// 初始化构造器
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2 (U8G2_R0, U8X8_PIN_NONE);

// 声明WiFiClient对象
WiFiClient wifi;

// 设置服务器地址端口
HttpClient client=HttpClient(wifi,host,80);

// 设置本地端口
unsigned int localPort = 8888;

// 24*24小电视
const unsigned char bilibilitv_24u[] U8X8_PROGMEM = {0x00, 0x00, 0x02, 0x00, 0x00, 0x03, 0x30, 0x00, 0x01, 0xe0, 0x80, 0x01,
                                                     0x80, 0xc3, 0x00, 0x00, 0xef, 0x00, 0xff, 0xff, 0xff, 0x03, 0x00, 0xc0, 0xf9, 0xff, 0xdf, 0x09, 0x00, 0xd0, 0x09, 0x00, 0xd0, 0x89, 0xc1,
                                                     0xd1, 0xe9, 0x81, 0xd3, 0x69, 0x00, 0xd6, 0x09, 0x91, 0xd0, 0x09, 0xdb, 0xd0, 0x09, 0x7e, 0xd0, 0x0d, 0x00, 0xd0, 0x4d, 0x89, 0xdb, 0xfb,
                                                     0xff, 0xdf, 0x03, 0x00, 0xc0, 0xff, 0xff, 0xff, 0x78, 0x00, 0x1e, 0x30, 0x00, 0x0c
                                                    };

// 64*32莱茵生命
const unsigned char RhineLab[] U8X8_PROGMEM = {0x00,0xC0,0x1F,0x00,0x00,0xF0,0x03,0x00,0x00,0xF0,0x7F,0x00,0x00,0xFC,0x1F,0x00,
0x00,0xFC,0xFF,0x01,0x00,0xFF,0x7F,0x00,0x00,0xFE,0xFF,0x03,0x80,0xFF,0xFF,0x00,
0x00,0xFF,0xFF,0x07,0xC0,0xFF,0xFF,0x01,0x80,0xFF,0xFF,0x0F,0xC0,0xFF,0xFF,0x03,
0xC0,0x7F,0xF0,0x1F,0xC0,0x1F,0xFC,0x03,0xC0,0x1F,0xC0,0x3F,0x80,0x07,0xF0,0x07,
0xE0,0x0F,0x82,0x7F,0x1E,0x00,0xE0,0x07,0xE0,0x07,0x07,0xFF,0x3F,0x00,0xE0,0x07,
0xE0,0x07,0x07,0xFE,0x3F,0x00,0xC0,0x07,0xE0,0xC7,0x1F,0xFC,0x3F,0xF0,0xC3,0x07,
0xE0,0xE7,0x3F,0xF8,0x1F,0xF8,0xC7,0x07,0xE0,0xE3,0x3F,0xF0,0x1F,0xF8,0xC7,0x07,
0xE0,0xC7,0x3F,0xF8,0x3F,0xF8,0xC7,0x07,0xE0,0x07,0x07,0xFC,0x7F,0x00,0xC0,0x07,
0xE0,0x07,0x07,0xFE,0xFF,0x00,0xE0,0x07,0xE0,0x0F,0x87,0xFF,0xFE,0x01,0xE0,0x07,
0xC0,0x1F,0xC0,0x7F,0xFC,0x03,0xF0,0x07,0xC0,0x3F,0xE0,0x3F,0xF8,0x0F,0xFC,0x03,
0x80,0xFF,0xFF,0x1F,0xF0,0xFF,0xFF,0x03,0x00,0xFF,0xFF,0x0F,0xE0,0xFF,0xFF,0x01,
0x00,0xFE,0xFF,0x03,0xC0,0xFF,0xFF,0x00,0x00,0xFC,0xFF,0x01,0x80,0xFF,0x7F,0x00,
0x00,0xF8,0xFF,0x00,0x00,0xFE,0x1F,0x00,0x00,0xE0,0x3F,0x00,0x00,0xF8,0x07,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC7,0x31,0x8E,0x63,0x0C,0xC6,0x01,
0x00,0xC7,0x31,0x8E,0x63,0x1C,0xC7,0x01,0x00,0xC7,0x31,0x8E,0x03,0x1C,0xC7,0x01};

// 24*24网易云
const unsigned char netease_24u[] U8X8_PROGMEM = {0x00,0xC0,0x01,0x00,0xF0,0x07,0x00,0xF3,0x07,0xC0,0xF3,0x07,0xE0,0x73,0x00,0xF0,
0x71,0x00,0xF8,0xF8,0x03,0x7C,0xFE,0x07,0x3C,0xFF,0x0F,0x3C,0xFF,0x1F,0x9E,0xE7,
0x3E,0x9E,0xE7,0x3D,0x9E,0xE7,0x3D,0x9E,0xE7,0x39,0x1E,0xFF,0x39,0x1E,0xFE,0x38,
0x3C,0x7E,0x3C,0x3C,0x00,0x3C,0xF8,0x00,0x1E,0xF0,0x81,0x1F,0xF0,0xFF,0x0F,0xC0,
0xFF,0x07,0x80,0xFF,0x01,0x00,0x7E,0x00};

// 创建WiFiUDP对象
WiFiUDP Udp;

// 设置NTPClient参数
NTPClient timeClient(Udp, "ntp1.aliyun.com", 3600*8, 1000*60);
EasyNTPClient ntpClient(Udp, "ntp1.aliyun.com", 3600*8);

// 初始化 (只执行一次)
void setup() {
  // 串口波特率
  Serial.begin(9600);

  // 初始化U8g2
  u8g2.begin();

  // 允许输出UTF8字符集
  u8g2.enableUTF8Print();

  // 设置字体集
  u8g2.setFont(u8g2_font_wqy12_t_gb2312b);  
   
  // 显示屏显示信息
  u8g2.clearBuffer();
  u8g2.setCursor(0, 14);
  u8g2.print("等待WIFI连接");
  u8g2.setCursor(0, 30);
  u8g2.print("连接中...");
  u8g2.setCursor(0, 47);
  u8g2.print("By Ring");
  u8g2.setCursor(0, 64);
  u8g2.print("BiliShow v1.0");
  u8g2.sendBuffer();

   // 设置WIFI模式
  WiFi.mode(WIFI_STA);

  // WIFI连接 
  wifi_connect();

  // 串口输出 
  Serial.printf("WIFI连接中...");

  // 判断是否连接成功 
  while (WiFi.status()!=WL_CONNECTED)
  {
    // 延迟再判断
    delay(500);
  }

  Serial.print("WIFI连接成功!");

  // 启用udp服务
  Udp.begin(localPort);

  // 启用NTPClient
  timeClient.begin();
}

// 循环执行体
void loop() {
  // 更新NTP服务
  timeClient.update();

  // 输出标准时间
  Serial.println(timeClient.getFormattedTime());

  // 连接到dweet.io
  String url = dweet_connect();
  client.get(url);

  // 返回响应码
  int statusCode =client.responseStatusCode();

  // 返回响应内容
  String response=client.responseBody();

  Serial.print("http码:");
  Serial.println(statusCode);
  Serial.println("响应内容:");
  Serial.println(response);

  // Json数据内存管理
  DynamicJsonDocument doc(512);

  // 反序列化json
  DeserializationError error = deserializeJson(doc, response);

  // 判断反序列化成功与否
  if (error.c_str() != "Ok")
  {
    Serial.print("反序列化错误:");
    Serial.println(error.c_str());
    return;
  }
  
  // 提取数据
  JsonObject data_with = doc["with"][0];
  JsonObject data_content = data_with["content"];

  // 存储数据
  String fans = data_content["Fans"];
  String likes = data_content["Likes"]; 
  String view = data_content["View"];
  String weather = data_content["Weather"]; 
  String temperature = data_content["Temperature"];
  String plays = data_content["Plays"];
  String netFans = data_content["NetFans"]; 
  String exponent = data_content["Exponent"];

  // 日期板块
  int flag = 0;
  while (flag <= 8)
  {
    // 清除缓冲区内容
    u8g2.clearBuffer();

    // 输出
    u8g2.enableUTF8Print();
    u8g2.setFont(u8g2_font_wqy12_t_gb2312b);
    u8g2.setCursor(0, 13);
    u8g2.print(weather.c_str());
    u8g2.drawStr(45,12,temperature.c_str());
    
    int hours = timeClient.getHours();
    int minutes = timeClient.getMinutes();
    int seconds = timeClient.getSeconds();
    int months = month(ntpClient.getUnixTime());
    int days = day(ntpClient.getUnixTime());
    int weekdays = weekday(ntpClient.getUnixTime());
    int years = year(ntpClient.getUnixTime());

    // 日期数据处理
    String currentTime = "";
    if (hours < 10)
      currentTime += 0;
    currentTime += hours;
    currentTime += ":";
    if (minutes < 10)
      currentTime += 0;
    currentTime += minutes;
    currentTime += ":";
    if (seconds < 10)
      currentTime += 0;
    currentTime += seconds;
    String currentDay = "";
    currentDay += years;
    currentDay += "/";
    if (months < 10)
      currentDay += 0;
    currentDay += months;
    currentDay += "/";
    if (days < 10)
      currentDay += 0;
    currentDay += days;
    u8g2.setFont(u8g2_font_wqy12_t_gb2312b);
    u8g2.setCursor(0, 44);
    u8g2.setFont(u8g2_font_logisoso24_tr);
    u8g2.print(currentTime);
    u8g2.setFont(u8g2_font_wqy12_t_gb2312b);
    u8g2.setCursor(0, 61);
    u8g2.print(currentDay);
    u8g2.setCursor(84, 62);
    u8g2.print("星");
    u8g2.setCursor(95, 62);
    u8g2.print("期");
    u8g2.setCursor(108, 62);
    if (weekdays == 1)
      u8g2.print("日");
    else if (weekdays == 2)
      u8g2.print("一");
    else if (weekdays == 3)
      u8g2.print("二");
    else if (weekdays == 4)
      u8g2.print("三");
    else if (weekdays == 5)
      u8g2.print("四");
    else if (weekdays == 6)
      u8g2.print("五");
    else if (weekdays == 7)
      u8g2.print("六");
    
    // 发送数据到缓冲区
    u8g2.sendBuffer();

    flag += 1;

    // 延迟差不多1s刷新一次
    delay(950);
  }
 
  // B站板块
  u8g2.clearBuffer();
  u8g2.setCursor(0, 15);
  u8g2.print("粉丝量:");
  u8g2.setCursor(0, 35);
  u8g2.print("点赞量:");
  u8g2.setCursor(0, 55);
  u8g2.print("播放量:");
  u8g2.drawStr(45,15,fans.c_str());
  u8g2.drawStr(45,35,likes.c_str());
  u8g2.drawStr(45,55,view.c_str());

  //绘制图像
  u8g2.drawXBMP( 95 , 0 , 24 , 24 , bilibilitv_24u );

  u8g2.sendBuffer();
  delay(8000);

  // 网易云板块
  u8g2.clearBuffer();
  u8g2.setCursor(0, 15);
  u8g2.print("播放量"   );
  u8g2.setCursor(0, 35);
  u8g2.print("粉丝量:"   );
  u8g2.setCursor(0, 55);
  u8g2.print("指数量:"   );
  u8g2.drawStr(45,15,plays.c_str());
  u8g2.drawStr(45,35,netFans.c_str());
  u8g2.drawStr(45,55,exponent.c_str());
  u8g2.drawXBMP( 95 , 0 , 24 , 24 , netease_24u );
  u8g2.sendBuffer();
  delay(8000);
}
