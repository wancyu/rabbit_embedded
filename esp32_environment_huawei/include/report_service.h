#ifndef REPORT_SERVICE_H
#define REPORT_SERVICE_H

#include <Arduino.h>

/**
 * @brief 上报环境数据
 * 
 * 获取温度和湿度传感器的数据，构建 JSON 格式，
 * 通过 MQTT 发布到属性主题
 * 
 * @example
 * report_env_data();  // 上报当前环境数据
 * 
 * 发布的 JSON 格式：
 * {
 *   "temperature": 25.5,
 *   "humidity": 65.3
 * }
 */
void report_env_data(String response_topic);

#endif // REPORT_SERVICE_H