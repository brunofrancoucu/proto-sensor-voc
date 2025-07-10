#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>

#include "data/state.h"

// const char *ssid = "BOMBA_HOTSPOT";
// const char *password = "12345678";

WebServer server(80);
DNSServer dnsServer;

const byte DNS_PORT = 53;

String ssid = "";
String password = "";

const char index_html[] PROGMEM = R"rawliteral(
    <form action="/connect" method="POST">
      WiFi SSID: <input type="text" name="ssid"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Connect">
    </form>
  )rawliteral";

// /
void handleRoot()
{
  server.send(200, "text/html", index_html);
}

// /data
void handleData()
{
  // Handle read errors
  if (isnan(state.temperature) || isnan(state.humidity))
  {
    server.send(500, "application/json", "{\"error\": \"Sensor read failed\"}");
    return;
  }

  String json = "{";
  json += "\"temperature\": " + String(state.temperature, 1) + ",";
  json += "\"humidity\": " + String(state.humidity, 1) + ",";
  json += "\"air\": " + String(state.air);
  json += "}";

  server.send(200, "application/json", json);
}

void handleConnect()
{
  ssid = server.arg("ssid");
  password = server.arg("password");

  server.send(200, "text/html", "Connecting to WiFi...");

  WiFi.begin(ssid.c_str(), password.c_str());
  delay(1000);
  // Optional: store to EEPROM or SPIFFS
}

void setupSpot()
{
  Serial.println("Starting AP...");

  // Start Access Point
  WiFi.softAP(ssid, password);
  delay(100);

  // Start DNS server and redirect all domains to ESP32 IP
  IPAddress apIP = WiFi.softAPIP(); // usually 192.168.4.1
  dnsServer.start(DNS_PORT, "*", apIP);

  // Handle any URL as "/"
  server.onNotFound(handleRoot);
  server.on("/", handleRoot);
  server.on("/connect", HTTP_POST, handleConnect);
  server.on("/data", handleData);

  server.begin();

  Serial.print("ESP32 IP: ");
  Serial.println(apIP);
  Serial.println("Captive portal started");
}

void runSpot()
{
  dnsServer.processNextRequest();
  server.handleClient();
}
