#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);


#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


#define MQ135PIN A0

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Sistema Iniciado");
  delay(2000);
}

void loop() {
  
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  int mqRaw = analogRead(MQ135PIN);
  float voltage = mqRaw * (5.0 / 1023.0);
  float ppm = voltage * 100.0;

  
  float adjustedPPM = adjustMQ135(ppm, humidity, temperature);
  String quality = evaluateAirQuality(adjustedPPM);

  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperature, 1);
  lcd.print("C H:");
  lcd.print(humidity, 0);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print(quality);
  lcd.print(" ");
  lcd.print(round(adjustedPPM));
  lcd.print("PPM");

  delay(2000); 
}


float adjustMQ135(float rawPPM, float humidity, float temp) {
  float factor = 1.0; //ajustando este valor se pueden calibrar las lecturas
  if (humidity > 70) factor -= 0.2;
  else if (humidity < 30) factor += 0.2;

  if (temp > 30) factor += 0.1;
  else if (temp < 15) factor -= 0.1;

  return rawPPM * factor;
}


String evaluateAirQuality(float ppm) {
  if (ppm < 100) return "Buena";
  else if (ppm < 300) return "Media";
  else return "Mala";
}
