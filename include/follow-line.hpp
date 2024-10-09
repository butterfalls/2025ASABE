#include <Arduino.h>
#include <stdio.h>
#include <SoftwareSerial.h>
#include <motor-control.hpp>
//README里面也说过了，这个灰度的传感器的值和使用厂家提供的资料已经有了，主要是在这里进行一些集体申明，然后主要功能还是依赖主程序。
//循迹灰度引脚定义
//D1      D2      D3      D4      D5      D6      D7     D8
const int D1  =  1;  
const int D2  =  2;  
const int D3 =   3;  
const int D4 =   4;  
const int D5  =  5;  
const int D6  =  6;  
const int D7 =   7;  
const int D8 =   8;  

//定义各个循迹灰度引脚采集的数据的变量
int TrackSensorValueD1;
int TrackSensorValueD2;
int TrackSensorValueD3;
int TrackSensorValueD4;
int TrackSensorValueD5;
int TrackSensorValueD6;
int TrackSensorValueD7;
int TrackSensorValueD8;

