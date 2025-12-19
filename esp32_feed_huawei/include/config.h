#ifndef CONFIG_H
#define CONFIG_H 

// ================= WiFi =================
#define WIFI_SSID     "chenyu1"
#define WIFI_PASSWORD "cy383245"

// 舵机参数
#define SERVO_360_PIN 25
#define SERVO_180_PIN 26

// 硬件引脚定义
#define LOADCELL_DOUT_PIN 17
#define LOADCELL_SCK_PIN  16
#define CALIBRATION_FACTOR 719 //校准因子



// ============ 投喂系统配置 ============

// ===== 称重目标与参数 =====
#define TARGET_WEIGHT 50.0f             // 目标重量（单位：g）
#define SETTLE_TIME 1000                // 倾倒前稳定时间（ms）

// ===== 舵机速度参数 =====
#define FEED_SPEED 1500                 // 输料舵机全速运转速度
#define STOP_ANGLE 1500                 // 输料舵机停止角度

// ===== 舵机倾倒角度参数 =====
#define DUMP_ANGLE 150                  // 翻斗倾倒角度
#define SHAKE_ANGLE 130                 // 翻斗抖动角度
#define RETURN_ANGLE 90                 // 翻斗返回初始位置角度

// ===== 其他倾倒参数 =====
#define DUMP_ANGLE2 140                 // 翻斗倾倒角度2
#define DUMP_HOLD_TIME 3000             // 倾倒保持时间（ms）
#define DUMP_SHAKE_TIME 1000            // 倾倒抖动时间（ms）

// ================= MQTT =================
#define MQTT_HOST     "ef861ca468.st1.iotda-device.cn-north-4.myhuaweicloud.com"
#define MQTT_PORT     1883
#define MQTT_CLIENT   "67b683d83f28ab3d0384f27e_feedcar_0_0_2025022308"
#define MQTT_USER     "67b683d83f28ab3d0384f27e_feedcar"
#define MQTT_PASSWORD "98c142b691bea4b4265fc308fcea02d847d0d2d8b667b7ba1d18caadc834a825"
#define DEVICE_ID "67b683d83f28ab3d0384f27e_feedcar"


#endif