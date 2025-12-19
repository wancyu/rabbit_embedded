#ifndef JSON_SERVICE_H
#define JSON_SERVICE_H

#include <Arduino.h>

/**
 * @brief 构建环境数据 JSON 字符串
 * @param temp 温度值（摄氏度）
 * @param hum 湿度值（百分比）
 * @return 返回序列化后的 JSON 字符串
 * 
 * @example
 * String json = build_env_json(25.5, 65.3);
 * // 返回: {"temperature":25.5,"humidity":65.3}
 */
String build_env_json(float temp, float hum,float nh3);

#endif // JSON_SERVICE_H