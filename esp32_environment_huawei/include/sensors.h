#ifndef SENSORS_H
#define SENSORS_H
#include "config.h"           // 自己的配置文件，例如引脚定义

// ================== 环境传感器接口 ==================

// 初始化环境传感器及PWM
void environment_init();

// 获取温度（单位：摄氏度）
float get_temperature();

// 获取湿度（单位：%RH）
float get_humidity();

// 获取氨气浓度（模拟量，单位根据传感器标定）
float get_nh3value();

void ledc_fan_out(int fan_power);

void ledc_water_curtain_out(int water_curtain_power);

#endif // SENSORS_H
