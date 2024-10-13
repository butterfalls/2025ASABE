#ifndef _STD_
#define _STD_

#include <Arduino.h>
#include <stdio.h>
#include <SoftwareSerial.h>

#endif
#include <egg-selection.hpp>
#include <follow-line.hpp>
#ifndef _FOLLOW_LINE_
#define _FOLLOW_LINE_

#include <motor-control.hpp>

#endif

#ifndef _EGG_SELECTION_
#define _EGG_SELECTION_
#include <Servo.h>
#endif

// put function declarations here:
// put function definitions here:

  int count=0;
  int number=0;
Servo myservo;
void setup() {
  // put your setup code here, to run once:
  //几个步进电机的对象的初始化
  myservo.attach(29, 500, 2500);//修正脉冲宽度，这个是伺服电机需要理解的代码之一，步进电机对象就是前面蓝色的部分，然后第一个值是引脚，后面是脉冲宽度的最小值和最大值就不多说了。
  servo_upgear.attach(30, 500, 2500);
  servo_leftgear.attach(31, 500, 2500);
  servo_rightgear.attach(32, 500, 2500);
  servo_grasp.attach(33, 500, 2500);
  servo_good.attach(34, 500, 2500);
  servo_bad.attach(35, 500, 2500);
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

  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
  digitalWrite(D5, HIGH);
  digitalWrite(D6, HIGH);
  digitalWrite(D7, HIGH);
  digitalWrite(D8, HIGH);
//这个是通信的部分启动那个串行接口，波特率给的是多少，然后arduino mega上面对应的哪个通信串口都有对应的编号，
  Serial.begin(9600);
  Serial3.begin(9600);

  leftward(50);
  forward(50);//左移+前进，定位到开始四个循环的初始位置

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
//如果没记错的话应该是黑1白0，然后八路循迹是从左到右1，2，3，4，5，6，7，8,3;4;5;6就是中间的四个//这个记错了，要把10全部换掉
  if((D3==1)&&(D4==0)&&(D5==0)&&(D6==1)){
    forward(50);//就是黑线在中间，这个车前进，因为这是个loop函数所以直接放if
  }

  if ((D3==0)&&(D4==0)&&(D5==0)&&(D6==0)){//3,4,5,6=黑黑黑黑，就是到中间岔路口停下来开始识别+抓取的进程
    leftward(0);//如果需要左移定位
  //与openMV通信，运行抓取和分类程序
  
  if (Serial3.available()) {    
   String data = Serial3.readStringUntil('\n');
   data.trim();//不会自动转化成字符串，不会自动添加其他字符
//读到1还是2 说的是视觉识别返回值是好蛋还是坏蛋
    if (data=="1"||data=="2"){
      if (data=="1") {
      Serial.println("Good detected!");//自动转化成字符串并添加换行符和回车符
      deposit_good();
      rightward(0);//如果需要左移定位,右移复位
      reset_good();
      number+=1;
      }
      else if (data=="2"){
      Serial.println("Bad detected!");
      deposit_bad();
      rightward(0);//如果需要左移定位,右移复位
      reset_bad();
      number+=1;
      }
    }
  }
  }

  //方法一：使用number记录收集次数:次数满之后返回，识别到一个蛋number值+1,4个满了之后掉头返回
  //count说的是现在在第几条循环上。
  if (number==4 && count<4){
    /*    if ((D3==1)&&(D4==0)&&(D5==0)&&(D6==1)||(D3==0)&&(D4==0)&&(D5==0)&&(D6==0)){
      backward(50);
    }
    else if ((D3==1)&&(D4==0)&&(D5==0)&&(D6==0)||(D3==0)&&(D4==0)&&(D5==0)&&(D6==0)){
      rightward (100);
    }*/
    revolve_cw(180);//掉头返回
    while ((D4==0)&&(D5==0)){
      forward(50);
    }
    revolve_ccw(90);
    forward(20);
    while ((D6==1)||(D7==1)||(D8==1)){
    forward(20);
    }
    if ((D1==0)||(D2==0)||(D3==0)){
    revolve_ccw(90);//左侧边沿由白转黑，转90度去下一条支路
    }
    forward(20);
    number=0;
    count++;
  }
//所有蛋均识别+收集完毕：count指的是第四条支路，启程去下料的位置
if (count==4){
  /*  if ((D3==1)&&(D4==0)&&(D5==0)&&(D6==1)||(D3==0)&&(D4==0)&&(D5==0)&&(D6==0)){
      backward(50);
    }
    else if ((D3==0)&&(D4==0)&&(D5==0)&&(D6==1)){
      leftward (100);
      backward(50);
       discharge_good();
      forward(50);
      leftward(100);
      discharge_bad();
    }*/
  revolve_cw(180);
    while ((D4==0)&&(D5==0)){
      forward(50);
    }
    revolve_cw(90);
    while (((D1==1)||(D2==1)||(D3==1))&&((D6==1)||(D7==1)||(D8==1)))//白黑白，继续执行，可能有逻辑上的重复后面可能要改先这样放着
    {
      forward(50);
    }
  if (((D1==0)||(D2==0))&&((D7==0)||(D8==0))){//黑黑黑，到收集框的那个位置。
    revolve_cw(90);
  }
  //后退对准
  backward(50);
  deposit_good();
//左移到另一个框
  leftward(100);
  deposit_bad();

}

}

