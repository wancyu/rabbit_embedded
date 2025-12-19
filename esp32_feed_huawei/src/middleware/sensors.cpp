#include "sensors.h"
#include <ESP32Servo.h>
#include "HX711.h"

Servo servo360;  // 输料舵机（360°连续旋转）
Servo servo180;  // 翻斗舵机（180°标准）
HX711 scale;  //HX711


// 舵机
void servo_init()
{
  servo360.attach(SERVO_360_PIN); // 输料螺杆舵机（连续旋转）
  servo180.attach(SERVO_180_PIN); // 翻斗舵机
  servo360.write(STOP_ANGLE);     // 初始停止状态1500
  servo180.write(RETURN_ANGLE);   // 初始水平状态120
}

void weight_init()
{
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(CALIBRATION_FACTOR); // 设置校准因子
  scale.tare();                        // 称，清零
}

void servo360_write(int speed)
{
  servo360.writeMicroseconds(speed);
}


void servo180_write(int angle)
{
  servo180.write(angle);
}

// 称重
float get_weight()
{
  scale.tare();
  float num = scale.get_units();
  return num;
}
