#include "report_service.h"
#include "wifi_manager.h"
#include "mqtt_client.h"
#include "sensors.h"
#include "report_service.h"

void setup()
{
    Serial.begin(115200); // 初始化串口
    environment_init();
    wifi_connect();
    mqtt_connect();
}
//循环尽量不要出现长时间堵塞的情况。
void loop()
{
    wifi_reconnect();
    mqtt_reconnect();
}

