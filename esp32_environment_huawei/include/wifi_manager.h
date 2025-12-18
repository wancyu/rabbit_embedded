#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H


#include <Arduino.h>
#include <WiFi.h>

extern WiFiClient wificlient;

/**
 * @brief 连接 WiFi（带超时）
 * @return true   连接成功
 * @return false  连接失败
 */
bool wifi_connect();

/**
 * @brief WiFi掉线自动重连（建议在 loop 周期调用）
 */
void wifi_reconnect();

#endif
