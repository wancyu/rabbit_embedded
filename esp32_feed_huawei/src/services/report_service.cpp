#include "json_service.h"
#include "sensors.h"
#include "mqtt_client.h"

#define TOPIC_MSG_REPORT "$oc/devices/" DEVICE_ID "/sys/messages/up"
#define TOPIC_PROP_REPORT "$oc/devices/" DEVICE_ID "/sys/properties/report"
#define TOPIC_EVENT_REPORT "$oc/devices/" DEVICE_ID "/sys/events/up"

// 电机开始运动属性上报
void report_move()
{
    Serial.println("电机开始运动属性上报");
    String payload = build_move_json();
    mqtt_publish(TOPIC_PROP_REPORT, payload);
}
