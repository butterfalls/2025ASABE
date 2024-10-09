#include <Arduino.h>
#include <stdio.h>
#include <SoftwareSerial.h>
//这些都是电机的引脚的申明，方向/脉冲/使能，就不多说了
#define directionPinlf 40  //定义11引脚接DIR，控制电机正反转
#define directionPinlb 2
#define directionPinrf 10
#define directionPinrb 9
#define stepPinlf 44   //定义12引脚接驱动器脉冲信号PUL
#define stepPinlb 4
#define stepPinrf 12
#define stepPinrb 11
#define ENlf 42
#define ENlb 6
#define ENrf 14
#define ENrb 13
#define DELAY_US 1000  //定义延时时间 _微秒，也就是半个脉冲的周期时间
#define stepsPerRevolution 56000   //脉冲数量
//发脉冲的，因为四个电机要同步转所以这么写
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
//1:lf,左前；2：rf,右前；3：lb,左后；4：rb,右后
//which说的是转哪个电机，然后1，2，3，4对应的哪个电机上面一条注释已经给出了。
//times是转的时间，这个需要重点调试。
//dir是转动方向。
//这个函数是写的最主要的函数，那个电机转什么方向转多久一个函数都解决了，后面整车向哪里运行都是基于这个函数的。
//说了那么多，那么这个函数有用吗？其实一点作用都没有，你可以发现后面的函数全部是初始化使能，然后涉及到这个函数的代码全部被注释掉了，因为这样子同步性会有一定程度的问题，
void runmotor(int which,int dir,int times){
if (which ==1){
    digitalWrite(ENlf ,HIGH);//高电平
    digitalWrite(directionPinlf ,dir);
    pulse_send(times);
}
      
else if (which==2){
    digitalWrite(ENrf ,HIGH);//高电平
    digitalWrite(directionPinrf ,dir);
    pulse_send(times);
}


else if(which==3){
    digitalWrite(ENlb ,HIGH);//高电平
    digitalWrite(directionPinlb ,dir);
    pulse_send(times);
}   

else if (which==4){
    digitalWrite(ENrb ,HIGH);//高电平
    digitalWrite(directionPinrb ,dir);
    pulse_send(times);
}
}

void forward(int times){
  //runmotor(1,HIGH,times);
 // runmotor(2,HIGH,times);
  //runmotor(3,HIGH,times);
  //runmotor(4,HIGH,times);
  digitalWrite(directionPinlf ,LOW);
  digitalWrite(directionPinrf ,HIGH);
  digitalWrite(directionPinlb ,LOW);
  digitalWrite(directionPinrb ,HIGH);
  pulse_send(times);
  }


void backward(int times){
  //runmotor(1,LOW,times);
  //runmotor(2,LOW,times);
  //runmotor(3,LOW,times);
  //runmotor(4,LOW,times);
  digitalWrite(directionPinlf ,LOW);
  digitalWrite(directionPinrf ,LOW);
  digitalWrite(directionPinlb ,LOW);
  digitalWrite(directionPinrb ,LOW);
  pulse_send(times);
}

void brake(){
  digitalWrite(ENlf ,LOW);
  digitalWrite(ENlb ,LOW);
  digitalWrite(ENrf ,LOW);
  digitalWrite(ENrb ,LOW);
}

void leftward(int times){
 // runmotor(1,LOW,times);
  //runmotor(2,HIGH,times);
  //runmotor(3,HIGH,times);
  //runmotor(4,LOW,times);

  digitalWrite(directionPinlf ,LOW);
  digitalWrite(directionPinrf ,HIGH);
  digitalWrite(directionPinlb ,HIGH);
  digitalWrite(directionPinrb ,LOW);
  pulse_send(times);
}

void rightward(int times){
  //runmotor(1,HIGH,times);
  //runmotor(2,LOW,times);
  //runmotor(3,LOW,times);
  //runmotor(4,HIGH,times);
  digitalWrite(directionPinlf ,HIGH);
  digitalWrite(directionPinrf ,LOW);
  digitalWrite(directionPinlb ,LOW);
  digitalWrite(directionPinrb ,HIGH);
  pulse_send(times);
}

void revolve_cw(int times){
  //runmotor(1,HIGH,times);
  //runmotor(2,LOW,times);
  //runmotor(3,HIGH,times);
  //runmotor(4,LOW,times);
  digitalWrite(directionPinlf ,HIGH);
  digitalWrite(directionPinrf ,LOW);
  digitalWrite(directionPinlb ,HIGH);
  digitalWrite(directionPinrb ,LOW);
  pulse_send(times);
}

void revolve_ccw(int times){
  //runmotor(1,LOW,times);
  //runmotor(2,HIGH,times);
  //runmotor(3,LOW,times);
  //runmotor(4,HIGH,times);

  digitalWrite(directionPinlf ,LOW);
  digitalWrite(directionPinrf ,HIGH);
  digitalWrite(directionPinlb ,LOW);
  digitalWrite(directionPinrb ,HIGH);
  pulse_send(times);
}
//下面的函数还是错误的，不过我们这里应该不会需要用到。
void leftback(int times){
  runmotor(1,LOW,times);
  digitalWrite(ENlb ,LOW);
  digitalWrite(ENrf ,LOW);
  runmotor(4,LOW,times);
}

void rightback(int times){
  runmotor(1,LOW,times);
  digitalWrite(ENlb ,LOW);
  digitalWrite(ENrf ,LOW);
  runmotor(4,LOW,times);
}

void leftforward(int times){
  digitalWrite(ENlf ,LOW);  
  digitalWrite(ENrb ,LOW);
  runmotor(2,HIGH,times);
  runmotor(3,HIGH,times);
}

void rightforward(int times){
  runmotor(1,HIGH,times);
  digitalWrite(ENlb ,LOW);
  digitalWrite(ENrf ,LOW);
  runmotor(4,HIGH,times);
}