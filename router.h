// router.h
#include <string>

#include <WebServer.h>
#include <ArduinoJson.h>
#include "esp_camera.h"

#define SERVER_PORT 88
WebServer server(SERVER_PORT);


void handleRoot() {
  server.send(200, "text/html", 
    "<html><body>"
    "<h1>SmartFridge API</h1>"
    "<p>available router: </p>"
    "<ul>"
    "<li>GET /api/image - get camera image</li>"
    // "<li>POST /api/control - 控制设备</li>"
    // "<li>GET /api/status - 系统状态</li>"
    "<li>Hello World!</li>"
    "</ul>"
    "</body></html>");
}

void handleGetImage() {
  camera_fb_t* fb = esp_camera_fb_get();
  if (!fb) {
    server.send(500, "text/plain", "Camera capture failed");
    return;
  }

  // uint8_t *image_data = fb->buf;      // 图像数据指针
  // size_t image_length = fb->len;      // 图像数据长度（字节数）

  server.send_P(200, PSTR("image/jpeg"), reinterpret_cast<const char*>(fb->buf), fb->len);
  
  esp_camera_fb_return(fb); // free memory
}