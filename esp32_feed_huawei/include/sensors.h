#ifndef SENSORS_H
#define SENSORS_H
#include "config.h"           // 自己的配置文件，例如引脚定义


void servo360_write(int speed);

void servo_init();

void weight_init();

void servo180_write(int angle);

float get_weight();


#endif // SENSORS_H
