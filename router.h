// router.h

#include <WebServer.h>
#include <ArduinoJson.h>

#define SERVER_PORT 88
WebServer server(SERVER_PORT);


void handleRoot() {
  server.send(200, "text/html", 
    "<html><body>"
    "<h1>SmartFridge API</h1>"
    // "<p>可用端点：</p>"
    "<ul>"
    // "<li>GET /api/sensors - 获取传感器数据</li>"
    // "<li>POST /api/control - 控制设备</li>"
    // "<li>GET /api/status - 系统状态</li>"
    "<li>Hello World!</li>"
    "</ul>"
    "</body></html>");
}

