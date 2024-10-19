#ifndef _STD_
#define _STD_
#include <Arduino.h>
#include <stdio.h>
#include <SoftwareSerial.h>
#endif

#ifndef _MOTOR_CONTROL_
#define _MOTOR_CONTROL_
#include <motor-control.hpp>
#endif

#ifndef _EGG_SELECTION_
#define _EGG_SELECTION_
#include <egg-selection.hpp>
#endif

#ifndef _GRAB_COLUMN_
#define _GRAB_COLUMN_
#include<grab_column.hpp>
#endif

#ifndef _FOLLOW_LINE_
#define _FOLLOW_LINE_
#include <follow-line.hpp>
#endif

// put function declarations here:
// put function definitions here:

  int count=0;

#define depth 2000

Servo myservo;
void setup() {
  // put your setup code here, to run once:
  //几个步进电机的对象的初始化
  myservo.attach(29, 500, 2500);//修正脉冲宽度，这个是伺服电机需要理解的代码之一，步进电机对象就是前面蓝色的部分，然后第一个值是引脚，后面是脉冲宽度的最小值和最大值就不多说了。
  servo_upgear.attach(27, 500, 2500);
  servo_leftgear.attach(2, 500, 2500);
  servo_rightgear.attach(9, 500, 2500);
  servo_grasp.attach(21, 500, 2500);
  servo_good.attach(3, 500, 2500);
  servo_bad.attach(8, 500, 2500);

  //配置舵机初始位置
  servo_upgear.write(1500);
  servo_leftgear.write(41);
  servo_rightgear.write(1500);
  servo_grasp.write(1500);
  servo_good.write(41);//面向arduino，左边是good
  servo_bad.write(139);
  //初始化OUTPUT和INPUT，这些就不多余说了，
  pinMode(directionPinlf ,OUTPUT);//DIR输出信号
  pinMode(directionPinlb ,OUTPUT);
  pinMode(directionPinrf ,OUTPUT);
  pinMode(directionPinrb ,OUTPUT);

  pinMode(stepPinlf ,OUTPUT);
  pinMode(stepPinlb ,OUTPUT);
  pinMode(stepPinrf ,OUTPUT);
  pinMode(stepPinrb ,OUTPUT);// PUL输出信号

  pinMode(ENlf ,OUTPUT);
  pinMode(ENlb ,OUTPUT);
  pinMode(ENrf ,OUTPUT);
  pinMode(ENrb ,OUTPUT);
//这个是灰度模块八个传感器的引脚的设置
  pinMode (D1, INPUT);
  pinMode (D2, INPUT);
  pinMode (D3, INPUT);
  pinMode (D4, INPUT);
  pinMode (D5, INPUT);
  pinMode (D6, INPUT);
  pinMode (D7, INPUT);
  pinMode (D8, INPUT);

  digitalWrite(ENrf, HIGH);
  digitalWrite(ENlf, HIGH);
  digitalWrite(ENrb, HIGH);
  digitalWrite(ENlb, HIGH);

//这个是通信的部分启动那个串行接口，波特率给的是多少，然后arduino mega上面对应的哪个通信串口都有对应的编号，
  Serial.begin(9600);
  Serial3.begin(9600);

  forward(100);
  revolve_ccw(100);
  forward(300);//达到初始位置
}

void loop() {
  // put your main code here, to run repeatedly:
  //储存传感器读到的数据
  TrackSensorValueD1=digitalRead(D1);
  TrackSensorValueD2=digitalRead(D2);
  TrackSensorValueD3=digitalRead(D3);
  TrackSensorValueD4=digitalRead(D4);
  TrackSensorValueD5=digitalRead(D5);
  TrackSensorValueD6=digitalRead(D6);
  TrackSensorValueD7=digitalRead(D7);
  TrackSensorValueD8=digitalRead(D8);
//检测是黑0白1
  track_zhixian1();
  //方法一：使用number记录收集次数:次数满之后返回，识别到一个蛋number值+1,4个满了之后掉头返回
  //count说的是现在在第几条循环上。
  if (number==4 && count==1){

    revolve_ccw(semicycle/2);
    forward(2000);//走到第一个下料处

    revolve_ccw(semicycle);
    discharge_good();
    revolve_cw(semicycle);

    forward(depth);
    revolve_ccw(semicycle);
    discharge_bad();
    number=0;
    count++;

    forward(depth);
    revolve_cw(semicycle/2);
  }
  if (number==4 && count==2){
    revolve_cw(semicycle/2);

    discharge_good();
    revolve_cw(semicycle);

    forward(depth);
    discharge_bad();
    number=0;
    count++;

    revolve_ccw(semicycle/2);
  }
  if (number==4 && count==3){
    revolve_cw(semicycle/2);

    discharge_bad();

    forward(depth);
    discharge_good();
    number=0;
    count++;

    revolve_cw(semicycle);

    forward(depth);
    forward(2000);

    revolve_ccw(semicycle);
  }
  if (number==4 && count==4){
    revolve_cw(semicycle/2);
    forward(2000);//走到第一个下料处

    discharge_bad();

    forward(depth);
    discharge_good();
    number=0;
    count++;

    revolve_ccw(semicycle);
    forward(depth);
    forward(2000);
    revolve_ccw(semicycle/2);

    //开始抓取第四线路右侧
    forward(8000);
    revolve_ccw(semicycle);

  }
  if (number==4 && count==5){
    revolve_cw(semicycle/2);
    forward(2000);//走到第一个下料处

    discharge_bad();

    forward(depth);
    discharge_good();
    number=0;
    count++;

    forward(2000);
    forward(200);
    left_translation(200);
  }
  
  if(count==5)
  {
    while(true)
    {
      
    }
  }
}

