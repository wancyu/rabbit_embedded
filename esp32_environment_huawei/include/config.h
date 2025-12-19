#ifndef CONFIG_H
#define CONFIG_H 

// ================= WiFi =================
#define WIFI_SSID     "chenyu1"
#define WIFI_PASSWORD "cy383245"




// 光敏传感器引脚定义
#define MQ135D 25  // 光敏传感器数字输出引脚
#define MQ135A 34  // 光敏传感器模拟输出引脚

// 风扇和水泵引脚定义
#define FAN_PIN 13   // 风扇连接的 PWM 引脚
#define PUMP_PIN 12  // 水泵连接的 PWM 引脚

// PWM 参数
#define PWM_FREQ 1000        // PWM 频率（Hz）
#define PWM_RESOLUTION 12    // PWM 分辨率（8 位，范围为 0-255）
#define PWM_FREQ2 1000       // PWM 频率（Hz）
#define PWM_RESOLUTION2 12   // PWM 分辨率（8 位，范围为 0-255）



// ================= MQTT =================
#define MQTT_HOST     "ef861ca468.st1.iotda-device.cn-north-4.myhuaweicloud.com"
#define MQTT_PORT     1883
#define MQTT_CLIENT   "67b683d83f28ab3d0384f27e_environment_0_0_2025022306"
#define MQTT_USER     "67b683d83f28ab3d0384f27e_environment"
#define MQTT_PASSWORD "17a85498dc8339943237186c61e7aa2861be33405971bd0eab52d080f762ae92"
#define DEVICE_ID "67b683d83f28ab3d0384f27e_environment"



#endif