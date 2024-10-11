import sensor, image, time, pyb
import pyb
from pyb import Pin , LED , UART
#TX=pyb.Pin("P4",pyb.Pin.OUT_PP)
#RX=pyb.Pin("P5",pyb.Pin.IN)
#TX.low()
# 初始化传感器
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA)
sensor.skip_frames(time=2000)
# 定义颜色阈值
red_threshold = (24, 80, 30, 117, -12, 80)
green_threshold = (23, 58,-70, -19, 0, 30)

# 初始化 UART 通信
uart = UART(3, 9600)
# Helper function to send a detection over UART
def send_detection(color, uart, detection_number, total_detections):
    message = f"{color}: {detection_number} - {total_detections} - {pyb.millis()}"
    uart.write((message + '\n').encode())
while(True):
    clock = time.clock()
    img = sensor.snapshot().lens_corr(strength=1.7, zoom=1)

    blobs_red = img.find_blobs([red_threshold])
    blobs_green = img.find_blobs([green_threshold])
    sent_ids = set()


    # 处理红色物体
    for i, blob in enumerate(blobs_red):
        if blob.pixels() not in sent_ids:
            img.draw_rectangle(blob.rect())
            #send_detection('red', uart, i + 1, len(blobs_red))
            uart.write('1\n')
            LED(2).off()
            LED(1).on()
            #TX.high()
            print(1)
            #time.sleep_ms(50)
            #TX.low()
            sent_ids.add(blob.pixels())
#            pyb.delay(50)  # 减少延迟以避免长时间暂停


# 处理绿色物体
    for i, blob in enumerate(blobs_green):
        if blob.pixels() not in sent_ids:
            img.draw_rectangle(blob.rect())
            uart.write('2\n')
            LED(2).on()
            LED(1).off()
            #TX.high()
            print(2)
        #time.sleep_ms(50)
        #TX.low()
        #send_detection('green', uart, i + 1, len(blobs_green))
            sent_ids.add(blob.pixels())
#            pyb.delay(50)  # 减少延迟以避免长时间暂停

    # 释放 CPU 资源
#    pyb.delay(50)  # 短时间延迟以保持循环响应
