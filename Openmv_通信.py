# Untitled - By: 86183 - 周三 3月 31 2021

import sensor, image, time, math, json
import time
from pyb import UART
from pyb import Servo

#舵机接口定义
s1 = Servo(1) # P7
s2 = Servo(2) # P8

# UART 3, and baudrate.
uart = UART(3, 19200)

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA) # we run out of memory if the resolution is much bigger...
sensor.skip_frames(30)
sensor.set_auto_gain(False)  # must turn this off to prevent image washout...
sensor.set_auto_whitebal(False)  # must turn this off to prevent image washout...
clock = time.clock()

# 注意！与find_qrcodes不同，find_apriltags 不需要软件矫正畸变就可以工作。



# 注意，输出的姿态的单位是弧度，可以转换成角度，但是位置的单位是和你的大小有关，需要等比例换算

# f_x 是x的像素为单位的焦距。对于标准的OpenMV，应该等于2.8/3.984*656，这个值是用毫米为单位的焦距除以x方向的感光元件的长度，乘以x方向的感光元件的像素（OV7725）
# f_y 是y的像素为单位的焦距。对于标准的OpenMV，应该等于2.8/2.952*488，这个值是用毫米为单位的焦距除以y方向的感光元件的长度，乘以y方向的感光元件的像素（OV7725）

# c_x 是图像的x中心位置
# c_y 是图像的y中心位置

f_x = (2.8 / 3.984) * 160 # 默认值
f_y = (2.8 / 2.952) * 120 # 默认值
c_x = 160 * 0.5 # 默认值(image.w * 0.5)
c_y = 120 * 0.5 # 默认值(image.h * 0.5)
Tx = 0
Ty = 0
Tz = 0
Tx_averange = 0
value = 0
str_read = ""
a = 1   # 代表判断循环次数
b = 0
c = 0

s1.calibration(500,2500,500)
s2.calibration(500,2500,500)

#s1.pulse_width(1500)
#s2.pulse_width(2500)

def degrees(radians):
    return (180 * radians) / math.pi

s2.pulse_width(2500)

while(True):
    # uart.write("1")
    if (uart.any()):
        str_read = str(uart.read(), "utf-8")
        # print(str_read)
        if (str_read == "began"):
            s2.pulse_width(1500)  #底盘舵机 2500为向前面看
            print("舵机转动完成，开始定位购物盒")
            while(1):
                for i in range(50):
                    clock.tick()
                    img = sensor.snapshot()
                    for tag in img.find_apriltags(fx=f_x, fy=f_y, cx=c_x, cy=c_y): # 默认为TAG36H11
                        img.draw_rectangle(tag.rect(), color = (255, 0, 0))
                        img.draw_cross(tag.cx(), tag.cy(), color = (0, 255, 0))
                        print_args = (tag.x_translation(), tag.y_translation(), tag.z_translation(), \
                            degrees(tag.x_rotation()), degrees(tag.y_rotation()), degrees(tag.z_rotation()))
                        # 位置的单位是未知的，旋转的单位是角度
                        Tx += tag.x_translation()
                        Ty += tag.y_translation()
                        Tz += tag.z_translation()
                        print("Tx: %f, Ty %f, Tz %f, Rx %f, Ry %f, Rz %f" % print_args)
                        b = b + 1
                    # print(clock.fps())
                if (b == 0):
                    b = 1
                Tx_averange = Tx/b + 4
                Ty_averange = Ty/b
                Tz_averange = Tz/b - 2.3
                print("Tx_average: %.2f, Ty_average: %.2f, Tz_average: %.2f" % (Tx_averange, Ty_averange, Tz_averange))
                jixiebi_range = (((9.5-Tx_averange)**2) + (Tz_averange-9)**2)**0.5
                openmv_range = ((Tx_averange**2) + ((Tz_averange-2)**2))**0.5
                print("jixiebi_range = %.2f\nopenmv_range = %.2f" % (jixiebi_range,openmv_range))
                foundation_angle = math.degrees(math.acos((12.42**2+jixiebi_range**2-openmv_range**2) / (2*12.42*jixiebi_range)))
                dabi_angle = math.degrees(math.acos((jixiebi_range**2 + 12**2 - 19**2) / (2*jixiebi_range*11.9)))
                xiaobi_angle = math.degrees(math.acos((12**2 + 19**2 - jixiebi_range**2) / (2*12*19)))

                foundation_angle = (2*(180-(foundation_angle+40.1)+135) / 3)
                dabi_angle = (180-dabi_angle)
                xiaobi_angle = (xiaobi_angle-10)

                if(Tz_averange**2>132.5):
                    foundation_angle = foundation_angle - 3
                    dabi_angle = dabi_angle + 8
                    xiaobi_angle = xiaobi_angle - 10
                if (dabi_angle < 68):
                    dabi_angle = 63
                elif (dabi_angle >= 68 and dabi_angle < 77):
                    dabi_angle = 72
                elif (dabi_angle >= 77 and dabi_angle < 86):
                    dabi_angle = 81
                elif (dabi_angle >= 86 and dabi_angle < 95):
                    dabi_angle = 90
                elif (dabi_angle >= 95 and dabi_angle < 104):
                    dabi_angle = 99
                elif (dabi_angle >= 104 and dabi_angle < 113):
                    dabi_angle = 108
                elif (dabi_angle >= 113 and dabi_angle < 122):
                    dabi_angle = 117
                elif (dabi_angle >= 122 and dabi_angle < 131):
                    dabi_angle = 126
                elif (dabi_angle >= 131):
                    dabi_angle = 135
                if(b != 1):
                    b = 0
                    print("底盘角度为：%d\n大臂角度为：%d\n小臂的角度为：%d" % (foundation_angle, dabi_angle, xiaobi_angle))
                    output_dipan = json.dumps(foundation_angle)
                    output_dabi = json.dumps(dabi_angle)
                    output_xiaobi = json.dumps(xiaobi_angle)
                    uart.write(output_dipan+','+output_dabi+','+output_xiaobi)
                    Tx = 0
                    Ty = 0
                    Tz = 0
                    print("b = %d" % b)
                    break
                elif (c == 4):
                    b = 0
                    print("经历了五次未识别到定位码,跳出循环")
                    break
                else:
                    c = c + 1
                    print("未识别到定位码")
        elif (str_read == "erweima"):
            # 二维码识别代码
            print("二维码识别")
            s1.pulse_width(1200)
            while(1):
                for i in range(400):
                    clock.tick()
                    img = sensor.snapshot()
                    img.lens_corr(1.8) # 1.8的强度参数对于2.8mm镜头来说是不错的。
                    for code in img.find_qrcodes():
                        img.draw_rectangle(code.rect(), color = (255, 0, 0))
                        if (code[4] == "XiaoMing"):
                            print("识别到小明")
                            uart.write("6")
                            value = 1
                            break
                        elif (code[4] == "XiaoHong"):
                            print("识别到小鸿")
                            uart.write("5")
                            value = 1
                            break
                if (value == 0 and a == 5):
                    print(a)
                    print("经历了5次未识别出二维码,程序将重新执行")
                    a = 1
                    uart.write("4")  # 代表未识别到二维码
                    break
                elif (value == 1):
                    a = 1
                    break
                else :
                    print(a)
                    uart.write("7")
                    print("未识别出二维码")
                a = a + 1
        else :
            print("未接收到开始信号")
    time.sleep_ms(1000)
