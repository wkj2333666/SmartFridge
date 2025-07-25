#include "camera_init.h"
#include <WiFi.h>
#include <SPIFFS.h>
#include "config.h"
#include "Suggester.h"

// Server
#include <WebServer.h>
#include <ArduinoJson.h>
#include "router.h"

// Subtask
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

bool previousSignal = 0;
bool currentSignal = 0;
bool ShotSignal = 0;
long duration = 0;
int distance = 0;

// 服务器任务句柄
TaskHandle_t serverTaskHandle = NULL;

// 服务器处理任务
void serverTask(void *parameter) {
  for (;;) {
    server.handleClient();
    vTaskDelay(pdMS_TO_TICKS(2)); // 2ms延迟
  }
}

bool detect_object() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin,HIGH);
  distance = duration * 0.034 / 2;
  if (distance<brigeHeight){
    currentSignal = 1;
  } else {
    currentSignal = 0;
  }
  if(currentSignal != previousSignal){
    ShotSignal = 1;
  }else{
    ShotSignal = 0;
  }
  previousSignal = currentSignal;

  return ShotSignal;
}

void setup() {
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);

  Serial.begin(SERIAL_PORT);
  while(!Serial);
  Serial.setDebugOutput(true);
  Serial.println();

  // initialize SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("An error occurred while mounting SPIFFS");
    return;
  }

  init_camera();

  WiFi.begin(ssid, password);
  WiFi.setSleep(false);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());

  Serial.print("Camera Ready! Use 'http://");
  Serial.print(WiFi.localIP());
  Serial.println("' to connect");

  // set Server:
  // set router
  server.on("/", handleRoot);
  server.on("/api/image", HTTP_GET, handleGetImage);

  // start server
  server.begin();
  Serial.print("HTTP server started on port ");
  Serial.println(SERVER_PORT);

  // 创建专用任务处理服务器
  xTaskCreatePinnedToCore(
    serverTask,       // 任务函数
    "ServerTask",     // 任务名称
    10000,            // 堆栈大小（字节）
    NULL,             // 任务参数
    1,                // 任务优先级（0-24，越大越高）
    &serverTaskHandle,// 任务句柄
    0                 // 运行在核心0（推荐）
  );
}

void loop() {
  // server.handleClient();
  // delay(2);
  if (detect_object()){
    Serial.println("shot!");
  }
  delay(100);
}
