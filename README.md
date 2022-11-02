---
typora-root-url: MdImg

---

# BiliShow说明文档 v1.0



# 前言

​			//本说明文档只是简单整理说明和教程内容相关的一些知识点(~~咱也没这水平~~)，不去深挖每个知识点，适合有一定基础的人群查阅 (~~没有也没关系~~) ,如需更深入了解，还请大家自行搜寻资料。此软件需要在64位的电脑运行，32位的请自行寻找替换。v1.0版本主要用于测试,咱也不知道能不能在别的设备上进行复现 (~~不知道有没有漏什么步骤~~)，根据大家反应后会进行程序优化,请耐心阅读完本文档。本文主要知识内容来源于网络,如有疑惑&建议&BUG可在视频下方评论区指出。请勿将本软件用于非法用途,禁止二次发布,责任将由你承担！(~~任何罪恶都将会被绳之于法.jpg~~)//

软件&材料:

- Arduino IDE

- ESP8266 开发板

- 0.96 寸OLED

- Micro USB 线 (能传数据那种) (不是type-C&苹果线哦)

- 4根 母对母杜邦线

  ​																																					Bilibili: [@风带铃音](https://space.bilibili.com/8407632)

# 使用前提

- 保持你浏览器 B站/网易云音乐人 的登录状态为已登录 (应该是15天还是30天登录一次,非扫码登录)
- 保持登录状态的浏览器与下面安装的浏览器驱动类型&版本一致 (比如edge对应edge驱动,chrome对应chrome驱动)
- 给ESP8266配置的WIFI必须为2.4GHz频段



# 安装步骤

- 解压到你希望的位置

- 发现HackBrowserData.exe被杀软清除 (请查阅 其他相关知识~>HackBrowserData)

- 外部安装部分

  1. 用4根杜邦线将ESP8266与OLED连接	(连接方法在本文档~>部分部件&软件说明~>ESP8266 开发板~>与OLED的连接方式)
  2. 用Micro USB 数据线将ESP8266与你的电脑相连接

- 软件&驱动&库安装部分 [必选]

  1. 打开Install文件夹
  2. 安装CH341SER.EXE (USB转串口驱动)
  3. 安装arduino-ide_2.0.0_Windows_64bit.exe (Arduino IDE)
  4. 检查驱动和IDE是否安装成功&进行设置 (检查方法在本文档~>其他相关知识~>检查&设置)

  ————————————————————驱动&软件完毕————————————————————

  5. 在工具~>开发板~>开发板管理器~>搜索esp8266~>安装 (可能需要科学上网,不行就看步骤6)
  6. 步骤5不成功可以安装离线包Install~>8266_package_3.0.1_arduino.cn.exe
  7. 在项目~>包含库~>管理库~>搜索arduinojson (by.Benoit)~>安装 (可能不需要科学上网,不行就看步骤8)
  8. 在项目~>包含库~>添加.ZIP库~>选择~>Install~>ArduinoJson-v6.19.4.zip
  9. 在项目~>包含库~>添加.ZIP库~>选择~>Install~>Time-master.zip
  10. 在项目~>包含库~>管理库~>搜索u8g2 (by.oliver)~>安装 (可能需要科学上网,不行就看步骤11)
  11. 在项目~>包含库~>添加.ZIP库~>选择~>Install~>U8g2-2.33.15.zip
  12. 在项目~>包含库~>管理库~>搜索ArduinoHttpClient (by.Arduino)~>安装 (可能需要科学上网,不行就看步骤13)
  13. 在项目~>包含库~>添加.ZIP库~>选择~>Install~>ArduinoHttpClient-0.4.0.zip
  14. 在项目~>包含库~>管理库~>搜索NTPClient (by.Fabrice)~>安装 (可能需要科学上网,不行就看步骤15)
  15. 在项目~>包含库~>添加.ZIP库~>选择~>Install~>NTPClient-3.2.1.zip
  16. 在项目~>包含库~>添加.ZIP库~>选择~>U8g2_wqy_Arduino-0.0.1.zip

  ——————————————————————库完毕———————————————————————

- WIFI设置部分 [必选]

  1. 用记事本打开setting.h
  2. 填写你的WIFI信息 (SSID是WIFI名字,PASSWORD是WIFI密码)
  3. 保存

  ——————————————————————WIFI完毕——————————————————————

- .spec文件配置 [必须]

  1. 打开BiliShow_v1.0.spec
  2. 把datas里面的 `Your python path`替换成你Python安装的目录，确保你的路径下存在 `Lib` 文件夹

——————————————————————spec文件配置完毕———————————————————

- 心知天气设置部分 [可选]

  1. 注册/登录 [心知天气](https://www.seniverse.com/)
  2. 点击立即免费试用 或者 [点这里](https://www.seniverse.com/products?iid=new)
  3. 点击免费版的免费申请
  4. 在产品管理~>免费版~>API 密钥~>复制私钥保存

  —————————————————————心知天气完毕—————————————————————

- Python安装部分 [必须]

  1. 打开Install~>python-3.10.6-amd64.exe (已安装的可以不用再装)
  2. 勾选Installer launcher for all users & Add Python 3.10 to PATH
  3. 点击Customize installation
  4. 全选~>下一步
  5. 到达设定安装目录界面~>选择安装目录~>其他默认不用动~>Install
  6. 点击Disable path length limit (没有就不用管)
  7. 安装完成
  8. 将解压出来的Ring_Utils移动到您Python安装目录下的Lib\site-packages (如果在下面步骤设置运行Update BiliShow_v1.0.bat时&运行BiliShow.exe时发生找不到包/模块问题，请把Ring_Utils里的文件移动到site-packages下,并重新运行BiliShow_v1.0.bat)
  9. 在包含BiliShow_v1.0.py目录下 Shift+鼠标右键 (win11可以直接右键)~>打开命令窗口
  10. 输入 `pip install -r requirements.txt -i https://pypi.tuna.tsinghua.edu.cn/simple` 等待安装完成 (如果报错，请检查你的python环境变量设置是否正确;若后面发生找不到库/模块问题,请将本命令中的requirements.txt更换成requirements_all.txt再重试)

  —————————————————————Python安装完毕———————————————————

- Python文件设置部分 [必选]

  1. 用pycharm或者记事本软件打开BiliShow_v1.0.py

  2. 替换填写你的信息并保存

     ```python
     # Dweepy设备名 与Arduino一致
     device_name = "device_name"
     
     # 您的城市名称的拼音
     city_name = "city_name"
     
     # 心知天气密钥
     xz_key = "v50"
     
     # B站bid
     bid = "bb"
     
     # 网易云账号&密码
     netease_acc = "a"
     netease_pwd = "p"
     
     # 网易云信息获取方式 (0:使用selenium 1:使用HackBrowserData)
     netease_way = 1
     
     # 您文件BiliShow.ino所在的目录
     root_path = r"Your Path"
     
     # 刷新间隔 (秒)
     time_interval = 60
     
     # 功能开关 (1:开 0:关)
     bili_button = 1
     netease_button = 1
     ```

3. 如果想禁止弹窗提醒,可以注释掉`from plyer import notification`和所有`notification.notify`

  —————————————————————Python设置完毕———————————————————

- 准备浏览器驱动 [必选]

  1. 打开您浏览器对应版本的驱动下载网站 ([Edge](https://developer.microsoft.com/en-us/microsoft-edge/tools/webdriver/)	[Firefox](https://github.com/mozilla/geckodriver/releases)	[Chrome](http://chromedriver.storage.googleapis.com/index.html)	[QQ](http://chromedriver.storage.googleapis.com/index.html)	其他浏览器请自行搜索)
  2. 下载驱动
  3. 复制驱动文件 (.exe) 到Python目录下的Scripts文件夹

  ——————————————————————驱动设置完毕————————————————————

- 更新本地文件&打开运行 [必选]

1. 打开Update BiliShow_v1.0.bat

2. 进入dist文件查看

3. 打开BiliShow_v1.0.exe (建议创建快捷方式到你想要的地方)

4. 如果想打开后不出现窗口，可以运行Update BiliShow_v1.0 (without window).bat 后用记事本打开BiliShow_v1.0.specbf~>完整复制datas和hiddenimports~>将复制的内容覆盖到BiliShow_v1.0.spec

   //⚠无窗口文件只能在任务管理器关闭

—————————————————————————完毕——————————————————————



# 烧录步骤

1. 用 Arduino IDE 打开 Bili_ring.ino
2. 在工具~>开发板~>esp8266~>选择NodeMCU 1.0 (ESP-12E Module)
3. 在工具~>端口~>选择你的COM端口 (插上USB才显示出来的端口)
4. 点击上传按钮
5. 等待出现Hard resetting via RTS pin... (如果出现找不到库的情况，请重新安装对应离线包)
6. 看向你的OLED屏幕
7. Done !



# 部分部件&软件说明

## 0.96寸OLED

### 简介

1. #### OLED，即有机发光二极管( Organic Light Emitting Diode)

2. #### `颜色`可以支持两种单色显示 (<font color='BrickRed'>白</font>，<font color='blue'>蓝</font>)

3. ### `分辨率`为128*64



### 模块接口定义

1. GND		电源地
2. VCC          电源正 (3~5.5V)
3. SCL           OLED的D0脚
4. SDA          OLED的D1脚



### 驱动IC

- 本屏使用的驱动IC为 *SSD1306*



### 物理总线

- 本屏使用物理总线为 *I2C*



### 初始化构造器方法

- U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2 (U8G2_R0, U8X8_PIN_NONE)

  ​	U8G2: 使用的库/前缀

  ​	SSD1306: 驱动IC/显示控制器

  ​	128X64_NONAME: 显示名称 (含分辨率)

  ​	F: 缓存大小 (F: 全屏缓存模式Full Frame Buffer,size = 1024 bytes)

  ​	HW_I2C: 通信协议 (Hardware I2C based on the Arduino Wire library)

  ​	u8g2: 对象名

  ​	U8G2_R0:  旋转图像 (R0: No rotation, landscape)

  ​	U8X8_PIN_NONE: 不使用针脚控制



## ESP8266 开发板



### 简介

1. ESP8266是乐鑫科技生产的一款内置WIFI功能的单片机
2. 开发方式可选用Arduino开发
3. 工作温度范围：-40~125℃ (~~正常来说应该没人会喜欢折磨单片机吧~~)



### 与OLED的连接方式

| ESP8266 | OLED |
| :-----: | :--: |
|    G    | GND  |
|   3V    | VCC  |
|   D1    | SCL  |
|   D2    | SDA  |

- ⚠注意: 连接错误可能会导致板子烧坏



# 库函数说明



## ArduinoJson

### 简介

1. 对json数据进行解析



#### 相关库函数

##### 基本函数

1. DynamicJsonDocument (*size)		//动态管理Json数据的内存

   ​	size: 内存大小 ( byte )



2. DeserializationError (*JsonDocument, *JsonData)		//反序列化json

   ​	JsonDocument: JsonDocument对象

   ​	JsonData: json数据

   ​	<u>成功则返回 `Ok`</u>



## ESP8266WIFI

### 简介

1. 支持WIFI连接
2. 设置WIFI属性



#### 相关库函数

##### 基本函数

1. WiFi.status (void)		//判断WIFI连接状态

   ​	<u>返回当前wifi连接状态</u>		<u>若返回 `WL_CONNECTED` 则代表wifi连接成功</u>



2. WiFi.begin (*ssid, *password)		//建立WiFi连接

   ​	ssid: wifi名称

   ​	password: wifi密码

   

3. WiFi.mode (*mode)		//配置WiFi模式

   ​	mode: wifi模式 (STA or AP)



## HttpClient

### 简介

1. 针对Http请求操作的库
2. HTTP默认的端口号是80
3. HTTPS默认的端口号是443



#### 相关库函数

##### 基本函数

1. HttpClient (*Client, *host, *port)		//配置http服务器

   ​	wifiClient: Client对象

   ​	host: 目标地址

   ​	port: 端口号

   

2. HttpClient.responseStatusCode (void)		//返回当前访问网页的状态码

   ​	<u>返回 `200` 就算成功</u>



3. HttpClient.responseBody (void)		//返回得到的响应内容

   ​	

## EasyNTPClient

### 简介

1. 主要用来获取时间戳



#### 相关库函数

##### 基本函数

1. EasyNTPClient (*Udp, *TimeServerPool, *Utc)		//配置NTP服务器
2. EasyNTPClient .getUnixTime (void)		//返回当前时间戳



## NTPClient

### 简介

1. 连接到NTP服务器
2. 获取UTC时间



#### 相关库函数

##### 基本函数

1. NTPClient (*Udp, *TimeServerPool, *Utc, *UpdateInterval)		//配置NTP服务器

   ​	Udp: Udp对象

   ​	TimeServerPool: NTP服务器池

   ​	Utc: 时区设置 (UTC+8 就是 3600*8)

   ​	UpdateInterval: 更新间隔 (1000 * 60 就是60秒)

   

2. NTPClient.begin (void)		//初始化方法

   

3. NTPClient.update (void)		//强制更新NTP服务



4. getFormattedTime (void)		//得到标准时间



## TimeLib

### 简介

1. 用于获取时间
2. 转换时间戳



#### 相关库函数

##### 基本函数

1. ​	year(*unixTime)	month(*unixTime)	day(*unixTime)	weekday(*unixTime)		//获取&转换对应时间



## WiFiUdp

### 简介

1. 用于监听指定窗口
2. 提供UDP协议通讯服务



#### 相关库函数

##### 基本函数

1. ​	Udp.begin (*port)		//启用udp服务

## U8g2wqy

### 简介

1. 中文字符集库
2. 字体详细请查看 [Github](https://github.com/larryli/U8g2_wqy_Arduino/) ([镜像](https://gitee.com/CHN_ZC/u8g2_wqy/tree/master/))



## Arduino

### 简介

1. Arduino核心库采用C与C++混合编写而成
2. Arduino核心库文件提供的各种应用程序编程接口 (API)
3. Arduino程序中没有main函数



#### 相关库函数

##### 基本函数

1. void setup ( )  {		//初始化

   ​	*//结构体内代码只会在Arduino通电和复位时运行一次*

   }

   

2. void loop ( )   {		//循环执行

   ​	*//结构体内代码会在初始化后被连续执行，直至电源关闭*

   }



3. Serial.begin (*speed)		//串行传输速率

   ​	speed: 波特率 (一般取9600)



4. Serial.print (*str)		//串口输出信息

   ​	<u>在 Arduino~>工具~>串口监视器 可以查看其输出的信息</u>	<u>可使用println () 来达到输出同时换行</u>

   

##### 其他函数

1. ​	delay (*seconds)		//强制暂停程序运行

   ​	seconds: 延迟秒数



2. c_str (*str)		//返回指向C语言字符串的指针常量



3. JsonObject		//用于存储json数据结构



#### 注意事项

- 串口监视器的波特率要和Serial.begin设置的一致



## U8G2库

#### 简介

1. u8g2是嵌入式设备的单色图形库
2. 支持单色 `OLED` 和 `SSD1306`
3. 支持Arduino主板 — `ESP8266`
4. 支持中文和不同字体



#### 相关库函数

##### 基本函数

1. u8g2.begin (void)	//初始化&构造u8g2库

   ​	其函数包括了以下函数 (可独立调用)

   ​	initDisplay (void)	//初始化显示器

   ​	clearDisplay (void)	//重置清屏幕

   ​	setPowerSave (0)	//唤醒屏幕 (0:禁用省电模式	1:启用省电模式 — `黑屏` 但是内存占用不变)



2. u8g2.clear (void)	//清除屏幕显示&缓冲区&光标回到原点 (0,0) <~~~不是表情啊喂~~

   ​	其函数包含了以下函数 (可独立调用)

   ​	home (void)	//回到原点

   ​	clearDisplay (void)	//上面说过了!

   ​	clearBuffer (void)	//清除缓冲区



3. u8g2.disableUTF8Print (void)	//禁用UTF8`中文字符集`打印

   

4. u8g2.enableUTF8Print (void)     //启用UTF8`中文字符集`打印



5. u8g2.drawStr (x, y, *str)	//绘制字符串

   ​	x: X轴坐标 (0~128)

   ​	y: Y轴坐标 (0~64)

   ​	*str: 字符串内容

   ​	<u>需要先用u8g2.setFont ()设置字体</u>		<u>一般只用来绘制英文字符</u>



6. u8g2.drawUTF8 (x, y, *str)	//绘制UTF8编码的字符串

   ​	<u>同样需要setFont ()设置字体在先</u>



7. u8g2.drawXBMP (x, y, w, h, *bitmap)	 //绘制图像

   ​	w: 图像宽度

   ​	h: 图像长度

   ​	*bitmap: 图像内容	//推荐使用 `PCtolLCD2022` 取模得到



8. u8g2.print (*str)	//绘制内容

   ​	<u>需要先与setFont ()和setCursor ()配合再使用</u>



9. u8g2.sendBuffer (void)	//绘制缓冲区内容

   ​	<u>⚠占用内存大大大</u>		<u>先在缓冲区保存内容后使用此函数进行绘制</u>



10. u8g2.setCursor (x, y)	//设置绘制光标位置

    ​	<u>光标位置即你想要内容显示的位置</u>



11. u8g2.setFont (*font)	//设置字符集

    ​	<u>⚠中文字符集内存占用大大大</u>



## 其他相关知识

### 检查&设置

#### 驱动检查

1. 右键Windows菜单~>设备管理器 (以win11为例)
2. 检查设备管理器中有无端口 (COM和LPT)
3. 若无则到操作~>添加过时硬件~>安装我手动从列表选择的硬件~>端口 (COM和LPT)~>选择通信端口~>安装完成后重新回到步骤2

#### 软件检查&设置

1. 打开Arduino IDE

2. 等待自动安装软件包 (信息在Output)

3. 在 File~>Preferences~>Language 选择中文 ~>OK

4. 在文件~>首选项~>其他开发板管理器地址~>添加

   https://arduino.esp8266.com/stable/package_esp8266com_index.json
   https://dl.espressif.com/dl/package_esp32_index.json

5. 在文件~>首选项~>勾选上传后验证代码

6. 在文件~>首选项~>勾选显示详细输出

7. 在文件~>首选项~>项目文件夹地址~>选择您安装Arduino IDE的路径



### 关于程序功能选择

- 程序默认执行并显示三个内容 (时间/天气&B站数据&网易云数据)
- 如需关闭某项功能，请在BiliShow_v1.0.py找到如下两条代码

```python
# 功能开关
bili_button = 1		//B站模块
netease_button = 1		//网易云模块
```

- 把最后的参数1都更改为0即关闭功能
- 以上操作为功能性关闭，如需关闭OLED屏幕显示，请在BiliShow.ino找到如下板块
  - //B站板块	(250行-265行)
  - //网易云板块	(268行-280行)
  - 根据需要注释即可
- 做完以上操作后请重新生成exe和烧录程序



### 运行性能相关 (~~不严谨~~)

测试平台:	i5-1155G7/16G	一般负载

运行时间:	15s~40s

内存占用:	100MB

CPU占用: 	0%~9.3%



### 项目文件夹结构

- build: 生成exe的中间文件存放文件夹
- dist: 生成的可执行文件存放的文件夹
- img: 存放验证码图片的文件夹
- logs: 存放日志的文件夹
- MdImg: 存放.md文件图片的文件夹
- results: 存放获得的浏览器数据
- BiliShow.ino: Arduino文件
- BiliShow_v1.0.py: Python文件
- BiliShow_v1.0.spec: 生成exe所用的配置文件
- chromiumKey: 浏览器密钥 ¿
- cookies.txt: 存放获取到的B站Cookies
- ESP8266_v1.0.specbf: spec文件的备份
- HackBrowserData.exe: 获取浏览器信息的程序
- icon_bilibili-square.ico: 图标
- requirements.txt: pipreqs生成的依赖库
- requirements_all.txt: pip freeze生成的依赖库
- setting.h: 设置头文件
- Update BiliShow_v1.0 (without window).bat: 用于生成无窗口的exe
- Update BiliShow_v1.0.bat: 用于生成有命令行窗口的exe
- 说明文档.md: 说明文档



### HackBrowserData

- 功能: 获取本地存储的Cookies,用Cookies完成Python对数据的抓取
- 来源: 大佬的[项目地址](https://github.com/moonD4rk/HackBrowserData) (镜像地址: [gitee](https://gitee.com/writeup/HackBrowserData?_from=gitee_search))
- 关于报毒: 因为获取了敏感数据，所以部分杀毒软件会报错,请为它设置一个信任区，它不会发送任何数据到网络，只作用于本地,请用户了解作者的免责声明
- 速度比用selenium模拟浏览器登录快,而且成功率也高,使用selenium会出现登录提醒 (登录频率高了会被ban)
- 如果发现此程序没有权限打开/没有正常运行~>请用管理员权限打开cmd后输入
  - `net user administrator /active:yes`<~获得超级管理员权限
- 如果不想使用本程序，请将b站模块关闭，并把设置为netease_way=0
- 动手能力强的可以尝试手动获取cookie导入程序 （推荐浏览器插件: [EditThisCookie](https://www.editthiscookie.com/)）<~没用过不知道获取cookie能力如何



### dweet

- 支持把数据同步上传至云端
- 无需注册%获取API
- 可以直接访问网站 `dweet.io/get/latest/dweet/for/你的dweepy名字` 查看你的数据



### SliderYolo

- [项目地址](https://github.com/ScrapingBoot/SliderYolo)
- 滑块验证码Yolo识别！



### 图片取模

1. 安装并打开PCtolLCD2022

2. 选项~>字模选项    (设置为下图选项)

   ![1666756306964](D:\Mis\exe\Bili_Ring\Bili_ring\MdImg\1666756306964.png)

3. 文件~>打开    (选择BMP格式文件打开，分辨率最大为128*64,推荐为白底图片)

4. 对显示出来的图片进行修改    (左键为点亮，右键为熄灭)

5. 点击生成字模

6. 复制中间的`0x..,0x..`的部分

7. Done !
