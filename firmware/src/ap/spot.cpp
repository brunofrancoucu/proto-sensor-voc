#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>
#include <LittleFS.h>
// Internal
#include "spot.h"
#include "state.h"
#include "routes.h"

WebServer server(80);
DNSServer dns;

void setupRoutes()
{
  // clang-format off
  server.onNotFound([]() { handleRoot(server); });
  server.on("/", []() { handleRoot(server); });
  server.on("/data", []() { handleData(server); });
  // clang-format on
}

void setupSpot(SpotConfig config)
{
  LittleFS.begin(true); // unhandled exceptions
  WiFi.softAP(config.SSID, config.PWD);
  // Start DNS server and redirect all domains to AP
  dns.start(53, "*", WiFi.softAPIP()); // usually 192.168.4.1
  // Web server setup
  setupRoutes();
  server.begin();

  Serial.print("Captive Portal,DNS & AP-IP: " + String(WiFi.softAPIP()));
  Serial.print("SSID" + String(config.SSID) + "PWD: " + String(config.PWD));
}

void runSpot()
{
  dns.processNextRequest();
  server.handleClient();
}
