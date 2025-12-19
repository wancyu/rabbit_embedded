#include "json_service.h"
#include "sensors.h"
#include "mqtt_client.h"

// 摄像头拍照上报
void report_cam_data(String response_topic)
{
    String payload = build_stop_json();
    mqtt_publish(response_topic, payload);
}
