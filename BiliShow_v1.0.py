# 导包
import os
import time
import requests
from fake_useragent import UserAgent
import json
import dweepy
import logging
from Ring_Utils.cookies import bili_login
from Ring_Utils.spiders import life_weather
from Ring_Utils.spiders import netease_personal_2
from Ring_Utils.spiders import netease_personal
from plyer import notification

# Dweepy设备名 与Arduino一致
device_name = "devicename"

# 您的城市名称的拼音
city_name = "beijing"

# 心知天气密钥
xz_key = "CRAZYKFCV50"

# B站bid
bid = "111145"

# 网易云账号&密码
netease_acc = "account"
netease_pwd = "password"

# 网易云信息获取方式 (0:使用selenium 1:使用HackBrowserData)
netease_way = 1

# 您文件BiliShow.ino所在的目录
root_path = r"D:\blue\unwelcomeshcool"

# 刷新间隔 ("time_interval"秒刷新一次天气,每刷新10次天气刷新一次B站/网易云~>这俩官方基本一天才刷一次)
time_interval = 60

# 功能开关 (1:开 0:关)
bili_button = 1
netease_button = 1

# 初始化
old_1 = 0
old_2 = 0
old_3 = 0
old_5 = 0
old_6 = 0
old_7 = 0
count_1 = 1
count_2 = 1
flag_1 = 0
flag_2 = 0

# 其他变量定义
fans_number = ""
view_number = ""
likes_number = ""
plays_number = ""
fans_number_n = ""
exponent_number = ""
o_1 = ""
o_2 = ""
o_3 = ""
o_5 = ""
o_6 = ""
o_7 = ""
cookies_bili = ""

# Bilibili接口URL
fans_url = f"https://api.bilibili.com/x/relation/stat?vmid={bid}"
view_likes_url = f"https://api.bilibili.com/x/space/upstat?mid={bid}"

