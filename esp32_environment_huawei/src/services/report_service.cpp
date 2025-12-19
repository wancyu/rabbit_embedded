#include "json_service.h"
#include "sensors.h"
#include "mqtt_client.h"

void report_env_data(String response_topic){
    float temp = get_temperature();
    float hum = get_humidity();
    float nh3 = get_nh3value();
    String payload = build_env_json(temp,hum,nh3);
    mqtt_publish(response_topic,payload);
}

