#include "camera_init.h"
#include <WiFi.h>
#include <SPIFFS.h>

// Server
#include <WebServer.h>
#include <ArduinoJson.h>
#include "router.h"

// ===========================
// Enter your WiFi credentials
// ===========================
const char* ssid = "wkj24";
const char* password = "wkj24wkj";

void startCameraServer();

void setup() {
  Serial.begin(115200);
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
}
