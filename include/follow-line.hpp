/*
 * @Author: butterfalls 1731860884@qq.com
 * @Date: 2024-10-09 17:48:24
 * @LastEditors: butterfalls 1731860884@qq.com
 * @LastEditTime: 2024-10-11 17:29:15
 * @FilePath: \hw1e:\Files\code\2025ASABE-selection\include\follow-line.hpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
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
//白色出1，黑色出0
void track_zhixian1()
{
	if((D4 == 0)&&(D5 == 0))    
	{
		forward(40);
	}
	else if((D4 == 0)&&(D5 != 0))   
	{
		leftward(40);
	}
	else if((D4 != 0)&&(D5 == 0))   
	{
		rightward(40);
	}
	else if((D3 == 0)&&(D4 == 0))   
	{
		rightward(40);
	}
	else if((D5 == 0)&&(D6 == 0))   
	{
		leftward(40);
	}
	else if((D3 == 0)&&(D4 != 0))    
	{
		rightward(40);
	}
	else if((D5 != 0)&&(D6 == 0))   
	{
		leftward(40);
	}
	else if((D2 == 0)&&(D3 == 0))   
	{
		rightward(40);
	}
	else if((D6 == 0)&&(D7 == 0))   
	{
		leftward(40);
	}
	else if((D2 == 0)&&(D3 != 0))    
	{
		rightward(40);
	}
	else if((D6 != 0)&&(D7 == 0))  
	{
		leftward(40);
	}
	else if((D1 == 0)&&(D2 == 0))   
	{
		rightward(40);
	}
	else if((D7 == 0)&&(D8 == 0))   
	{
		leftward(40);
	}
	else if((D1 == 0)&&(D2 != 0))    
	{
		rightward(40);
	}	
	else if((D7 !=0)&&(D8 == 0))   
	{
		leftward(40);
	}
	else   
	{
		forward(40);
	}
}

int track_detect()
{
    if(D3==0&&D4==0&&D5==0&&D6==0) return 1;
}
