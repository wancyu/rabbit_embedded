#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <PubSubClient.h>

extern PubSubClient mqttclient;

bool mqtt_connect(void);
void mqtt_reconnect(void);
void mqtt_subscribe(void);
void mqtt_callback(char *topic, byte *payload, unsigned int length);

#endif
