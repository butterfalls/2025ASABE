#ifndef _STD_
#define _STD_
#include <Arduino.h>
#include <stdio.h>
#include <SoftwareSerial.h>
#endif

#ifndef _EGG_SELECTION_
#define _EGG_SELECTION_
#include <egg-selection.hpp>
#endif

#ifndef _MOTOR_CONTROL_
#define _MOTOR_CONTROL_
#include <motor-control.hpp>
#endif

#define semicycle 180

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

int corner_right_count=0;
int corner_left_count = 0;
int corner_track_count = 0;


int number=0;

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

void back_first_track()
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
			corner_track_count--;
			if(corner_track_count==0) {
				forward(80);
				while(D8==1&&D1==1)
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
				}
				break;
			}
		}
	}
}


//十字路口处抓取，计数抓取到第四个蛋时，掉头返回，不负责移动
void column_grab()
{
    if (track_detect()){//3,4,5,6=黑黑黑黑，就是到中间岔路口停下来开始识别+抓取的进程
    forward(200);//如果需要左移定位
    left_translation(100);

  //与openMV通信，运行抓取和分类程序
    if (Serial3.available()) {    
        while(true)
        {
        String data = Serial3.readStringUntil('\n');
        data.trim();//不会自动转化成字符串，不会自动添加其他字符
    //读到1还是2 说的是视觉识别返回值是好蛋还是坏蛋
        if (data.substring(0, 5)=="white"||data.substring(0, 5)=="green"){
            if (data.substring(0, 5)=="white") {
            Serial.println("Good detected!");//自动转化成字符串并添加换行符和回车符
            if((3000<(data.substring(7,11).toInt()))&&((data.substring(7,11).toInt())<4000)){
            deposit_good();
            right_translation(100);//如果需要左移定位,右移复位
            reset_good();
            number+=1;
            break;
            }
            else if(data.substring(7,11).toInt()<=3000)//以下数值需要在下面同步调整另一组，即修改一个修改两处
            {
            left_translation(100);
            }
            else
            {
            right_translation(100);
            }
            }
            else if (data.substring(0, 5)=="brown"){
            Serial.println("Bad detected!");
            if((3000<(data.substring(7,11).toInt()))&&((data.substring(7,11).toInt())<4000)){
            deposit_bad();
            rightward(0);//如果需要左移定位,右移复位
            reset_bad();
            number+=1;
            break;
            }
            else if(data.substring(7,11).toInt()<=3000)
            {
            left_translation(100);
            }
            else
            {
            right_translation(100);
            }
        }
    }
    }
  }
    right_translation(30);
    forward(100);
    if(number==4){
        revolve_cw(semicycle);//掉头返回
        back_first_track();
    }
  }
}