#include "sensors.h"
#include <Adafruit_AHTX0.h>  

// 创建对象
Adafruit_AHTX0 aht;

// 初始化温湿度传感器，氨气传感器，两个pwm
void environment_init()
{
  ledcAttach(FAN_PIN, PWM_FREQ, PWM_RESOLUTION);
  ledcAttach(PUMP_PIN, PWM_FREQ2, PWM_RESOLUTION2);
  Wire.begin();
  aht.begin();
}


void ledc_fan_out(int fan_power)
{
    fan_power = constrain(fan_power, 0, 100);
    int power = round(fan_power * 4095.0 / 100.0); // 12 bit
    ledcWrite(FAN_PIN, power);
}

void ledc_water_curtain_out(int water_curtain_power)
{
    water_curtain_power = constrain(water_curtain_power, 0, 100);
    int power = round(water_curtain_power * 4095.0 / 100.0); // 12 bit
    ledcWrite(PUMP_PIN, power);
}


//获取温度
float get_temperature()
{
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);
  float temperature = 0;
  temperature = temp.temperature;
  return temperature;
}
//获取湿度
float get_humidity()
{
  sensors_event_t hum, temp;
  aht.getEvent(&hum, &temp);
  float humidity = 0;
  humidity = hum.relative_humidity;
  return humidity;
}
//获取氨气浓度
float get_nh3value()
{
  float nh3value = 0;
  nh3value = analogRead(MQ135A);
  return nh3value;
}