# 循环
while flag_1 == 0:
    # 捕获可能异常
    try:

        print("开始获取数据...")

        if netease_button == 1:
            if netease_way == 0:
                plays_number, fans_number_n, exponent_number = netease_personal.net_spiders(netease_acc, netease_pwd,
                                                                                            root_path, netease_button)
            elif netease_way == 1:
                net_tuple = netease_personal_2.netease_login(root_path)
                plays_number = net_tuple[0]
                fans_number_n = net_tuple[1]
                exponent_number = net_tuple[2]

        if bili_button == 1:

            # 伪装请求标头
            headers_bili = {
                "user-agent": UserAgent(use_cache_server=False, verify_ssl=False).random,
            }

            # 获取cookies
            cookies_bili = bili_login.bili_cookies(root_path, bili_button)

            # 请求获得Response
            fans_response = requests.get(url=fans_url)
            view_likes_response = requests.get(url=view_likes_url, headers=headers_bili, cookies=cookies_bili)

            # 判断状态码
            if fans_response.status_code == 200 and view_likes_response.status_code == 200:

                # 取出数据
                fans_number = json.loads(fans_response.text)["data"]["follower"]
                view_number = json.loads(view_likes_response.text)["data"]["archive"]["view"]
                likes_number = json.loads(view_likes_response.text)["data"]["likes"]
            else:
                print(
                    f"状态码: {fans_response.status_code}, {view_likes_response.status_code},请检查网络状况!/n如果仍错误，也许爬虫URL已失效!")

                # count计数器+1
                count_1 += 1

        # 内循环Loop
        while flag_2 == 0:

            w_text, w_temperature = life_weather.get_weather(city_name, xz_key, 1)

            # 数据处理
            # 第一次进入
            if count_1 == 1:
                o_1 = ""
                o_2 = ""
                o_3 = ""
                o_5 = ""
                o_6 = ""
                o_7 = ""
                count_1 = 2

            # 第一次之后进入
            else:
                if bili_button == 1:
                    o_1 = f"({fans_number - old_1})"
                    o_2 = f"({view_number - old_2})"
                    o_3 = f"({likes_number - old_3})"
                if netease_button == 1:
                    o_5 = f"({int(plays_number) - int(old_5)})"
                    o_6 = f"({int(fans_number_n) - int(old_6)})"
                    o_7 = f"({int(exponent_number) - int(old_7)})"

            # 判断数据
            if o_1 == "(0)":
                o_1 = ""
            if o_2 == "(0)":
                o_2 = ""
            if o_3 == "(0)":
                o_3 = ""
            if o_5 == "(0)":
                o_5 = ""
            if o_6 == "(0)":
                o_6 = ""
            if o_7 == "(0)":
                o_7 = ""

            # 拼装数据
            dweepy_data = {
                "Fans": str(fans_number) + o_1,
                "Likes": str(likes_number) + o_2,
                "View": str(view_number) + o_3,
                "Weather": str(w_text),
                "Temperature": str(w_temperature),
                "Plays": str(plays_number) + o_5,
                "NetFans": str(fans_number_n) + o_6,
                "Exponent": str(exponent_number) + o_7
            }

            # Dweepy连接
            dweepy.dweet_for(device_name, dweepy_data)

            # 控制台输出
            print("-" * 50)
            print(dweepy_data)
            print("已上传至dweepy")
            print("-" * 50)

            # 存储为旧数据
            old_1 = fans_number
            old_2 = view_number
            old_3 = likes_number
            old_5 = plays_number
            old_6 = fans_number_n
            old_7 = exponent_number

            # count计数器+1
            count_2 += 1

            # 控制循环结束
            if count_2 > 10:
                flag_2 = 1
                count_2 = 1

            # 设置循环间隔时间
            time.sleep(time_interval)

    # B站Cookie失效执行其他有效操作
    except KeyError as e:

        # 输出情况
        print(f"错误类型: {type(e)},发生错误详情: {e}, 很可能B站cookie已失效, 等待更新中...")

        # 重新获取Cookies
        cookies_bili = bili_login.bili_cookies(root_path)

        # 弹窗提示
        notification.notify(title="ESP8266_v1.0", message="B站Cookie失效",
                            app_icon="D:/Mis/exe/Bili_Ring/Bili_ring/icon_bilibili-square.ico", timeout=5)

        # count计数器+1
        count_1 += 1

    except requests.exceptions.ConnectTimeout as e:
        # 输出情况
        print(f"错误类型: {type(e)},发生错误详情: {e}, 连接过于频繁，正在重试...")

        # 设置循环间隔时间
        time.sleep(time_interval)

        # 弹窗提示
        notification.notify(title="ESP8266_v1.0", message="连接过于频繁",
                            app_icon="D:/Mis/exe/Bili_Ring/Bili_ring/icon_bilibili-square.ico", timeout=5)

        # count计数器+1
        count_1 += 1

    # 未知错误时执行操作
    except Exception as e:

        # 输出情况
        print(f"错误类型: {type(e)},发生错误详情: {e}, 未知错误")

        # 设置循环间隔时间
        time.sleep(time_interval)

        # 弹窗提示
        notification.notify(title="ESP8266_v1.0", message="未知错误",
                            app_icon="D:/Mis/exe/Bili_Ring/Bili_ring/icon_bilibili-square.ico", timeout=5)

        # count计数器+1
        count_1 += 1

    # 控制循环结束
    if count_1 > 10:
        flag_1 = 1

# 暂停程序
os.system("pause")

# 输出日志
# 创建logger
logger = logging.getLogger()
logger.setLevel(logging.INFO)

# 创建handler
log_path = f"{root_path}/logs/log.txt"
handler = logging.FileHandler(log_path, mode='w')
handler.setLevel(logging.DEBUG)

# 定义输出格式
formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(lineno)d - %(message)s')
handler.setFormatter(formatter)

# 加载logger到handler
logger.addHandler(handler)
