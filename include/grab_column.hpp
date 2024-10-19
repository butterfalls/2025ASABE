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

#ifndef _FOLLOW_LINE_
#define _FOLLOW_LINE_
#include <follow-line.hpp>
#endif

#ifndef _MOTOR_CONTROL_
#define _MOTOR_CONTROL_
#include <motor-control.hpp>
#endif

int number=0;

void column_grab()
{
      if (track_detect()){//3,4,5,6=黑黑黑黑，就是到中间岔路口停下来开始识别+抓取的进程
    forward(100);//如果需要左移定位
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
        if(3000<(data.substring(7,11).toInt())<4000){
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
        if(3000<(data.substring(7,11).toInt())<4000){
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
  }
}