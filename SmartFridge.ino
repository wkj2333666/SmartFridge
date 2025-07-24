#include "camera_init.h"
#include <WiFi.h>
#include <SPIFFS.h>
#include "config.h"

// Server
#include <WebServer.h>
#include <ArduinoJson.h>
#include "router.h"

void startCameraServer();

bool previousSignal = 0;
bool currentSignal = 0;
bool ShotSignal = 0;
long duration = 0;
int distance = 0;

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

  startCameraServer();

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
}

void loop() {
  // Do nothing. Everything is done in another task by the web server
  // delay(10000);

  server.handleClient();
  delay(2);
  if (detect_object()){
    Serial.println("shot!");
  }
  delay(50);
}
