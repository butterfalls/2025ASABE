/*
 * @Author: butterfalls 1731860884@qq.com
 * @Date: 2024-10-09 17:48:24
 * @LastEditors: butterfalls 1731860884@qq.com
 * @LastEditTime: 2024-10-09 23:18:25
 * @FilePath: \hw1e:\Files\code\2025ASABE-selection\include\egg-selection.hpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <Arduino.h>
#include <stdio.h>
#include <SoftwareSerial.h>
#include <Servo.h>

Servo servo_upgear;//横杆齿轮驱动伺服电机，在这里是声明的对象，后续函数为这个名字加上.write这样的形式做引用。
Servo servo_leftgear;//左侧齿轮驱动伺服电机
Servo servo_rightgear;//右侧齿轮驱动伺服电机
Servo servo_grasp;//爪抓取驱动伺服电机
Servo servo_good;//好蛋出料驱动伺服电机
Servo servo_bad;//坏蛋出料驱动伺服电机

int pos_upgear=0;//这几个写的是伺服电机的位角，说人话就是每次转到多少度角的问题。
int pos_leftgear=0;
int pos_rightgear=0;
int pos_grasp=0;
int pos_good=0;
int pos_bad=0;

void grasp(){
    for (pos_grasp= 0; pos_grasp<= 90; pos_grasp+= 1) {       //pos+=1等价于pos=pos+1
    servo_grasp.write(pos_grasp);//看这里的servo_grasp说的是叫这个抓取的爪子的伺服电机进行转动；作用就是英文名，叫他抓东西的
    delay(5);					
}
}
void release(){
for (pos_grasp= 130; pos_grasp>=0; pos_grasp-= 1) {       //pos+=1等价于pos=pos+1
    servo_grasp.write(pos_grasp);//叫抓取的爪子放开来。
    delay(5);					
}
}
//我的构思的话，这个函数是实现调用旁边齿轮两个电机加上抓取的电机加上水平移动实现抓取到放好的整个过程
void deposit_good(){
for (pos_leftgear= 0; pos_leftgear<= 90; pos_leftgear+= 1) {       //降低爪的高度
    servo_leftgear.write(pos_leftgear);
    servo_rightgear.write(pos_rightgear);//这边可能会在同步上出现情况但是先这样写着毕竟两个齿轮应该不会出现这么精密的时间差影响运行的问题
    delay(5);					
}
grasp();//高度降低到足够低之后抓取。
for (pos_leftgear= 130; pos_leftgear>=0; pos_leftgear-= 1) {       //高度复位到下料合适高度。注意，这里不是简单的回到最开始的高度就行，而是下料合适的高度，所以有了后面的reset复位函数。
    servo_leftgear.write(pos_leftgear);
    servo_rightgear.write(pos_rightgear);
    delay(5);					
}
for (pos_upgear=0; pos_upgear<=130; pos_upgear+= 1) {       //水平移动到好蛋下料位置
    servo_upgear.write(pos_upgear);
    delay(5);					
}
release();
}
//刚才也讲了，我们放鸡蛋不可以直接在出发点的高度直接放，所以需要一个复位的过程，每次运行后回到一个固定的位置，然后程序才可以不断调用同样的函数持续进行。
void reset_good(){//good说的是好蛋放完之后的复位，后面bad就是坏蛋，这些命名应该很显而易见
//高度复位
for (pos_leftgear= 0; pos_leftgear<= 130; pos_leftgear+= 1) {       //降低爪的高度
    servo_leftgear.write(pos_leftgear);
    servo_rightgear.write(pos_rightgear);
    delay(5);					
}
//水平复位
for (pos_upgear=0; pos_upgear<=130; pos_upgear+= 1) {       //水平移动到好蛋下料位置
    servo_upgear.write(pos_upgear);
    delay(5);					
}
}

void deposit_bad(){
for (pos_leftgear= 0; pos_leftgear<= 130; pos_leftgear+= 1) {       //降低爪的高度
    servo_leftgear.write(pos_leftgear);
    servo_rightgear.write(pos_rightgear);
    delay(5);					
}
grasp();
for (pos_leftgear= 130; pos_leftgear>=0; pos_leftgear-= 1) {       //高度复位到下料合适高度
    servo_leftgear.write(pos_leftgear);
    servo_rightgear.write(pos_rightgear);
    delay(5);					
}
for (pos_upgear=0; pos_upgear<=130; pos_upgear+= 1) {       //水平移动到坏蛋下料位置
    servo_upgear.write(pos_upgear);
    delay(5);					
}
release();
}

void reset_bad(){
//高度复位
for (pos_leftgear= 0; pos_leftgear<= 130; pos_leftgear+= 1) {       //降低爪的高度
    servo_leftgear.write(pos_leftgear);
    servo_rightgear.write(pos_rightgear);
    delay(5);					
}
//水平复位
for (pos_upgear=0; pos_upgear<=130; pos_upgear+= 1) {       //水平移动到坏蛋下料位置
    servo_upgear.write(pos_upgear);
    delay(5);					
}
}
//这个就是到最后的位置把好蛋和坏蛋倒入收集框的函数
void discharge_good(){
for (pos_good=0; pos_good<=130; pos_good+= 1) {       //好蛋下料
    servo_good.write(pos_good);
    delay(5);					
}
}

void discharge_bad(){
for (pos_bad=0; pos_bad<=130; pos_bad+= 1) {       //好蛋下料
    servo_bad.write(pos_bad);
    delay(5);					
}
}