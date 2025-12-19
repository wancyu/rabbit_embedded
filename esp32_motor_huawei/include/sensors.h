#ifndef SENSORS_H
#define SENSORS_H
#include "config.h"           // 自己的配置文件，例如引脚定义

void motor_init();
void motor_moving(int pluse_count = PULSE_COUNT, int pluse_delay = PULSE_DELAY);

#endif // SENSORS_H
