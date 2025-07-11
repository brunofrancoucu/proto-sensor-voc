// On low storage: server.sendHeader("Content-Encoding", "gzip");
#include <WebServer.h> // Include the WebServer library
#include <LittleFS.h>
// Internal
#include "state.h"

void handleRoot(WebServer &server)
{
    File file = LittleFS.open("/root.html", "r");
    if (!file)
    {
        server.send(500, "text/plain", "File not found");
        return;
    }
    server.streamFile(file, "text/html");
    file.close();
}

// /data
void handleData(WebServer &server)
{
    // Handle read errors
    // if (isnan(state.temperature) || isnan(state.humidity))
    // {
    //     server.send(500, "application/json", "{\"error\": \"Sensor read failed\"}");
    //     return;
    // }

    String json = "{";
    json += "\"temperature\": " + String(state.temperature, 1) + ",";
    json += "\"humidity\": " + String(state.humidity, 1) + ",";
    json += "\"air\": " + String(state.air);
    json += "}";

    server.send(200, "application/json", json);
}

// // From html form - connect esp to wifi network
// void handleConnect()
// {
//     ssid = server.arg("ssid");
//     password = server.arg("password");

//     server.send(200, "text/html", "Connecting to WiFi...");

//     // WiFi.begin(ssid.c_str(), password.c_str());
//     // delay(1000);
//     // Optional: store to EEPROM or SPIFFS
// }

// Catchall routes

//   // Optional: catch-all for other static files (CSS, JS, etc.)
//   server.onNotFound([]() {
//     String path = server.uri();
//     File file = LittleFS.open(path, "r");
//     if (file) {
//       String contentType = "text/plain";
//       if (path.endsWith(".html")) contentType = "text/html";
//       else if (path.endsWith(".css")) contentType = "text/css";
//       else if (path.endsWith(".js")) contentType = "application/javascript";

//       server.streamFile(file, contentType);
//       file.close();
//     } else {
//       server.send(404, "text/plain", "Not Found");
//     }