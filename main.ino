#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pines del ESP32

#define DHTPIN 25 // DHT11 DATA
#define DHTTYPE DHT11
#define MQPIN 35 // MQ135 conectado

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(115200);
  dht.begin();
  Wire.begin(33, 32); // SDA, SCL
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Hello ESP32!");
  display.display();

  delay(1500);
}

void loop()
{
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  int mq_raw = analogRead(MQPIN);
  float mq_volt = mq_raw * (3.3 / 4095.0); // ADC de 12 bits

  // Calcular calidad del aire

  String calidad;

  if (mq_volt < 0.5)
  {
    calidad = "Buena";
  }
  else if (mq_volt < 1.0)
  {
    calidad = "Regular";
  }
  else
  {
    calidad = "Mala";
  }

  // Serial monitor

  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" C | ");

  Serial.print("Hum: ");
  Serial.print(hum);
  Serial.print(" % | ");

  Serial.print("MQ: ");
  Serial.print(mq_volt);
  Serial.print(" V | ");

  Serial.println("Aire: " + calidad);

  // Mostrar en OLED

  display.clearDisplay();
  display.setCursor(0, 0);

  if (!isnan(temp) && !isnan(hum))
  {
    display.print("Temp: ");
    display.print(temp, 1);
    display.println(" C");
    display.print("Humedad: ");
    display.print(hum, 0);
    display.println(" %");
  }
  else
  {
    display.println("Error DHT11");
  }

  display.print("Aire: ");
  display.println(calidad);
  display.display();

  delay(2000);
}