#include <ESP8266WiFi.h>
#include <ArduinoHttpClient.h>

//设置WIFI用户名、密码
const char* ssid = "ssid";
const char* password = "pwd";

// 自定义您的dweet设备名称,与python文件中保持一致
String device_name = "devicename";

void wifi_connect()
{
	WiFi.begin(ssid, password);
}

String dweet_connect()
{
	String url = "/get/latest/dweet/for/" + device_name;
	return url;
}

