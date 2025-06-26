#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>
#include "State.h"

const char *ssid = "BOMBA_HOTSPOT";
const char *password = "12345678";

WebServer server(80);
DNSServer dnsServer;

const byte DNS_PORT = 53;

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head><title>Ni una fruta de mas</title></head>
<body>
<h2>Muestreo del aire:</h2>
<p>Temperature: <span id="temp">--</span> °C</p>
<p>Humidity: <span id="hum">--</span> %</p>
<p>Air Quality: <span id="air">--</span> ppm</p>

<script>
function updateData() {
  fetch('/data')
    .then(r => r.json())
    .then(data => {
      document.getElementById('temp').textContent = data.temperature;
      document.getElementById('hum').textContent = data.humidity;
      document.getElementById('air').textContent = data.air;
    });
}
setInterval(updateData, 2000);  // update every 2s
updateData(); // also call it once on load
</script>
<p></p>
<span>Equipo Bomba</span>
</body>
</html>
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
