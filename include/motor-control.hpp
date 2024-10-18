/*
 * @Author: butterfalls 1731860884@qq.com
 * @Date: 2024-10-09 17:48:24
 * @LastEditors: butterfalls 1731860884@qq.com
 * @LastEditTime: 2024-10-13 00:38:26
 * @FilePath: \hw1e:\Files\code\2025ASABE-selection\include\motor-control.hpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef _STD_
#define _STD_

#include <Arduino.h>
#include <stdio.h>
#include <SoftwareSerial.h>

#endif
//这些都是电机的引脚的申明，方向/脉冲/使能，就不多说了
#define directionPinlf 48  //定义11引脚接DIR，控制电机正反转
#define directionPinlb 40
#define directionPinrf 50
#define directionPinrb 41
#define stepPinlf 46   //定义12引脚接驱动器脉冲信号PUL
#define stepPinlb 44
#define stepPinrf 52
#define stepPinrb 45
#define ENlf 47
#define ENlb 42
#define ENrf 51
#define ENrb 43
#define DELAY_US 1000  //定义延时时间 _微秒，也就是半个脉冲的周期时间
#define stepsPerRevolution 56000   //脉冲数量
//发脉冲的，因为四个电机要同步转所以这么写
//1:lf,左前；2：rf,右前；3：lb,左后；4：rb,右后
//which说的是转哪个电机，然后1，2，3，4对应的哪个电机上面一条注释已经给出了。
//times是转的时间，这个需要重点调试。
//dir是转动方向。
//这个函数是写的最主要的函数，那个电机转什么方向转多久一个函数都解决了，后面整车向哪里运行都是基于这个函数的。
//说了那么多，那么这个函数有用吗？其实一点作用都没有，你可以发现后面的函数全部是初始化使能，然后涉及到这个函数的代码全部被注释掉了，因为这样子同步性会有一定程度的问题，
void pulse_send(int times){
      for(int i=0;i<times;i++)//脉冲信号函数循环、数字控制圈数
      {
      digitalWrite(stepPinlf ,HIGH); //高电平
      digitalWrite(stepPinrf ,HIGH); //高电平      
      digitalWrite(stepPinlb ,HIGH); //高电平
      digitalWrite(stepPinrb ,HIGH); //高电平  
      delayMicroseconds(DELAY_US);//延时
      digitalWrite(stepPinlf ,LOW);//低电平
      digitalWrite(stepPinrf ,LOW);//低电平
      digitalWrite(stepPinlb ,LOW);//低电平
      digitalWrite(stepPinrb ,LOW);//低电平
      delayMicroseconds(DELAY_US);//延时
      }
}

void start(){
  digitalWrite(ENlf ,HIGH);
  digitalWrite(ENlb ,HIGH);
  digitalWrite(ENrf ,HIGH);
  digitalWrite(ENrb ,HIGH);
}

void forward(int times){
  start();
  digitalWrite(directionPinlf ,HIGH);
  digitalWrite(directionPinrf ,LOW);
  digitalWrite(directionPinlb ,HIGH);
  digitalWrite(directionPinrb ,LOW);
  pulse_send(times);
  }


void backward(int times){
  start();
  digitalWrite(directionPinlf ,LOW);
  digitalWrite(directionPinrf ,HIGH);
  digitalWrite(directionPinlb ,LOW);
  digitalWrite(directionPinrb ,HIGH);
  pulse_send(times);
}

void brake(){
  digitalWrite(ENlf ,LOW);
  digitalWrite(ENlb ,LOW);
  digitalWrite(ENrf ,LOW);
  digitalWrite(ENrb ,LOW);
}

void leftward(int times){
  start();
  digitalWrite(directionPinlf ,LOW);
  digitalWrite(directionPinrf ,HIGH);
  digitalWrite(directionPinlb ,HIGH);
  digitalWrite(directionPinrb ,LOW);
  pulse_send(times);
}

void rightward(int times){
  start();
  digitalWrite(directionPinlf ,HIGH);
  digitalWrite(directionPinrf ,HIGH);
  digitalWrite(ENlb ,LOW);
  digitalWrite(ENrb ,LOW);
  pulse_send(times);
}

void revolve_cw(int times){
  start();
  digitalWrite(directionPinlf ,HIGH);
  digitalWrite(directionPinrf ,HIGH);
  digitalWrite(directionPinlb ,HIGH);
  digitalWrite(directionPinrb ,HIGH);
  pulse_send(times);
}

void revolve_ccw(int times){
  start();
  digitalWrite(directionPinlf ,LOW);
  digitalWrite(directionPinrf ,LOW);
  digitalWrite(directionPinlb ,LOW);
  digitalWrite(directionPinrb ,LOW);
  pulse_send(times);
}
