#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFi.h>
#include <Arduino.h>
#include "config.h"

// ================== WiFi 管理接口 ==================

// 尝试连接 WiFi（异步，不阻塞）
bool wifi_connect();

// WiFi 重连逻辑（定时调用，非阻塞）
void wifi_reconnect();

#endif // WIFI_MANAGER_H
