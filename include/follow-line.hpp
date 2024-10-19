/*
 * @Author: butterfalls 1731860884@qq.com
 * @Date: 2024-10-09 17:48:24
 * @LastEditors: butterfalls 1731860884@qq.com
 * @LastEditTime: 2024-10-19 22:36:44
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

#ifndef _GRAB_COLUMN_
#define _GRAB_COLUMN_
#include<grab_column.hpp>
#endif




//白色出1，黑色出0
void track_zhixian1()
{
	while(true)
	{
		if((D3==1)&&(D4 == 0)&&(D5 == 0)&&(D6 == 1))    
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
		else if((D3 == 0)&&(D4 == 0)&&(D2 == 0)&&(D1==1))   
		{
			rightward(40);
		}
		else if((D5 == 0)&&(D6 == 0)&&(D7 == 0)&&(D8==1))   
		{
			leftward(40);
		}
		else if(track_detect())
		{
			corner_track_count++;
			column_grab();
			break;
		}
		else if(corner_left())
		{
			revolve_ccw(semicycle);
		}
		else if(corner_right())
		{
			revolve_cw(semicycle);
		}
		else   
		{
			forward(40);
		}
	}
}


// void discharge(int quality,int direction)//1是好蛋，0是坏蛋，右侧下料，不负责转回去;1是右手下蛋，0是左手
// {
// if (corner_left()||corner_right()||track_detect())
// {//第一次下料
//     if(direction) revolve_ccw(semicycle); else revolve_cw(semicycle);
//     if(quality)discharge_good();else discharge_bad();
// }
// else
// {
// 	forward(20);
// }
// }