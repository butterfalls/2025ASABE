/*
 * @Author: butterfalls 1731860884@qq.com
 * @Date: 2024-10-09 17:48:24
 * @LastEditors: butterfalls 1731860884@qq.com
 * @LastEditTime: 2024-10-18 17:03:49
 * @FilePath: \hw1e:\Files\code\2025ASABE-selection\include\follow-line.hpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef _STD_
#define _STD_

#include <Arduino.h>
#include <stdio.h>
#include <SoftwareSerial.h>

#endif


#ifndef _FOLLOW_LINE_
#define _FOLLOW_LINE_

#include <motor-control.hpp>

#endif
//README里面也说过了，这个灰度的传感器的值和使用厂家提供的资料已经有了，主要是在这里进行一些集体申明，然后主要功能还是依赖主程序。
//循迹灰度引脚定义
//D1      D2      D3      D4      D5      D6      D7     D8
const int D1 =   32; 
const int D2 =   48; 
const int D3 =   47; 
const int D4 =   33; 
const int D5 =   34; 
const int D6 =   36; 
const int D7 =   35;  
const int D8 =   37; 

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
		rightward(40);
	}
	else if((D4 != 0)&&(D5 == 0))   
	{
		leftward(40);
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
	else   
	{
		forward(40);
	}
}

int track_detect()
{
    if(D3==0&&D4==0&&D5==0&&D6==0) return 1;
}

int corner_right()
{
	if(D1==0&&D2==0&&D3==0&&D4==0&&D5==0) return 1;
}

int corner_left()
{
	if(D4==0&&D5==0&&D6==0&&D7==0&&D8==0) return 1;
}