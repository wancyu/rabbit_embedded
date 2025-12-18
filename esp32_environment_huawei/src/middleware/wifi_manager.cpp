#include "wifi_manager.h"
#include "config.h"
static unsigned long lastWifiAttempt = 0;

bool wifi_connect()
{
    Serial.print("[WiFi] Connecting to ");
    Serial.println(WIFI_SSID);

    WiFi.mode(WIFI_STA);
    WiFi.setSleep(false);   
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    return true;
}

void wifi_reconnect()
{
    if (WiFi.status() == WL_CONNECTED)
        return;

    unsigned long now = millis();

    if (now - lastWifiAttempt < 3000)
        return;

    lastWifiAttempt = now;

    Serial.println("[WiFi] Reconnecting...");
    WiFi.disconnect(true);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}
