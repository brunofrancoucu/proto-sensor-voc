#include "ap/spot.h"
#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>
#include <LittleFS.h>
// Internal
#include "state.h"
#include "ap/routes.h"

namespace {
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
  
  void initSetup(SpotConfig config)
  {
    LittleFS.begin(true); // unhandled exceptions
    WiFi.softAP(config.SSID, config.PWD);
    // Start DNS server and redirect all domains to AP
    dns.start(53, "*", WiFi.softAPIP()); // usually 192.168.4.1
    // Web server setup
    setupRoutes();
    server.begin();
  
    state.hotspot.SSID = config.SSID;
    state.hotspot._PWD = config.PWD;
    state.hotspot.isRunning = true;
    
    Serial.print("Captive Portal,DNS & AP-IP: " + String(WiFi.softAPIP()));
    Serial.print("SSID" + String(config.SSID) + "PWD: " + String(config.PWD));
  }
  
  void cycle()
  {
    dns.processNextRequest();
    server.handleClient();
  }
}

decltype(spot) spot = makeCycleComp(initSetup, cycle);