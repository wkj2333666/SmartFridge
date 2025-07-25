#pragma once

// hc-sr05 config
#define echoPin 1//连接D0引脚
#define trigPin 2//连接D1引脚
extern const int brigeHeight;// = 50; //冰箱高度

// ===========================
// Enter your WiFi credentials
// ===========================
extern const char* ssid;// = "wkj24";
extern const char* password;// = "wkj24wkj";

extern const int SERIAL_PORT;// = 115200;
extern const int DEFAULT_QUEUE_LENGTH;