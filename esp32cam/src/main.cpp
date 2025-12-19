#include <Arduino.h>
#include <WiFi.h>
#include "esp_camera.h"
#include "board_config.h"

// ================== 服务器配置 ==================
const char *SERVER_IP = "10.20.41.103";
const int SERVER_PORT = 80;

// ================== WiFi ==================
const char *ssid = "chenyu";
const char *password = "cy383245";

// ================== 发送照片 ==================
void sendPhoto(camera_fb_t *fb)
{
    WiFiClient client;

    Serial.println("Connecting to server...");
    if (!client.connect(SERVER_IP, SERVER_PORT))
    {
        Serial.println("Server connect failed");
        return;
    }

    // ---- HTTP Header（必须完整、规范）----
    client.print(
        "POST /upload HTTP/1.1\r\n"
        "Host: ");
    client.print(SERVER_IP);
    client.print("\r\n"
                 "Content-Type: application/octet-stream\r\n"
                 "Content-Length: ");
    client.print(fb->len);
    client.print("\r\n"
                 "Connection: close\r\n"
                 "\r\n");

    // JPEG 原始二进制
    client.write(fb->buf, fb->len);

    Serial.printf("Photo sent: %d bytes\n", fb->len);

    // 给 Flask 时间读完数据
    delay(200);

    // 读服务器响应
    while (client.available())
    {
        Serial.write(client.read());
    }

    client.stop();
    Serial.println("\nUpload done");
}

void setup()
{
    Serial.begin(115200);
    delay(500);
    Serial.println("\nBooting...");

    // ---------- WiFi ----------
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(300);
        Serial.print(".");
    }
    Serial.println("\nWiFi OK");
    Serial.print("ESP32 IP: ");
    Serial.println(WiFi.localIP());

    // ---------- Camera ----------
    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;

    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;

    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sccb_sda = SIOD_GPIO_NUM;
    config.pin_sccb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;

    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;

    // 调节图片质量,低分辨率
    config.frame_size = FRAMESIZE_QVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;

    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK)
    {
        Serial.printf("Camera init failed: 0x%x\n", err);
        while (true)
            ;
    }
    Serial.println("Camera OK");

    camera_fb_t *fb = esp_camera_fb_get();
    if (!fb)
    {
        Serial.println("Capture failed");
    }
    else
    {
        Serial.printf("Captured %d bytes\n", fb->len);
        sendPhoto(fb);
        esp_camera_fb_return(fb);
    }
}
//只运行一次，重启重新发送
void loop()
{
}
