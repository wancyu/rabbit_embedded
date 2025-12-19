#include "json_service.h"
#include <ArduinoJson.h>

// 构建env的json数据
String build_env_json(float temp, float hum, float nh3)
{
    JsonDocument doc;
    doc["temperature"] = temp;
    doc["humidity"] = hum;
    doc["ammonia"] = nh3;
    String payload;
    serializeJson(doc, payload);
    return payload;
}
String build_stop_json()
{
    JsonDocument doc;
    doc["services"][0]["service_id"] = "stop";
    doc["services"][0]["properties"]["camstate"] = 1;
    String payload;
    serializeJson(doc, payload);
    return payload;
}
