#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>

const char *ssid = "BOMBA_HOTSPOT";
const char *password = "12345678";

WebServer server(80);
DNSServer dnsServer;

const byte DNS_PORT = 53;

const char *htmlPage = R"rawliteral(
<!DOCTYPE html>
<html>
  <head>
    <title>ESP32 Captive Portal</title>
    <style>
      body { font-family: sans-serif; text-align: center; padding-top: 50px; }
    </style>
  </head>
  <body>
    <h1>Hi from ESP32!</h1>
    <p>This page auto-opened. You're connected directly.</p>
  </body>
</html>
)rawliteral";

void handleRoot()
{
    server.send(200, "text/html", htmlPage);
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
