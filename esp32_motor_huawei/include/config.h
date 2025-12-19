#ifndef CONFIG_H
#define CONFIG_H 

// ================= WiFi =================
#define WIFI_SSID     "chenyu1"
#define WIFI_PASSWORD "cy383245"

// 步进电机引脚定义
#define PUL_PIN 16   // 脉冲信号引脚（PUL）
#define DIR_PIN 17   // 方向信号引脚（DIR）
#define EN_PIN 4     // 使能引脚

// 步进电机参数
#define PULSE_COUNT 41000  // 脉冲数量
#define PULSE_DELAY 80     // 脉冲周期（微秒）


// ================= MQTT =================
#define MQTT_HOST     "ef861ca468.st1.iotda-device.cn-north-4.myhuaweicloud.com"
#define MQTT_PORT     1883
#define MQTT_CLIENT   "67b683d83f28ab3d0384f27e_motor_0_0_2025022306"
#define MQTT_USER     "67b683d83f28ab3d0384f27e_motor"
#define MQTT_PASSWORD "17a85498dc8339943237186c61e7aa2861be33405971bd0eab52d080f762ae92"
#define DEVICE_ID "67b683d83f28ab3d0384f27e_motor"


#endif