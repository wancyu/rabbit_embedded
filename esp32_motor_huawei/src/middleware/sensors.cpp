#include "sensors.h"
#include <ESP32Servo.h>
#include "HX711.h"


//电机初始化
void motor_init()
{
  // 先配置引脚模式
  pinMode(PUL_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(EN_PIN, OUTPUT);

  // 再设置初始电平
  digitalWrite(DIR_PIN, HIGH); // 设置方向为正转（远离电机）
  digitalWrite(EN_PIN, LOW);   // 使能电机
  digitalWrite(PUL_PIN, LOW);  // 脉冲初始化为低电平
}

// 电机运动指定距离，有默认参数
void motor_moving(int pluse_count, int pluse_delay)
{
  for (long i = 0; i < pluse_count; i++)
  {
    digitalWrite(PUL_PIN, HIGH);    // 发送 HIGH 脉冲
    delayMicroseconds(pluse_delay); // 延时
    digitalWrite(PUL_PIN, LOW);     // 发送 LOW 脉冲
    delayMicroseconds(pluse_delay); // 延时
  }
}