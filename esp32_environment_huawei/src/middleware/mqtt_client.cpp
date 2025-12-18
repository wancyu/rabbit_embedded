#include "mqtt_client.h"
#include "wifi_manager.h"
#include "config.h"
#include <Arduino.h>
#include "ArduinoJson.h"
// ================= 华为云 IoT MQTT Topic =================
// 平台 → 设备
#define TOPIC_MSG_DOWN "$oc/devices/" DEVICE_ID "/sys/messages/down"
#define TOPIC_PROP_GET "$oc/devices/" DEVICE_ID "/sys/properties/get/request_id="
#define TOPIC_PROP_SET "$oc/devices/" DEVICE_ID "/sys/properties/set/request_id="
#define TOPIC_COMMAND_SET "$oc/devices/" DEVICE_ID "/sys/commands/request_id="
#define TOPIC_EVENT_DOWN "$oc/devices/" DEVICE_ID "/sys/events/down"
// 设备 → 平台
#define TOPIC_PROP_GET_RESP "$oc/devices/" DEVICE_ID "/sys/properties/get/response/request_id="
#define TOPIC_PROP_SET_RESP "$oc/devices/" DEVICE_ID "/sys/properties/set/response/request_id="
#define TOPIC_COMMAND_SET_RESP "$oc/devices/" DEVICE_ID "/sys/commands/response/request_id="
#define TOPIC_MSG_REPORT "$oc/devices/" DEVICE_ID "/sys/messages/up"
#define TOPIC_PROP_REPORT "$oc/devices/" DEVICE_ID "/sys/properties/report"
#define TOPIC_EVENT_REPORT "$oc/devices/" DEVICE_ID "/sys/events/up"
// ================= MQTT 对象 =================
PubSubClient mqttclient(wificlient);

// 上次 MQTT 重连时间
static unsigned long lastMqttConn = 0;

// mqtt连接
bool mqtt_connect()
{
    mqttclient.setServer(MQTT_HOST, MQTT_PORT);
    mqttclient.setCallback(mqtt_callback);
    mqttclient.setKeepAlive(30);

    Serial.println("[MQTT] Connecting...");

    if (mqttclient.connect(MQTT_CLIENT, MQTT_USER, MQTT_PASSWORD))
    {
        mqtt_subscribe();
        Serial.println("[MQTT] Connected");
        return true;
    }
    else
    {
        Serial.print("Failed, rc=");
        Serial.println(mqttclient.state());
        return false;
    }
}
// mqtt订阅
void mqtt_subscribe()
{
    mqttclient.subscribe(TOPIC_MSG_DOWN);
    mqttclient.subscribe(TOPIC_PROP_GET);
    mqttclient.subscribe(TOPIC_PROP_SET);
    mqttclient.subscribe(TOPIC_COMMAND_SET);
    mqttclient.subscribe(TOPIC_EVENT_DOWN);
}
// mqtt重连
void mqtt_reconnect()
{
    if (!mqttclient.connected())
    {
        unsigned long now = millis();
        if (now - lastMqttConn > 30000)
        {
            lastMqttConn = now;
            Serial.println("[MQTT] ReConnecting...");
            if (mqtt_connect())
            {
                mqtt_subscribe();
                Serial.println("[MQTT] ReConnected");
            }
        }
    }

    mqttclient.loop();
}
//mqtt回调
void mqtt_callback(char *topic, byte *payload, unsigned int length)
{
    JsonDocument doc;
    DeserializationError err = deserializeJson(doc, payload, length);
    if (err)
    {
        Serial.print("[MQTT] JSON parse failed: ");
        Serial.println(err.f_str());
        return;
    }

    Serial.println(topic);      // 打印topic
    serializeJson(doc, Serial); // 打印json内容

    if (strncmp(topic, TOPIC_MSG_DOWN, strlen(TOPIC_MSG_DOWN)) == 0)
    {
        message_handle(doc);
    }
    else if (strncmp(topic, TOPIC_PROP_GET, strlen(TOPIC_PROP_GET)) == 0)
    {
        String topic(topic);
        String response_topic = TOPIC_PROP_GET_RESP + topic.substring(strlen(TOPIC_PROP_GET_RESP));
        property_handle(doc, response_topic);
    }
    else if (strncmp(topic, TOPIC_PROP_SET, strlen(TOPIC_PROP_SET)) == 0)
    {
        String topic(topic);
        String response_topic = TOPIC_PROP_SET_RESP + topic.substring(strlen(TOPIC_PROP_SET_RESP));
        property_set(doc, response_topic);
    }

    else if (strncmp(topic, TOPIC_COMMAND_SET, strlen(TOPIC_COMMAND_SET)) == 0)
    {
        String topic(topic);
        String response_topic = TOPIC_COMMAND_SET_RESP + topic.substring(strlen(TOPIC_COMMAND_SET_RESP));
        command_handle(doc, response_topic);
    }
    else
    {
        Serial.println("TOPIC_UNKNOWN");
    }
}
//消息下发处理
void message_handle(const JsonDocument &doc)
{
    if (!doc["content"].is<JsonObject>())
        return;

    const char *type = doc["content"]["type"];
    if (!type)
        return;
    if (strcmp(type, "post_f") == 0)
    {
        int feed = doc["content"]["feed"] | 0;
    }
}
// 属性查询处理
void property_handle(const JsonDocument &doc, String response_topic)
{
    const char *service_id = doc["service_id"];
    if (!service_id)
        return;
    if (strcmp(service_id, "get_tha") == 0)
    {
        // 这里回属性
    }
}
// 命令设置处理
void command_handle(const JsonDocument &doc, String response_topic)
{
    // const char *command = doc["command_name"];
    // if (!command)
    //     return;
    // if (strcmp(command, "state") == 0)
    // {
    //     const char *requestId = strrchr(topic, '=');
    //     if (requestId)
    //     {
    //         response_sf(doc, requestId + 1);
    //     }
    // }
}
// 属性设置设置
void property_set(const JsonDocument &doc, String response_topic)
{
}
//mqtt上报
void mqtt_publish(String topic, String payload)
{
    mqttclient.publish(topic.c_str(), payload.c_str());
}