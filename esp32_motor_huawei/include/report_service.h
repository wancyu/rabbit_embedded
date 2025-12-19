#ifndef REPORT_SERVICE_H
#define REPORT_SERVICE_H

#include <Arduino.h>
//上报环境参数
void report_env_data(String response_topic);

//上报摄像头拍照
void report_cam_data(String response_topic);

#endif // REPORT_SERVICE_H