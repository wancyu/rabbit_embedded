#ifndef JSON_SERVICE_H
#define JSON_SERVICE_H

#include <Arduino.h>

//构建环境数据 JSON 字符串
String build_env_json(float temp, float hum,float nh3);

//构建上报摄像头拍照json字符串
String build_stop_json();
#endif // JSON_SERVICE_H