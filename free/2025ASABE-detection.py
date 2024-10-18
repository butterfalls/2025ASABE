import sensor, image, time, pyb
from pyb import Pin, LED, UART

# 初始化传感器
sensor.reset()
sensor.set_pixformat(sensor.RGB565)  # 设置为 RGB 彩色格式
sensor.set_framesize(sensor.QQVGA)    # 设置分辨率为 QQVGA (160x120)
sensor.skip_frames(time=2000)         # 等待 2 秒让设置生效

# 定义颜色阈值（可以根据需要调整）
red_threshold = (24, 80, 30, 117, -12, 80)
green_threshold = (27, 87, -48, -20, -11, 44)

# 定义最小像素阈值，过滤掉太小的干扰
MIN_PIXELS = 100  # 根据实际需求调整

# 定义距离检测参数
KNOWN_WIDTH = 2.7      # 物体的实际宽度（厘米）
FOCAL_LENGTH = 840     # 通过校准得到的焦距（像素）

def calculate_distance(perceived_width):
    """
    根据物体在图像中的宽度计算距离
    """
    if perceived_width == 0:
        return 0
    distance = (KNOWN_WIDTH * FOCAL_LENGTH) / perceived_width
    return distance

# 初始化 UART 通信（串口3，波特率9600）
uart = UART(3, 9600)

# 辅助函数：通过 UART 发送检测信息
def send_detection(color, uart, detection_value):
    message = f"{color}: {detection_value} - {pyb.millis()}"
    uart.write((message + '\n').encode())

# 封装处理函数，避免代码重复
def process_blobs(blobs, color, led_on, led_off, count, sum_pixels):
    """
    处理检测到的 blobs，只返回最大的有效 blob
    """
    if not blobs:
        return count, sum_pixels  # 没有检测到该颜色的 blob

    # 过滤掉小于 MIN_PIXELS 的 blobs
    valid_blobs = [blob for blob in blobs if blob.pixels() >= MIN_PIXELS]

    if not valid_blobs:
        return count, sum_pixels  # 没有有效的 blob

    # 找到最大的 blob
    largest_blob = max(valid_blobs, key=lambda b: b.pixels())

    # 绘制矩形
    img.draw_rectangle(largest_blob.rect())

    # 发送颜色标识符
    uart.write(f"{'1' if color == 'red' else '2'}\n".encode())

    # 控制 LED
    led_off.off()
    led_on.on()

    # 打印信息到串口监视器
    print(largest_blob.pixels())

    # 更新计数与累加
    if count[color] >= 10:
        average = sum_pixels[color] / 10
        send_detection(color, uart, average)
        sum_pixels[color] = 0
        count[color] = 0

    # 检查当前 blob 是否与平均值的偏差在允许范围内
    if count[color] != 0:
        average = sum_pixels[color] / count[color]
        if abs(average - largest_blob.pixels()) / average <= 0.4:
            sum_pixels[color] += largest_blob.pixels()
            count[color] += 1
        else:
            # 如果偏差过大，重置累加器
            sum_pixels[color] = largest_blob.pixels()
            count[color] = 1
    else:
        # 如果计数为0，初始化累加器
        sum_pixels[color] += largest_blob.pixels()
        count[color] += 1

    return count, sum_pixels

# 初始化计数器和累加器
count = {'red': 0, 'green': 0}
sum_pixels = {'red': 0, 'green': 0}

while True:
    clock = time.clock()
    img = sensor.snapshot().lens_corr(strength=1.7, zoom=1)  # 捕获一帧并进行畸变校正

    # 查找颜色 blobs
    blobs_red = img.find_blobs([red_threshold], pixels_threshold=MIN_PIXELS, area_threshold=MIN_PIXELS)
    blobs_green = img.find_blobs([green_threshold], merge=True, pixels_threshold=MIN_PIXELS, area_threshold=MIN_PIXELS)

    # 处理红色物体
    count, sum_pixels = process_blobs(
        blobs_red,
        'red',
        LED(1),  # 红色 LED，假设 LED(1) 代表红色
        LED(2),  # 其他 LED
        count,
        sum_pixels
    )

    # 处理绿色物体
    count, sum_pixels = process_blobs(
        blobs_green,
        'green',
        LED(2),  # 绿色 LED，假设 LED(2) 代表绿色
        LED(1),  # 其他 LED
        count,
        sum_pixels
    )

    # 释放 CPU 资源，防止 CPU 占用过高
    pyb.delay(50)  # 根据需要调整延迟时间
