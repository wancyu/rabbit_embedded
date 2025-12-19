#include "report_service.h"
#include "wifi_manager.h"
#include "mqtt_client.h"
#include "sensors.h"
#include "feed_service.h"

void setup()
{
    Serial.begin(115200); 
    servo_init();
    weight_init();
    wifi_connect();
    mqtt_connect();

}

void loop()
{
    wifi_reconnect();
    mqtt_reconnect();
    feed_control();
}

